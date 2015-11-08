import time
import os
import sys
import pygame

# Re-direct our output to standard error, we need to ignore standard out to hide some nasty print statements from pygame
sys.stdout = sys.stderr

# Setup pygame
os.environ["SDL_VIDEODRIVER"] = "dummy" # Removes the need to have a GUI window
pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()

clear = lambda: os.system('clear')

try:
    values = [0]*23
    axes = joystick.get_numaxes()
    buttons = joystick.get_numbuttons()
    while True:
        #hadEvent = False
        #events = pygame.event.get()
        #for event in events:
        #    if event.type = JOYBUTTONDOWN:
        for i in range(4):
            values[i] = joystick.get_axis(i)
        for i in range(16):
            values[i+4] = joystick.get_button(i)

        clear()
        print "Press CTRL+C to quit"
        print "Axes: ", axes
        print "Buttons: ", buttons
        print values
        time.sleep(0.1)

except KeyboardInterrupt:
    #CTRL+C exit
    print
    
