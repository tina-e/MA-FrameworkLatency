extends Node

var screenW = DisplayServer.screen_get_size().x
var screenH = DisplayServer.screen_get_size().y

# Called when the node enters the scene tree for the first time.
func _ready():
	DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_EXCLUSIVE_FULLSCREEN)
	

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
	for i in range(999):
		var rect = ColorRect.new()
		rect.color = Color(randf(), randf(), randf(), 1)
		var x = randi_range(screenW / 2, screenW)
		var y = randi_range(0, screenH)
		rect.position = Vector2(x, y)
		var w = randi_range(1, screenW - x)
		var h = randi_range(1, screenH - y)
		rect.size = Vector2(w, h)
		add_child(rect)
	var rect = ColorRect.new()
	rect.color = Color(1, 1, 1, 1)
	rect.position = Vector2(0, 0)
	rect.size = Vector2(300, 300)
	add_child(rect)

		
func clear_rects():
	for child in get_children(): remove_child(child) 
	
