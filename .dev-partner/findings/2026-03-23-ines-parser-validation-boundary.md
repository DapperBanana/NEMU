---
title: iNES header validation catches common ROM corruption issues early
date: 2026-03-23
tags: [pattern, gotcha]
type: pattern
project: DapperBanana/NEMU
---

The Cartridge iNES loader validates the magic bytes (0x4E 0x45 0x53 0x1A) and enforces strict bounds on PRG/CHR sizes before mapping. This catches truncated ROMs and corrupted headers before they propagate into the address space.

Key insight: by rejecting invalid cartridges at load time rather than during runtime access, you avoid cascading bugs where invalid memory reads corrupt emulator state. The mapper selection (currently just mapper 000) gates against unknown mappers too—worth keeping that strict as new mappers get added.

One consideration: if you're planning to support bankable mappers later (1, 2, 3, etc.), the current read/write interface on Cartridge will need to become stateful. Mapper 000 is fixed-bank, so it's straightforward now, but the abstraction should prepare for switchable PRG/CHR banks.
