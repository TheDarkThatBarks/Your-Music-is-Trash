#include "ArrowBox.h"
#include "EventCollision.h"

ArrowBox::ArrowBox(df::Vector pos) {
	setType("ArrowBox");
	setSprite("arrow-box.sprite");
	setPosition(pos);
	topBig = getBox();
	topBig.setCorner(df::Vector(pos.getX(), pos.getY() - 2));
	topBig.setVertical(4);
	topSmall = getBox();
	topSmall.setCorner(df::Vector(pos.getX(), pos.getY() - 1));
	topSmall.setVertical(2);
	bottomBig = getBox();
	bottomBig.setCorner(df::Vector(pos.getX(), pos.getY() + getBox().getVertical() - 2));
	bottomBig.setVertical(4);
	bottomBig.setCorner(df::Vector(pos.getX(), pos.getY() + getBox().getVertical() - 1));
	bottomBig.setVertical(2);
	setAltitude(0);
	setSolidness(df::SOFT);
}

int ArrowBox::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c_e = dynamic_cast <const df::EventCollision*> (p_e);
		return 0;
	}
	return -1;
}