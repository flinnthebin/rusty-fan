#!/usr/bin/env sh

fanctl=/usr/local/bin/fanctl

if [ ! -x "$fanctl" ]; then
    echo "error: fan needs $fanctl"
    exit 1
fi

if [[ "$1" == "-h" ]]; then
    echo "Usage: fan [left right]"
    exit 0
elif [ "$#" -gt 0 ]; then
    # pass args to fanctl fan
    exec "$fanctl" "fan" "$@"
else
    # interface
    echo "Please select a fan speed mode:"
    echo "1) Off"
    echo "2) Low"
    echo "3) Medium"
    echo "4) High"
    echo "5) Max"
    read -p "Enter your choice [1-5]: " choice

    case $choice in
        1)
            # off: both fans off
            commands=("fan 0 0")
            ;;
        2)
            # low: left speed: 2400, right speed: 0
            commands=("fan 0 0" "sleep 1" "fan 1 -1")
            ;;
        3)
            # med: left speed: 0 right speed: 5100
            commands=("fan 0 1")
            ;;
        4)
            # high: left speed: 2400 right speed: 5500
            commands=("fan 1 1")
            ;;
        5)
            # max: left speed: 6400 right speed: 5800
            commands=("fan 2 2")
            ;;
        *)
            echo "invalid choice"
            exit 1
            ;;
    esac

    # privilege determination
    if [ "$(id -u)" != "0" ]; then
        sudo="sudo"
    else
        sudo=""
    fi

    for cmd in "${commands[@]}"; do
        if [[ "$cmd" == "sleep "* ]]; then
            sleep_duration="${cmd#sleep }"
            sleep "$sleep_duration"
        else
            $sudo "$fanctl" $cmd > /dev/null 2>&1
        fi
    done
fi
