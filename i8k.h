/*
 * i8k.h -- Linux driver for accessing the SMM BIOS on Dell laptops
 *
 * Copyright (C) 2001  Massimo Dal Zotto <dz@debian.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#ifndef _LINUX_I8K_H
#define _LINUX_I8K_H

#define I8K_PROC            "/proc/i8k"
#define I8K_PROC_FMT        "1.0"

#define I8K_GET_TEMP        _IOR ('i', 0x84, size_t)
#define I8K_GET_SPEED       _IOWR('i', 0x85, size_t)
#define I8K_GET_FAN         _IOWR('i', 0x86, size_t)
#define I8K_SET_FAN         _IOWR('i', 0x87, size_t)

#define I8K_FAN_LEFT        1
#define I8K_FAN_RIGHT       0
#define I8K_FAN_OFF         0
#define I8K_FAN_LOW         1
#define I8K_FAN_HIGH        2
#define I8K_FAN_MAX         I8K_FAN_HIGH

#endif
