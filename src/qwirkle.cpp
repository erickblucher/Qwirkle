#include "../test/TestAll.h"
#include <string>

#include "GameMenu.h"
#include "OperationModes.h"

int main(void) {

#ifdef TEST_MODE
    TestAll::testAll();

#else
    GameMenu *gameMenu = new GameMenu();

    gameMenu->run();
    delete gameMenu;
#endif
    return EXIT_SUCCESS;
}
