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

CC      := gcc
CFLAGS  := -g -O2 -fstack-protector-strong -Wformat -Werror=format-security -Wall
LDFLAGS := -Wl,-Bsymbolic-functions -Wl,-z,relro

PREFIX  := /usr/local
BINDIR  := $(PREFIX)/bin

TARGET  := fanctl
SCRIPT  := fan
MANAGER := fanmgr

all: $(TARGET)

$(TARGET): fanctl.c i8k.h fanctl.h
	$(CC) $(CFLAGS) -o $(TARGET) fanctl.c $(LDFLAGS)

install: $(TARGET) $(SCRIPT) $(MANAGER)
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)
	install -m 755 $(SCRIPT) $(DESTDIR)$(BINDIR)/$(SCRIPT)
	install -m 755 $(MANAGER) $(DESTDIR)$(BINDIR)/$(MANAGER)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)
	rm -f $(DESTDIR)$(BINDIR)/$(SCRIPT)
	rm -f $(DESTDIR)$(BINDIR)/$(MANAGER)

clean:
	rm -f $(TARGET)

