extends Panel

var inside = false

func mouse_inside():
	var mpos = get_global_mouse_position()
	var rectpos = rect_global_position
	if mpos.x > rectpos.x and mpos.x < rectpos.x + rect_size.x:
		if mpos.y > rectpos.y and mpos.y < rectpos.y + rect_size.y:
			return true

func _on_Control_mouse_entered() -> void:
	if not inside:
		$AnimationPlayer.play("Popup")
		inside = true
		print("entered")

func _on_Control_mouse_exited() -> void:
	if not mouse_inside():
		$AnimationPlayer.play_backwards("Popup")
		inside = false
		print("exited")
