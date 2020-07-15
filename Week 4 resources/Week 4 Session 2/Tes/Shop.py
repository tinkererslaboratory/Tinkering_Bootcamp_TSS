from PIL import Image
import pytesseract as tess
tess.pytesseract.tesseract_cmd=r'D:\Python\Tesseract\tesseract.exe'
from bina import binarize
name=input("Name of the Image-")
img=Image.open(name)

#img=img.crop((45,30,700,150))#shop
#img=img.convert('L')
#img=img.convert('1')
#img=binarize(img,200)
#img=img.resize((img.width,img.height),Image.BICUBIC)
Image._show(img)
text=tess.image_to_string(img)
print(text)