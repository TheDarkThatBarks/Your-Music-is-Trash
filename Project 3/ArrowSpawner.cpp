#include <fstream>
#include "ArrowSpawner.h"
#include "EventStep.h"
#include "LeftArrow.h"
#include "RightArrow.h"
#include "UpArrow.h"
#include "DownArrow.h"

ArrowSpawner::ArrowSpawner(ArrowBox* u, ArrowBox* d, ArrowBox* l, ArrowBox* r, std::string songFile) {
	setType("ArrowSpawner");
	up = u;
	down = d;
	left = l;
	right = r;
	beatsPerSecond = 0;
	std::ifstream song(songFile);
	if (song.is_open()) {
		std::string line;
		getline(song, line);
		int bpm = stoi(line);
		beatsPerSecond = bpm / 60;
		while (song) {
			getline(song, line);
			std::vector<Direction> arrowsOnBeat;
			bool w = false;
			bool s = false;
			bool a = false;
			bool d = false;
			for (int i = 0; i < line.length(); i++) {
				char c = line.at(i);
				if (c == 'W' && !w) {
					arrowsOnBeat.push_back(UP);
					w = true;
				} else if (c == 'S' && !s) {
					arrowsOnBeat.push_back(DOWN);
					s = true;
				} else if (c == 'A' && !a) {
					arrowsOnBeat.push_back(LEFT);
					a = true;
				} else if (c == 'D' && !d) {
					arrowsOnBeat.push_back(RIGHT);
					d = true;
				}
			}
			arrows.push(arrowsOnBeat);
		}
	}
	std::queue<std::vector<Direction>> q = arrows;
	while (!q.empty()) {
		std::vector<Direction> list = q.front();
		for (int i = 0; i < list.size(); i++) {
			switch (list.at(i)) {
				case LEFT:
					printf("LEFT ");
					break;
				case UP:
					printf("UP ");
					break;
				case DOWN:
					printf("DOWN ");
					break;
				case RIGHT:
					printf("RIGHT ");
					break;
			}
		}
		printf("\n");
		q.pop();
	}
	registerInterest(df::STEP_EVENT);
}

int ArrowSpawner::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_s_e = dynamic_cast <const df::EventStep*> (p_e);
		if (p_s_e->getStepCount() % (30 / beatsPerSecond) == 0) {
			if (arrows.empty())
				return -1;
			std::vector<Direction> arrowList = arrows.front();
			arrows.pop();
			for (int i = 0; i < arrowList.size(); i++) {
				switch (arrowList.at(i)) {
					case LEFT:
						left->addArrow(new LeftArrow());
						break;
					case UP:
						up->addArrow(new UpArrow());
						break;
					case DOWN:
						down->addArrow(new DownArrow());
						break;
					case RIGHT:
						right->addArrow(new RightArrow());
						break;
				}
			}
			return 0;
		}
	}
	return -1;
}