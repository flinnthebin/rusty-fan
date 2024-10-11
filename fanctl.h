/*
 * fanctl.h -- Utility to query the i8k kernel module on Dell laptops to
 * retrieve information
 *
 * Copyright (C) 2024 Chris Flinn <christopher.flinn@gmail.com>
 * Copyright (C) 2013-2017 Vitor Augusto <vitorafsr@gmail.com>
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

int i8k_get_cpu_temp();
int i8k_get_fan_status(int);
int i8k_get_fan_status(int);
int i8k_get_fan_speed(int);
int i8k_get_fan_speed(int);
int i8k_set_fan(int, int);

#ifdef LIB
void init();
void finish();
#endif
