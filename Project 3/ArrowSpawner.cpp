#include <fstream>
#include "ArrowSpawner.h"
#include "EventStep.h"
#include "LeftArrow.h"
#include "RightArrow.h"
#include "UpArrow.h"
#include "DownArrow.h"
#include "GameManager.h"
#include "EventKeyboard.h"

int ArrowSpawner::beatsPerSecond;
Combometer* ArrowSpawner::combo;
CombometerMax* ArrowSpawner::comboMax;
GameStart* ArrowSpawner::gameStart;

ArrowSpawner::ArrowSpawner(ArrowBox* l, ArrowBox* u, ArrowBox* d, ArrowBox* r, std::string songFile) {
	setType("ArrowSpawner");
	left = l;
	up = u;
	down = d;
	right = r;
	beatsPerSecond = 0;
	
	// Reads song beats file
	std::ifstream song(songFile);
	if (song.is_open()) {
		std::string line;
		getline(song, line);
		int bpm = stoi(line);
		beatsPerSecond = bpm / 60;
		while (song) {
			getline(song, line);

			// Adds only one of each arrow to each beat
			std::vector<Direction> arrowsOnBeat;
			bool w = false;
			bool s = false;
			bool a = false;
			bool d = false;
			for (int i = 0; i < line.length(); i++) {
				char c = line.at(i);
				if ((c == 'W' || c == 'w') && !w) {
					arrowsOnBeat.push_back(UP);
					w = true;
				} else if ((c == 'S' || c == 's') && !s) {
					arrowsOnBeat.push_back(DOWN);
					s = true;
				} else if ((c == 'A' || c == 'a') && !a) {
					arrowsOnBeat.push_back(LEFT);
					a = true;
				} else if ((c == 'D' || c == 'd') && !d) {
					arrowsOnBeat.push_back(RIGHT);
					d = true;
				}
			}
			arrows.push(arrowsOnBeat);
		}
	}

	// Prints arrows on each beat to terminal
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
	registerInterest(df::KEYBOARD_EVENT);
}

int ArrowSpawner::getBeatsPerSecond() {
	return beatsPerSecond;
}

Combometer* ArrowSpawner::getCombo() {
	return combo;
}

void ArrowSpawner::setCombo(Combometer* newCombo) {
	combo = newCombo;
}

CombometerMax* ArrowSpawner::getComboMax() {
	return comboMax;
}

void ArrowSpawner::setComboMax(CombometerMax* newCombo) {
	comboMax = newCombo;
}

void ArrowSpawner::setGameStart(GameStart* newGameStart) {
	gameStart = newGameStart;
}

int ArrowSpawner::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_s_e = dynamic_cast <const df::EventStep*> (p_e);
		if (p_s_e->getStepCount() % ((int)(1000.0 / GM.getFrameTime()) / beatsPerSecond) == 0) {
			if (arrows.empty())
				return -1;
			std::vector<Direction> arrowList = arrows.front();
			arrows.pop();

			// Sends out the arrows for each beat to the respective boxes
			for (int i = 0; i < arrowList.size(); i++) {
				switch (arrowList.at(i)) {
					case LEFT:
						left->addArrow(new LeftArrow(left));
						break;
					case UP:
						up->addArrow(new UpArrow(up));
						break;
					case DOWN:
						down->addArrow(new DownArrow(down));
						break;
					case RIGHT:
						right->addArrow(new RightArrow(right));
						break;
				}
			}
			return 1;
		}
	} else if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_k_e = dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_k_e->getKeyboardAction() != df::KEY_PRESSED)
			return 0;
		if (p_k_e->getKey() == df::Keyboard::ESCAPE) {
			gameStart->stop();
			return 1;
		}
	}
	return 0;
}