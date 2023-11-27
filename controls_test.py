# import statments
import math
import time

# function to write a new initial value to the gpio pin
def set_speed(speed):
    # access pin initial values
    with open('/dev/bone/pwm/1/a/duty_cycle', 'w') as filetowrite:
        # write desired speed to gpio value
        filetowrite.write(str(speed))

# function to drive motor at a slow speed
def steady_speed():
    # set speed value to give 8.1% to drive motor
    steady_speed = 1620000
    # print speed setting
    print("speed: ", steady_speed)
    # print 'going' intention
    print("going")
    # write the new speed value to the initial gpio pin setting to drive motor
    set_speed(steady_speed)

# function to drive motor at a faster speed
def faster_speed():
    # set speed value to give 8.175% to drive motor
    faster_speed = 1635000
    # print speed setting
    print("speed: ", faster_speed)
    # print 'going faster' intention
    print("going faster")
    # write the new speed value to the initial gpio pin setting to drive motor
    set_speed(faster_speed)

# function to drive motor at a slower speed
def crawling_speed():
    # set speed value to give 8.05% to drive motor
    slow_speed = 1610000
    # print speed setting
    print("speed: ", slow_speed)
    # print 'going slower' intention
    print("going slower")
    # write the new speed value to the initial gpio pin setting to drive motor
    set_speed(slow_speed)

# function to drive motor at a stop speed
def stop():
    # set speed value to give 8% to drive motor
    stop_speed = 1600000
    # print speed setting
    print("speed: ", stop_speed)
    # print 'going stop' intention
    print("going stop")
    # write the new speed value to the initial gpio pin setting to drive motor
    set_speed(stop_speed)

# function to write a new initial value to the gpio pin
def set_turnish(veer):
    # access pin initial values
    with open('/dev/bone/pwm/1/b/duty_cycle', 'w') as filetowrite:
        # write desired speed to gpio value
        filetowrite.write(str(veer))

# function to set motor controller to turn axel to center
def center():
    # set veer value to give 7.5% to drive motors equally
    no_veer = int(.075 * 20000000)
    print("veer: ", no_veer)
    print("going forward")
    set_turnish(no_veer)

# function to set motor controller to turn axel to left
def lefter():
    # set veer value to give 6% to drive left motor strong
    left_veer = int(.06 * 20000000)
    print("veer: ", left_veer)
    print("going left")
    set_turnish(left_veer)

# function to set motor controller to turn axel to right
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