#!/bin/bash

if (( EUID != 0 ))
then
  echo "Please run as root."
  exit -1
fi

if [[ ! -x "$(command -v gpiofind)" ]]
then
    echo "gpiod could not be found."
    exit -2
fi

i=1
while (( i <= 40 ))
do
    PIN=PIN_$i
    GPIO=$(gpiofind $PIN)
    if [[ $GPIO != "" ]]
    then
        PIN_INFO=$(gpioinfo | grep "\"$PIN\"")

        # Test input mode
        LEVEL=$(gpioget $GPIO)
        read -p "$PIN = $LEVEL. Please attach $PIN to $( (( LEVEL )) && echo GND || echo 3.3v )."
        LEVEL=$(gpioget $GPIO)
        read -p "$PIN = $LEVEL. Please attach $PIN to the meter for output test."
        LEVEL=$(gpioget $GPIO)

        # Test output mode
        LEVEL=$(( 1 - LEVEL ))
        gpioset $GPIO=$LEVEL
        read -p "$PIN = $LEVEL."
        LEVEL=$(( 1 - LEVEL ))
        gpioset $GPIO=$LEVEL
        echo "$PIN = $LEVEL."
    fi
    i=$(( i + 1 ))
done