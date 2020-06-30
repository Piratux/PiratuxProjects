extends Label

onready var margin = get_node("../..")

func _on_TextEdit_text_changed():
	text = $TextEdit.text
	if get_line_count() == 1:
		margin.set_h_size_flags(SIZE_SHRINK_CENTER)
		autowrap = false
	if get_parent().rect_size.x > 300:
		margin.set_h_size_flags(SIZE_FILL)
		autowrap = true
