'''
Created on 2021/12/15

@author: Sin Shimozono
'''

class rect:
    def __init__(self,width,height,pos=(0,0) ):
        self._width = width
        self._height = height
        self.position = pos

    def width(self):
        return self._width
    
    def height(self):
        return self._height
    
class polygon:
    def __init__(self, points=[(0,0)], pos = (0,0)):
        self.points = list()
        btlt = points[0]
        btltindex = 0
        for pt in points:
            self.points.append([pt[0], pt[1]])
            if btlt[1] > pt[1] :
                btlt = (pt[0],pt[1])
                btltindex = len(self.points) - 1
            elif btlt[1] == pt[1] and btlt[0] < pt[0] :
                btlt = (pt[0],pt[1])
                btltindex = len(self.points) - 1
        self.position = pos
        self.points = self.points[btltindex:] + self.points[:btltindex]
        
    
    def origin(self, x, y):
        self.position = [x,y]
        
    def append(self, pointlist):
        for pt in pointlist:
            self.points.append( (pt[0],pt[1]) )
    
    def placeinside(self,shape):
        if not isinstance(shape,rect):
            return
        
    def draw(self, window, color = (0,0,0), width = 1):
        if len(self.points) == 0 :
            return
        pointlist = [(pt[0]+self.position[0], pt[1]+self.position[1]) for pt in self.points]
        pygame.draw.polygon(window, color, pointlist, width)
        pygame.draw.circle(window,color,pointlist[-1],4)

if __name__ == '__main__':
    import pygame
    from pygame.locals import *
    import time
    
    COLOR_WHITE = (255, 255, 255)
    pygame.init()
    window = pygame.display.set_mode((512, 512))
    window.fill(COLOR_WHITE)
    line = polygon([(100,40)])
    line.origin(200,200)
    line.append([(100,0), (0,0), (0,40)])
    r = rect(30,20)
    line.placeinside(r)
    line.draw(window,width=2)
    pygame.display.update()

    time.sleep(5)