---
title: OAM address post-increment on data writes
date: 2026-05-02
tags: [ppu, oam, nes]
type: gotcha
project: DapperBanana/NEMU
---

The PPU's OAM (Object Attribute Memory) address register doesn't automatically increment on every write to the OAM data register. Instead, it only increments when writing to the OAM data register *through* the OAM data port ($2004).  If you directly modify the OAM through DMA, you're responsible for managing the address. This is a nuance easily missed but crucial for correct sprite rendering, particularly when using DMA transfers to update sprite attributes.
