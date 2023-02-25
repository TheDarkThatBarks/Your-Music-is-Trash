#include "DownArrow.h"

DownArrow::DownArrow() {
	setSprite("down-arrow");
	setDir(DOWN);
	setPosition(df::Vector(30, 0));
}