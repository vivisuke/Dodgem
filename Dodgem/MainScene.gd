extends Node2D

enum {
	MODE_INIT = 0,
	MODE_RAND_HUMAN,
	MODE_RAND_RAND,
}
const N_HORZ = 3
const N_VERT = 3
const TILE_NONE = -1
const TILE_RED = 0
const TILE_BLUE = 1
const TILE_SRC = 0
const TILE_DST = 1

var mode = MODE_INIT
var last_mode = MODE_INIT
var nEpisode = 0
var nEpisodeRest = 0
var red_first = true		# 赤が先手
var dstcur_showed = false		# 移動先カーソル表示状態
var nMoved = 0				# 何手着手したか
var next = TILE_RED			# TILE_RED | TILE_BLUE
var nRed = 2				# 下側ピース個数
var nBlue = 2				# 左側ピース個数
var nRedWon = 0		# 赤勝利数
var nBlueWon = 0	# 青勝利数

var cursor = Vector2(-1, -1)
var rng = RandomNumberGenerator.new()

func _ready():
	rng.randomize()
	init_board()			# 盤面消去
	init_cursor()
func init_board():
	for y in range(N_VERT):
		for x in range(N_HORZ):
			$Board/TileMap.set_cell(x, y, TILE_NONE)
	for y in range(0, N_VERT-1):
		$Board/TileMap.set_cell(0, y, TILE_BLUE)
	for x in range(1, N_HORZ):
		$Board/TileMap.set_cell(x, 2, TILE_RED)
	nRed = N_HORZ - 1
	nBlue = N_VERT - 1
	nMoved = 0
func clear_stats():
	nRedWon = 0
	nBlueWon = 0
	nEpisode = 0
func update_stats_label():
	if nEpisode == 0:
		$OutputLabel.text = ""
	else:
		$OutputLabel.text = "Red won: %d (%.1f%%)\n" % [nRedWon, nRedWon*100.0/nEpisode]
		$OutputLabel.text += "Blue won: %d (%.1f%%)\n" % [nBlueWon, nBlueWon*100.0/nEpisode]
	pass
func init_cursor():
	dstcur_showed = false
	cursor = Vector2(-1, -1)
	for y in range(N_VERT+1):
		for x in range(N_HORZ):
			$Board/CursorTileMap.set_cell(x, y-1, TILE_NONE)

func _input(event):
	if event is InputEventMouseButton && event.is_pressed():
		#if next == TILE_BLUE: return
		if mode != MODE_RAND_HUMAN: return
		if( (red_first && (nMoved%2) != 0) ||
				(!red_first && (nMoved%2) != 1) ): return
		# mp := クリックされたタイルマップ座標
		var mp = $Board/TileMap.world_to_map($Board/TileMap.get_local_mouse_position())
		if( $Board/CursorTileMap.get_cellv(mp) != TILE_DST &&
			(mp.x < 0 || mp.x >= N_HORZ || mp.y < 0 || mp.y >= N_VERT) ):
				return		# 盤面外がクリックされた場合
		if $Board/TileMap.get_cellv(mp) == TILE_RED:	# 赤ピースがクリックされた場合
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
				dstcur_showed = true
		else:
			if $Board/CursorTileMap.get_cellv(mp) == TILE_DST:		# 移動先がクリックされた場合
				print("src = ", cursor, ", dst = ", mp)
				$Board/TileMap.set_cellv(cursor, TILE_NONE)		# 移動元
				if mp.y >= 0:		# 盤面内の場合
					$Board/TileMap.set_cellv(mp, TILE_RED)
				else:
					nRed -= 1
				#print("#blue = %d, #red = %d" % [nBlue, nRed])
				nMoved += 1
				if nRed == 0:
					$MessLabel.text = "赤の勝ちです。"
					nEpisode += 1
					nRedWon += 1
					update_stats_label()
					mode = MODE_INIT
					red_first = !red_first
				else:
					next = TILE_BLUE
			init_cursor()
func get_blue_moves() -> Array:
	var lst = []		# 着手（Vector2(移動元, 移動先)）配列
	for y in range(N_VERT):
		for x in range(N_HORZ):
			if $Board/TileMap.get_cell(x, y) == TILE_BLUE:
				if y > 0 && $Board/TileMap.get_cell(x, y-1) < 0:
					lst.push_back([Vector2(x, y), Vector2(x, y-1)])
				if y < N_VERT-1 && $Board/TileMap.get_cell(x, y+1) < 0:
					lst.push_back([Vector2(x, y), Vector2(x, y+1)])
				if x == N_HORZ-1 || $Board/TileMap.get_cell(x+1, y) < 0:
					lst.push_back([Vector2(x, y), Vector2(x+1, y)])
	return lst
func get_red_moves() -> Array:
	var lst = []		# 着手（Vector2(移動元, 移動先)）配列
	for y in range(N_VERT):
		for x in range(N_HORZ):
			if $Board/TileMap.get_cell(x, y) == TILE_RED:
				if x > 0 && $Board/TileMap.get_cell(x-1, y) < 0:
					lst.push_back([Vector2(x, y), Vector2(x-1, y)])
				if x < N_HORZ-1 && $Board/TileMap.get_cell(x+1, y) < 0:
					lst.push_back([Vector2(x, y), Vector2(x+1, y)])
				if y == 0 || $Board/TileMap.get_cell(x, y-1) < 0:
					lst.push_back([Vector2(x, y), Vector2(x, y-1)])
	return lst
func gameOver(won):
	nEpisode += 1
	if won == TILE_BLUE:
		$MessLabel.text = "#%d: 青の勝ちです。" % nEpisode
		nBlueWon += 1
	else:
		$MessLabel.text = "#%d: 赤の勝ちです。" % nEpisode
		nRedWon += 1
	update_stats_label()
	red_first = !red_first
func moveRandom(nx) -> bool:		# nx: TILE_BLUE or TILE_RED, return: ゲーム終了？
	var mvs = get_blue_moves() if nx == TILE_BLUE else get_red_moves()
	if mvs.empty():
		print(("red" if nx == TILE_RED else "blue"), " can't move")
		gameOver(nx)	# 着手不可の場合は、その手番の勝ち
		return true
	var mv : Array	# 
	if mvs.size() == 1: mv = mvs[0]
	else:
		mv = mvs[rng.randi_range(0, mvs.size() - 1)]
	$Board/TileMap.set_cellv(mv[0], TILE_NONE)		# 移動元消去
	if mv[1].x < N_HORZ && mv[1].y >= 0:		# 盤面内の場合
		$Board/TileMap.set_cellv(mv[1], nx)			# 移動先にピース設置
	else:		# 盤面外に移動した場合
		if nx == TILE_BLUE:
			nBlue -= 1
		else:
			nRed -= 1
	#print("#blue = %d, #red = %d" % [nBlue, nRed])
	nMoved += 1
	if nBlue == 0 || nRed == 0:
		gameOver(TILE_BLUE if nBlue == 0 else TILE_RED)
		return true;		# 終局
	else:
		return false;
func _process(delta):
	if mode == MODE_RAND_HUMAN:
		if next == TILE_BLUE:
			$MessLabel.text = ""
			var go = moveRandom(TILE_BLUE)
			if go:
				mode = MODE_INIT
			else:
				next = TILE_RED
		else:
			if !dstcur_showed:
				$MessLabel.text = "移動元をクリックしてください。"
			else:
				$MessLabel.text = "移動先をクリックしてください。"
	elif mode == MODE_RAND_RAND:
		init_board()
		while true:
			var go = moveRandom(next)
			if go:
				nEpisodeRest -= 1
				if nEpisodeRest <= 0:
					mode = MODE_INIT
				else:
					#init_board()
					next = TILE_RED		# 常に赤が先手
				break
			else:
				next = (TILE_BLUE + TILE_RED) - next

func _on_RxHUM_Button_pressed():
	if mode == MODE_RAND_HUMAN: return
	if last_mode != MODE_RAND_HUMAN:
		clear_stats()
		update_stats_label()
	mode = MODE_RAND_HUMAN
	last_mode = MODE_RAND_HUMAN
	init_board()
	next = TILE_RED if red_first else TILE_BLUE
	pass

func _on_RxRx100_Button_pressed():
	nEpisodeRest = 100
	nEpisode = 0
	clear_stats()
	mode = MODE_RAND_RAND
	last_mode = MODE_RAND_RAND
	init_board()
	next = TILE_RED		# 常に赤先手
	pass

func _on_RxRx1000_Button_pressed():
	nEpisodeRest = 1000
	nEpisode = 0
	clear_stats()
	mode = MODE_RAND_RAND
	last_mode = MODE_RAND_RAND
	init_board()
	next = TILE_RED		# 常に赤先手
	pass
