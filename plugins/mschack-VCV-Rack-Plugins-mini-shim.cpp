// Mini-only compile of mschack-VCV-Rack-Plugins' shared plugin-wide file
// (thePlugin) without the addModel() calls for modules CardinalMini didn't
// wire in -- those symbols aren't compiled for Mini, so init()'s normal body
// (never actually called; Mini uses StaticPluginLoader instead) would
// otherwise leave dangling references to them.
#define CARDINAL_MINI_TRIM_INIT
#include "mschack-VCV-Rack-Plugins/src/mscHack.cpp"
