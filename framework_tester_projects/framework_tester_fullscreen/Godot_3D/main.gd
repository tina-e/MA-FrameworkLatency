extends Node3D

const NUM_CUBES = 166
var screenW = DisplayServer.screen_get_size().x
var screenH = DisplayServer.screen_get_size().y
var rotations_x = []
var rotations_y = []
var rotations_z = []
var is_pressed = false
var template


# Called when the node enters the scene tree for the first time.
func _ready():
	DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_EXCLUSIVE_FULLSCREEN)
	DisplayServer.window_set_title("framework")
	template = $MeshInstance3D.duplicate()
	remove_child($MeshInstance3D)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	if is_pressed:
		var index = 0
		for child in get_children():
			if child is MeshInstance3D:
				child.rotation_degrees += Vector3(rotations_x[index], rotations_y[index], rotations_z[index])
				index += 1
				

func _input(event):
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_LEFT:
			if event.pressed:
				create_cubes()
				is_pressed = true
			elif not event.pressed:
				is_pressed = false
				clear_cubes()
				

func create_cubes():
	for i in range(NUM_CUBES):
		rotations_x.append(randf() / 10)
		rotations_y.append(randf() / 10)
		rotations_z.append(randf() / 10)
		var cube = template.duplicate()
		var material = cube.get_surface_override_material(0).duplicate()
		material.flags_unshaded = true
		material.albedo_color = Color(randf(), randf(), randf(), 1)
		cube.set_surface_override_material(0, material)
		cube.scale = Vector3(randf() / 5, randf() / 5, randf() / 5)
		cube.rotation_degrees = Vector3(randi_range(0, 360), randi_range(0, 360), randi_range(0, 360))
		cube.position = Vector3(randf_range(-0.6, 0.8), randf_range(-0.8, 0.8), randf_range(-1, 1))
		add_child(cube)
	var rect = ColorRect.new()
	rect.color = Color(1, 1, 1, 1)
	rect.position = Vector2(0, 0)
	rect.size = Vector2(200, 200)
	add_child(rect)

		
func clear_cubes():
	rotations_x = []
	rotations_y = []
	rotations_z = []
	for child in get_children():
		if child is MeshInstance3D or child is ColorRect:
			remove_child(child)
