extends Node2D

const N_HORZ = 3
const N_VERT = 3
const TILE_RED = 0
const TILE_BLUE = 1
const TILE_SRC = 0
const TILE_DST = 1

var cursor = Vector2(-1, -1)

func _ready():
	init_cursor()
	
func init_cursor():
	cursor = Vector2(-1, -1)
	for y in range(N_VERT):
		for x in range(N_HORZ):
			$Board/CursorTileMap.set_cell(x, y, -1)

func _input(event):
	if event is InputEventMouseButton && event.is_pressed():
		var mp = $Board/TileMap.world_to_map($Board/TileMap.get_local_mouse_position())
		if mp.x < 0 || mp.x >= N_HORZ || mp.y < 0 || mp.y >= N_VERT:
			return
		if $Board/TileMap.get_cellv(mp) == TILE_RED:
			if cursor == mp:
				init_cursor()
			else:
				init_cursor()
				cursor = mp
				$Board/CursorTileMap.set_cellv(cursor, TILE_SRC)
				if mp.x > 0 && $Board/TileMap.get_cell(mp.x-1, mp.y) < 0:
					$Board/CursorTileMap.set_cell(mp.x-1, mp.y, TILE_DST)
				if mp.x < N_HORZ - 1 && $Board/TileMap.get_cell(mp.x+1, mp.y) < 0:
					$Board/CursorTileMap.set_cell(mp.x+1, mp.y, TILE_DST)
				if mp.y == 0 || $Board/TileMap.get_cell(mp.x, mp.y-1) < 0:
					$Board/CursorTileMap.set_cell(mp.x, mp.y-1, TILE_DST)
		else:
			if $Board/CursorTileMap.get_cellv(mp) == TILE_DST:
				print("src = ", cursor, ", dst = ", mp)
				pass
			init_cursor()
