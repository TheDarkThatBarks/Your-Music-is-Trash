#include "ArrowBox.h"
#include "EventCollision.h"
#include "EventKeyboard.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Combometer.h"
#include "EventView.h"

ArrowBox::ArrowBox(df::Vector pos, Direction d) {
	setType("ArrowBox");
	setSprite("arrow-box");
	setPosition(pos);

	topBig = getBox();
	topBig.setCorner(df::Vector(getBox().getCorner().getX(), getBox().getCorner().getY() - 2));
	topBig.setVertical(4);

	topSmall = getBox();
	topSmall.setCorner(df::Vector(getBox().getCorner().getX(), getBox().getCorner().getY() - 1));
	topSmall.setVertical(2);

	bottomBig = getBox();
	bottomBig.setCorner(df::Vector(getBox().getCorner().getX(), getBox().getCorner().getY() + getBox().getVertical() - 2));
	bottomBig.setVertical(4);

	bottomSmall = getBox();
	bottomSmall.setCorner(df::Vector(getBox().getCorner().getX(), getBox().getCorner().getY() + getBox().getVertical() - 1));
	bottomSmall.setVertical(2);

	setAltitude(0);
	setSolidness(df::SOFT);
	dir = d;
	registerInterest(df::KEYBOARD_EVENT);
}

void ArrowBox::addArrow(Arrow* arrow) {
	arrowQueue.push(arrow);
}

int ArrowBox::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_k_e = dynamic_cast <const df::EventKeyboard*> (p_e);
		df::Keyboard::Key key = p_k_e->getKey();
		if (p_k_e->getKeyboardAction() != df::KEY_PRESSED)
			return -1;
		if (arrowQueue.empty()) {
			printf("%i EMPTY\n", dir);
			return 0;
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
			/*if (df::boxIntersectsBox(arrow->getBox(), topSmall) && df::boxIntersectsBox(arrow->getBox(), bottomSmall)) {
				score = "PERFECT";
			} else if (df::boxIntersectsBox(arrow->getBox(), topBig) && df::boxIntersectsBox(arrow->getBox(), bottomBig)) {
				score = "GOOD";
			}*/
			if (floatComp(">=", arrow->getPosition().getY(), getPosition().getY()) && floatComp("<=", arrow->getPosition().getY() + arrow->getBox().getVertical(), getPosition().getY() + getBox().getVertical())) {
				score = "PERFECT";
				WM.onEvent(new df::EventView(COMBO_STRING, 2, true));
			} else if (floatComp(">=", arrow->getPosition().getY(), getPosition().getY() - 1) && floatComp("<=", arrow->getPosition().getY() + arrow->getBox().getVertical(), getPosition().getY() + getBox().getVertical() + 1)) {
				score = "GOOD";
				WM.onEvent(new df::EventView(COMBO_STRING, 1, true));
			} else {
				WM.onEvent(new df::EventView(COMBO_STRING, 0, false));
			}
			WM.removeObject(arrow);
			printf("%f %f\n", getPosition().getY(), getPosition().getY() + getBox().getVertical());
			printf("%f %f\n", arrow->getPosition().getY(), arrow->getPosition().getY() + arrow->getBox().getVertical());
			printf("%s\n\n", score.c_str());
			return 1;
		}
	}
	return 0;
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