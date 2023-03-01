//#include <fstream>
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "GameStart.h"
#include "ArrowBox.h"
#include "ArrowSpawner.h"
#include "Player.h"
#include "Boss.h"

GameStart::GameStart() {
	setType("GameStart");
	setLocation(df::CENTER_CENTER);
	setSprite("game-start");
	p_music = RM.getMusic("start-music");
	registerInterest(df::KEYBOARD_EVENT);
	playMusic();
	//std::ifstream input;
	//input.open("highscore.txt");
	//int highScore = 0;
	//input >> highScore;
	//input.close();
	//new HighScore(highScore);
}

int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		switch (p_keyboard_event->getKey()) {
			case df::Keyboard::NUM1:
				start(1);
				break;
			case df::Keyboard::NUM2:
				start(2);
				break;
			case df::Keyboard::NUM3:
				start(3);
				break;
			case df::Keyboard::ESCAPE:
				GM.setGameOver();
				break;
		}
		return 1;
	}
	return 0;
}

void GameStart::start(int level) {
	// Creates ArrowBoxes
	ArrowBox* left = new ArrowBox(df::Vector(10, 10), LEFT);
	ArrowBox* up = new ArrowBox(df::Vector(20, 10), UP);
	ArrowBox* down = new ArrowBox(df::Vector(30, 10), DOWN);
	ArrowBox* right = new ArrowBox(df::Vector(40, 10), RIGHT);

	// Creates ArrowSpawner
	new ArrowSpawner(left, up, down, right, "music/Stage" + std::to_string(level) + "-Song.txt");

	new Player((int) (1000.0 / GM.getFrameTime()) / ArrowSpawner::getBeatsPerSecond());
	Boss* boss = new Boss("boss2", (int) (1000.0 / GM.getFrameTime()) / ArrowSpawner::getBeatsPerSecond());
	boss->setPosition(df::Vector(60 + (level == 3 ? 10 : 0), 15));

	setActive(false);
	//p_music->pause();
	//printf("%s\n", "stage" + std::to_string(level));
	std::string str = std::to_string(level);
	printf("%s\n", std::to_string(level).c_str());
	RM.getMusic("stage" + std::to_string(level))->play();
}

void GameStart::stop() {
	df::ObjectList object_list = WM.getAllObjects(true);
	df::ObjectListIterator i(&object_list);
	int points = 0;
	for (i.first(); !i.isDone(); i.next()) {
		df::Object* p_o = i.currentObject();
		if (p_o->getType() == "Saucer" || p_o->getType() == "ViewObject") {
			//if (p_o->getType() == "ViewObject" && (dynamic_cast <ViewObject*> (p_o))->getViewString() == POINTS_STRING)
			//	points = (dynamic_cast <ViewObject*> (p_o))->getValue();
			//WM.markForDelete(p_o);
		}
		if (p_o->getType() == "GameStart") {
			p_o->setActive(true);
			(dynamic_cast <GameStart*> (p_o))->playMusic();
		}
	}
	/*std::ifstream input;
	input.open("highscore.txt");
	int highScore = 0;
	input >> highScore;
	input.close();
	if (points > highScore) {
		highScore = points;
		std::ofstream output;
		output.open("highscore.txt");
		output << points;
		output.close();
	}
	new HighScore(highScore);*/
}

int GameStart::draw() {
	return df::Object::draw();
}

void GameStart::playMusic() {
	if (p_music)
		p_music->play();
}