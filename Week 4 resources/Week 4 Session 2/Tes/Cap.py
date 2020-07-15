import cv2
import time
cap = cv2.VideoCapture(0)
time.sleep(2)
for i in range(1):
    ret, frame= cap.read()
#cv2.imwrite("lol.jpg", frame)
cv2.imshow("a",frame)
cv2.waitKey(0)