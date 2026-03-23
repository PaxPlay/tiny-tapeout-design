![](../../workflows/gds/badge.svg) ![](../../workflows/docs/badge.svg) ![](../../workflows/test/badge.svg) ![](../../workflows/fpga/badge.svg)

# Tiny Tapeout Mini Synthesizer

A monophonic digital synthesizer for the [Tiny Tapeout](https://tinytapeout.com) IHP platform. Features three oscillators (triangle, LFO-detuned triangle, and 4× square) mixed together with a full ADSR envelope.

## Inputs

| Pin | Function |
|-----|----------|
| `ui[5:0]` | Note index (0–63 → MIDI 36–99, C2–Eb7) |
| `ui[6]` | Gate (1 = note on) |

## Output

| Pin | Function |
|-----|----------|
| `uo[7]` | 1-bit sigma-delta audio (connect to Audio Pmod) |

## How it works

- **Oscillators**: triangle wave + LFO-detuned triangle (slow chorus) + square wave at 4× frequency
- **Pitch**: 64 chromatic notes (MIDI 36–99). 12 base increments stored; octave derived by left-shifting.
- **ADSR envelope**: pulse-density amplitude control — a 7-bit counter (period 125) at 50 MHz gates the audio signal. f_chop = 400 kHz, aliasing-free at 50 kHz sample rate.
- **Sigma-delta**: 12-bit first-order modulator drives the 1-bit output at 50 MHz.

| Parameter | Value |
|-----------|-------|
| Clock | 50 MHz |
| Sample rate | 50 kHz |
| Note range | MIDI 36–99 (C2–Eb7) |
| Attack | ~20 ms |
| Decay | ~30 ms |
| Release | ~100 ms |

## Simulation

A Verilator testbench is included under `verilator/`:

```sh
cd verilator
make
./synth
ffmpeg -f u16le -ar 50000 -i audio.raw audio.wav
```

Renders a 16-note chromatic sweep (MIDI 48–63, C3–Eb4) to `audio.raw`.

## External hardware

Tiny Tapeout Audio Pmod connected to the `uo` output header.

