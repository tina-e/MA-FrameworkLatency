extends Node

var screenW = DisplayServer.screen_get_size().x
var screenH = DisplayServer.screen_get_size().y

# Called when the node enters the scene tree for the first time.
func _ready():
	DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_EXCLUSIVE_FULLSCREEN)
	DisplayServer.window_set_title("framework")
	# Create a new MeshInstance node
	var cube_instance = MeshInstance3D.new()
	
	# Create a new CubeMesh
	var cube_mesh = BoxMesh.new()
	
	# Set the mesh of the MeshInstance to the CubeMesh
	cube_instance.mesh = cube_mesh
	
	# Add the MeshInstance node as a child of this node
	add_child(cube_instance)
	

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
	var cube = CSGBox3D.new()
	add_child(cube)
	#for i in range(9):
		#var cube = MeshInstance3D.new()
		#var cube_mesh = BoxMesh.new()
		#cube.mesh = cube_mesh
		#cube.material_override = StandardMaterial3D.new()
		#cube.material_override.albedo_color = Color(randf(), randf(), randf(), 1)
		#var x = randi_range(screenW / 2, screenW)
		#var y = randi_range(0, screenH)
		#var z = randi_range(0, 10) # Adjust the range for the cube's z-coordinate
		#cube.transform.origin = Vector3(x, y, z)
		#var size = randi_range(10, 50) # Adjust the range for the cube's size
		##cube.transform.basis.scale(Vector3(size, size, size))
		#add_child(cube)
	#var cube = MeshInstance3D.new()
	#var cube_mesh = BoxMesh.new()
	#cube.mesh = cube_mesh
	#cube.material_override = StandardMaterial3D.new()
	#cube.material_override.albedo_color = Color(1, 1, 1, 1)
	#cube.translation = Vector3(0, 0, 0)
	#cube.scale = Vector3(300, 300, 300) # Adjust the size of the main cube
	#add_child(cube)

		
func clear_rects():
	for child in get_children(): remove_child(child) 
	

