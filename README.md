# Package adopted

https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=948521  
https://www.debian.org/devel/wnpp/rfa

## i8k

Linux driver for accessing the SMM BIOS on Dell laptops  
Note: fanctl is entirely built upon the dell-smm-hwmon kernel module.

## fan

Fan is a program that works on my Alienware m15 R5 with AMD Ryzen 9 5900HX.
If you have any Alienware Laptop (or Dell Laptop), install Ubuntu and if the bootloader
displays the Alienware/Dell logo in tandem with the Ubuntu logo during the boot process
then you likely have some compatible hardware.

For my particular laptop, there are effectively 4 configurations for fan control.

    Off: Both fans off
    Low: Left Speed: 2400 Right Speed: 0
    Medium: Left Speed: 0 Right Speed: 5100
    High: Left Speed: 5500 Right Speed: 5500
    Intense: Left Speed: 6400 Right Speed: 5800

## Safety

The Alienware Laptops come with Alienware Command Center on Windows distributions. They provide the same functionality,
but with some sensor-driven safety features that will increase the fanspeed to prevent overheating.

I believe the configuration of fanmgr is reasonably close to the ACC setup, but please run fanctl yourself regularly
and check that its right on your hardware, and edit the fanmgr script to your personal preferences
## fanmgr

The config for this is reasonably smooth now, if you have any suggestions for improvement please feel free to send me an
email!

## fanctl

Fanctl is the all-purpose tool, the help menu is comprehensive

```bash
fanctl -h
```

## Installing fan

These modules should load if you pass the Ubuntu Bootloader test.

``` bash
sudo make install
echo "i8k" | sudo tee /etc/modules-load.d/i8k.conf
echo "options i8k force=1" | sudo tee /etc/modprobe.d/i8k.conf
```

# Smarter people than me

    Pablo Bianucci <pbian@physics.utexas.edu>

    David Bustos <bustos@caltech.edu>

    Jonathan Buzzard <jonathan@buzzard.org.uk>

    Karl E. Jørgensen <karl@jorgensen.com>

    Stephane Jourdois <stephane@tuxfinder.org>

    Marcel J.E. Mol <marcel@mesa.nl>

    Gianni Tedesco <gianni@ecsc.co.uk>

    David Woodhouse <dwmw2@redhat.com>

    Vitor Augusto <vitorafsr@gmail.com>

    Massimo Dal Zotto <dz@debian.org>
