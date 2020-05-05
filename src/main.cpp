
#include "UserInterface/UserInterface.h"
#include <iostream>
#include "GraphFactory.h"

using namespace std;

int main() {
    UserInterface ui;
    //ui.mainMenuSelection(ui.showMainMenu());
    GraphFactory *g = new GraphFactory();
    g->readVertex("nodes.csv");
    return 0;
}
