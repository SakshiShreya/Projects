import cv2
import numpy as np
from circles import Circle
from random import randint


############ INPUT IMAGE ##############
inputImg = cv2.imread("Ebbo.png")
# inputImg = cv2.imread("HelloWorld.png")
#######################################

########### BLANK CANVAS ############
h, w = inputImg.shape[0], inputImg.shape[1]
img = np.zeros((h, w, 3), np.uint8)
#####################################

## Variables
circles = []
thickness = -1

## newCircle Function
# Generates a new circle if possible. Else, None.
def newCircle():
	x, y = randint(0, w-1), randint(0, h-1)
	for other in circles:
		d = ((x - other.x)**2 + (y - other.y)**2)**(0.5)
		if d < other.r + 3 or inputImg[y, x, 0] == 0:
			return None
	if len(circles) == 0 and inputImg[y, x, 0] == 0:
		return None
	return Circle(x, y, thickness)

## The loop for animation
while 1:
	img = np.zeros((h, w, 3), np.uint8)
	for i in range(50):
		newC = newCircle()
		if newC:
			circles.append(newC)
	for c in circles:
		c.draw(img)
		if c.growing:
			c.grow()
			for other in circles:
				if other != c:
					d = ((c.x - other.x)**2 + (c.y - other.y)**2)**(0.5)
					if d < c.r + other.r + 3:
						c.growing = False
						break


	cv2.imshow("Circles", img)
	if cv2.waitKey(1) == 27:
		break

#####################################
cv2.destroyAllWindows()