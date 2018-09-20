import cv2
import numpy as np

# Directions
UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

######### USER INPUT ###############################
pixel_size = input("Enter pixel size: ")
print "Enter canvas size"
h = int(raw_input("Enter the height: ")) * pixel_size
w = int(raw_input("Enter the width: ")) * pixel_size
print "Enter the current position"
current_pos = [0, 0]				#[height, width]
current_pos[0] = int(raw_input("Enter the height: "))
current_pos[1] = int(raw_input("Enter the width: "))
print "Now enter the direction:\nUP = 0, RIGHT = 1, DOWN = 2, LEFT = 3"
current_direction = input()
####################################################

########## CANVAS ##################################
img = np.zeros((h, w, 3), np.uint8)
img.fill(255)
####################################################

########## SETTING UP CUSTOM PIXEL SIZES ###########
black_pixel = np.zeros((pixel_size, pixel_size, 3), np.uint8)
white_pixel = black_pixel.copy()
white_pixel.fill(255)
red_pixel = black_pixel.copy()
red_pixel[:, :, 2].fill(255)
####################################################

def moveRight(direction, pos):
	if direction == UP:
		next_pos = [pos[0], pos[1]+pixel_size]
	elif direction == RIGHT:
		next_pos = [pos[0]+pixel_size, pos[1]]
	elif direction == DOWN:
		next_pos = [pos[0], pos[1]-pixel_size]
	elif direction == LEFT:
		next_pos = [pos[0]-pixel_size, pos[1]]	
	return (direction+1)%4, next_pos

def moveLeft(direction, pos):
	if direction == UP:
		next_pos = [pos[0], pos[1]-pixel_size]
	elif direction == RIGHT:
		next_pos = [pos[0]-pixel_size, pos[1]]
	elif direction == DOWN:
		next_pos = [pos[0], pos[1]+pixel_size]
	elif direction == LEFT:
		next_pos = [pos[0]+pixel_size, pos[1]]	
	return (direction-1)%4, next_pos


pos = np.multiply(current_pos, pixel_size)
while(1):
	if img[pos[0], pos[1], 0]:
		# Take any one channel. All are same.
		# If the pixel is white, then turn right
		current_direction, next_pos = moveRight(current_direction, pos)
		next_color = black_pixel
	elif not img[pos[0], pos[1], 0]:
		# Take any one channel. All are same.
		# If the pixel is white, then turn right
		current_direction, next_pos = moveLeft(current_direction, pos)
		next_color = white_pixel

	img[pos[0]:pos[0]+pixel_size, pos[1]:pos[1]+pixel_size] = red_pixel
	cv2.imshow("Output", img)
	if cv2.waitKey(0) == 27:
		break
	img[pos[0]:pos[0]+pixel_size, pos[1]:pos[1]+pixel_size] = next_color
	pos = next_pos

########## ENDING FORMALITIES ######################
cv2.destroyAllWindows()