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

def print_axis(axis):
    if values[axis] >= 0:
        pos = int (values[axis]*64)
        print "[", " "*64, " "*pos, "#", " "*(64-pos), "]" 
        #print "Axis", axis, ": ", pos
    else:
        pos = int( values[axis]*-64)
        #print "Axis", axis, ": ", pos
        print "[", " "*(64-pos),"#", " "*pos, " "*64, "]" 
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
        events = pygame.event.get()
        # for event in events:
        #     if event.type == pygame.QUIT:
        #          print "HEI"
                 
        #     if event.type == pygame.JOYBUTTONDOWN:
        #         hadEvent = True
        #         buttonPressed = True
        #     if event.type == pygame.JOYBUTTONUP:
        #         hadEvent = True
        #         buttonReleased = True

        for i in range(4):
            # temp = joystick.get_axis(i)
            # temp *= 255
            # values[i] = int(temp)
            values[i] = joystick.get_axis(i)
        for i in range(16):
            values[i+4] = joystick.get_button(i)

        if values[7]:
            running = False

        clear()
        print "Press CTRL+C or 'start' to quit"
        print "Name: ", name
        print "Axes: "
        for i in range(4):
            print_axis(i)
        
        print "Buttons: ", buttons
        print values
        time.sleep(0.1)

except KeyboardInterrupt:
    #CTRL+C exit
    print
    
