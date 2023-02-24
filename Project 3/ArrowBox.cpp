#include "ArrowBox.h"
#include "EventCollision.h"
#include "EventKeyboard.h"
#include "LogManager.h"

ArrowBox::ArrowBox(df::Vector pos, Direction d) {
	setType("ArrowBox");
	setSprite("arrow-box");
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
	dir = d;
	arrow = NULL;
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	//setBox(df::Box(pos, getBox().getHorizontal(), getBox().getVertical()));
	printf("%f %f %f %f\n", pos.getX(), pos.getY(), topBig.getCorner().getX(), topBig.getCorner().getY());
	printf("%f %f %f %f\n", getBox().getCorner().getX(), getBox().getCorner().getY(), getBox().getVertical(), getBox().getHorizontal());
}

int ArrowBox::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c_e = dynamic_cast <const df::EventCollision*> (p_e);
		if (p_c_e->getObject1()->getType() == "Arrow") {
			arrow = dynamic_cast <Arrow*> (p_c_e->getObject1());
		} else if (p_c_e->getObject2()->getType() == "Arrow") {
			arrow = dynamic_cast <Arrow*> (p_c_e->getObject2());
		}
		printf("%f %f %f %f\n", arrow->getBox().getCorner().getX(), arrow->getBox().getCorner().getY(), arrow->getBox().getVertical(), arrow->getBox().getHorizontal());
		return 0;
	} else if (p_e->getType() == df::KEYBOARD_EVENT) {
		//puts("DEBUG");
		//LM.writeLog("DEBUG 1\n");
		const df::EventKeyboard* p_k_e = dynamic_cast <const df::EventKeyboard*> (p_e);
		df::Keyboard::Key key = p_k_e->getKey();
		std::string score = "";
		if (arrow == NULL)
			return -1;
		if (dir == DOWN && key == df::Keyboard::DOWNARROW) {
			//LM.writeLog("DEBUG 2\n");
			if (df::boxIntersectsBox(arrow->getBox(), topSmall) && df::boxIntersectsBox(arrow->getBox(), bottomSmall)) {
				score = "PERFECT";
			} else if (df::boxIntersectsBox(arrow->getBox(), topBig) && df::boxIntersectsBox(arrow->getBox(), bottomBig)) {
				score = "GOOD";
			}
		}
		printf("%s\n", score.c_str());
		return 0;
	}
	return -1;
}