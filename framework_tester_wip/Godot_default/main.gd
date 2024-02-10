extends Node

var rect

# Called when the node enters the scene tree for the first time.
func _ready():
	DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_EXCLUSIVE_FULLSCREEN)
	DisplayServer.window_set_title("framework")
	rect = ColorRect.new()
	rect.color = Color(0, 0, 0, 1)
	rect.position = Vector2(0, 0)
	rect.size = Vector2(DisplayServer.screen_get_size().x, DisplayServer.screen_get_size().y)
	add_child(rect)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_LEFT:
			if event.pressed:
				rect.color = Color(1, 1, 1, 1)
			elif not event.pressed:
				rect.color = Color(0, 0, 0, 1) 
