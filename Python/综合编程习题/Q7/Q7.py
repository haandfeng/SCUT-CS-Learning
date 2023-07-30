from PIL import Image

im = Image.open('bird.jpg')
width = im.size[0]
height = im.size[1]
gim = im.convert(mode='L')
dx = 16
dy = 16
x1 = 0
y1 = 0
x2 = dx
y2 = dy
maxaverage = 0
minaverage = 255

while x2 <= width:
    while y2 <= height:
        average = 0
        im2 = im.crop((x1, y1, x2, y2))
        im2 = im2.convert(mode='L')
        # 求每份图的灰度值
        for i in range(16):
            for j in range(16):
                average += im2.getpixel((i, j)) / 256
        if average > maxaverage:
            maxaverage = average
        if average < minaverage:
            minaverage = average
        y1 = y1 + dy
        y2 = y2 + dy
    x1 = x1 + dx
    x2 = x2 + dx
    y1 = 0
    y2 = dy

x1 = 0
y1 = 0
x2 = dx
y2 = dy
txt = ""
while y2 <= width:
    while x2 <= height:
        average = 0
        im2 = im.crop((x1, y1, x2, y2))
        im2 = im2.convert(mode='L')
        # 求每份图的灰度值
        for i in range(16):
            for j in range(16):
                average += im2.getpixel((i, j)) / 256
        # 求完之后paste
        if minaverage <= average < minaverage + (maxaverage - minaverage) / 2:
            txt += ' □ '
        elif minaverage + (maxaverage - minaverage) / 2 <= average <= maxaverage:
            txt += ' ■ '
        x1 = x1 + dy
        x2 = x2 + dy
    y1 = y1 + dy
    y2 = y2 + dy
    x1 = 0
    x2 = dx
    txt += "\n"
fo = open("bird.txt", "w")
fo.write(txt)
fo.close()
