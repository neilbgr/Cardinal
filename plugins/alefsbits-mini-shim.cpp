// Mini-only compile of alefsbits' shared plugin-wide file (PanelBackground,
// global_contrast/module_contrast/use_global_contrast) without the addModel()
// calls for modules CardinalMini didn't wire in -- those symbols aren't compiled
// for Mini, so init()'s normal body (never actually called; Mini uses
// StaticPluginLoader instead) would otherwise leave dangling references to them.
#define CARDINAL_MINI_TRIM_INIT
#include "alefsbits/src/plugin.cpp"
