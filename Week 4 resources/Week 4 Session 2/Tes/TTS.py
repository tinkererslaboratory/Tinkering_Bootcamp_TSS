from gtts import gTTS
import os

text="Hello World"
output=gTTS(text)
output.save("out.mp3")
os.system("start out.mp3")
