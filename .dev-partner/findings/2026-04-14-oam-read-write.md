---
title: Dedicated OAM ports simplify PPU interaction
date: 2026-04-14
tags: [ppu, memory, nes]
type: pattern
project: DapperBanana/NEMU
---

The decision to implement separate address and data ports for OAM (Object Attribute Memory) read/write operations in the PPU streamlines the interface between the CPU and PPU. Instead of multiplexing access through a single port, dedicated ports for address setting and data transfer enhance code clarity and maintainability. This design choice mirrors the hardware architecture of the NES, leading to more accurate emulation.

By explicitly separating address and data concerns, the PPU's read/write logic becomes easier to reason about. This also allows for the OAM address increment to be implemented as a side effect of writing to the data port, closely mimicking the behavior of the original NES PPU.
