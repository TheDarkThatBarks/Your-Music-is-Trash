#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "ArrowBox.h"
#include "Arrow.h"

int main(int argc, char* argv[]) {

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

    // Show splash screen.
    //df::splash();

    RM.loadSprite("arrow-box-sprite.txt", "arrow-box");
    new ArrowBox(df::Vector(10, 10), DOWN);

    RM.loadSprite("arrow-sprite.txt", "arrow");
    Arrow* arrow = new Arrow(DOWN);
    arrow->setPosition(df::Vector(10, 0));

    GM.run();

    // Shut everything down.
    GM.shutDown();
}