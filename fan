#!/usr/bin/env sh

FANCTL=/usr/bin/fanctl

if [ ! -x "$FANCTL" ]; then
    echo "Error: fan needs $FANCTL"
    exit 1
fi


if [[ "$1" == "-h" ]]; then
    echo "Usage: fan [left right]"
    echo "       i8kfan [-v]"
    exit 0
elif [ "$#" -gt 0 ]; then
    # Pass args to i8kctl fan
    exec "$I8KCTL" "fan" "$@"
else
    # Interface
    echo "Please select a fan speed mode:"
    echo "1) Off"
    echo "2) Low"
    echo "3) High"
    echo "4) Intense"
    read -p "Enter your choice [1-4]: " CHOICE

    case $CHOICE in
        1)
            # Off: Both fans off
            COMMANDS=("fan 0 0")
            ;;
        2)
            # Low: Left Speed: 2400, Right Speed: 0
            COMMANDS=("fan 0 0" "sleep 1" "fan 1 -1")
            ;;
        3)
            # High: Left Speed: 5500 Right Speed: 5500
            COMMANDS=("fan 1 1")
            ;;
        4)
            # Intense: Left Speed: 6400 Right Speed: 5800
            COMMANDS=("fan 2 2")
            ;;
        *)
            echo "Invalid choice"
            exit 1
            ;;
    esac

    # Privilege determination
    if [ "$(id -u)" != "0" ]; then
        SUDO="sudo"
    else
        SUDO=""
    fi

    for CMD in "${COMMANDS[@]}"; do
        if [[ "$CMD" == "sleep "* ]]; then
            SLEEP_DURATION="${CMD#sleep }"
            sleep "$SLEEP_DURATION"
        else
            $SUDO "$FANCTL" $CMD > /dev/null 2>&1
        fi
    done
fi
