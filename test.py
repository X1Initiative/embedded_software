import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)


TRIG = 5
ECHO = 7

GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)


GPIO.output(TRIG,False)
time.sleep(2)
measurements=[]

test_dist=int(raw_input("Distance for Test >> "))
startTime=time.time()
elapsedTime=0
while elapsedTime < 5:
    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    while GPIO.input(ECHO) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start

    distance = pulse_duration*1000
    measurements.append(distance)

    time.sleep(0.1)
    elapsedTime=time.time()-startTime

avg = sum(measurements)/len(measurements)
print("The average voltage for the distance of %f cm was %r") %(test_dist, avg)
GPIO.cleanup()


