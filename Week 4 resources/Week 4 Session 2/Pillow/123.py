from PIL import Image
from PIL import ImageFilter
from PIL import ImageDraw
from PIL import ImageEnhance
can= Image.open("can.jpg")
can=can.convert('RGB')
print(can.width,can.height)
ecan=ImageEnhance.Brightness(can)
bunch=[]
for i in range(0,10):
    bunch.append(ecan.enhance(i/10))
fimage=bunch[0]
sheet=Image.new(fimage.mode,(fimage.width,10*fimage.height))
x=0
y=0
for p in bunch:
    sheet.paste(p,(x,y))
    y=y+5000
sheet=sheet.resize((400,5000))
Image._show(sheet)
