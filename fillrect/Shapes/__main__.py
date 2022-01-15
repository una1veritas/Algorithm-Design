'''
Created on 2021/12/15

@author: Sin Shimozono
'''
import math

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
    
    def __dist(self, pta, ptb):
        ptd= (pta[0] - ptb[0], pta[1] - ptb[1])
        if ptd[0] == 0 :
            return abs(ptd[1])
        elif ptd[1] == 0 :
            return abs(ptd[0])
        else:
            return math.sqrt(ptd[0]**2+ptd[1]**2)
        
    def placeholder_width(self):
        blpt = self.points[-1]
        brpt = self.points[0]
        return self.__dist(blpt, brpt)
    
    def origin(self, x, y):
        self.position = [x,y]
        
    def append(self, pointlist):
        for pt in pointlist:
            self.points.append( (pt[0],pt[1]) )
    
    def placeinside(self,shape):
        if not isinstance(shape,rect):
            return
        maxwidth = self.placeholder_width()
        if shape.width() <= maxwidth :
            blpt = self.points.pop()
            self.points.append( (blpt[0], blpt[1] + shape.height()) )
            self.points.append( (self.points[-1][0] + shape.width(), self.points[-1][1]) )
            self.points.append( (self.points[-1][0], blpt[1]) )
        else:
            raise RuntimeError('width overflow')
        
    def draw(self, window, color = (0,0,0), width = 1):
        if len(self.points) == 0 :
            return
        pointlist = [(pt[0]+self.position[0], -pt[1]+self.position[1]) for pt in self.points]
        pygame.draw.polygon(window, color, pointlist, width)
        pygame.draw.circle(window,color,pointlist[-1],4)

class rect(polygon):
    def __init__(self,width,height,pos=(0,0) ):
        self._width = width
        self._height = height
        self.position = pos

    def width(self):
        return self._width
    
    def height(self):
        return self._height

if __name__ == '__main__':
    import pygame
    from pygame.locals import *
    import time
    
    COLOR_WHITE = (255, 255, 255)
    pygame.init()
    window = pygame.display.set_mode((512, 512))
    window.fill(COLOR_WHITE)
    line = polygon([(0,0),(160,0),(160,80),(0,80)])
    line.origin(100,200)
    line.draw(window,width=2)
    pygame.display.update()
    
    r = rect(60,40)
    line.placeinside(r)
    line.draw(window,width=2)
    pygame.display.update()
    
    r = rect(80,60)
    line.placeinside(r)
    
    line.draw(window,width=2)
    pygame.display.update()

    time.sleep(5)