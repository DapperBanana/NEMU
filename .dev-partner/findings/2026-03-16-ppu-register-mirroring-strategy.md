---
title: PPU register mirroring implementation via address modulo
date: 2026-03-16
tags: [architecture, memory-mapping, nes-hardware]
type: pattern
project: DapperBanana/NEMU
---

The PPU registers (8 bytes) are mirrored every 8 bytes across the $2000–$3FFF range in NES memory. The implementation uses a modulo approach on the address to resolve to the base 8-byte register set. This is simpler than range-checking but assumes contiguous mirroring without gaps—watch for edge cases if PPU address decoding needs to handle reads from unmapped regions within the mirror range (some cartridges exploit this). The Bus wiring looks clean here: PPU gets all accesses in that range, then internally folds them. Good separation of concerns.
