#include "RightArrow.h"

RightArrow::RightArrow(ArrowBox* b) {
	setSprite("right-arrow");
	//dir = RIGHT;
	box = b;
	setPosition(df::Vector(40, 0));
}