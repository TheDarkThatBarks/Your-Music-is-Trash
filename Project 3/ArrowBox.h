#pragma once

#include <queue>
#include "Object.h"
#include "Event.h"
#include "Arrow.h"

class ArrowBox : public df::Object {
	private:
	Direction dir;
	df::Box topBig;
	df::Box topSmall;
	df::Box bottomBig;
	df::Box bottomSmall;
	std::queue<Arrow*> arrowQueue;
	bool floatComp(std::string comp, float f1, float f2);

	public:
	ArrowBox() {};
	ArrowBox(df::Vector pos, Direction d);
	void addArrow(Arrow* arrow);
	int eventHandler(const df::Event* p_e) override;
};