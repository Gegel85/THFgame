import sys
import os

def pasteImage(img1, img2, pos):
    pix1 = img1.load()
    pix2 = img2.load()
    for x in range(img2.size[0]):
        for y in range(img2.size[1]):
            if x + pos[0] < img1.size[0] and y + pos[1] < img1.size[1] and y + pos[1] >= 0 and x + pos[0] >= 0:
                pix1[x + pos[0], y + pos[1]] = pix2[x, y]

try:
	from PIL import Image, ImageDraw, ImageFont

	result = Image.new("RGBA", (2048, 16), (0, 0, 0, 0))
	print("Dossier de ressources:")
	folder = input()
	for i in range(0, 128):
		file = os.path.join(folder, "tile_" + str(i) + ".png")
		try:
			image = Image.open(file)
			pasteImage(result, image, (i * 16, 0))
		except:
			print("Warning: Cannot load " + file)
	result.save("tilemap.png")
except:
	import traceback
	traceback.print_exc()
	os.system("pause")
	exit(1)