import cv2
from random import randint

class Circle:
	def __init__(self, x, y, thickness):
		self.x = x
		self.y = y
		self.r = 1
		self.growing = True
		self.thickness = thickness
		self.colour = (randint(50, 255), randint(50, 255), randint(50, 255))

	def draw(self, img):
		cv2.circle(img, (self.x, self.y), self.r, self.colour, self.thickness, cv2.LINE_AA)

	def grow(self):
		self.r += 1
		if self.r > 10:
			self.growing = False