from PIL import Image
img = Image.open("../resources/1b.bmp").convert("1")
char_width = 40
char_height = 71
width, height = img.size
font_map = []

for y in range(0, height, char_height):
	row = []

	for x in range(0, width, char_width):
		char = img.crop((
			x, y,
			min(x + char_width, width),
			min(y + char_height, height)
		))

		# Convert character image into a 2D array of 1s and 0s
		pixels = [
			[1 if char.getpixel((px, py)) else 0
			 for px in range(char.width)]
			for py in range(char.height)
		]

		row.append(pixels)

	font_map.append(row)

def output_char(character):
	name = input()
	symbol = input()
	print(f'''#include <stdint.h>
#include "character.h"

const Character {name}_bmp = {{ {{''')
	for row in character:
		print("\t\t0b",end="")
		for col in row:
			print(col, end="")
		print(",")
	print(f'''	}},
	'{symbol}'
}};''')

output_char(font_map[int(input())][int(input())])
