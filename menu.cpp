/*******************************************************
*   Title: team3-project
*   Author(s): Forrest Buehlow, Hayden Mirza, Matthew O'Neill, and Cara Swab
*   Date: 2022-10-06
*   Code version: 1.0
*
*********************************************************/

#include "menu.h"

Menu::Menu(QString n, QStringList list, Menu* p) {

    name = n;
    menuItems = list;
    parent = p;
}


Menu::~Menu() {

    for(int x = 0; x < subMenus.length(); x++) {
        delete subMenus[x];
    }
}


void Menu::addChildMenu(Menu* m) {

    subMenus.push_back(m);
}


// getters
QString Menu::getName() { return name; }
QStringList Menu::getMenuItems() { return menuItems; }
Menu* Menu::getParent() { return parent; }
//int Menu::getPos() { return position; }
Menu* Menu::get(int i) { return subMenus[i]; }//this errors out as its out of index
QString* Menu::getName(int i) { return &menuItems[i]; }//this errors out as its out of index
//bool Menu::hasChildMenu(){return menuItems.length()>0;}
bool Menu::hasChildMenu(){return subMenus.length()>0;}