#include "LeftArrow.h"

LeftArrow::LeftArrow(ArrowBox* b) {
	setSprite("left-arrow");
	//dir = LEFT;
	box = b;
	setPosition(df::Vector(10, 0));
}