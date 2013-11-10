#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>

#include "configuration.h"

void Quit(Fl_Widget *unused0, void *unused1){
    exit(0);
}

void DoNothing(Fl_Widget *unused0, void *unused1){

}

void createMenuBar(){
    static Fl_Menu_Item menuItems[] = {
        {"&File", 0, 0, 0, FL_SUBMENU},
        {"&Save\t", FL_COMMAND + 's', (Fl_Callback *)DoNothing, 0},
        {"&Revert\t", FL_COMMAND + 'z', (Fl_Callback *)DoNothing, 0},
        {"E&xit\t", FL_COMMAND + 'q', (Fl_Callback *)Quit, 0},
        {0}
    };
    Fl_Menu_Bar *mainMenu = new Fl_Menu_Bar(0, 0, tsconf::windowWidth, tsconf::smallWidgetHeight);
    mainMenu->copy(menuItems);
}


int main(int argc, char *argv[]){
    Fl_Window confWindow(tsconf::windowWidth, tsconf::windowHeight, tsconf::windowTitle);
    confWindow.begin();
        createMenuBar();
    confWindow.end();

    confWindow.show();

    return Fl::run();
}
