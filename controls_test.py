import math
import time

def set_speed(speed):
    with open('/dev/bone/pwm/1/a/duty_cycle', 'w') as filetowrite:
        filetowrite.write(str(speed))

def steady_speed():
    steady_speed = 1620000
    print("speed: ", steady_speed)
    print("going")
    set_speed(steady_speed)

def faster_speed():
    faster_speed = 1635000
    print("speed: ", faster_speed)
    print("going faster")
    set_speed(faster_speed)

def crawling_speed():
    slow_speed = 1610000
    print("speed: ", slow_speed)
    print("going slower")
    set_speed(slow_speed)

def stop():
    stop_speed = 1600000
    print("speed: ", stop_speed)
    print("going stop")
    set_speed(stop_speed)


def set_turnish(veer):
    with open('/dev/bone/pwm/1/b/duty_cycle', 'w') as filetowrite:
        filetowrite.write(str(veer))

def center():
    no_veer = int(.075 * 20000000)
    print("veer: ", no_veer)
    print("going forward")
    set_turnish(no_veer)

def lefter():
    left_veer = int(.06 * 20000000)
    print("veer: ", left_veer)
    print("going left")
    set_turnish(left_veer)

def righter():
    right_veer = int(.09 * 20000000)
    print("veer: ", right_veer)
    print("going right")
    set_turnish(right_veer)


# speed, i am speed
steady_speed()
time.sleep(3)
faster_speed()
time.sleep(3)
stop()
time.sleep(3)
crawling_speed()
steady_speed()


# check steering
center()
time.sleep(2)
lefter()
time.sleep(2)
righter()
time.sleep(2)
center()