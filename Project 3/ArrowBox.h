#pragma once

#include <queue>
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Event.h"
#include "Object.h"
#include "Sound.h"

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
	df::Sound* correct;
	df::Sound* miss;

	public:
	ArrowBox() {};
	ArrowBox(df::Vector pos, Direction d);
	void addArrow(Arrow* arrow);
	Arrow* popArrow();
	int eventHandler(const df::Event* p_e) override;
};

class Arrow : public df::Object {
	private:
	df::Sound* miss;

	protected:
	ArrowBox* box;

	public:
	Arrow();
	int eventHandler(const df::Event* p_e) override;
};