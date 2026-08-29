// Mini-only compile of ImpromptuModular's shared plugin-wide file (clockMaster,
// InstantiateExpanderItem, theme helpers, etc.) without the addModel() calls for
// modules CardinalMini didn't wire in -- those symbols aren't compiled for Mini,
// so init()'s normal body (never actually called; Mini uses StaticPluginLoader
// instead) would otherwise leave dangling references to them.
#define CARDINAL_MINI_TRIM_INIT
#include "ImpromptuModular/src/ImpromptuModular.cpp"
