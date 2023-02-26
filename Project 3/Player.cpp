#include "Player.h"


Player::Player() {
	setPosition(df::Vector(60,5));
	printf("%i\n", setSprite("player"));
}