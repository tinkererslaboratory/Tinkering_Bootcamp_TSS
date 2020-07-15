from PIL import Image

img=Image.open("news.jpg")
#img =img.convert('L')
img=img.convert('1')
Image._show(img)