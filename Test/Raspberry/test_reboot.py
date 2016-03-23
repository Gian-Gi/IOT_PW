#!/usr/bin/python3

#------------------------------------------------------------------------------
# test_reboot.py - Prova di intercettazione pulsante di reboot
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
PIN_FEEDBACK_ARDUINO = 15


#--------------------------------------
# Setup iniziali
#--------------------------------------
##### Impostazione board GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
##### Impostazione pin reboot requested
GPIO.setup(PIN_REBOOT_REQUESTED, GPIO.IN)
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


##### Intercettazione Ctrl-C
signal.signal(signal.SIGINT, uscita_ctrl_c)


#---------------------------
# MAIN
#---------------------------

while True:
    ##### Feedback ON per Arduino
    GPIO.output(PIN_FEEDBACK_ARDUINO, 1)
    ##### Attende un fronte di risalita
    GPIO.wait_for_edge(PIN_REBOOT_REQUESTED,GPIO.RISING)
    print("\n Richiesto REBOOT\n")
    GPIO.output(PIN_FEEDBACK_ARDUINO, 0)
    time.sleep(1)
