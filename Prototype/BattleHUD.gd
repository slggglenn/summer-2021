extends CanvasLayer

# Called when the node enters the scene tree for the first time.
func _ready():
	hide_enemy_buttons()
	$WAIT.hide()

func hide_enemy_buttons():
	$ENEMY1.hide()
	$ENEMY2.hide()
	$ENEMY3.hide()
	$ENEMY4.hide()

func hide_atk_buttons():
	$ATK1.hide()
	$ATK2.hide()
	$ATK3.hide()
	$ATK4.hide()
	
func show_enemy_buttons():
	$ENEMY1.show()
	$ENEMY2.show()
	$ENEMY3.show()
	$ENEMY4.show()

func show_atk_buttons():
	$ATK1.show()
	$ATK2.show()
	$ATK3.show()
	$ATK4.show()

func pick_enemy_setup():
	hide_atk_buttons()
	show_enemy_buttons()

func _on_ATK1_pressed():
	pick_enemy_setup()

func _on_ENEMY1_pressed():
	hide_enemy_buttons()
	$WAIT.show()
	yield($Enemy, "player_damaged")
	$WAIT.hide()
	show_atk_buttons()

func _on_ATK2_pressed():
	pick_enemy_setup()

func _on_ATK3_pressed():
	pick_enemy_setup()

func _on_ATK4_pressed():
	pick_enemy_setup()


func _on_Player_player_defeated():
	$OUTCOME.text = "ENEMY VICTORY"


func _on_Enemy_enemy_defeated():
	$OUTCOME.text = "PLAYER VICTORY"
