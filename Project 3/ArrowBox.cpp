#include "ArrowBox.h"
#include "EventCollision.h"
#include "EventKeyboard.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "Combometer.h"
#include "EventView.h"
#include "DisplayManager.h"

ArrowBox::ArrowBox(df::Vector pos, Direction d) {
	setType("ArrowBox");
	setSprite("arrow-box");
	setPosition(pos);

	// Sets extra collision boxes above and below the arrow box
	df::Box box = df::getWorldBox(this);
	topBig = box;
	topBig.setCorner(df::Vector(box.getCorner().getX(), box.getCorner().getY() - 2));
	topBig.setVertical(4);

	topSmall = box;
	topSmall.setCorner(df::Vector(box.getCorner().getX(), box.getCorner().getY() - 1));
	topSmall.setVertical(2);

	bottomBig = box;
	bottomBig.setCorner(df::Vector(box.getCorner().getX(), box.getCorner().getY() + box.getVertical() - 2));
	bottomBig.setVertical(4);

	bottomSmall = box;
	bottomSmall.setCorner(df::Vector(box.getCorner().getX(), box.getCorner().getY() + box.getVertical() - 1));
	bottomSmall.setVertical(2);

	setAltitude(0);
	setSolidness(df::SOFT);
	dir = d;
	registerInterest(df::KEYBOARD_EVENT);
}

void ArrowBox::addArrow(Arrow* arrow) {
	arrowQueue.push(arrow);
}

Arrow* ArrowBox::popArrow() {
	if (arrowQueue.empty())
		return NULL;
	Arrow* arrow = arrowQueue.front();
	arrowQueue.pop();
	return arrow;
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

		// If key press matches arrow
		if ((dir == LEFT && key == df::Keyboard::LEFTARROW) ||
			(dir == UP && key == df::Keyboard::UPARROW) ||
			(dir == DOWN && key == df::Keyboard::DOWNARROW) ||
			(dir == RIGHT && key == df::Keyboard::RIGHTARROW)) {
			Arrow* arrow = popArrow();
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

			// Checks if arrow meets PERFECT or GOOD criteria and updates the combOmeter(TM)

			df::Box arrowBox = df::getWorldBox(arrow);
			printf("%f %f %f %f\n", arrowBox.getCorner().getX(), arrowBox.getCorner().getY(), arrowBox.getHorizontal(), arrowBox.getVertical());
			printf("%f %f %f %f\n", topSmall.getCorner().getX(), topSmall.getCorner().getY(), topSmall.getHorizontal(), topSmall.getVertical());
			printf("%f %f %f %f\n", topBig.getCorner().getX(), topBig.getCorner().getY(), topBig.getHorizontal(), topBig.getVertical());
			if (df::boxIntersectsBox(arrowBox, topSmall) && df::boxIntersectsBox(arrowBox, bottomSmall)) {
				score = "PERFECT";
				WM.onEvent(new df::EventView(COMBO_STRING, 2, true));
				DM.shake(1, 1, 10, false);
				//DM.
			} else if (df::boxIntersectsBox(arrowBox, topBig) && df::boxIntersectsBox(arrowBox, bottomBig)) {
				score = "GOOD";
				WM.onEvent(new df::EventView(COMBO_STRING, 1, true));
			} else {
				WM.onEvent(new df::EventView(COMBO_STRING, 0, false));
			}
			WM.markForDelete(arrow);
			printf("%f %f\n", getPosition().getY(), getPosition().getY() + getBox().getVertical());
			printf("%f %f\n", arrow->getPosition().getY(), arrow->getPosition().getY() + arrow->getBox().getVertical());
			printf("%s\n\n", score.c_str());
			return 1;
		}
	}
	return 0;
}