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
	music = RM.getMusic("start-music");
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
		const df::EventKeyboard* p_k_e = dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_k_e->getKeyboardAction() != df::KEY_PRESSED)
			return 0;
		switch (p_k_e->getKey()) {
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
			default:
				return 0;
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

	new Player((int) round((1000.0 / GM.getFrameTime()) / ArrowSpawner::getBeatsPerSecond()));
	Boss* boss = new Boss("boss" + std::to_string(level), (int) round((1000.0 / GM.getFrameTime()) / ArrowSpawner::getBeatsPerSecond()));
	boss->setPosition(df::Vector((float)(60 + (level == 3 ? 10 : 0)), 15));

	ArrowSpawner::setCombo(new Combometer());
	ArrowSpawner::setComboMax(new CombometerMax());
	ArrowSpawner::setGameStart(this);

	setActive(false);
	music->pause();
	levelMusic = RM.getMusic("stage" + std::to_string(level));
	levelMusic->play();
}

void GameStart::stop() {
	df::ObjectList list = WM.getAllObjects(false);
	df::ObjectListIterator li(&list);
	for (li.first(); !li.isDone(); li.next())
		WM.markForDelete(li.currentObject());
	levelMusic->stop();
	setActive(true);
	playMusic();
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
	if (music)
		music->play();
}