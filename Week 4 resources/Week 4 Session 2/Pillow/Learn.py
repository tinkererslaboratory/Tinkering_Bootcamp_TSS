from PIL import Image
from PIL import ImageFilter
import PIL
a=Image.open('map final.jpg')
a=a.convert('L')
Image._show(a)

