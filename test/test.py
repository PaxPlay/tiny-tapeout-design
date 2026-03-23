# SPDX-FileCopyrightText: © 2024 Tiny Tapeout
# SPDX-License-Identifier: Apache-2.0

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ClockCycles


def make_ui(note, gate):
    """Pack note index (0-63) and gate bit into ui_in."""
    return (int(gate) << 6) | (int(note) & 0x3F)


@cocotb.test()
async def test_project(dut):
    dut._log.info("Start")

    # 50 MHz clock → 20 ns period
    clock = Clock(dut.clk, 20, unit="ns")
    cocotb.start_soon(clock.start())

    # Reset
    dut.ena.value = 1
    dut.ui_in.value = 0
    dut.uio_in.value = 0
    dut.rst_n.value = 0
    await ClockCycles(dut.clk, 10)
    dut.rst_n.value = 1

    # Unused bidir pins must stay at 0
    assert dut.uio_out.value == 0
    assert dut.uio_oe.value == 0

    # Gate off: sigma-delta still toggles (outputting midpoint)
    dut.ui_in.value = make_ui(33, False)
    await ClockCycles(dut.clk, 500)
    transitions_off = 0
    prev = (int(dut.uo_out.value) >> 7) & 1
    for _ in range(500):
        await ClockCycles(dut.clk, 1)
        cur = (int(dut.uo_out.value) >> 7) & 1
        if cur != prev:
            transitions_off += 1
        prev = cur
    dut._log.info(f"PWM transitions (gate off): {transitions_off}")
    assert transitions_off > 0

    # Gate on: ADSR attack begins; after 4 sample_ticks (4000 clocks) vol > 0
    # and the PWM pattern should change vs the silent midpoint
    dut.ui_in.value = make_ui(33, True)   # A4, gate on
    await ClockCycles(dut.clk, 5000)      # covers at least one attack_tick

    transitions_on = 0
    prev = (int(dut.uo_out.value) >> 7) & 1
    for _ in range(500):
        await ClockCycles(dut.clk, 1)
        cur = (int(dut.uo_out.value) >> 7) & 1
        if cur != prev:
            transitions_on += 1
        prev = cur
    dut._log.info(f"PWM transitions (gate on, mid-attack): {transitions_on}")
    assert transitions_on > 0

    # Switch note while gate is held — should retrigger attack
    dut.ui_in.value = make_ui(24, True)   # C4
    await ClockCycles(dut.clk, 1000)

    # Release: gate off, ADSR enters release phase
    dut.ui_in.value = make_ui(24, False)
    await ClockCycles(dut.clk, 1000)

    transitions_rel = 0
    prev = (int(dut.uo_out.value) >> 7) & 1
    for _ in range(500):
        await ClockCycles(dut.clk, 1)
        cur = (int(dut.uo_out.value) >> 7) & 1
        if cur != prev:
            transitions_rel += 1
        prev = cur
    dut._log.info(f"PWM transitions (early release): {transitions_rel}")
    assert transitions_rel > 0
