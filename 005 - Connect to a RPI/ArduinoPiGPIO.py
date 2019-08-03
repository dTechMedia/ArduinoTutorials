#! /usr/bin/python3

from gpiozero import DigitalOutputDevice
from time import sleep

onButton = DigitalOutputDevice(3, active_high=False)
offButton = DigitalOutputDevice(2, active_high=False)

while True:
    print("Turning LED on")
    onButton.on()
    #sleep(1)
    onButton.off()
    sleep(5)
    print("Turning LED off")
    offButton.on()
    #sleep(1)
    offButton.off()
    sleep(5)