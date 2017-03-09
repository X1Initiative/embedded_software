# Data Processing Overview
# 1. Queue1: sensor directions (receive/pop at rate of 1ms)
# 2. Queue2: computer vision instructions (receive/pop when turn is executed)
# 3. Priorities
#	- Sensor distance gets extremely low -> Turn on that motor/turn off opposing motor
#   - Sensor distance in travel direction gets low -> Slowly turn that motor on/slowly turn opposing motor off
#	- Turn on motor opposite of direction of travel -> Slowly turn on motor opposite of desired travel direction

#WORK

import os
import RPi.GPIO as GPIO
from functools import partial
from time import sleep


#########################################
######### COMPUTER VISION SETUP #########
#########################################

class Queue:
    def __init__(self):
        self.items = []

    def isEmpty(self):
        return self.items == []

    def enqueue(self, item):
        self.items.insert(0,item)

    def dequeue(self):
        return self.items.pop()

    def size(self):
        return len(self.items)


# -------------------------------------------------------------------------- #
# When: - Run constantly in thread until program ends
# What: - Attempts to move the drone in direction of current travel
#       - Will not move if sensor is detecting wall in direction of travel

# Parameters: direction character ('N', 'E', 'S', 'W')
# -------------------------------------------------------------------------- #
def attemptMove(direction):
    # Attempt to move in desired direction of travel
    # Do not move if sensor says wall is close
    if direction == 'N':
        if GPIO.input(SensorN):
            deactivateMotor(MotorS)
        else:
            activateMotor(MotorS)
    elif direction == 'E':
        if GPIO.input(SensorE):
            deactivateMotor(MotorW)
        else:
            activateMotor(MotorW)
    elif direction == 'S':
        if GPIO.input(SensorS):
            deactivateMotor(MotorN)
        else:
            activateMotor(MotorN)
    elif direction == 'W':
        if GPIO.input(SensorS):
            deactivateMotor(MotorE)
        else:
            activateMotor(MotorE)


# Computer Vision data
cv_queue = Queue()
cv_file = open('temp_cv_file.txt', 'r')
cv_queue.items = cv_file.read().splitlines()
cv_queue.items.reverse()


class Directions:
    def __init__(self):
        self.current    = 'N'
        self.next_dir   = ''
        self.num_turns  = 0

direction = Directions()
time_to_turn = False



#########################################
############## GPIO SETUP ###############
#########################################

# Declare GPIO mode as board
GPIO.setmode(GPIO.BOARD)



#########################################
############## MOTOR SETUP ##############
#########################################

# Setup motor control through GPIO.OUT
MotorN = 16
MotorE = 18
MotorS = 22
MotorW = 24

GPIO.setup(MotorN,GPIO.OUT,inital=0)
GPIO.setup(MotorE,GPIO.OUT,inital=0)
GPIO.setup(MotorS,GPIO.OUT,inital=0)
GPIO.setup(MotorW,GPIO.OUT,inital=0)

# Sets of motors
motors = Set([MotorN, MotorE, MotorS, MotorW])
active_motors = Set([])
 

# -------------------------------------------------------------------------- #
# When: When motor status must be updated
# What: Ensures that all motors reflect their respective "active" status

# Parameters: none
# -------------------------------------------------------------------------- #
def updateMotors(self)
    # Turn on active motors
    print("Motors {} are on".format(list(active_motors)))
    print("Motors {} are off".format(list(motors - active_motors)))

    # for motor in active_motors:
    #     print("Turning on motor {}".format(motor))
    #     GPIO.output(motor,GPIO.HIGH)

    # Turn off inactive motors
    # for motor in (motors - active_motors):
    #     print("Turning off motor {}".format(motor))
    #     GPIO.output(motor,GPIO.LOW)


# -------------------------------------------------------------------------- #
# When: Call this method when logic determines a motor should be activated
# What: Adds a motor to set of "active motors"

# Parameters: motor_id = motor that should turn on
# -------------------------------------------------------------------------- #
def activateMotor(self, motor_ID):
    active_motors.add(motor_ID)
    self.updateMotors()


# -------------------------------------------------------------------------- #
# When: Call this method when logic determines a motor should be deactivated
# What: Removes a motor from set of "active motors"

# Parameters: motor_id = motor that should turn off
# -------------------------------------------------------------------------- #
def deactivateMotor(self, motor_ID):
    active_motors.remove(motor_ID)
    self.updateMotors()


# ----------------------------------------------------------------- #
# When: Call this method when passing a turn option
# What: Handles logic that tells drone when to turn

# Parameters: sensor_id = sensor that detected the potential turn
# ----------------------------------------------------------------- #
def potentialTurnDetected(self, sensor_ID):

    if sensor_ID == SensorN and direction.next_dir == 'N':
        direction.num_turns -= 1
        if direction.num_turns == 0:
            time_to_turn = True

    if sensor_ID == SensorE and direction.next_dir == 'E':
        direction.num_turns -= 1
        if direction.num_turns == 0:
            time_to_turn = True

    if sensor_ID == SensorS and direction.next_dir == 'S':
        direction.num_turns -= 1
        if direction.num_turns == 0:
            time_to_turn = True

    if sensor_ID == SensorW and direction.next_dir == 'W':
        direction.num_turns -= 1
        if direction.num_turns == 0:
            time_to_turn = True

    if time_to_turn:
        # Change direction of travel
        direction.current   = direction.next_dir
        next_direction      = cv_queue.dequeue()
        direction.num_turns = next_direction[0]
        direction.next_dir  = next_direction[1]
        time_to_turn        = False



#########################################
############# SENSOR SETUP ##############
#########################################

# Setup motor control through GPIO.IN
SensorN = 15;
SensorE = 19;
SensorS = 21;
SensorW = 23;

GPIO.setup(SensorN,GPIO.IN,pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(SensorE,GPIO.IN,pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(SensorS,GPIO.IN,pull_up_down=GPIO.PUD_DOWN)
GPIO.setup(SensorW,GPIO.IN,pull_up_down=GPIO.PUD_DOWN)

# Setup sensor rising edge callbacks
GPIO.add_event_detect(SensorN, GPIO.RISING, callback=partial(activateMotor, MotorN))
GPIO.add_event_detect(SensorE, GPIO.RISING, callback=partial(activateMotor, MotorE))
GPIO.add_event_detect(SensorS, GPIO.RISING, callback=partial(activateMotor, MotorS))
GPIO.add_event_detect(SensorW, GPIO.RISING, callback=partial(activateMotor, MotorW))

# Setup sensor falling edge callbacks
GPIO.add_event_detect(SensorN, GPIO.FALLING, callback=partial(deactivateMotor, MotorN))
GPIO.add_event_detect(SensorE, GPIO.FALLING, callback=partial(deactivateMotor, MotorE))
GPIO.add_event_detect(SensorS, GPIO.FALLING, callback=partial(deactivateMotor, MotorS))
GPIO.add_event_detect(SensorW, GPIO.FALLING, callback=partial(deactivateMotor, MotorW))



#########################################
############# MAIN THREADS ##############
#########################################

# Create one thread to continually attempt movement
while True:
    attemptMove(direction.current)
    sleep(0.3)

# TODO: Create one thread to detect potential turns

# Create one thread to wait for user to quit
while True:
    user_in = input("Type \"quit\" to shut down: ")
    if user_in == "quit":
        GPIO.cleanup()
    else:
        print("Please type \"quit\" to shutdown motors.")

GPIO.cleanup()




