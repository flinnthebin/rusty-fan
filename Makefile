# Makefile for fanctl
#
# Copyright 2024 Chris Flinn <christopher.flinn@gmail.com 
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 3, or (at your option) any
# later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

CFLAGS:=-g -O2 -fstack-protector-strong -Wformat -Werror=format-security -Wall
LDFLAGS:=-Wl,-Bsymbolic-functions -Wl,-z,relro

all: fanctl

fanctl: fanctl.c i8k.h fanctl.h

fanctl_DLIB.o: fanctl.c i8k.h fanctl.h
	$(CC) $(CFLAGS) -Wall -c -g -DLIB fanctl.c -o fanctl_DLIB.o

clean:
	rm -f fanctl *.o
