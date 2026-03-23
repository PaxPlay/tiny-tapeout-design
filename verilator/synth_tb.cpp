#include "Vsynth.h"
#include "verilated.h"
#include <stdint.h>
#include <stdio.h>

// All 64 note indices chromatically (input 0-63 → MIDI 36-99).
static const int N_NOTES = 16;

// Clock: 50 MHz. Sample rate: 50 kHz. Clocks per audio sample: 1000.
#define SAMPLE_RATE 50000
#define CLKS_PER_SAMPLE 1000

// Output: 16-bit unsigned PCM, mono, 50 kHz.
// Play back with e.g.:
//   ffplay -f u16le -ar 50000 -ac 1 audio.raw
//   aplay  -f U16_LE -r 50000 -c 1 audio.raw
#define OUTPUT_FILE "audio.raw"

int main(int argc, char **argv) {
  Verilated::commandArgs(argc, argv);
  Vsynth *top = new Vsynth;

  FILE *fp = fopen(OUTPUT_FILE, "wb");
  if (!fp) {
    perror("fopen");
    return 1;
  }

  // Reset
  top->rst_n = 0;
  top->gate = 0;
  top->midi_note = 0;
  top->clk = 0;
  top->eval();
  top->clk = 1;
  top->eval();
  top->rst_n = 1;

  // One full chromatic sweep: 64 notes × 0.5 s = 32 s of audio
  const uint64_t gate_samples = SAMPLE_RATE * 3 / 10;   // 0.3 s gate on
  const uint64_t period_samples = SAMPLE_RATE * 5 / 10; // 0.5 s per note
  const uint64_t total_samples = (uint64_t)N_NOTES * period_samples;

  int note_idx = -1;
  uint64_t release_at = 0;
  uint64_t next_note = 0;
  bool gate_on = false;

  for (uint64_t s = 0; s < total_samples; s++) {
    // Note scheduling
    if (s >= next_note) {
      note_idx = (note_idx + 1) % N_NOTES;
      next_note = s + period_samples;
      release_at = s + gate_samples;
      top->midi_note = (uint8_t)note_idx + 12;
      top->gate = 1;
      gate_on = true;
      fprintf(stderr, "\rnote %3d / %3d  (MIDI %3d)\e[K", note_idx + 1, N_NOTES,
              note_idx + 36);
      fflush(stderr);
    }
    if (gate_on && s >= release_at) {
      top->gate = 0;
      gate_on = false;
    }

    // Advance one sample period, averaging audio_sample to simulate the
    // RC filter that the audio pmod applies to the sigma-delta output.
    uint32_t acc = 0;
    for (int c = 0; c < CLKS_PER_SAMPLE; c++) {
      top->clk = 0;
      top->eval();
      top->clk = 1;
      top->eval();
      acc += top->audio_sample;
    }
    uint16_t sample = (uint16_t)((acc / CLKS_PER_SAMPLE) << 4);
    fwrite(&sample, sizeof(uint16_t), 1, fp);
  }

  fprintf(stderr, "\nWrote %s  (%llu samples, %.1f s)\n", OUTPUT_FILE,
          (unsigned long long)total_samples,
          (double)total_samples / SAMPLE_RATE);

  fclose(fp);
  delete top;
  return 0;
}
