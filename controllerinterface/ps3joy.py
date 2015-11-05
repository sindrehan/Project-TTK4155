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

try:
    print "Press CTRL+C to quit"
    # events = pygame.event.get()
    while True:
        print 
        for i in range (20):
           print "Button {0}: {1}\n".format(i, pygame.get_button(i))
        

    
except KeyboardInterrupt:
    #CTRL+C exit
    print
