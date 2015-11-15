import time
import os
import sys
import pygame
import serial

print_width = 32

# Re-direct our output to standard error, we need to ignore standard out to hide some nasty print statements from pygame
sys.stdout = sys.stderr

# Setup pygame
os.environ["SDL_VIDEODRIVER"] = "dummy" # Removes the need to have a GUI window
pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()
#ser = serial.Serial('/dev/ttyACM0', 9600)

clear = lambda: os.system('clear')

def print_axis(axis):
    if values[axis] >= 0:
        pos = int (values[axis]*print_width)
        print "["+" "*print_width+" "*pos+"#"+" "*(print_width-pos-1)+"]" 
    else:
        pos = int( values[axis]*-print_width)
        print "["+" "*(print_width-pos)+"#"+" "*pos+" "*(print_width-1)+"]" 

try:
    values = [0]*23
    name = joystick.get_name()
    axes = joystick.get_numaxes()
    buttons = joystick.get_numbuttons()
    running = True
    while running:
        hadEvent = False
        buttonPressed = False
        buttonReleased = False
        
        #Clear the event stack to prevent overflow
        events = pygame.event.get()

        for i in range(4):
            values[i] = joystick.get_axis(i)
        for i in range(16):
            values[i+4] = joystick.get_button(i)

        if values[7]:
            running = False

        clear()
        print "Press CTRL+C or 'start' to quit"
        print "Name: ", name
        print "Number of axes:", axes 
        print "Number of buttons: ", buttons

        for i in range(4):
            print_axis(i)

        print "Buttons: "
        for i in values[4:]:
            print i, 

        #Sleep to prevent flickering
        time.sleep(0.05)
        
except KeyboardInterrupt:
    #CTRL+C exit
    print
    
