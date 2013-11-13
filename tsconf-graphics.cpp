#include "tsconf-main.h"
#include "tsconf-configuration.h"
#include <FL/Fl.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Slider.H>

void ScaleCallback(Fl_Widget *widget, void * unused){

    Fl_Valuator *scaleSlider = (Fl_Valuator *)widget;
    switch((int)(scaleSlider->value())){
        case 1:
        widget->label("Scaling (none)");
        break;
        case 2:
        widget->label("Scaling (x2)");
        break;
        case 3:
        widget->label("Scaling (x3)");
        break;
        case 4:
        widget->label("Scaling (x4)");
        break;
        default:
        widget->label("Scaling (badvalue)");
    }

    tsconf::GameConfig * conf = tsconf::GetGameConfig();

    conf->scale = scaleSlider->value();

    widget->redraw_label();
}

void FullscreenCallback(Fl_Widget *widget, void * unused){

    Fl_Button *fullscreenButton = (Fl_Button *)widget;

    tsconf::GameConfig * conf = tsconf::GetGameConfig();

    conf->fullscreen = fullscreenButton->value();
}

void createGraphicsArea(int32_t x, int32_t y, int32_t w, int32_t h){
        tsconf::GameConfig *conf = tsconf::GetGameConfig();
    int curH_L = y;

    if((x+(tsconf::smallPadding<<1)+tsconf::largeWidgetWidth)>w){ //Enter no-space mode



    }
    else{ //We got space.

        curH_L+=tsconf::smallPadding;

        Fl_Check_Button *fullscreenCheck = new Fl_Check_Button(x+tsconf::smallPadding, curH_L, tsconf::largeWidgetWidth, tsconf::smallWidgetHeight, "Fullscreen");

        fullscreenCheck->value((conf->fullscreen==0)?0:1);

        fullscreenCheck->callback(FullscreenCallback);

        curH_L+=tsconf::smallPadding>>1;
        curH_L+=tsconf::smallPadding;


        Fl_Slider *scaleSlider = new Fl_Slider(x+tsconf::smallPadding, curH_L, tsconf::largeWidgetWidth, tsconf::smallWidgetHeight, "Scaling");
        scaleSlider->type(FL_HORIZONTAL);
        scaleSlider->bounds(1, 4);
        scaleSlider->step(1);
        scaleSlider->value(conf->scale);
        //scaleSlider->box(FL_FLAT_BOX);
        scaleSlider->callback(ScaleCallback);
        scaleSlider->do_callback();
        curH_L+=tsconf::smallPadding;

        curH_L+=tsconf::smallPadding<<1;
    }


}
