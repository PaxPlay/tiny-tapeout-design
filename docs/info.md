<!---

This file is used to generate your project datasheet. Please fill in the information below and delete any unused
sections.

You can also include images in this folder and reference them in the markdown. Each image must be less than
512 kb in size, and the combined size of all images must be less than 1 MB.
-->

## How it works

A monophonic synthesizer with three oscillators and an ADSR envelope.

### Signal chain

1. **Phase accumulator** — 16-bit register incremented every sample tick (50 kHz) by a note-dependent value. Wraps freely.
2. **Triangle wave** — the phase is folded at the midpoint (`phase[15] ? ~phase : phase`) and shifted to 11 bits.
3. **Square wave** — derived from `phase[13]`, giving a square at 4× the fundamental frequency.
4. **LFO-detuned triangle** — a second 16-bit phase accumulator runs at almost the same rate, offset by a ~4 Hz triangle LFO, producing a slow chorus/detune effect.
5. **Mix** — the three oscillators are summed into a 12-bit audio sample.
6. **ADSR envelope** — pulse-density amplitude control: a 7-bit counter (period 125) runs at the full 50 MHz clock. When the counter value is below the current volume level the raw audio is passed; otherwise the output is held at the midpoint (12'h800, silence). This gives a chopping frequency of 50 MHz / 125 = **400 kHz**, well above the audio pmod RC filter cutoff, with no aliasing into the audio band.
7. **Sigma-delta modulator** — a 12-bit first-order sigma-delta accumulator converts the envelope-controlled sample to a 1-bit PWM stream on `uo[7]` at the full 50 MHz clock rate.

### Note selection

The 6 input bits (`ui[5:0]`) select one of 64 chromatic notes spanning MIDI 36–99 (C2 to Eb7, roughly 65 Hz–2.5 kHz).

Pitch lookup is compressed using the octave-doubling property of equal temperament: only 12 base increments (one octave) are stored. The octave is determined by a comparison chain, and the base increment is left-shifted by the octave number — equivalent to multiplying the frequency by 2 for each higher octave.

### ADSR envelope

`ui[6]` is the gate input. A rising edge triggers the attack phase; releasing the gate (falling edge) triggers release.

| Phase | Rate | Duration |
|---|---|---|
| Attack | vol++ every 8 samples | ~20 ms (0 → full) |
| Decay | vol-- every 32 samples | ~30 ms (full → sustain) |
| Sustain | held at ~62% volume | until gate released |
| Release | vol-- every 64 samples | ~100 ms (sustain → 0) |

### Parameters

| Parameter | Value |
|---|---|
| Clock | 50 MHz |
| Sample rate | 50 kHz (÷1000) |
| Phase accumulator | 16-bit |
| Audio sample | 12-bit unsigned |
| Chop counter period | 125 (f_chop = 400 kHz) |
| Note range | MIDI 36–99 (C2–Eb7) |
| Note resolution | 1 semitone (64 notes, 6 bits) |

## How to test

Connect the Tiny Tapeout Audio Pmod to the output pin header. Drive `ui[5:0]` with a 6-bit note index (0 = MIDI 36 / C2, 63 = MIDI 99 / Eb7) and set `ui[6]` high to open the gate. The ADSR envelope will attack, decay, and sustain while the gate is held; releasing the gate triggers the release phase.

A Verilator simulation is included under `verilator/`. Build and run it with:

```sh
cd verilator
make
./synth
# Output written to audio.raw — play back with:
ffplay -f u16le -ar 50000 audio.raw
# Or convert using ffmpeg:
ffmpeg -f u16le -ar 50000 -i audio.raw audio.wav
```

This renders a chromatic sweep of 16 notes (MIDI 48–63, C3–Eb4), 0.3 s gate-on + 0.2 s release per note, to `audio.raw` as 16-bit unsigned PCM at 50 kHz mono.

## External hardware

Tiny Tapeout Audio Pmod connected to the `uo` output header.
