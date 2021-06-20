extends Area2D

# this doesn't work
func _process(_delta):
	if Input.is_action_pressed("ui_accept") && overlaps_body($Player):
		print("Hi!")

# no result!
# works without the button pressed
func _on_Cyndaquil_body_entered(body):
	if body.is_in_group("Player"):# && Input.is_action_pressed("ui_accept"):
		print(body.name)
