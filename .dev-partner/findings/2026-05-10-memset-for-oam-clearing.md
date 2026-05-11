---
title: memset is a good way to clear large memory regions
date: 2026-05-10
tags: [PPU, OAM, memset, performance]
type: performance
project: DapperBanana/NEMU
---

Using `memset` to clear the Object Attribute Memory (OAM) in the PPU constructor is a good choice for performance. Directly looping and zeroing the OAM can be significantly slower, especially in emulators where the write operations might be more costly due to overhead. `memset` leverages optimized, platform-specific implementations, resulting in much better performance, especially when dealing with larger memory regions.
