#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "ArrowBox.h"
#include "Arrow.h"
#include "ArrowSpawner.h"

int main(int argc, char* argv[]) {

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

    // Show splash screen.
    //df::splash();

    RM.loadSprite("sprites/arrow-box-sprite.txt", "arrow-box");
    ArrowBox* up = new ArrowBox(df::Vector(20, 10), UP);
    ArrowBox* down = new ArrowBox(df::Vector(30, 10), DOWN);
    ArrowBox* left = new ArrowBox(df::Vector(10, 10), LEFT);
    ArrowBox* right = new ArrowBox(df::Vector(40, 10), RIGHT);

    RM.loadSprite("sprites/left-arrow-sprite.txt", "left-arrow");
    RM.loadSprite("sprites/right-arrow-sprite.txt", "right-arrow");
    RM.loadSprite("sprites/up-arrow-sprite.txt", "up-arrow");
    RM.loadSprite("sprites/down-arrow-sprite.txt", "down-arrow");
    //Arrow* arrow = new Arrow(df::Vector(10, 0), DOWN);
    //arrow->setPosition(df::Vector(10, 0));
    new ArrowSpawner(up, down, left, right, "test.txt");

    GM.run();

    // Shut everything down.
    GM.shutDown();
}