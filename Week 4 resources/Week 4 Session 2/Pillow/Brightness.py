from PIL import Image
from PIL import ImageEnhance
a=Image.open("can.jpg")
enhancer=ImageEnhance.Brightness(a)
Image._show(enhancer.enhance(0.3))