# Package adopted

https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=948521
https://www.debian.org/devel/wnpp/rfa

## i8k

Linux driver for accessing the SMM BIOS on Dell laptops
Note: fanctl is entirely built upon the dell-smm-hwmon kernel module.

## Fan

Fan is a program that works on my Alienware m15 R5 with AMD Ryzen 9 5900HX.
If you have any Alienware Laptop (or Dell Laptop), install Ubuntu and the bootloader
displays the Alienware/Dell logo in tandem with the Ubuntu logo, then will probably work.

For my particular laptop, there are effectively 4 configurations for fan control.

    # Off: Both fans off
    # Low: Left Speed: 2400, Right Speed: 0
    # High: Left Speed: 5500 Right Speed: 5500
    # Intense: Left Speed: 6400 Right Speed: 5800

If you are going to use Linux, I cannot recommend Manjaro/i3. It is a very well-maintained distro,
with i3 out of the box so you don't have to remove GNOME/x11.

## Whipfan

Uses whiptail, if you like that kind of thing

## Building fan

To compile use ```make```

# Those on whose shoulders I stand

    Pablo Bianucci <pbian@physics.utexas.edu>

    David Bustos <bustos@caltech.edu>

    Jonathan Buzzard <jonathan@buzzard.org.uk>

    Karl E. Jørgensen <karl@jorgensen.com>

    Stephane Jourdois <stephane@tuxfinder.org>

    Marcel J.E. Mol <marcel@mesa.nl>

    Gianni Tedesco <gianni@ecsc.co.uk>

	patch to restrict fan contol to SYS_ADMIN capability

    David Woodhouse <dwmw2@redhat.com>

    Vitor Augusto <vitorafsr@gmail.com>

    Massimo Dal Zotto <dz@debian.org>
