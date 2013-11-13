#include "tsconf-configuration.h"
#include "t5.h"

#include <FL/fl_ask.H>

using tsconf::error::LoadError;

tsconf::GameConfig *tsconf::GetGameConfig(){
    static tsconf::GameConfig conf = tsconf::GameConfig();
    return &conf;
}

tsconf::GameConfig::GameConfig(){
        gamefunc = "game";
        sgmname = "game.sgmLOL";
        tsgmname = "game.tsgm";
        fullscreen = false;
        scale = 1;
        soundchannels = 32; //This value is deprecated for the audioBass sound plugin.
        fileloaded = false;
        startupdir = "startup";
        filename = NULL;
        t5file = NULL;
}

tsconf::GameConfig::~GameConfig(){
    if(fileloaded){
        T5_close(t5file);
    }
}

void tsconf::GameConfig::CopyFrom(const tsconf::GameConfig *conf){

    gamefunc = conf->gamefunc;
    sgmname = conf->sgmname;
    tsgmname = conf->tsgmname;
    startupdir = conf->startupdir;
    soundchannels = conf->soundchannels;
    scale = conf->scale;
    fullscreen = conf->fullscreen;

}

const tsconf::GameConfig *tsconf::GetDefaultConfig(){

    static tsconf::GameConfig conf = tsconf::GameConfig();

    conf.gamefunc = "game";
    conf.sgmname = "game.sgm";
    conf.tsgmname = "game.tsgm";
    conf.startupdir = "startup";
    conf.fullscreen = false;
    conf.scale = 1;
    conf.soundchannels = 32;

    return &conf;

}

tsconf::error::LoadError tsconf::GameConfig::Load(void){
    Load("engine.ini");
    return LoadError::noerror;
}

tsconf::error::LoadError tsconf::GameConfig::Load(const char *enginefile){
    if(!T5_IsFile(enginefile)){
        return LoadError::nofile;
    }
    t5file = T5_OpenFile(enginefile);
    if(!t5file){
        return LoadError::badfile;
    }

    t5file = T5_OpenFile(enginefile);

    gamefunc    = t5file->getValueFromSection("mainfunction", "Engine");
    sgmname     = t5file->getValueFromSection("sgmname", "Engine");
    startupdir  = t5file->getValueFromSection("startupdir", "Engine");
    tsgmname    = t5file->getValueFromSection("extendedsgmname", "Engine");

    fullscreen  = atoi(t5file->getValueFromSection("fullscreen", "Video"));
    scale       = atoi(t5file->getValueFromSection("scale", "Video"));

    soundchannels = atoi(t5file->getValueFromSection("soundchannels", "Audio"));

    return LoadError::noerror;
}

#include <cstring>

#define ISVALID(text1) ((text1!=NULL)&&(strnlen(text1, 2)>0))


#define ISDIRVALID(text2) (ISVALID(text2)&&T5_IsDir(text2))\


tsconf::error::LoadError tsconf::GameConfig::Save(const char *file){
    if(file==NULL){

        if(!(ISVALID(gamefunc))){
            gamefunc = tsconf::GetDefaultConfig()->gamefunc;
            printf("Nothing went wrong gamefunc.\n");
            printf("IsNull\t%i\nStrnlen(2)\t%i\n", gamefunc!=NULL, strnlen(gamefunc, 2)>0);
        }

        t5file->writeValue(gamefunc, "mainfunction");

        if(!ISVALID(sgmname)){
            sgmname = tsconf::GetDefaultConfig()->sgmname;
            printf("Nothing went wrong sgmname.\n");
            printf("IsNull\t%i\nStrnlen(2)\t%i\n", sgmname!=NULL, strnlen(sgmname, 2)>0);
        }
        t5file->writeValue(sgmname, "sgmname");

        if(!ISDIRVALID(startupdir)){
            int usebaddir = fl_choice("The directory \"%s\" cannot be verified as valid.\nDo you want to use it anyway?", "Cancel", "Yes", "No", startupdir);
            if(usebaddir==2){
                startupdir = tsconf::GetDefaultConfig()->startupdir;
                printf("We didn't use the unverified directory.\n");
            }
            else if(usebaddir==0)
                return LoadError::noerror;
            else
                printf("We used the unverified directory.\n");
        }

        t5file->writeValue(startupdir, "startupdir");

        if(!ISVALID(tsgmname)){
            tsgmname = tsconf::GetDefaultConfig()->tsgmname;
            printf("Nothing went wrong tsgmname.\n");
            printf("IsNull\t%i\nStrnlen(2)\t%i\n", tsgmname!=NULL, strnlen(tsgmname, 2)>0);
        }
        t5file->writeValue(tsgmname, "extendedsgmname");

        char scalestr[3];
        char soundchannelsstr[3];
        sprintf(scalestr, "%i", scale);
        sprintf(soundchannelsstr, "%i", soundchannels);

        t5file->writeValue((fullscreen)?"1":"0", "fullscreen");
        t5file->writeValue(scalestr, "scale");

        t5file->writeValue(soundchannelsstr, "soundchannels");

        return LoadError::noerror;
    }


    return LoadError::noerror;
}

