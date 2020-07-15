import cv2
import time

cap = cv2.VideoCapture(0)
time.sleep(2)
for i in range(1):
    ret, frame= cap.read()
cv2.imwrite("img.jpg", frame)
#cv2.imshow("a",frame)
#cv2.waitKey(0)
from PIL import Image
import pytesseract as tess
from gtts import gTTS
import os
tess.pytesseract.tesseract_cmd=r'D:\Python\Tesseract\tesseract.exe'
from bina import binarize
name="img.jpg"

img=Image.open(name)

#img=img.crop((45,30,700,150))#shop
#img=img.crop((0,100,1120,550))#News
#img=img.convert('L')
#img=img.convert('1')
#img=binarize(img,200)
#img=img.resize((img.width,img.height),Image.BICUBIC)

text=tess.image_to_string(img)

Image._show(img)
output=gTTS(text)
output.save("read.mp3")
os.system("start read.mp3")
print(text)