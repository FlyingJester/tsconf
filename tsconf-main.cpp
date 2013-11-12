#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/fl_ask.H>

#include "tsconf-main.h"
#include "tsconf-graphics.h"

#include "configuration.h"


void Quit(DEF_FL_ARGS){
    exit(0);
}

void DoNothing(DEF_FL_ARGS){

}

void lol(){
    printf("It worked.\n");
}

void SetAllDefault(DEF_FL_ARGS){
    int resetall = fl_ask("Are you sure you want to change all settings to the defaults?\n");

    if(!resetall)
        return;

}

void createMenuBar(){
    static Fl_Menu_Item menuItems[] = {
        {"&File", 0, 0, 0, FL_SUBMENU},
        {"&Save\t", FL_COMMAND + 's', (Fl_Callback *)DoNothing, 0},
        {"&Revert\t", FL_COMMAND + 'z', (Fl_Callback *)DoNothing, 0},
        {"E&xit\t", FL_COMMAND + 'q', (Fl_Callback *)Quit, 0},
        {0},

        {"&Edit", 0, 0, 0, FL_SUBMENU},
        {"&Set to Defaults\t", FL_COMMAND + 'd', (Fl_Callback *)DoNothing, 0},
        {"&Set all to Defaults\t", FL_COMMAND + FL_SHIFT + 'd', (Fl_Callback *)SetAllDefault, 0},
        {0}
    };

    Fl_Menu_Bar *mainMenu = new Fl_Menu_Bar(0, 0, tsconf::windowWidth, tsconf::smallWidgetHeight);
    mainMenu->copy(menuItems);
}


int main(int argc, char *argv[]){
    Fl_Window confWindow(tsconf::windowWidth, tsconf::windowHeight, tsconf::windowTitle);
    confWindow.begin();
        createMenuBar();
        createGraphicsArea(0, 48, tsconf::windowWidth, 128);
    confWindow.end();

    confWindow.show();

    return Fl::run();
}
