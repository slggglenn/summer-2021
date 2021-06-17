extends Label

signal display_health(curr)
signal enemy1_damaged(e1_dmg)
signal player_defeated

var health = 30
var damage = 0

func _ready():
	emit_signal("display_health", health)

func take_damage(dmg):
	health -= dmg
	if health <= 0:
		health = 0
		emit_signal("player_defeated")
		
	emit_signal("display_health", health)

# records amount of damage to deal on turn
# depending on ATK button pressed

#??ways to consolidate??
func _on_ATK1_pressed():
	damage = 10
	
func _on_ATK2_pressed():
	damage = 5

func _on_ATK3_pressed():
	damage = 0

func _on_ATK4_pressed():
	damage = 8

# deals damage on given enemy
func _on_ENEMY1_pressed():
	emit_signal("enemy1_damaged", damage)

func _on_Enemy_player_damaged(p_dmg):
	take_damage(p_dmg)
