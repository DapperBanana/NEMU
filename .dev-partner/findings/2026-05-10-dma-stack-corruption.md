---
title: DMA writes can easily corrupt the CPU stack
date: 2026-05-10
tags: [PPU, DMA, stack, memory]
type: gotcha
project: DapperBanana/NEMU
---

The DMA implementation needs to be extremely careful about memory boundaries. A naive implementation can easily overwrite the CPU stack if the DMA source address isn't validated against the current stack pointer. This can lead to very difficult-to-debug crashes and memory corruption issues. It's important to validate memory boundaries before performing large memory transfers.
