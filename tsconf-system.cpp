#include "tsconf-main.h"
#include "tsconf-configuration.h"
#include <FL/Fl.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_File_Chooser.H>

/*
startupdir=startup
sgmname=game.sgm
extendedsgmname=game.tsgm
mainfunction=game
*/

void DirectoryChooser(Fl_Widget *widget, void *text){
    Fl_Input *dirfield = (Fl_Input *)text;
    char *dir = fl_dir_chooser("Select a directory to use as the startup directory", dirfield->value(), 1);

    if(dir==NULL){
        return;
    }

    dirfield->value(dir);

    dirfield->do_callback();

}

void TextCallback(Fl_Widget *widget, void *toSet){
    Fl_Input *inp = (Fl_Input *)widget;
    void **val = (void **)toSet;
    *val = (void *)inp->value();
}

void startupCallback(Fl_Widget *widget, void *unused){
    Fl_Input *inp = (Fl_Input *)widget;
    tsconf::GetGameConfig()->startupdir = inp->value();
}

void sgmnameCallback(Fl_Widget *widget, void *unused){
    Fl_Input *inp = (Fl_Input *)widget;
    tsconf::GetGameConfig()->sgmname = inp->value();

}

void tsgmnameCallback(Fl_Widget *widget, void *unused){
    Fl_Input *inp = (Fl_Input *)widget;
    tsconf::GetGameConfig()->tsgmname = inp->value();

}

void mainfuncCallback(Fl_Widget *widget, void *unused){
    Fl_Input *inp = (Fl_Input *)widget;
    tsconf::GetGameConfig()->gamefunc = inp->value();

}

void createSystemArea(int32_t x, int32_t y, int32_t w, int32_t h){

    tsconf::GameConfig *conf = tsconf::GetGameConfig();
    int curH_L = y;

    if((x+(tsconf::smallPadding<<1)+tsconf::largeWidgetWidth)>w){ //Enter no-space mode



    }
    else{ //We got space.

        curH_L+=tsconf::smallPadding;
        Fl_Group *startupGroup = new Fl_Group(x+tsconf::smallPadding, curH_L, w-(tsconf::smallPadding*2), tsconf::largeWidgetHeight, "Startup Directory");
        startupGroup->box(FL_EMBOSSED_BOX);

        startupGroup->begin();
            Fl_Input *startupInput = new Fl_Input(x+tsconf::smallPadding+12, curH_L+12, (w-(tsconf::smallPadding*2))-76, tsconf::smallWidgetHeight);
            startupInput->value(conf->startupdir);
            startupInput->when(FL_WHEN_CHANGED);
            startupInput->callback(startupCallback);

            int newX = static_cast<Fl_Widget *>(startupInput)->x()+static_cast<Fl_Widget *>(startupInput)->w();
            Fl_Button *chooseStartupButton = new Fl_Button(newX+12, curH_L+12, 40, tsconf::smallWidgetHeight, "...");
            chooseStartupButton->callback(DirectoryChooser, startupInput);
        startupGroup->end();

        curH_L+=tsconf::smallPadding+tsconf::largeWidgetHeight;
        Fl_Group *sgmnameGroup = new Fl_Group(x+tsconf::smallPadding, curH_L, w-(tsconf::smallPadding*2), tsconf::largeWidgetHeight, "SGM File Name");
        sgmnameGroup->box(FL_EMBOSSED_BOX);

        sgmnameGroup->begin();
            Fl_Input *sgmnameInput = new Fl_Input(x+tsconf::smallPadding+12, curH_L+12, (w-(tsconf::smallPadding*2))-24, tsconf::smallWidgetHeight);
            sgmnameInput->value(conf->sgmname);
            sgmnameInput->when(FL_WHEN_CHANGED);
            sgmnameInput->callback(sgmnameCallback);

        sgmnameGroup->end();

        curH_L+=tsconf::smallPadding+tsconf::largeWidgetHeight;
        Fl_Group *tsgmnameGroup = new Fl_Group(x+tsconf::smallPadding, curH_L, w-(tsconf::smallPadding*2), tsconf::largeWidgetHeight, "TSGM File Name");
        tsgmnameGroup->box(FL_EMBOSSED_BOX);

        tsgmnameGroup->begin();
            Fl_Input *tsgmnameInput = new Fl_Input(x+tsconf::smallPadding+12, curH_L+12, (w-(tsconf::smallPadding*2))-24, tsconf::smallWidgetHeight);
            tsgmnameInput->value(conf->tsgmname);
            tsgmnameInput->when(FL_WHEN_CHANGED);
            tsgmnameInput->callback(tsgmnameCallback);


        tsgmnameGroup->end();

        curH_L+=tsconf::smallPadding+tsconf::largeWidgetHeight;
        Fl_Group *mainfuncGroup = new Fl_Group(x+tsconf::smallPadding, curH_L, w-(tsconf::smallPadding*2), tsconf::largeWidgetHeight, "Main Function");
        mainfuncGroup->box(FL_EMBOSSED_BOX);

        mainfuncGroup->begin();
            Fl_Input *mainfuncInput = new Fl_Input(x+tsconf::smallPadding+12, curH_L+12, (w-(tsconf::smallPadding*2))-24, tsconf::smallWidgetHeight);
            mainfuncInput->value(conf->gamefunc);
            mainfuncInput->when(FL_WHEN_CHANGED);
            mainfuncInput->callback(mainfuncCallback);


        mainfuncGroup->end();
    }


}
