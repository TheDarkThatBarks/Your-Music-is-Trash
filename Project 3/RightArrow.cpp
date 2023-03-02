#include "RightArrow.h"

RightArrow::RightArrow(ArrowBox* b) {
	setSprite("right-arrow");
	box = b;
	setPosition(df::Vector(40, 0));
}