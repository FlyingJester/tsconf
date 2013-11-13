#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/fl_ask.H>

#include "tsconf-main.h"
#include "tsconf-graphics.h"
#include "tsconf-system.h"
#include "tsconf-configuration.h"

#include "t5.h"

void Quit(DEF_FL_ARGS){
    exit(0);
}

void DoNothing(DEF_FL_ARGS){

}

void SaveAll(DEF_FL_ARGS){
    tsconf::GameConfig *conf = tsconf::GetGameConfig();

    auto error = conf->Save(NULL);


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
        {"&Open...\t", FL_COMMAND + 'o', (Fl_Callback *)DoNothing, 0},
        {"&Save\t", FL_COMMAND + 's', (Fl_Callback *)SaveAll, 0},
        {"Save &As...\t", FL_SHIFT + FL_COMMAND + 's', (Fl_Callback *)DoNothing, 0},
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

    T5_init(1, "./");

    tsconf::GameConfig *config = tsconf::GetGameConfig();

    tsconf::error::LoadError err = config->Load();

    if(err){
        fprintf(stderr, "Could not open engine.ini file. Error was %i.\n", err);
    }

    printf("%s\n", config->sgmname);


    Fl_Window confWindow(tsconf::windowWidth, tsconf::windowHeight, tsconf::windowTitle);
    confWindow.begin();
        createMenuBar();
        Fl_Tabs tabs(tsconf::smallWidgetHeight, tsconf::smallWidgetHeight<<1, tsconf::windowWidth-(tsconf::smallWidgetHeight*2), tsconf::windowHeight-(tsconf::largeWidgetHeight<<1));
        tabs.begin();
            Fl_Group GraphicsGroup(tsconf::smallWidgetHeight, tsconf::smallWidgetHeight*3, tsconf::windowWidth-(tsconf::smallWidgetHeight*2), tsconf::windowHeight-(tsconf::largeWidgetHeight*3), "Graphics");
            GraphicsGroup.begin();
                createGraphicsArea(tsconf::smallWidgetHeight, tsconf::smallWidgetHeight*3, tsconf::windowWidth-(tsconf::smallWidgetHeight*2), 128);
            GraphicsGroup.end();

            Fl_Group SystemGroup(tsconf::smallWidgetHeight, tsconf::smallWidgetHeight*3, tsconf::windowWidth-(tsconf::smallWidgetHeight*2), tsconf::windowHeight-(tsconf::largeWidgetHeight*3), "System");
            SystemGroup.begin();
                createSystemArea(tsconf::smallWidgetHeight, tsconf::smallWidgetHeight*3, tsconf::windowWidth-(tsconf::smallWidgetHeight*2), 128);
            SystemGroup.end();
        tabs.end();
    confWindow.end();

    confWindow.show();

    return Fl::run();
}
