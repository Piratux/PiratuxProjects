extends Node2D

var expression = Expression.new()

var dict = {
	"car": 5
}

func _ready():
	var arg = []
	arg.push_back("test")
	var a = "test"
	parse('print("%s")' % str(arg))

func parse(command: String):
	var error : int = expression.parse(command, [])
	if error != OK:
		printerr(expression.get_error_text())
		return null
	
	var result = expression.execute([], null, true)
	if expression.has_execute_failed():
		printerr("Expression execution failed for command '%s'" % command)
	
	return result
