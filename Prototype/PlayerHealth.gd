extends Label

func health_display(curr):
	self.text = str(curr)

func _on_Player_display_health(curr):
	health_display(curr)
