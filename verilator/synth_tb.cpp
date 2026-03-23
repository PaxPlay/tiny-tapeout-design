#include <stdint.h>
#include <stdio.h>
#include "Vsynth.h"
#include "verilated.h"
#include <SDL2/SDL.h>

// All 64 note indices chromatically (input 0-63 → MIDI 36-99).
static const int N_NOTES = 64;

// Simulate at 200 kHz; SDL audio at 50 kHz.
// We advance 4 clock cycles per audio sample (200kHz/4 = 50kHz).
#define CLK_HZ        200000
#define SAMPLE_RATE    50000
#define CLKS_PER_SAMPLE 4

static Vsynth *top;
static uint64_t clk_count = 0;
static int note_idx = 0;
static uint64_t note_change_at = 0;   // in samples
static uint64_t sample_count = 0;
static bool gate_on = true;
static uint64_t release_at = 0;

// Advance N clock cycles, return final audio_sample value
static uint16_t advance_clocks(int n) {
    for (int i = 0; i < n; i++) {
        top->clk = 0; top->eval();
        top->clk = 1; top->eval();
        clk_count++;
    }
    return (uint16_t) top->audio_sample;
}

static void sdl_audio_callback(void* /*userdata*/, uint8_t* stream, int len) {
    uint16_t *out = (uint16_t*) stream;
    int nsamples = len / 2;

    for (int i = 0; i < nsamples; i++) {
        // Note scheduling: each note plays for 0.4 s, releases 0.1 s before end
        uint64_t note_period_samples = SAMPLE_RATE * 4 / 10;  // 0.4 s
        uint64_t release_offset      = SAMPLE_RATE * 3 / 10;  // release at 0.3 s

        if (sample_count >= note_change_at) {
            note_idx = (note_idx + 1) % N_NOTES;
            top->midi_note = note_idx;
            top->gate = 1;
            gate_on = true;
            note_change_at = sample_count + note_period_samples;
            release_at     = sample_count + release_offset;
            fprintf(stderr, "\rnote=%3d (MIDI %3d)  sample=%lu\e[K", note_idx, note_idx + 36, sample_count);
            fflush(stderr);
        }
        if (gate_on && sample_count >= release_at) {
            top->gate = 0;
            gate_on = false;
        }

        out[i] = advance_clocks(CLKS_PER_SAMPLE);
        sample_count++;
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    top = new Vsynth;

    // Reset
    top->rst_n = 0;
    top->gate  = 0;
    top->midi_note = 60;
    top->clk = 0; top->eval();
    top->clk = 1; top->eval();
    top->rst_n = 1;

    // Kick off first note immediately
    note_change_at = 0;

    SDL_SetHint(SDL_HINT_NO_SIGNAL_HANDLERS, "1");
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec desired, obtained;
    SDL_zero(desired);
    desired.freq     = SAMPLE_RATE;
    desired.format   = AUDIO_U16SYS;
    desired.channels = 1;
    desired.samples  = 4096;
    desired.callback = sdl_audio_callback;

    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(NULL, 0, &desired, &obtained, 0);
    if (!dev) {
        fprintf(stderr, "SDL_OpenAudioDevice failed: %s\n", SDL_GetError());
        return 1;
    }

    fprintf(stderr, "Playing C major scale demo. Ctrl-C to stop.\n");
    SDL_PauseAudioDevice(dev, 0);

    for (;;) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) goto done;
        }
        SDL_Delay(100);
    }
done:
    SDL_CloseAudioDevice(dev);
    SDL_Quit();
    delete top;
    return 0;
}
