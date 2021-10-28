extends Node2D

const N_HORZ = 3
const N_VERT = 3
const TILE_NONE = -1
const TILE_RED = 0
const TILE_BLUE = 1
const TILE_SRC = 0
const TILE_DST = 1

var next = TILE_RED			# TILE_RED | TILE_BLUE
var cursor = Vector2(-1, -1)
var rng = RandomNumberGenerator.new()

func _ready():
	init_cursor()
	
func init_cursor():
	cursor = Vector2(-1, -1)
	for y in range(N_VERT+1):
		for x in range(N_HORZ):
			$Board/CursorTileMap.set_cell(x, y-1, TILE_NONE)

func _input(event):
	if event is InputEventMouseButton && event.is_pressed():
		if next == TILE_BLUE: return
		var mp = $Board/TileMap.world_to_map($Board/TileMap.get_local_mouse_position())
		if( $Board/CursorTileMap.get_cellv(mp) != TILE_DST &&
			(mp.x < 0 || mp.x >= N_HORZ || mp.y < 0 || mp.y >= N_VERT) ):
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
				if mp.x < N_HORZ-1 && $Board/TileMap.get_cell(mp.x+1, mp.y) < 0:
					$Board/CursorTileMap.set_cell(mp.x+1, mp.y, TILE_DST)
				if mp.y == 0 || $Board/TileMap.get_cell(mp.x, mp.y-1) < 0:
					$Board/CursorTileMap.set_cell(mp.x, mp.y-1, TILE_DST)
		else:
			if $Board/CursorTileMap.get_cellv(mp) == TILE_DST:
				print("src = ", cursor, ", dst = ", mp)
				$Board/TileMap.set_cellv(cursor, TILE_NONE)
				if mp.y >= 0:
					$Board/TileMap.set_cellv(mp, TILE_RED)
				next = TILE_BLUE
				pass
			init_cursor()

func moveBlueRandom():
	var lst = []
	for y in range(N_VERT+1):
		for x in range(N_HORZ):
			if $Board/TileMap.get_cell(x, y) == TILE_BLUE:
				if y > 0 && $Board/TileMap.get_cell(x, y-1) < 0:
					lst.push_back([Vector2(x, y), Vector2(x, y-1)])
				if y < N_VERT-1 && $Board/TileMap.get_cell(x, y+1) < 0:
					lst.push_back([Vector2(x, y), Vector2(x, y+1)])
				if x == N_HORZ-1 || $Board/TileMap.get_cell(x+1, y) < 0:
					lst.push_back([Vector2(x, y), Vector2(x+1, y)])
	if lst.empty():
		return			# BLUE won
	var mv
	if lst.size() == 1: mv = lst[0]
	else:
		mv = lst[rng.randi_range(0, lst.size() - 1)]
	$Board/TileMap.set_cellv(mv[0], TILE_NONE)
	if mv[1][1] < N_HORZ:
		$Board/TileMap.set_cellv(mv[1], TILE_BLUE)
func _process(delta):
	if next == TILE_BLUE:
		moveBlueRandom()
		next = TILE_RED
