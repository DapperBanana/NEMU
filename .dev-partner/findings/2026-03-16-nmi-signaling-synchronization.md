---
title: NMI edge-triggered on vblank without explicit handshake
date: 2026-03-16
tags: [interrupt-handling, timing, cpu-ppu-sync]
type: gotcha
project: DapperBanana/NEMU
---

The PPU triggers NMI on the CPU when vblank is set, but there's no explicit acknowledgment or de-assertion logic visible yet. Real NES hardware has vblank flag that the CPU must read to acknowledge the interrupt. If the PPU just fires NMI every clock while vblank is active, the CPU will be interrupted repeatedly. Likely need to add flag logic: PPU sets vblank + NMI, CPU reads status register, vblank flag clears automatically on CPU read. Check if that's already in the status register read handler or if it needs wiring.
