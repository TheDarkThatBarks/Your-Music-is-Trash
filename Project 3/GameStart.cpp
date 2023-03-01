#include <fstream>
#include "GameManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventKeyboard.h"
#include "GameStart.h"
#include "ArrowBox.h"
#include "ArrowSpawner.h"
#include "Player.h"
#include "Boss.h"
//#include "ViewObject.h"

GameStart::GameStart() {
	setType("GameStart");
	setLocation(df::CENTER_CENTER);
	setSprite("game-start");
	music = RM.getMusic("start-music");
	level = 0;
	combo1 = 0;
	combo2 = 0;
	combo3 = 0;
	registerInterest(df::KEYBOARD_EVENT);
	playMusic();
	createCombos();
}

void GameStart::start(int l) {
	df::ObjectList list = WM.getAllObjects(false);
	df::ObjectListIterator li(&list);
	for (li.first(); !li.isDone(); li.next()) {
		Object* p_o = li.currentObject();
		if (p_o->getType() == "ViewObject")
			WM.markForDelete(p_o);
	}

	level = l;

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
	int combo = -1;
	for (li.first(); !li.isDone(); li.next()) {
		Object* p_o = li.currentObject();
		if (p_o->getType() == "GameStart")
			puts("DEBUG");
		if (p_o->getType() == "CombometerMax")
			combo = (dynamic_cast <CombometerMax*> (p_o))->getValue();
		WM.markForDelete(p_o);
	}
	levelMusic->stop();
	setActive(true);
	playMusic();
	std::ifstream input;
	input.open("maxCombos.txt");
	input >> combo1 >> combo2 >> combo3;
	input.close();
	bool changed = false;
	if (level == 1 && combo > combo1) {
		combo1 = combo;
		changed = true;
	} else if (level == 2 && combo > combo2) {
		combo2 = combo;
		changed = true;
	} else if (level == 3 && combo > combo3) {
		combo3 = combo;
		changed = true;
	}
	if (changed) {
		std::ofstream output;
		output.open("maxCombos.txt");
		output << combo1 << " " << combo2 << " " << combo3;
		output.close();
	}
	createCombos();
}

int GameStart::draw() {
	return df::Object::draw();
}

void GameStart::playMusic() {
	if (music)
		music->play();
}

void GameStart::createCombos() {
	std::ifstream input;
	input.open("maxCombos.txt");
	input >> combo1 >> combo2 >> combo3;
	input.close();
	ViewObject* level1 = new ViewObject();
	level1->setLocation(df::TOP_LEFT);
	level1->setViewString("Level 1:");
	level1->setValue(combo1);
	ViewObject* level2 = new ViewObject();
	level2->setLocation(df::TOP_CENTER);
	level2->setViewString("Level 2:");
	level2->setValue(combo2);
	ViewObject* level3 = new ViewObject();
	level3->setLocation(df::TOP_RIGHT);
	level3->setViewString("Level 3:");
	level3->setValue(combo3);
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