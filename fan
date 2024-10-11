#!/usr/bin/env sh

I8KCTL=/usr/bin/i8kctl

if [ ! -x "$I8KCTL" ]; then
    echo "Error: i8kfan needs $I8KCTL"
    exit 1
fi

# Handle command-line options
if [[ "$1" == "-h" ]]; then
    echo "Usage: i8kfan [left right]"
    echo "       i8kfan [-v]"
    exit 0
elif [[ "$1" == "-v" ]]; then
    exec "$I8KCTL" "-v"
elif [ "$#" -gt 0 ]; then
    # If arguments are provided, pass them to i8kctl fan
    exec "$I8KCTL" "fan" "$@"
else
    # No arguments provided, show prompt
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

    # Determine if sudo is needed
    if [ "$(id -u)" != "0" ]; then
        SUDO="sudo"
    else
        SUDO=""
    fi

    # Execute the commands
    for CMD in "${COMMANDS[@]}"; do
        if [[ "$CMD" == "sleep "* ]]; then
            # Extract the sleep duration
            SLEEP_DURATION="${CMD#sleep }"
            sleep "$SLEEP_DURATION"
        else
            # Execute the i8kctl command
            $SUDO "$I8KCTL" $CMD
        fi
    done
fi
