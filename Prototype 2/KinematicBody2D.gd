extends KinematicBody2D

# https://www.youtube.com/watch?v=IwduUYLC6UU
var speed = 80
var velocity = Vector2.ZERO

func _physics_process(delta):
	if Input.is_action_pressed("ui_right"):
		$PlayerAnimations.play("WalkRight")
		velocity.x = speed
	elif Input.is_action_pressed("ui_left"):
		$PlayerAnimations.play("WalkLeft")
		velocity.x = -speed
	else:
		if Input.is_action_just_released("ui_right"):
			$PlayerAnimations.play("IdleRight")
		elif Input.is_action_just_released("ui_left"):
			$PlayerAnimations.play("IdleLeft")
		velocity.x = 0
		
	if Input.is_action_pressed("ui_down"):
		$PlayerAnimations.play("WalkDown")
		velocity.y = speed
	elif Input.is_action_pressed("ui_up"):
		$PlayerAnimations.play("WalkUp")
		velocity.y = -speed
	else:
		if Input.is_action_just_released("ui_down"):
			$PlayerAnimations.play("IdleDown")
		elif Input.is_action_just_released("ui_up"):
			$PlayerAnimations.play("IdleUp")
		velocity.y = 0
		
# warning-ignore:return_value_discarded
	move_and_slide(velocity)




#func _on_Cyndaquil_area_entered(area):
	#if area.is_in_group("Player") && Input.is_action_pressed("ui_accept"):
	#	print(area.name)
