// Mini-only compile of MindMeldModular's shared plugin-wide file (mixerMessageBus,
// readGlobalSettings, etc.) without the addModel() calls for modules CardinalMini
// didn't wire in -- those symbols aren't compiled for Mini, so init()'s normal body
// (never actually called; Mini uses StaticPluginLoader instead) would otherwise
// leave dangling references to them.
#define CARDINAL_MINI_TRIM_INIT
#include "MindMeldModular/src/MindMeldModular.cpp"
