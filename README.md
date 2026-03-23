![](../../workflows/gds/badge.svg) ![](../../workflows/docs/badge.svg) ![](../../workflows/test/badge.svg) ![](../../workflows/fpga/badge.svg)

# Tiny Tapeout Mini Synthesizer

A monophonic digital synthesizer for the [Tiny Tapeout](https://tinytapeout.com) IHP platform. Features three oscillators (triangle, LFO-detuned triangle, and 4× square) mixed together with a full ADSR envelope.

## Inputs

| Pin | Function |
|-----|----------|
| `ui[6:0]` | MIDI note number (0–127, C-1 to G9) |
| `ui[7]` | Gate (1 = note on) |

## Output

| Pin | Function |
|-----|----------|
| `uo[7]` | 1-bit sigma-delta audio (connect to Audio Pmod) |

## How it works

- **Oscillators**: triangle wave + LFO-detuned triangle (slow chorus) + square wave at 4× frequency
- **Pitch**: full 128 MIDI notes (0–127, C-1 to G9). 12 base increments stored anchored at C2; octave derived by left- or right-shifting.
- **ADSR envelope**: pulse-density amplitude control — a 7-bit counter (period 125) at 50 MHz gates the audio signal. f_chop = 400 kHz, aliasing-free at 50 kHz sample rate.
- **Sigma-delta**: 12-bit first-order modulator drives the 1-bit output at 50 MHz.

| Parameter | Value |
|-----------|-------|
| Clock | 50 MHz |
| Sample rate | 50 kHz |
| Note range | MIDI 0–127 (C-1–G9) |
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

Renders a 64-note chromatic sweep (MIDI 36–99, C2–Eb7) to `audio.raw`.

## External hardware

Tiny Tapeout Audio Pmod connected to the `uo` output header.

