# SPDX-FileCopyrightText: © 2024 Tiny Tapeout
# SPDX-License-Identifier: Apache-2.0

import cocotb
from cocotb.clock import Clock
from cocotb.triggers import ClockCycles


@cocotb.test()
async def test_project(dut):
    dut._log.info("Start")

    # 200 kHz clock → 5 us period
    clock = Clock(dut.clk, 5, unit="us")
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

    # Drive note index 33 (A4, 440 Hz) and run long enough for the
    # sigma-delta to produce at least one rising edge on uo[7]
    dut.ui_in.value = 33
    await ClockCycles(dut.clk, 500)

    # Collect uo[7] samples over the next 1000 cycles
    transitions = 0
    prev = int(dut.uo_out.value) >> 7
    for _ in range(1000):
        await ClockCycles(dut.clk, 1)
        cur = (int(dut.uo_out.value) >> 7) & 1
        if cur != prev:
            transitions += 1
        prev = cur

    dut._log.info(f"PWM transitions in 1000 cycles: {transitions}")
    assert transitions > 0, "Expected sigma-delta PWM activity on uo[7]"

    # Switch note and confirm PWM keeps toggling
    dut.ui_in.value = 0
    await ClockCycles(dut.clk, 100)
    dut.ui_in.value = 24  # C4
    await ClockCycles(dut.clk, 500)

    transitions2 = 0
    prev = (int(dut.uo_out.value) >> 7) & 1
    for _ in range(1000):
        await ClockCycles(dut.clk, 1)
        cur = (int(dut.uo_out.value) >> 7) & 1
        if cur != prev:
            transitions2 += 1
        prev = cur

    dut._log.info(f"PWM transitions after note change: {transitions2}")
    assert transitions2 > 0, "Expected PWM activity after note change"
