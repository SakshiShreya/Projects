import numpy as np
import cv2
import random
import time

##########CANVAS####################
height = 500
width = 800
img = np.zeros((height, width, 3), np.uint8)
img.fill(51)		# Makes canvas gray
####################################

grid = []
w = 20
rows = height/w
cols = width/w

stack = []

def index(i, j):
	if (i < 0):
		i, j = 0, j+1
	elif(i > cols-1):
		i, j = -1, j+1
	if (j < 0):
		i, j = i+1, 0
	elif(j > rows-1):
		j, i = -1, i+1
	return i + j * cols

def removeWalls(a, b):
	x = a.i - b.i
	if x == 1:
		a.walls[3] = False
		b.walls[1] = False
	elif x == -1:
		a.walls[1] = False
		b.walls[3] = False

	y = a.j - b.j
	if y == 1:
		a.walls[0] = False
		b.walls[2] = False
	elif y == -1:
		a.walls[2] = False
		b.walls[0] = False

class Cell:
	def __init__(self, i, j):
		self.i = i
		self.j = j
		self.walls = [True, True, True, True]
		self.visited = False

	def show(self):
		x = self.i * w
		y = self.j * w

		if self.visited:
			cv2.rectangle(img, (x, y), (x+w, y+w), (50, 150, 50), -1)
			
		if self.walls[0]:
			cv2.line(img, (x    , y)    , (x + w, y)    , (255, 255, 255), 1)
		if self.walls[1]:
			cv2.line(img, (x + w, y)    , (x + w, y + w), (255, 255, 255), 1)
		if self.walls[2]:
			cv2.line(img, (x + w, y + w), (x    , y + w), (255, 255, 255), 1)
		if self.walls[3]:	
			cv2.line(img, (x    , y + w), (x    , y)    , (255, 255, 255), 1)

	def checkNeighbors(self):
		neighbors = []
		print self.i, self.j
		top = grid[index(self.i, self.j-1)]
		right = grid[index(self.i+1, self.j)]
		bottom = grid[index(self.i, self.j+1)]
		left = grid[index(self.i-1, self.j)]

		if top and (not top.visited):
			neighbors.append(top)
		if right and (not right.visited):
			neighbors.append(right)
		if bottom and (not bottom.visited):
			neighbors.append(bottom)
		if left and (not left.visited):
			neighbors.append(left)

		if len(neighbors) > 0:
			r = random.randint(0, len(neighbors)-1)
			return neighbors[r]
		else:
			return None

	def highlight(self):
		x = self.i * w
		y = self.j * w
		cv2.rectangle(img, (x, y), (x+w, y+w), (255, 100, 0), -1)

for j in range(rows):
	for i in range(cols):
		cell = Cell(i, j)
		grid.append(cell)

current = grid[0]

while (1):
	for i in range(len(grid)):
		grid[i].show()
	
	current.visited = True
	current.highlight()

	# STEP 1
	nextcell = current.checkNeighbors()
	if(nextcell):
		nextcell.visited = True

		# STEP 2
		stack.append(current)

		# STEP 3
		removeWalls(current, nextcell)

		# STEP 4
		current = nextcell
	elif len(stack) > 0:
		current = stack.pop()

	cv2.imshow("Image", img)
	#time.sleep(0.1)

	if cv2.waitKey(1) == 27:	#27 - ASCII for escape key
		break

#########SHOW AND SAVE##############
cv2.imwrite("Maze.jpg", img)
cv2.destroyAllWindows()
####################################
