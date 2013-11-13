#include "tsconf-configuration.h"
#include "t5.h"

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

tsconf::error::LoadError tsconf::GameConfig::Save(const char *file){
    if(file==NULL){

        t5file->writeValue(gamefunc, "mainfunction");
        t5file->writeValue(sgmname, "sgmname");
        t5file->writeValue(startupdir, "startupdir");
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

