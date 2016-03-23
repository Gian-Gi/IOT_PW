#!/usr/bin/python3

#------------------------------------------------------------------------------
# test_shutdown.py - Prova di intercettazione pulsante di shutdown
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
PIN_SHUTDOWN_REQUESTED = 13
PIN_FEEDBACK_ARDUINO = 15


#--------------------------------------
# Setup iniziali
#--------------------------------------
##### Impostazione board GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
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


##### Intercettazione Ctrl-C
signal.signal(signal.SIGINT, uscita_ctrl_c)


#---------------------------
# MAIN
#---------------------------

while True:
    ##### Feedback ON per Arduino
    GPIO.output(PIN_FEEDBACK_ARDUINO, 1)
    ##### Attende un fronte di risalita
    GPIO.wait_for_edge(PIN_SHUTDOWN_REQUESTED,GPIO.RISING)
    print("\n Richiesto SHUTDOWN\n")
    GPIO.output(PIN_FEEDBACK_ARDUINO, 0)
    time.sleep(1)
