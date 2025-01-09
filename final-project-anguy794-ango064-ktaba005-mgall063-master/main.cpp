#include "./classes/Menu.h"


using namespace std;

int main() {
    Menu* menu = new Menu();
    User* user = nullptr;
    bool continueDisplay = false;

    do {
        continueDisplay = menu->displayLoginMenu(user);
    } while (continueDisplay);

    do {
        cout << "\n\n\n\n" << endl;
        continueDisplay = menu->displayMainMenu();
    } while (continueDisplay);
    

    return 0;
}