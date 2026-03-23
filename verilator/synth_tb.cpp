#include <stdint.h>
#include <stdio.h>
#include "Vsynth.h"
#include "verilated.h"
#include <SDL2/SDL.h>

// All 64 note indices chromatically (input 0-63 → MIDI 36-99).
static const int N_NOTES = 64;

// Simulate at 200 kHz; SDL audio at 50 kHz.
// We advance 4 clock cycles per audio sample (200kHz/4 = 50kHz).
#define SAMPLE_RATE     50000
#define CLKS_PER_SAMPLE 4

static Vsynth *top;
static int note_idx = 0;
static uint64_t note_change_at = 0;
static uint64_t sample_count = 0;

static void advance_clocks(int n) {
    for (int i = 0; i < n; i++) {
        top->clk = 0; top->eval();
        top->clk = 1; top->eval();
    }
}

static void sdl_audio_callback(void* /*userdata*/, uint8_t* stream, int len) {
    uint16_t *out = (uint16_t*) stream;
    int nsamples = len / 2;

    for (int i = 0; i < nsamples; i++) {
        uint64_t note_samples  = SAMPLE_RATE * 3 / 10;  // 0.3 s tone
        uint64_t pause_samples = SAMPLE_RATE * 1 / 10;  // 0.1 s silence
        uint64_t period        = note_samples + pause_samples;

        if (sample_count >= note_change_at) {
            note_idx = (note_idx + 1) % N_NOTES;
            note_change_at = sample_count + period;
            fprintf(stderr, "\rnote=%3d (MIDI %3d)  sample=%lu\e[K",
                    note_idx, note_idx + 36, sample_count);
            fflush(stderr);
        }

        bool in_pause = (sample_count >= note_change_at - pause_samples) &&
                        (sample_count <  note_change_at);
        top->midi_note = (uint8_t) note_idx;
        advance_clocks(CLKS_PER_SAMPLE);
        // Output DC midpoint during pause; oscillator keeps running underneath
        out[i] = in_pause ? 0x8000u : (uint16_t)(top->audio_sample << 4);
        sample_count++;
    }
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    top = new Vsynth;

    // Reset
    top->rst_n = 0;
    top->midi_note = 0;
    top->clk = 0; top->eval();
    top->clk = 1; top->eval();
    top->rst_n = 1;

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

    fprintf(stderr, "Chromatic sweep MIDI 36-99. Ctrl-C to stop.\n");
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
