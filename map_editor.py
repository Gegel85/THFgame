import pygame
import json

def tranform_int(value):
	return [
		(value << 24) % 256,
		(value << 16) % 256,
		(value << 8) % 256,
		(value) % 256,
	]

def save_map(map):
	with open(map["path"], "wb") as fd:
		fd.write(map["tilemap"].encode("ASCII"))
		fd.write(bytes(1))
		fd.write(bytes(map["tilesize"], map["size"]["x"], map["size"]["y"]))
		for i in map["data"]:
			fd.write(bytes(i))

def load_map(path):
	map = {
		"path": path
	}
	with open(path, "rb") as fd:
		pass

def main():
	print("Chargement des assets du jeu...")
	with open("assets/list.json") as fd:
		assets = json.load(fd)

	print("Chemin de la carte (carte.map)")
	path = input()

	try:
		map = load_map(path)
	except:
		print("La carte n'a pas pu être chargé.")
		import traceback
		traceback.print_exc()
		print("Une nouvelle carte va être créé et supprimer l'ancienne. Est-ce OK ? [O/n]")
		if input() == "n":
			exit(1)
		map = {
			"path": path,
			"tilemap": print("Donner l'id de la tilemap") or input(),
			"tilesize": print("Donner la taille du tile") or int(input()),
			"size": {
				"x": print("Donner la largeur de la carte") or int(input()),
				"y": print("Donner la longueur de la carte") or int(input())
			},
		}
		map["data"] = [[0] * map["size"]["x"]] * map["size"]["y"]
		save_map(map)

	pygame.init()
	pygame.display.set_caption("THFGame map editor")

	image = pygame.image.load(assets["sprites"][map["tilemap"]])
	screen = pygame.display.set_mode((640,480))

	running = True

	while running:
		screen.fill((0, 0, 0))
		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				running = False
		screen.flip()


if __name__=="__main__":
	main()