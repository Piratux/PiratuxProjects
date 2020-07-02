extends Control

onready var p = get_node("Panel")
var inside = false

func mouse_inside():
	if get_global_mouse_position().x > p.margin_left and p.get_global_mouse_position().x < p.margin_right:
		if get_global_mouse_position().y > p.margin_top and p.get_global_mouse_position().y < p.margin_bottom:
			return true

func _on_Panel_mouse_entered():
	if not inside:
		inside = true
		print("entered")

func _on_Panel_mouse_exited():
	if not mouse_inside():
		inside = false
		print("exited")
