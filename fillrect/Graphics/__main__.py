'''
Created on 2021/12/15

@author: Sin Shimozono
'''

# Importing pygame module
import pygame
from pygame.locals import *
import time
 
# initiate pygame and give permission
# to use pygame's functionality.
pygame.init()
 
# create the display surface object
# of specific dimension.
window = pygame.display.set_mode((600, 600))
 
# Fill the scree with white color
window.fill((255, 255, 255))
 
# Using draw.rect module of
# pygame to draw the outlined rectangle
pygame.draw.rect(window, (0, 0, 255),
                 [100, 100, 400, 100], 2)
# pygame to draw the solid circle
pygame.draw.circle(window, (0, 255, 0),
                   [300, 300], 170, 3)
# Using draw.rect module of
# pygame to draw the outlined polygon
pygame.draw.polygon(window, (255, 0, 0),
                    [[300, 300], [100, 400],
                     [100, 300]])
# pygame.draw.line(surface, color,
# start point, end point, thickness) 
pygame.draw.line(window, (0, 255, 0),
                (60, 300), (120, 200), 4)

# Draws the surface object to the screen.
pygame.display.update()

time.sleep(5)