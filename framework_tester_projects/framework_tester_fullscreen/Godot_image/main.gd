extends Node

var screenW = DisplayServer.screen_get_size().x
var screenH = DisplayServer.screen_get_size().y
var image_texture = preload("res://noise.png").duplicate()

# Called when the node enters the scene tree for the first time.
func _ready():
	DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_EXCLUSIVE_FULLSCREEN)
	DisplayServer.window_set_title("framework")
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
	
func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_LEFT:
			if event.pressed:
				create_rects()
			elif not event.pressed:
				clear_rects()
				
				
func create_rects():
	var texture_rect = TextureRect.new()
	texture_rect.texture = image_texture
	add_child(texture_rect)

		
func clear_rects():
	for child in get_children(): remove_child(child) 
	
