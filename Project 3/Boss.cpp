#include "Boss.h"

Boss::Boss(std::string boss, int newSlowdown) {
	setSprite(boss);
	getAnimation().getSprite()->setSlowdown(newSlowdown);
}