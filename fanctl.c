/*
 * fanctl.c -- Utility to query the i8k kernel module on Dell laptops to
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

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "i8k.h"
#include "fanctl.h"

static int i8k_fd;

int i8k_set_fan(int fan, int speed) {
    int args[2];
    int rc;

    args[0] = fan;
    args[1] = speed;
    if ((rc = ioctl(i8k_fd, I8K_SET_FAN, &args)) < 0) {
	return rc;
    }

    return args[0];
}

int i8k_get_fan_status(int fan) {
    int args[1];
    int rc;

    args[0] = fan;
    if ((rc = ioctl(i8k_fd, I8K_GET_FAN, &args)) < 0) {
	return rc;
    }

    return args[0];
}

int i8k_get_fan_speed(int fan) {
    int args[1];
    int rc;

    args[0] = fan;
    if ((rc = ioctl(i8k_fd, I8K_GET_SPEED, &args)) < 0) {
	return rc;
    }

    return args[0];
}

int i8k_get_cpu_temp() {
    int args[1];
    int rc;

    if ((rc = ioctl(i8k_fd, I8K_GET_TEMP, &args)) < 0) {
	return rc;
    }

    return args[0];
}

int fan(int argc, char **argv) {
    int left, right;

    if ((argc > 1) && isdigit(argv[1][0])) {
	left = i8k_set_fan(I8K_FAN_LEFT, atoi(argv[1]));
    } else {
	left = i8k_get_fan_status(I8K_FAN_LEFT);
    }

    if ((argc > 2) && isdigit(argv[2][0])) {
	right = i8k_set_fan(I8K_FAN_RIGHT, atoi(argv[2]));
    } else {
	right = i8k_get_fan_status(I8K_FAN_RIGHT);
    }

    printf("Left Fan Mode  (0-2): %d\n"
           "Right Fan Mode (0-2): %d\n", left, right);
    return 0;
}

int fan_speed(int argc, char **argv) {
    int left, right;

    left = i8k_get_fan_speed(I8K_FAN_LEFT);
    right = i8k_get_fan_speed(I8K_FAN_RIGHT);

    printf("Left Fan Speed  (rpm): %d\n"
           "Right Fan Speed (rpm): %d\n", left, right);
    return 0;
}

int cpu_temperature() {
    printf("CPU Temperature  (°C): %d\n", i8k_get_cpu_temp());
    return 0;
}

int status() {
    int cpu_temp;
    int left_fan, right_fan, left_speed, right_speed;

    cpu_temp        = i8k_get_cpu_temp();
    left_fan        = i8k_get_fan_status(I8K_FAN_LEFT);
    right_fan       = i8k_get_fan_status(I8K_FAN_RIGHT);
    left_speed      = i8k_get_fan_speed(I8K_FAN_LEFT);
    right_speed     = i8k_get_fan_speed(I8K_FAN_RIGHT);

    /*
     * User Info
     */
    printf("CPU Temperature  (°C): %d\n"
           "Left Fan Mode   (0-2): %d\n"
           "Left Fan Speed  (rpm): %d\n"
           "Right Fan Mode  (0-2): %d\n"
           "Right Fan Speed (rpm): %d\n",
           cpu_temp,
           left_fan,
           left_speed,
           right_fan,
           right_speed);

    return 0;
}

void usage() {
    printf("Usage: fanctl [command] [arguments]\n");
    printf("\n");
    printf("Commands:\n");
    printf("  fan l r\n");
    printf("    Sets the speed of the left and right fans.\n");
    printf("    - l: Speed setting for the left fan (0 - 2)\n");
    printf("    - r: Speed setting for the right fan (0 - 2)\n\n");
    printf("    Typical configurations:\n");
    printf("      0 0 - Off: Both fans are off (any state)\n");
    printf("      1 -1 - Low: Left fan speed 2400 rpm, Right fan off (previous state must be 'Off')\n");
    printf("      0 1 - Med: Left fan speed 0 rpm, Right fan 5100 rpm (any state)\n");
    printf("      1 1 - High: Left fan spee 5500 rpm, Right fan speed 5500 rpm (any state)\n");
    printf("      2 2 - Intense: Left fan speed 6400 RPM, Right fan speed 5800 rpm (any state)\n");
    printf("\n");
    printf("  speed\n");
    printf("    Displays the current speed of the left and right fans in rpm.\n");
    printf("\n");
    printf("  temp\n");
    printf("    Displays the current CPU temperature in degrees Celsius.\n");
    printf("\n");
    printf("  -h\n");
    printf("    Displays this help message.\n");
    printf("\n");
    printf("Examples:\n");
    printf("  fanctl fan 1 1\n");
    printf("    Sets both fans to high speed.\n");
    printf("\n");
    printf("  fanctl speed\n");
    printf("    Displays the current RPM of both fans.\n");
    printf("\n");
    printf("  fanctl temp\n");
    printf("    Displays the current CPU temperature.\n");
}

#ifdef LIB
void init() {
    i8k_fd = open(I8K_PROC, O_RDONLY);
    if (i8k_fd < 0)
    {
        perror("can't open " I8K_PROC);
        exit(-1);
    }
}

void finish() {
    close(i8k_fd);
}
#else

int
main(int argc, char **argv) {
    if (argc >= 2) {
        if ((strcmp(argv[1],"-h")==0) || (strcmp(argv[1],"--help")==0)) {
            usage();
            exit(0);
        }
    }

    i8k_fd = open(I8K_PROC, O_RDONLY);
    if (i8k_fd < 0) {
        perror("can't open " I8K_PROC);
        exit(-1);
    }

    /* -2 as a magic number: if var 'ret' reachs the end of main() as -2, than
     * no command was executed, and the user input was an invalid command
     */
    int ret = -2;

    /* No args, print status: same output as 'cat /proc/i8k' */
    if (argc < 2) {
        ret = status();
        close(i8k_fd);
        return ret;
    }

    if (strcmp(argv[1],"fan")==0) {
        argc--; argv++;
        ret = fan(argc,argv);
    }

    else if (strcmp(argv[1],"speed")==0) {
        ret = fan_speed(argc,argv);
    }

    else if (strcmp(argv[1],"temp")==0) {
        ret = cpu_temperature();
    }

    close(i8k_fd);

    if (ret == -2) {
        fprintf(stderr,"Invalid Selection: %s\n", argv[1]);
    }

    return 0;
}
#endif
