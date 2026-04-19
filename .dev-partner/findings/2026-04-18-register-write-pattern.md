---
title: Register write abstraction
date: 2026-04-18
tags: [ppu, register, abstraction]
type: pattern
project: DapperBanana/NEMU
---

The code consistently uses a specific pattern for handling PPU register writes. This involves checking the address, masking the input value, and then updating the corresponding PPU state. This consistent approach makes the code more readable and maintainable.  Consider encapsulating the masking and state update logic into reusable functions or methods to further reduce code duplication and improve clarity. This will be especially helpful as more PPU registers are implemented.
