#include "UpArrow.h"

UpArrow::UpArrow(ArrowBox* b) {
	setSprite("up-arrow");
	box = b;
	setPosition(df::Vector(20, 0));
}