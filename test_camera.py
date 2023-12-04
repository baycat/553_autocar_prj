import cv2

video = cv2.VideoCapture(0)

while True:
  ret,frame = video.read()
  frame = cv2.flip(frame,-1) # used to flip the image vertically
  cv2.imshow('original',frame)
  cv2.imwrite('original.jpg',frame)

  key = cv2.waitKey(1)
  if key == 27:
     break

video.release()