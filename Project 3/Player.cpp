#include "Player.h"

Player::Player(int newSlowdown) {
	setPosition(df::Vector(60,5));
	setSprite("player");
	getAnimation().getSprite()->setSlowdown(newSlowdown);
}