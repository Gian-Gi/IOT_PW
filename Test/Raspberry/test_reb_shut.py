#!/usr/bin/python3

#------------------------------------------------------------------------------
# test_reb_shut.py - Prova di intercettazione pulsanti di reboot e shutdown
#------------------------------------------------------------------------------

#--------------------------------------
# Importazione librerie
#--------------------------------------
import time
import RPi.GPIO as GPIO
import signal
import sys
import os


#--------------------------------------
# Variabili globali
#--------------------------------------
PIN_REBOOT_REQUESTED = 11
PIN_SHUTDOWN_REQUESTED = 13
PIN_FEEDBACK_ARDUINO = 15


#--------------------------------------
# Setup iniziali
#--------------------------------------
##### Impostazione board GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
##### Impostazione pin reboot requested
GPIO.setup(PIN_REBOOT_REQUESTED, GPIO.IN)
##### Impostazione pin shutdown requested
GPIO.setup(PIN_SHUTDOWN_REQUESTED, GPIO.IN)
##### Impostazione pin feedback
GPIO.setup(PIN_FEEDBACK_ARDUINO, GPIO.OUT)


#--------------------------------------
# Definizione funzioni locali
#--------------------------------------

##### Uscita per Ctrl-C
def uscita_ctrl_c(signal, frame):
    GPIO.output(PIN_FEEDBACK_ARDUINO, 0)
    GPIO.cleanup()
    sys.exit(0)


def reboot_requested(channel):
    GPIO.output(PIN_FEEDBACK_ARDUINO, 0)
    print("\nReboot requested on channel" + " " + str(channel))


def shutdown_requested(channel):
    GPIO.output(PIN_FEEDBACK_ARDUINO, 0)
    print("\nShutdown requested on channel" + " " + str(channel))


##### Intercettazione Ctrl-C
signal.signal(signal.SIGINT, uscita_ctrl_c)


#---------------------------
# MAIN
#---------------------------
##### Feedback ON per Arduino
GPIO.add_event_detect(PIN_REBOOT_REQUESTED, GPIO.RISING, callback = reboot_requested, bouncetime = 500)
GPIO.add_event_detect(PIN_SHUTDOWN_REQUESTED, GPIO.RISING, callback = shutdown_requested, bouncetime = 500)

while True:
    ##### Feedback ON per Arduino
    GPIO.output(PIN_FEEDBACK_ARDUINO, 1)
    time.sleep(2)
