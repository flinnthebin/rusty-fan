# Package adopted

https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=948521
https://www.debian.org/devel/wnpp/rfa

## i8k

Linux driver for accessing the SMM BIOS on Dell laptops
Note: fanctl is entirely built upon the dell-smm-hwmon kernel module.

## Fan

Fan is a program that works on my Alienware m15 R5 with AMD Ryzen 9 5900HX.
If you have any Alienware Laptop (or Dell Laptop), install Ubuntu and if the bootloader
displays the Alienware/Dell logo in tandem with the Ubuntu logo during the boot process
then you likely have some compatible hardware.

For my particular laptop, there are effectively 4 configurations for fan control.

    # Off: Both fans off
    # Low: Left Speed: 2400, Right Speed: 0
    # High: Left Speed: 5500 Right Speed: 5500
    # Intense: Left Speed: 6400 Right Speed: 5800

If you are going to use Linux, I cannot recommend Manjaro/i3. It is a very well-maintained distro,
with i3 out of the box so you don't have to remove GNOME/x11.

## Safety

The Alienware Laptops come with Alienware Command Center on Windows distributions. They provide the same functionality,
but with some sensor-driven safety features that will increase the fanspeed to prevent overheating.

This functionality is difficult to replicate on Linux and is not yet implemented.

Anecdotally, my CPU temperature range at the various configurations are:

Off:     70-75°C
Low:     65-70°C
High:    55-65°C
Intense: 45-55°C

If you are going to use fan to manually control your fanspeed, ensure you are routinely running fanctl and appropriately
configuring your fanspeed to your usage. I made this because I love Linux, I love having Linux on nice hardware (I
rarely go into double digit CPU usage) and I hope more people are encouraged to try to install Linux on nice hardware

You don't need to wait for the Linux hardware to come to you! I started out with a 2012 Macbook Pro (in 2014) and
headless Ubuntu and now we are here!

## Installing fan

``` bash
sudo make install
```

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
