#include "ArrowBox.h"
#include "EventCollision.h"
#include "EventKeyboard.h"
#include "LogManager.h"
#include "WorldManager.h"

ArrowBox::ArrowBox(df::Vector pos, Direction d) {
	setType("ArrowBox");
	setSprite("arrow-box");
	setPosition(pos);

	topBig = getBox();
	//topBig.setCorner(df::Vector(pos.getX(), pos.getY() - 2));
	//printf("%f\n", topBig.getCorner().getY());
	//topBig.getCorner().setY(getBox().getCorner().getY() - 2);
	topBig.setCorner(df::Vector(getBox().getCorner().getX(), getBox().getCorner().getY() - 2));
	//printf("%f\n", topBig.getCorner().getY());
	topBig.setVertical(4);

	topSmall = getBox();
	//topSmall.setCorner(df::Vector(pos.getX(), pos.getY() - 1));
	topSmall.setCorner(df::Vector(getBox().getCorner().getX(), getBox().getCorner().getY() - 1));
	topSmall.setVertical(2);

	bottomBig = getBox();
	//bottomBig.setCorner(df::Vector(pos.getX(), pos.getY() + getBox().getVertical() - 2));
	bottomBig.setCorner(df::Vector(getBox().getCorner().getX(), getBox().getCorner().getY() + getBox().getVertical() - 2));
	bottomBig.setVertical(4);

	bottomSmall = getBox();
	//bottomSmall.setCorner(df::Vector(pos.getX(), pos.getY() + getBox().getVertical() - 1));
	bottomSmall.setCorner(df::Vector(getBox().getCorner().getX(), getBox().getCorner().getY() + getBox().getVertical() - 1));
	bottomSmall.setVertical(2);

	setAltitude(0);
	setSolidness(df::SOFT);
	dir = d;
	//registerInterest(df::COLLISION_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	//setBox(df::Box(pos, getBox().getHorizontal(), getBox().getVertical()));
	//printf("%f %f %f %f\n", getPosition().getX(), getPosition().getY(), topBig.getCorner().getX(), topBig.getCorner().getY());
	//printf("%f %f %f %f\n", getBox().getCorner().getX(), getBox().getCorner().getY(), getBox().getHorizontal(), getBox().getVertical());
}

void ArrowBox::addArrow(Arrow* arrow) {
	arrowQueue.push(arrow);
}

int ArrowBox::eventHandler(const df::Event* p_e) {
	/*if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c_e = dynamic_cast <const df::EventCollision*> (p_e);
		if (p_c_e->getObject1()->getType() == "Arrow") {
			arrow = dynamic_cast <Arrow*> (p_c_e->getObject1());
		} else if (p_c_e->getObject2()->getType() == "Arrow") {
			arrow = dynamic_cast <Arrow*> (p_c_e->getObject2());
		}
		//printf("%f %f %f %f\n", arrow->getBox().getCorner().getX(), arrow->getBox().getCorner().getY(), arrow->getBox().getVertical(), arrow->getBox().getHorizontal());
		return 0;
	} else */if (p_e->getType() == df::KEYBOARD_EVENT) {
		//puts("DEBUG");
		//LM.writeLog("DEBUG 1\n");
		const df::EventKeyboard* p_k_e = dynamic_cast <const df::EventKeyboard*> (p_e);
		df::Keyboard::Key key = p_k_e->getKey();
		if (p_k_e->getKeyboardAction() != df::KEY_PRESSED)
			return -1;
		if (arrowQueue.empty()) {
			printf("%i EMPTY\n", dir);
			return -1;
		}
		if ((dir == LEFT && key == df::Keyboard::LEFTARROW) ||
			(dir == UP && key == df::Keyboard::UPARROW) ||
			(dir == DOWN && key == df::Keyboard::DOWNARROW) ||
			(dir == RIGHT && key == df::Keyboard::RIGHTARROW)) {
			Arrow* arrow = arrowQueue.front();
			arrowQueue.pop();
			if (dir == LEFT) {
				puts("LEFT");
			} else if (dir == RIGHT) {
				puts("RIGHT");
			} else if (dir == UP) {
				puts("UP");
			} else if (dir == DOWN) {
				puts("DOWN");
			}
			std::string score = "MISS";
			//puts("DEBUG");
			/*if (df::boxIntersectsBox(arrow->getBox(), topBig))
				puts("COLLIDE");*/
			/*if (df::boxIntersectsBox(arrow->getBox(), topSmall) && df::boxIntersectsBox(arrow->getBox(), bottomSmall)) {
				//printf("%f %f %f %f\n", arrow->getBox().getCorner().getX(), arrow->getBox().getCorner().getY(), arrow->getBox().getHorizontal(), arrow->getBox().getVertical());
				//printf("%f %f %f %f\n", topSmall.getCorner().getX(), topSmall.getCorner().getY(), topSmall.getHorizontal(), topSmall.getVertical());
				//printf("%f %f %f %f\n", bottomSmall.getCorner().getX(), bottomSmall.getCorner().getY(), bottomSmall.getHorizontal(), bottomSmall.getVertical());
				score = "PERFECT";
			} else if (df::boxIntersectsBox(arrow->getBox(), topBig) && df::boxIntersectsBox(arrow->getBox(), bottomBig)) {
				score = "GOOD";
			}*/
			//printf("%f %f\n", getPosition().getY(), getPosition().getY() + getBox().getVertical());
			//printf("%f %f\n\n", arrow->getPosition().getY(), arrow->getPosition().getY() + arrow->getBox().getVertical());
			if (floatComp(">=", arrow->getPosition().getY(), getPosition().getY()) && floatComp("<=", arrow->getPosition().getY() + arrow->getBox().getVertical(), getPosition().getY() + getBox().getVertical())) {
				score = "PERFECT";
				//printf("%f %f\n", arrow->getPosition().getY(), getPosition().getY() + 1);
				//printf("%f %f\n", arrow->getPosition().getY() + arrow->getBox().getVertical(), getPosition().getY() + getBox().getVertical());
			} else if (floatComp(">=", arrow->getPosition().getY(), getPosition().getY() - 1) && floatComp("<=", arrow->getPosition().getY() + arrow->getBox().getVertical(), getPosition().getY() + getBox().getVertical() + 1)) {
				score = "GOOD";
			}
			WM.removeObject(arrow);
			printf("%f %f\n", getPosition().getY(), getPosition().getY() + getBox().getVertical());
			printf("%f %f\n", arrow->getPosition().getY(), arrow->getPosition().getY() + arrow->getBox().getVertical());
			printf("%s\n\n", score.c_str());
			return 0;
		}
	}
	return -1;
}

bool ArrowBox::floatComp(std::string comp, float f1, float f2) {
	const float EPSILON = (float) 0.0001;
	if (!comp.compare("=")) {
		return abs(f1 - f2) <= EPSILON;
	} else if (!comp.compare(">=")) {
		return f1 > f2 || floatComp("=", f1, f2);
	} else if (!comp.compare("<=")) {
		return f1 < f2 || floatComp("=", f1, f2);
	}
	return false;
}