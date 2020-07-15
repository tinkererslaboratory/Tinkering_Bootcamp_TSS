from PIL import Image
import pytesseract as tess
tess.pytesseract.tesseract_cmd=r'D:\Python\Tesseract\tesseract.exe'
name=input("Name of Image:")
from bina import binarize
img=Image.open(name)
#img=img.convert('L')
#img=img.convert('1')
#Image._show(img)
img=binarize(img,50)
Image._show(img)
text=tess.image_to_string(img)
print(text)