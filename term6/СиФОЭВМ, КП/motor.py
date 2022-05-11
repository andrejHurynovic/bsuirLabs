import sys
import time
import RPi.GPIO as GPIO
import getch


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
    for pin in range (0, 4):
            GPIO.output(pins[pin], 0)

aMotorPins = [14, 15, 17, 18]
bMotorPins = [21, 20, 16, 7]

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

while True:
	char = getch.getch()
	if char == 'w':
		rotate(aMotorPins, degreesToSteps(2), 0, stepTime(1))
	if char == 's':
                rotate(aMotorPins, degreesToSteps(2), 1, stepTime(1))
	if char == 'a':
                rotate(bMotorPins, degreesToSteps(2), 0, stepTime(1))
	if char == 'd':
                rotate(bMotorPins, degreesToSteps(2), 1, stepTime(1))
#	print(char)
# if keyboard.is_pressed('c'):
#    print('The c key was pressed')
rotate(aMotorPins, degreesToSteps(360), 0, stepTime(1))



GPIO.cleanup()
