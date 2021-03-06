extends ColorRect

const CELL_WIDTH = 96
const LINE_WIDTH = 4.0

var font = DynamicFont.new()

func _ready():
	var font_data:DynamicFontData = preload("res://fonts/arialbd.ttf")
	font.font_data = font_data
	font.size = 40
	pass # Replace with function body.

func _draw():
	draw_line(Vector2(0, 96), Vector2(288, 96), Color.black, LINE_WIDTH)
	draw_line(Vector2(0, 192), Vector2(288, 192), Color.black, LINE_WIDTH)
	draw_line(Vector2(96, 0), Vector2(96, 288), Color.black, LINE_WIDTH)
	draw_line(Vector2(192, 0), Vector2(192, 288), Color.black, LINE_WIDTH)
	
	#var label = Label.new()
	#var font = label.get_font("")
	#var font = Control.new().get_font("font")
	#var ctrl = Control.new()
	#ctrl.add_font_override("height", 64)
	#var font = ctrl.get_font("font")
	#draw_string(font, Vector2(0,0), "a")
	
	for y in range(3):
		var pos = Vector2(-CELL_WIDTH*0.4, CELL_WIDTH*(y+0.65))
		draw_string(font, pos, "%d" % (y+1))
	for x in range(3):
		var pos = Vector2(CELL_WIDTH*(x+0.35), -CELL_WIDTH*0.15)
		draw_string(font, pos, "abc"[x])
