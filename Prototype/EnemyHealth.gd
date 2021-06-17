extends Label

# https://godotengine.org/qa/50898/labels-and-set_text
func health_display(curr):
	self.text = str(curr)

func _on_Enemy_display_health(curr):
	health_display(curr)
