#include "DownArrow.h"

DownArrow::DownArrow(ArrowBox* b) {
	setSprite("down-arrow");
	//dir = DOWN;
	box = b;
	setPosition(df::Vector(30, 0));
}