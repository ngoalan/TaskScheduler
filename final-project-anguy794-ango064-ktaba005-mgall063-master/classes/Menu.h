#ifndef MENU
#define MENU

#include "User.h"
#include <algorithm>
using namespace std;


class Menu {
  public:
    Menu();
    bool displayLoginMenu(User* user);
    bool displayMainMenu();

  private:
    User* user;
};


#endif