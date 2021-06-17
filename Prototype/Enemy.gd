extends Label

signal display_health(curr)
signal player_damaged(p_dmg)
signal enemy_defeated

var health = 30
var damage = 7

func _ready():
	emit_signal("display_health", health)

func take_damage(dmg):
	health -= dmg
	if health <= 0:
		health = 0
		emit_signal("enemy_defeated")
		
	emit_signal("display_health", health)
	emit_signal("player_damaged", damage)

# if attack and enemy buttons pressed to deal
# damage to self, takes appropriate damage
func _on_Player_enemy1_damaged(e1_dmg):
	take_damage(e1_dmg)
