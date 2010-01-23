class Tile:
	tile_id = -1
	def show(self):
		print self.tile_id

class Castle(Tile):
	tile_id = 1

if __name__ == "__main__":
	a = Castle()
	print a.tile_id;
	a.show()
	a = Tile()
	a.show()
