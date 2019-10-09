import pygame
import json

dirs = [
	"UP",
	"RIGHT",
	"DOWN",
	"LEFT"
]


def tranform_int(value):
	return [
		(value << 24) % 256,
		(value << 16) % 256,
		(value << 8) % 256,
		value % 256,
	]


def save_map(map):
	with open(map["path"], "wb") as fd:
		fd.write(map["tilemap"].encode("ASCII"))
		fd.write(bytes(1))
		fd.write(bytes((map["tilesize"], map["size"]["x"], map["size"]["y"])))
		for i in range(4):
			fd.write(bytes((map["links"][i] >> 8, map["links"][i] % 256)))
		for i in map["data"]:
			fd.write(bytes(i))


def load_map(path):
	data_map = {
		"path": path
	}
	with open(path, "rb") as fd:
		pass
	return data_map


def main():
	print("Chargement des assets du jeu...")
	with open("assets/list.json") as fd:
		assets = json.load(fd)

	print("Chemin de la carte (carte.map)")
	path = input()

	try:
		data_map = load_map(path)
	except:
		print("La carte n'a pas pu être chargé.")
		import traceback
		traceback.print_exc()
		print("Une nouvelle carte va être créé et supprimer l'ancienne. Est-ce OK ? [O/n]")
		if input() == "n":
			exit(1)
		data_map = {
			"path": path,
			"tilemap": print("Donner l'id de la tilemap") or input(),
			"tilesize": print("Donner la taille du tile") or int(input()),
			"size": {
				"x": print("Donner la longueur de la carte") or int(input()),
				"y": print("Donner la hauteur de la carte") or int(input())
			},
			"links": [
				print("Donner la connection vers " + dirs[i] + ". (Nothing for no connection)") or
				int(input() or "65535") for i in range(4)
			]
		}
		data_map["data"] = [[0] * data_map["size"]["x"]] * data_map["size"]["y"]
		save_map(data_map)

	pygame.init()
	pygame.display.set_caption("THFGame map editor")

	image = pygame.image.load(assets["sprites"][data_map["tilemap"]])
	screen = pygame.display.set_mode((640, 480))

	running = True

	while running:
		screen.fill((0, 0, 0))
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				running = False
		screen.flip()


if __name__ == "__main__":
	main()
