#pragma once

#include <queue>
#include "Object.h"
#include "Event.h"

class Arrow;

enum Direction {
	LEFT,
	UP,
	DOWN,
	RIGHT
};

class ArrowBox : public df::Object {
	private:
	Direction dir;
	df::Box topBig;
	df::Box topSmall;
	df::Box bottomBig;
	df::Box bottomSmall;
	std::queue<Arrow*> arrowQueue;

	public:
	ArrowBox() {};
	ArrowBox(df::Vector pos, Direction d);
	void addArrow(Arrow* arrow);
	Arrow* popArrow();
	int eventHandler(const df::Event* p_e) override;
};

class Arrow : public df::Object {
	protected:
	ArrowBox* box;

	public:
	Arrow();
	int eventHandler(const df::Event* p_e) override;
};