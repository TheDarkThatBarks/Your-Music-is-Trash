#include "Boss.h"

Boss::Boss(std::string boss, int newSlowdown) {
	setPosition(df::Vector(60, 15));					//Boss3 looks good in (70, 15) so move from out of screen to this pos.
	setSprite(boss);
	getAnimation().getSprite()->setSlowdown(newSlowdown);
}