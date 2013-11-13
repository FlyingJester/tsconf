#ifndef TSCONF_CONFIGURATION_HEAD
#define TSCONF_CONFIGURATION_HEAD

#include <cstdint>
#include "t5.h"

namespace tsconf {
    namespace error{

        enum LoadError {noerror = 0, nofile, badfile, oom, access};

    }

    class GameConfig {

public:
        GameConfig(void);
        ~GameConfig();
        const char *gamefunc;
        const char *sgmname;
        const char *tsgmname;
        const char *startupdir;
        bool fullscreen;
        int scale;
        int soundchannels; //This value is deprecated for the audioBass sound plugin.

        tsconf::error::LoadError Load(const char *enginefile);
        tsconf::error::LoadError Load(void);

        tsconf::error::LoadError Save(const char *file);

        void CopyFrom(const tsconf::GameConfig *conf);


private:
        bool fileloaded;
        T5_file *t5file;
        const char *filename;

    };

    const GameConfig *GetDefaultConfig();

    GameConfig *GetGameConfig();

    static const int32_t windowWidth = 440;
    static const int32_t windowHeight = 512;

    static const int32_t smallWidgetHeight = 30;
    static const int32_t largeWidgetHeight = 52;

    static const int32_t smallWidgetWidth = 64;
    static const int32_t largeWidgetWidth = 96;

    static const int32_t smallPadding = 32;
    static const int32_t largePadding = 52;

    static const int32_t noPadding = 4;

    static const char * windowTitle = "TurboSphere Configuration";


}


#endif  //TSCONF_CONFIGURATION_HEAD
