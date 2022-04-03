import sys
import time
import RPi.GPIO as GPIO
from pyPS4Controller.controller import Controller
    
    
class MyController(Controller):

    def __init__(self, **kwargs):
        Controller.__init__(self, **kwargs)

    def on_x_press(self):
       print("Hello world")

    def on_x_release(self):
       print("Goodbye world")

controller = MyController(interface="/dev/input/js0", connecting_using_ds4drv=False)
# you can start listening before controller is paired, as long as you pair it within the timeout window
controller.listen(timeout=60)

def motorInitialization(pins):
    for pin in pins:
        GPIO.setup(pin,GPIO.OUT)
        GPIO.output(pin, False)

def degreesToSteps(degree):
    return int(degree * 11.377777777777)

def stepTime(speed):
    return 0.0007 / speed
    
def rotate(pins, steps, direction, speed):
    if direction == 0:
        currentSequence = clockwiseSequense
    else:
        currentSequence = counterclockwiseSequense
    for step in range(1, steps):
        for pin in range (0, 4):
            GPIO.output(pins[pin], currentSequence[step % 8][pin])
        time.sleep(speed)
        

aMotorPins = [14, 15, 17, 18]
bMotorPins = [26, 19, 13, 6]

clockwiseSequense = [
    [0,0,0,1],
    [0,0,1,1],
    [0,0,1,0],
    [0,1,1,0],
    [0,1,0,0],
    [1,1,0,0],
    [1,0,0,0],
    [1,0,0,1]
]
counterclockwiseSequense = [
    [1,0,0,1],
    [1,0,0,0],
    [1,1,0,0],
    [0,1,0,0],
    [0,1,1,0],
    [0,0,1,0],
    [0,0,1,1],
    [0,0,0,1]
    ]

GPIO.setmode(GPIO.BCM)

motorInitialization(aMotorPins)
motorInitialization(bMotorPins)

#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.1))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.2))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.3))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.4))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.5))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.6))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.7))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.8))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(0.9))
#rotate(aMotorPins, degreesToSteps(30), 0, stepTime(1))



GPIO.cleanup()
