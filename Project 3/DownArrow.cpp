#include "DownArrow.h"

DownArrow::DownArrow(ArrowBox* b) {
	setSprite("down-arrow");
	box = b;
	setPosition(df::Vector(30, 0));
}