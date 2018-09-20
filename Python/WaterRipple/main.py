import cv2
import numpy as np
from random import randint
from scipy import signal

# https://web.archive.org/web/20160418004149/http://freespace.virgin.net/hugo.elias/graphics/x_water.htm

height = 450
width  = 800
damping = 0.99		# Some non-integer between 0 and 1

current = np.zeros((height, width), np.float32)
previous = np.zeros((height, width), np.float32)
temp = np.zeros((height, width), np.float32)

## MOUSE INTERACTION
pressed = False
px, py, nx, ny = 0, 0, 0, 0

def mouse_drop(event,x,y,flags,param):
	global pressed
	global px, py, nx, ny

	if event == cv2.EVENT_LBUTTONDOWN:
		pressed = True
		previous[y, x] = 255
		px, py = x, y

	elif event == cv2.EVENT_LBUTTONUP:
		pressed = False

	elif event == cv2.EVENT_MOUSEMOVE:
		if pressed == True:
			## Use any one

			# nx, ny = x, y
			# cv2.line(previous,(nx, ny),(px, py),(255,255,255),1)
			# px, py = nx, ny

			previous[y, x] = 255

cv2.namedWindow('Image')
cv2.setMouseCallback('Image',mouse_drop)

img = np.zeros((height, width), np.uint8)
conv = np.array([[0, 0.5, 0], [0.5, 0, 0.5], [0, 0.5, 0]], np.float32)

count = 8
# previous[height/8, width/2] = 255   # Testing

while (1):
	# img = np.zeros((height, width), np.uint8)
	count += 1
	if count > randint(1, 10):
		 count = 0
		 previous[randint(1, height-1), randint(1, width-1)] = 255

	## Original Code
	# 
	# for i in range(1, height-1):
	# 	for j in range(1, width-1):
	# 		current[i, j] = (previous[i-1,j] +
	# 						 previous[i+1,j] +
	# 						 previous[i,j+1] +
	# 						 previous[i,j-1]) / 2 - current[i,j]

	## Very much faster
	img1 = signal.convolve2d(previous, conv, mode='same')
	current = img1 - current
	current = (current * damping)

	img = (current).clip(0, 255).astype(np.uint8)
	cv2.imshow("Image", img)

	# SWAPPING
	temp = current.copy()
	current = previous.copy()
	previous = temp.copy()

	if cv2.waitKey(1) == 27:
		break
cv2.destroyAllWindows()