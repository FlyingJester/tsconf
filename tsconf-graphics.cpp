#include "tsconf-main.h"
#include "configuration.h"
#include <FL/Fl.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Slider.H>

void ScaleCallback(Fl_Widget *widget, void * unused){
    //TODO: Make this NOT leak.
    Fl_Valuator *scaleSlider = (Fl_Valuator *)widget;
    switch((int)(scaleSlider->value())){
        case 1:
        widget->label("Scaling (none)");
        break;
        case 2:
        widget->label("Scaling (x2)\0");
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
    widget->redraw_label();
}

void createGraphicsArea(int32_t x, int32_t y, int32_t w, int32_t h){

    int curH_L = 0;

    if((x+(tsconf::smallPadding<<1)+tsconf::largeWidgetWidth)>w){ //Enter no-space mode



    }
    else{ //We got space.

        curH_L+=tsconf::smallPadding;

        Fl_Check_Button *fullscreenCheck = new Fl_Check_Button(x+tsconf::smallPadding, curH_L, tsconf::largeWidgetWidth, tsconf::smallWidgetHeight, "Fullscreen");

        curH_L+=tsconf::smallPadding>>1;
        curH_L+=tsconf::smallPadding;


        Fl_Slider *scaleSlider = new Fl_Slider(x+tsconf::smallPadding, curH_L, tsconf::largeWidgetWidth, tsconf::smallWidgetHeight, "Scaling");
        scaleSlider->type(FL_HORIZONTAL);
        scaleSlider->bounds(1, 4);
        scaleSlider->step(1);
        scaleSlider->value(1);
        //scaleSlider->box(FL_FLAT_BOX);
        scaleSlider->callback(ScaleCallback);
        scaleSlider->do_callback();
        curH_L+=tsconf::smallPadding;

        curH_L+=tsconf::smallPadding<<1;
    }


}
