/*
 * DISTRHO Cardinal Plugin
 * Copyright (C) 2021-2023 Filipe Coelho <falktx@falktx.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the LICENSE file.
 */

#include "rack.hpp"
#include "plugin.hpp"

#include "DistrhoUtils.hpp"

// Cardinal (built-in)
#include "Cardinal/src/plugin.hpp"

// Fundamental
#include "Fundamental/src/plugin.hpp"

// Aria
extern Model* modelSpleet;
extern Model* modelSwerge;

// AudibleInstruments
#include "AudibleInstruments/src/plugin.hpp"

// BogaudioModules - integrate theme/skin support
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#define private public
#include "BogaudioModules/src/skins.hpp"
#undef private

// BogaudioModules
extern Model* modelAD;
extern Model* modelBogaudioLFO;
extern Model* modelBogaudioNoise;
extern Model* modelBogaudioVCA;
extern Model* modelBogaudioVCF;
extern Model* modelBogaudioVCO;
extern Model* modelOffset;
extern Model* modelSampleHold;
extern Model* modelSwitch;
extern Model* modelSwitch18;
extern Model* modelUnison;

extern Model* modelMono;
extern Model* modelAnalyzerXL;
extern Model* modelMix8;
extern Model* modelXFade;
extern Model* modelLVCF;
extern Model* modelStack;
extern Model* modelArp;
extern Model* modelUMix;
extern Model* modelLVCO;
extern Model* modelBool;
extern Model* modelBogaudioADSR;
extern Model* modelLLFO;
extern Model* modelFMOp;
extern Model* modelASR;
extern Model* modelMix4;
extern Model* modelPolyCon8;
extern Model* modelAddrSeqX;
extern Model* modelAddrSeq;
extern Model* modelMix4x;
extern Model* modelPressor;
extern Model* modelVelo;
extern Model* modelSlew;
extern Model* modelPulse;
extern Model* modelSine;
extern Model* modelDGate;
extern Model* modelVCAmp;
extern Model* modelMix8x;
extern Model* modelReftone;
extern Model* modelMatrix81;
// MockbaModular
#include "MockbaModular/src/plugin.hpp"
#include "MockbaModular/src/MockbaModular.hpp"
#undef min
#define saveBack ignoreMockbaModular1
#define loadBack ignoreMockbaModular2
#include "MockbaModular/src/MockbaModular.cpp"
#undef saveBack
#undef loadBack
std::string loadBack(int) { return "res/Empty_gray.svg"; }

// surgext
#include "surgext/src/SurgeXT.h"
void surgext_rack_initialize();
void surgext_rack_update_theme();

// ValleyAudio
#include "ValleyAudio/src/Valley.hpp"

// Aluminium
extern Model* modelPadX;
extern Model* modelZones;
extern Model* modelPads;

// AmbientModules
extern Model* modelLunarPapaSrapa;
extern Model* modelLunarSequencer;
extern Model* modelLunar50Drone;
extern Model* modelBlank;
extern Model* modelLunarLFO;
extern Model* modelLunarVCO;

// cf
extern Model* modelLABEL;

// unless_modules
extern Model* modelPianoid;

// ProducerPack
extern Model* modelSeventiesComp;
extern Model* modelStereoWidth;
extern Model* modelDrumBus;

// AS
extern Model* modelStereoVUmeter;
extern Model* modelDelayPlusStereoFx;
extern Model* modelPhaserFx;
extern Model* modelMonoVUmeter;

// VCVRackPlugins
extern Model* modelOscilloscope;
extern Model* modelBarGraph;

// GrandeModular
extern Model* modelMerge8;

// ImpromptuModular
extern Model* modelClkd;
extern Model* modelClocked;
extern Model* modelClockedExpander;
extern Model* modelPhraseSeq16;
extern Model* modelPhraseSeqExpander;

// JW-Modules
extern Model* modelFullScope;
extern Model* modelGrains;

// LittleUtils
extern Model* modelButtonModule;

// MindMeldModular
extern Model* modelMasterChannel;
extern Model* modelMixMasterJr;

extern Model* modelAuxExpanderJr;
extern Model* modelMSMelder;
extern Model* modelBassMaster;
extern Model* modelBassMasterJr;
// SignalFunctionSet-VCV-Rack
extern Model* modelFill;

// stoermelder-packone
extern Model* modelGlue;

// submit-vcv-modules
extern Model* modelTag;

// Venom
extern Model* modelVenomMixSolo;
extern Model* modelVenomPolyUnison;
extern Model* modelVenomBayOutput;
extern Model* modelVenomPolyScale;
extern Model* modelVenomMixFade2;
extern Model* modelVenomBayNorm;
extern Model* modelVenomPolyOffset;
extern Model* modelVenomMixPan;
extern Model* modelVenomKnob5;
extern Model* modelVenomMixFade;
extern Model* modelVenomMixMute;
extern Model* modelVenomBayInput;
extern Model* modelVenomMixSend;
extern Model* modelVenomMix4;
extern Model* modelVenomMixOffset;
extern Model* modelVenomMix4Stereo;
extern Model* modelVenomCloneMerge;
extern Model* modelVenomVCAMix4;
extern Model* modelVenomPush5;
extern Model* modelVenomBypass;
extern Model* modelVenomVCAMix4Stereo;

// Autinn
extern Model* modelAutinnSnare;
extern Model* modelAmp;
extern Model* modelKicker;
extern Model* modelAutinnScope;

// Biset
extern Model* modelBisetBlank;

// alefsbits
extern Model* modelLights;

// HetrickCV (HETRICKCV_CUSTOM in plugins/Makefile renames these at compile
// time -- see plugins.cpp's own initStatic__HetrickCV for the same pattern)
#define modelMinMax modelHetrickCVMinMax
#define modelMidSide modelHetrickCVMidSide
extern Model* modelMinMax;
extern Model* modelMidSide;
#undef modelMinMax
#undef modelMidSide

// CellaVCV
extern Model* modelLoud;
extern Model* modelLoudnessMeter;

// Kilpatrick-Toolbox
extern Model* modelStereo_Meter;
extern Model* modelMulti_Meter;

// mschack-VCV-Rack-Plugins
extern Model* modelPingPong;

// kathode
extern Model* modelKathode;

// known terminal modules
std::vector<Model*> hostTerminalModels;

// plugin instances
Plugin* pluginInstance__Cardinal;
Plugin* pluginInstance__Fundamental;
Plugin* pluginInstance__Aria;
Plugin* pluginInstance__AudibleInstruments;
Plugin* pluginInstance__BogaudioModules;
Plugin* pluginInstance__MockbaModular;
Plugin* pluginInstance__surgext;
Plugin* pluginInstance__ValleyAudio;

Plugin* pluginInstance__Aluminium;
Plugin* pluginInstance__AmbientModules;
Plugin* pluginInstance__cf;
Plugin* pluginInstance__unless_modules;
Plugin* pluginInstance__ProducerPack;
Plugin* pluginInstance__AS;
extern Plugin* pluginInstance__VCVRackPlugins;
Plugin* pluginInstance__GrandeModular;
extern Plugin* pluginInstance__ImpromptuModular;
extern void readThemeAndContrastFromDefault();
Plugin* pluginInstance__JW;
Plugin* pluginInstance__LittleUtils;
extern Plugin* pluginInstance__MindMeld;
Plugin* pluginInstance__SignalFunctionSet_VCV_Rack;
extern Plugin* pluginInstance__stoermelder_p1;
Plugin* pluginInstance__submit_vcv_modules;
Plugin* pluginInstance__Venom;
Plugin* pluginInstance__Autinn;
Plugin* pluginInstance__Biset;
Plugin* pluginInstance__HetrickCV;
Plugin* pluginInstance__CellaVCV;
extern Plugin* pluginInstance__Kilpatrick_Toolbox;
extern Plugin* pluginInstance__mschack_VCV_Rack_Plugins;
extern Plugin* pluginInstance__kathode;
extern Plugin* pluginInstance__alefsbits;
namespace rack {

namespace asset {
std::string pluginManifest(const std::string& dirname);
std::string pluginPath(const std::string& dirname);
}

namespace plugin {

struct StaticPluginLoader {
    Plugin* const plugin;
    FILE* file;
    json_t* rootJ;

    StaticPluginLoader(Plugin* const p, const char* const name)
        : plugin(p),
          file(nullptr),
          rootJ(nullptr)
    {
#ifdef DEBUG
        DEBUG("Loading plugin module %s", name);
#endif

        p->path = asset::pluginPath(name);

        const std::string manifestFilename = asset::pluginManifest(name);

        if ((file = std::fopen(manifestFilename.c_str(), "r")) == nullptr)
        {
            d_stderr2("Manifest file %s does not exist", manifestFilename.c_str());
            return;
        }

        json_error_t error;
        if ((rootJ = json_loadf(file, 0, &error)) == nullptr)
        {
            d_stderr2("JSON parsing error at %s %d:%d %s", manifestFilename.c_str(), error.line, error.column, error.text);
            return;
        }

        // force ABI, we use static plugins so this doesnt matter as long as it builds
        json_t* const version = json_string((APP_VERSION_MAJOR + ".0").c_str());
        json_object_set(rootJ, "version", version);
        json_decref(version);

        // Load manifest
        p->fromJson(rootJ);

        // Reject plugin if slug already exists
        if (Plugin* const existingPlugin = getPlugin(p->slug))
            throw Exception("Plugin %s is already loaded, not attempting to load it again", p->slug.c_str());
    }

    ~StaticPluginLoader()
    {
        if (rootJ != nullptr)
        {
            // Load modules manifest
            json_t* const modulesJ = json_object_get(rootJ, "modules");
            plugin->modulesFromJson(modulesJ);

            json_decref(rootJ);
            plugins.push_back(plugin);
        }

        if (file != nullptr)
            std::fclose(file);
    }

    bool ok() const noexcept
    {
        return rootJ != nullptr;
    }

    void removeModule(const char* const slugToRemove) const noexcept
    {
        json_t* const modules = json_object_get(rootJ, "modules");
        DISTRHO_SAFE_ASSERT_RETURN(modules != nullptr,);

        size_t i;
        json_t* v;
        json_array_foreach(modules, i, v)
        {
            if (json_t* const slug = json_object_get(v, "slug"))
            {
                if (const char* const value = json_string_value(slug))
                {
                    if (std::strcmp(value, slugToRemove) == 0)
                    {
                        json_array_remove(modules, i);
                        break;
                    }
                }
            }
        }
    }
};

static void initStatic__Cardinal()
{
    Plugin* const p = new Plugin;
    pluginInstance__Cardinal = p;

    const StaticPluginLoader spl(p, "Cardinal");
    if (spl.ok())
    {
        p->addModel(modelHostAudio2);
        p->addModel(modelHostCV);
        p->addModel(modelHostMIDI);
        p->addModel(modelHostMIDICC);
        p->addModel(modelHostMIDIGate);
        p->addModel(modelHostMIDIMap);
        p->addModel(modelHostParameters);
        p->addModel(modelHostParametersMap);
        p->addModel(modelHostTime);
        p->addModel(modelTextEditor);
        /* TODO
       #ifdef HAVE_FFTW3F
        p->addModel(modelAudioToCVPitch);
       #else
        */
        spl.removeModule("AudioToCVPitch");
        /*
       #endif
        */
        spl.removeModule("AIDA-X");
        spl.removeModule("AudioFile");
        spl.removeModule("Blank");
        spl.removeModule("Carla");
        spl.removeModule("ExpanderInputMIDI");
        spl.removeModule("ExpanderOutputMIDI");
        spl.removeModule("HostAudio8");
        spl.removeModule("Ildaeil");
        spl.removeModule("MPV");
        spl.removeModule("SassyScope");
        spl.removeModule("glBars");

        hostTerminalModels = {
            modelHostAudio2,
            modelHostCV,
            modelHostMIDI,
            modelHostMIDICC,
            modelHostMIDIGate,
            modelHostMIDIMap,
            modelHostParameters,
            modelHostParametersMap,
            modelHostTime,
        };
    }
}

static void initStatic__Fundamental()
{
    Plugin* const p = new Plugin;
    pluginInstance__Fundamental = p;

    const StaticPluginLoader spl(p, "Fundamental");
    if (spl.ok())
    {
        p->addModel(modelADSR);
        p->addModel(modelLFO);
        p->addModel(modelMerge);
        p->addModel(modelMidSide);
        p->addModel(modelNoise);
        p->addModel(modelQuantizer);
        p->addModel(modelRandom);
        p->addModel(modelScope);
        p->addModel(modelSplit);
        p->addModel(modelSum);
        p->addModel(modelVCA_1);
        p->addModel(modelVCF);
        p->addModel(modelVCMixer);
        p->addModel(modelVCO);
        p->addModel(modelMixer);
        p->addModel(model_8vert);
        p->addModel(modelVCO2);
        p->addModel(modelPulses);
        p->addModel(modelVCA);
        p->addModel(modelSequentialSwitch1);
        p->addModel(modelSequentialSwitch2);
        p->addModel(modelOctave);
        p->addModel(modelSEQ3);
        p->addModel(modelDelay);
        p->addModel(modelLFO2);
        p->addModel(modelMutes);
    }
}

static void initStatic__Aria()
{
    Plugin* const p = new Plugin;
    pluginInstance__Aria = p;

    const StaticPluginLoader spl(p, "AriaModules");
    if (spl.ok())
    {
        spl.removeModule("Aleister");
        spl.removeModule("Arcane");
        spl.removeModule("Atout");
        spl.removeModule("Blank");
        spl.removeModule("Darius");
        spl.removeModule("Grabby");
        spl.removeModule("Pokies4");
        spl.removeModule("Psychopump");
        spl.removeModule("Q");
        spl.removeModule("Qqqq");
        spl.removeModule("Quack");
        spl.removeModule("Quale");
        spl.removeModule("Rotatoes4");
        spl.removeModule("Smerge");
        spl.removeModule("Solomon16");
        spl.removeModule("Solomon4");
        spl.removeModule("Solomon8");
        spl.removeModule("Spleet");
        spl.removeModule("Splirge");
        spl.removeModule("Splort");
        spl.removeModule("Swerge");
        spl.removeModule("Undular");

    }
}

static void initStatic__AudibleInstruments()
{
    Plugin* const p = new Plugin;
    pluginInstance__AudibleInstruments = p;

    const StaticPluginLoader spl(p, "AudibleInstruments");
    if (spl.ok())
    {
        p->addModel(modelPlaits);

        spl.removeModule("Blinds");
        spl.removeModule("Braids");
        spl.removeModule("Branches");
        spl.removeModule("Clouds");
        spl.removeModule("Elements");
        spl.removeModule("Frames");
        spl.removeModule("Kinks");
        spl.removeModule("Links");
        spl.removeModule("Marbles");
        spl.removeModule("Rings");
        spl.removeModule("Ripples");
        spl.removeModule("Shades");
        spl.removeModule("Shelves");
        spl.removeModule("Stages");
        spl.removeModule("Streams");
        spl.removeModule("Tides");
        spl.removeModule("Tides2");
        spl.removeModule("Veils");
        spl.removeModule("Warps");
    }
}

static void initStatic__BogaudioModules()
{
    Plugin* const p = new Plugin;
    pluginInstance__BogaudioModules = p;

    const StaticPluginLoader spl(p, "BogaudioModules");
    if (spl.ok())
    {
        // Make sure to use match Cardinal theme
        Skins& skins(Skins::skins());
        skins._default = settings::preferDarkPanels ? "dark" : "light";

        p->addModel(modelAD);
        p->addModel(modelBogaudioLFO);
        p->addModel(modelBogaudioNoise);
        p->addModel(modelBogaudioVCA);
        p->addModel(modelBogaudioVCF);
        p->addModel(modelBogaudioVCO);
        p->addModel(modelOffset);
        p->addModel(modelSampleHold);
        p->addModel(modelSwitch);
        p->addModel(modelSwitch18);
        p->addModel(modelUnison);

        p->addModel(modelMono);
        p->addModel(modelAnalyzerXL);
        p->addModel(modelMix8);
        p->addModel(modelXFade);
        p->addModel(modelLVCF);
        p->addModel(modelStack);
        p->addModel(modelArp);
        p->addModel(modelUMix);
        p->addModel(modelLVCO);
        p->addModel(modelBool);
        p->addModel(modelBogaudioADSR);
        p->addModel(modelLLFO);
        p->addModel(modelFMOp);
        p->addModel(modelASR);
        p->addModel(modelMix4);
        p->addModel(modelPolyCon8);
        p->addModel(modelAddrSeqX);
        p->addModel(modelAddrSeq);
        p->addModel(modelMix4x);
        p->addModel(modelPressor);
        p->addModel(modelVelo);
        p->addModel(modelSlew);
        p->addModel(modelPulse);
        p->addModel(modelSine);
        p->addModel(modelDGate);
        p->addModel(modelVCAmp);
        p->addModel(modelMix8x);
        p->addModel(modelReftone);
        p->addModel(modelMatrix81);
        // cat plugins/BogaudioModules/plugin.json  | jq -r .modules[].slug - | sort
        spl.removeModule("Bogaudio-Additator");
        spl.removeModule("Bogaudio-AMRM");
        spl.removeModule("Bogaudio-Analyzer");
        spl.removeModule("Bogaudio-Assign");
        spl.removeModule("Bogaudio-Blank3");
        spl.removeModule("Bogaudio-Blank6");
        spl.removeModule("Bogaudio-Chirp");
        spl.removeModule("Bogaudio-Clpr");
        spl.removeModule("Bogaudio-Cmp");
        spl.removeModule("Bogaudio-CmpDist");
        spl.removeModule("Bogaudio-CVD");
        spl.removeModule("Bogaudio-DADSRH");
        spl.removeModule("Bogaudio-DADSRHPlus");
        spl.removeModule("Bogaudio-Detune");
        spl.removeModule("Bogaudio-Edge");
        spl.removeModule("Bogaudio-EightFO");
        spl.removeModule("Bogaudio-EightOne");
        spl.removeModule("Bogaudio-EQ");
        spl.removeModule("Bogaudio-EQS");
        spl.removeModule("Bogaudio-FFB");
        spl.removeModule("Bogaudio-FlipFlop");
        spl.removeModule("Bogaudio-Follow");
        spl.removeModule("Bogaudio-FourFO");
        spl.removeModule("Bogaudio-FourMan");
        spl.removeModule("Bogaudio-Inv");
        spl.removeModule("Bogaudio-Lgsw");
        spl.removeModule("Bogaudio-LLPG");
        spl.removeModule("Bogaudio-Lmtr");
        spl.removeModule("Bogaudio-LPG");
        spl.removeModule("Bogaudio-Manual");
        spl.removeModule("Bogaudio-Matrix18");
        spl.removeModule("Bogaudio-Matrix44");
        spl.removeModule("Bogaudio-Matrix44Cvm");
        spl.removeModule("Bogaudio-Matrix88");
        spl.removeModule("Bogaudio-Matrix88Cv");
        spl.removeModule("Bogaudio-Matrix88M");
        spl.removeModule("Bogaudio-MegaGate");
        spl.removeModule("Bogaudio-Mix1");
        spl.removeModule("Bogaudio-Mix2");
        spl.removeModule("Bogaudio-Mult");
        spl.removeModule("Bogaudio-Mumix");
        spl.removeModule("Bogaudio-Mute8");
        spl.removeModule("Bogaudio-Nsgt");
        spl.removeModule("Bogaudio-OneEight");
        spl.removeModule("Bogaudio-Pan");
        spl.removeModule("Bogaudio-PEQ");
        spl.removeModule("Bogaudio-PEQ14");
        spl.removeModule("Bogaudio-PEQ14XF");
        spl.removeModule("Bogaudio-PEQ6");
        spl.removeModule("Bogaudio-PEQ6XF");
        spl.removeModule("Bogaudio-Pgmr");
        spl.removeModule("Bogaudio-PgmrX");
        spl.removeModule("Bogaudio-PolyCon");
        spl.removeModule("Bogaudio-PolyMult");
        spl.removeModule("Bogaudio-PolyOff16");
        spl.removeModule("Bogaudio-PolyOff8");
        spl.removeModule("Bogaudio-Ranalyzer");
        spl.removeModule("Bogaudio-RGate");
        spl.removeModule("Bogaudio-Shaper");
        spl.removeModule("Bogaudio-ShaperPlus");
        spl.removeModule("Bogaudio-Sums");
        spl.removeModule("Bogaudio-Switch1616");
        spl.removeModule("Bogaudio-Switch44");
        spl.removeModule("Bogaudio-Switch81");
        spl.removeModule("Bogaudio-Switch88");
        spl.removeModule("Bogaudio-VCM");
        spl.removeModule("Bogaudio-Vish");
        spl.removeModule("Bogaudio-VU");
        spl.removeModule("Bogaudio-Walk");
        spl.removeModule("Bogaudio-Walk2");
        spl.removeModule("Bogaudio-XCO");
    }
}

static void initStatic__MockbaModular()
{
    Plugin* const p = new Plugin;
    pluginInstance__MockbaModular = p;

    const StaticPluginLoader spl(p, "MockbaModular");
    if (spl.ok())
    {
        spl.removeModule("Blank");
        spl.removeModule("Comparator");
        spl.removeModule("Countah");
        spl.removeModule("CZDblSine");
        spl.removeModule("CZOsc");
        spl.removeModule("CZPulse");
        spl.removeModule("CZReso1");
        spl.removeModule("CZReso2");
        spl.removeModule("CZReso3");
        spl.removeModule("CZSaw");
        spl.removeModule("CZSawPulse");
        spl.removeModule("CZSquare");
        spl.removeModule("Dividah");
        spl.removeModule("DualAND");
        spl.removeModule("DualBUFFER");
        spl.removeModule("DualNAND");
        spl.removeModule("DualNOR");
        spl.removeModule("DualNOT");
        spl.removeModule("DualOR");
        spl.removeModule("DualXNOR");
        spl.removeModule("DualXOR");
        spl.removeModule("Feidah");
        spl.removeModule("FeidahS");
        spl.removeModule("Filtah");
        spl.removeModule("Holdah");
        spl.removeModule("MaugOsc");
        spl.removeModule("MaugSaw");
        spl.removeModule("MaugSaw2");
        spl.removeModule("MaugShark");
        spl.removeModule("MaugSquare");
        spl.removeModule("MaugSquare2");
        spl.removeModule("MaugSquare3");
        spl.removeModule("MaugTriangle");
        spl.removeModule("Mixah");
        spl.removeModule("Mixah3");
        spl.removeModule("Pannah");
        spl.removeModule("PSelectah");
        spl.removeModule("ReVoltah");
        spl.removeModule("Selectah");
        spl.removeModule("Shapah");
        spl.removeModule("UDPClockMaster");
        spl.removeModule("UDPClockSlave");
    }
}

static void initStatic__surgext()
{
    Plugin* const p = new Plugin;
    pluginInstance__surgext = p;

    const StaticPluginLoader spl(p, "surgext");
    if (spl.ok())
    {
        p->addModel(modelVCOModern);
        p->addModel(modelVCOSine);
        /*
        p->addModel(modelVCOAlias);
        p->addModel(modelVCOClassic);
        p->addModel(modelVCOFM2);
        p->addModel(modelVCOFM3);
        p->addModel(modelVCOSHNoise);
        p->addModel(modelVCOString);
        p->addModel(modelVCOTwist);
        p->addModel(modelVCOWavetable);
        p->addModel(modelVCOWindow);
        */
        spl.removeModule("SurgeXTOSCAlias");
        spl.removeModule("SurgeXTOSCClassic");
        spl.removeModule("SurgeXTOSCFM2");
        spl.removeModule("SurgeXTOSCFM3");
        spl.removeModule("SurgeXTOSCSHNoise");
        spl.removeModule("SurgeXTOSCString");
        spl.removeModule("SurgeXTOSCTwist");
        spl.removeModule("SurgeXTOSCWavetable");
        spl.removeModule("SurgeXTOSCWindow");

        // Add the ported ones
        p->addModel(modelSurgeLFO);
        p->addModel(modelSurgeMixer);
        p->addModel(modelSurgeMixerSlider);
        p->addModel(modelSurgeModMatrix);
        p->addModel(modelSurgeWaveshaper);
        /*
        p->addModel(modelSurgeDelay);
        p->addModel(modelSurgeDelayLineByFreq);
        p->addModel(modelSurgeDelayLineByFreqExpanded);
        p->addModel(modelSurgeDigitalRingMods);
        p->addModel(modelSurgeVCF);
        */
        spl.removeModule("SurgeXTDelay");
        spl.removeModule("SurgeXTDelayLineByFreq");
        spl.removeModule("SurgeXTDelayLineByFreqExpanded");
        spl.removeModule("SurgeXTDigitalRingMod");
        spl.removeModule("SurgeXTVCF");

        p->addModel(modelFXNimbus);
        p->addModel(modelFXPhaser);
        p->addModel(modelFXChorus);
        p->addModel(modelFXReverb);
        p->addModel(modelFXDistortion);
        p->addModel(modelFXFlanger);
        p->addModel(modelFXSpringReverb);
        spl.removeModule("SurgeXTFXBonsai");
        spl.removeModule("SurgeXTFXChow");
        spl.removeModule("SurgeXTFXCombulator");
        spl.removeModule("SurgeXTDigitalRingMod");
        spl.removeModule("SurgeXTFXExciter");
        spl.removeModule("SurgeXTFXEnsemble");
        spl.removeModule("SurgeXTFXFrequencyShifter");
        spl.removeModule("SurgeXTFXNeuron");
        spl.removeModule("SurgeXTFXResonator");
        spl.removeModule("SurgeXTFXReverb2");
        spl.removeModule("SurgeXTFXRingMod");
        spl.removeModule("SurgeXTFXRotarySpeaker");
        spl.removeModule("SurgeXTFXTreeMonster");
        spl.removeModule("SurgeXTFXVocoder");

        /*
        p->addModel(modelEGxVCA);
        p->addModel(modelQuadAD);
        p->addModel(modelQuadLFO);
        p->addModel(modelUnisonHelper);
        p->addModel(modelUnisonHelperCVExpander);
        */
        spl.removeModule("SurgeXTEGxVCA");
        spl.removeModule("SurgeXTQuadAD");
        spl.removeModule("SurgeXTQuadLFO");
        spl.removeModule("SurgeXTUnisonHelper");
        spl.removeModule("SurgeXTUnisonHelperCVExpander");

        surgext_rack_initialize();
    }
}

static void initStatic__ValleyAudio()
{
    Plugin* const p = new Plugin;
    pluginInstance__ValleyAudio = p;

    const StaticPluginLoader spl(p, "ValleyAudio");
    if (spl.ok())
    {
        p->addModel(modelPlateau);

        // Dexter/Interzone left out for now: this submodule has been
        // restructured upstream since this block was last maintained (its
        // source files moved to new subfolders, and Dexter's
        // Osc4Core_SIMD.cpp no longer exists at all) -- re-enabling them
        // needs a real path/dependency audit, not just uncommenting.
        spl.removeModule("Amalgam");
        spl.removeModule("Dexter");
        spl.removeModule("Feline");
        spl.removeModule("Interzone");
        spl.removeModule("Terrorform");
        spl.removeModule("Topograph");
        spl.removeModule("uGraph");
    }
}

static void initStatic__Aluminium()
{
    Plugin* const p = new Plugin;
    pluginInstance__Aluminium = p;

    const StaticPluginLoader spl(p, "Aluminium");
    if (spl.ok())
    {
        p->addModel(modelPadX);
        p->addModel(modelZones);
        p->addModel(modelPads);
    }
}

static void initStatic__AmbientModules()
{
    Plugin* const p = new Plugin;
    pluginInstance__AmbientModules = p;

    const StaticPluginLoader spl(p, "AmbientModules");
    if (spl.ok())
    {
        p->addModel(modelLunarPapaSrapa);
        p->addModel(modelLunarSequencer);
        p->addModel(modelLunar50Drone);
        p->addModel(modelBlank);
        p->addModel(modelLunarLFO);
        p->addModel(modelLunarVCO);
    }
}

static void initStatic__cf()
{
    Plugin* const p = new Plugin;
    pluginInstance__cf = p;

    const StaticPluginLoader spl(p, "cf");
    if (spl.ok())
    {
        p->addModel(modelLABEL);
        spl.removeModule("ALGEBRA");
        spl.removeModule("BUFFER");
        spl.removeModule("CHOKE");
        spl.removeModule("CUBE");
        spl.removeModule("CUTS");
        spl.removeModule("DAVE");
        spl.removeModule("DISTO");
        spl.removeModule("EACH");
        spl.removeModule("FOUR");
        spl.removeModule("FUNKTION");
        spl.removeModule("L3DS3Q");
        spl.removeModule("LEDSEQ");
        spl.removeModule("MASTER");
        spl.removeModule("METRO");
        spl.removeModule("MONO");
        spl.removeModule("PATCH");
        spl.removeModule("PEAK");
        spl.removeModule("PLAY");
        spl.removeModule("PLAYER");
        spl.removeModule("SLIDERSEQ");
        spl.removeModule("STEPS");
        spl.removeModule("STEREO");
        spl.removeModule("SUB");
        spl.removeModule("VARIABLE");
        spl.removeModule("trSEQ");
    }
}

static void initStatic__unless_modules()
{
    Plugin* const p = new Plugin;
    pluginInstance__unless_modules = p;

    const StaticPluginLoader spl(p, "unless_modules");
    if (spl.ok())
    {
        p->addModel(modelPianoid);
        spl.removeModule("atoms");
        spl.removeModule("avoider");
        spl.removeModule("cantor");
        spl.removeModule("markov");
        spl.removeModule("piong");
        spl.removeModule("premuter");
        spl.removeModule("room");
        spl.removeModule("snake");
        spl.removeModule("towers");
    }
}

static void initStatic__ProducerPack()
{
    Plugin* const p = new Plugin;
    pluginInstance__ProducerPack = p;

    const StaticPluginLoader spl(p, "ProducerPack");
    if (spl.ok())
    {
        p->addModel(modelSeventiesComp);
        p->addModel(modelStereoWidth);
        p->addModel(modelDrumBus);
        spl.removeModule("AuxSends");
        spl.removeModule("Bitcrusher");
        spl.removeModule("Boost");
        spl.removeModule("DJFilter");
        spl.removeModule("Decay");
        spl.removeModule("SeventiesEQ");
        spl.removeModule("Spatializer");
        spl.removeModule("StereoCrossfader");
    }
}

static void initStatic__AS()
{
    Plugin* const p = new Plugin;
    pluginInstance__AS = p;

    const StaticPluginLoader spl(p, "AS");
    if (spl.ok())
    {
        p->addModel(modelStereoVUmeter);
        p->addModel(modelDelayPlusStereoFx);
        p->addModel(modelPhaserFx);
        p->addModel(modelMonoVUmeter);
        spl.removeModule("ADSR");
        spl.removeModule("AtNuVrTr");
        spl.removeModule("BPMCalc");
        spl.removeModule("BPMCalc2");
        spl.removeModule("BPMClock");
        spl.removeModule("BlankPanel4");
        spl.removeModule("BlankPanel6");
        spl.removeModule("BlankPanel8");
        spl.removeModule("BlankPanelSpecial");
        spl.removeModule("Cv2T");
        spl.removeModule("DelayPlusFx");
        spl.removeModule("Flow");
        spl.removeModule("KillGate");
        spl.removeModule("LaunchGate");
        spl.removeModule("Merge2_5");
        spl.removeModule("Mixer2ch");
        spl.removeModule("Mixer4ch");
        spl.removeModule("Mixer8ch");
        spl.removeModule("Multiple2_5");
        spl.removeModule("QuadVCA");
        spl.removeModule("ReScale");
        spl.removeModule("ReverbFx");
        spl.removeModule("ReverbStereoFx");
        spl.removeModule("SEQ16");
        spl.removeModule("SawOSC");
        spl.removeModule("SignalDelay");
        spl.removeModule("SineOSC");
        spl.removeModule("Steps");
        spl.removeModule("SuperDriveFx");
        spl.removeModule("SuperDriveStereoFx");
        spl.removeModule("TremoloFx");
        spl.removeModule("TremoloStereoFx");
        spl.removeModule("TriLFO");
        spl.removeModule("TriggersMKI");
        spl.removeModule("TriggersMKII");
        spl.removeModule("TriggersMKIII");
        spl.removeModule("VCA");
        spl.removeModule("WaveShaper");
        spl.removeModule("WaveShaperStereo");
        spl.removeModule("ZeroCV2T");
    }
}

static void initStatic__VCVRackPlugins()
{
    Plugin* const p = new Plugin;
    pluginInstance__VCVRackPlugins = p;

    const StaticPluginLoader spl(p, "VCVRackPlugins");
    if (spl.ok())
    {
        p->addModel(modelOscilloscope);
        p->addModel(modelBarGraph);
        spl.removeModule("AnalogueShiftRegister");
        spl.removeModule("Arpeggiator");
        spl.removeModule("Attenuator");
        spl.removeModule("Attenuverter");
        spl.removeModule("BasicSequencer8");
        spl.removeModule("BinaryComparator");
        spl.removeModule("BinarySequencer");
        spl.removeModule("BinarySequencerPlus");
        spl.removeModule("Blank12HP");
        spl.removeModule("Blank16HP");
        spl.removeModule("Blank20HP");
        spl.removeModule("Blank24HP");
        spl.removeModule("Blank2HP");
        spl.removeModule("Blank4HP");
        spl.removeModule("Blank8HP");
        spl.removeModule("BooleanAND");
        spl.removeModule("BooleanOR");
        spl.removeModule("BooleanVCNOT");
        spl.removeModule("BooleanXOR");
        spl.removeModule("Breakout");
        spl.removeModule("BurstGenerator");
        spl.removeModule("BurstGenerator64");
        spl.removeModule("BusRoute");
        spl.removeModule("BusRoute2");
        spl.removeModule("CVSpreader");
        spl.removeModule("Carousel");
        spl.removeModule("Chances");
        spl.removeModule("ClockDivider");
        spl.removeModule("ClockedRandomGateExpanderCV");
        spl.removeModule("ClockedRandomGateExpanderLog");
        spl.removeModule("ClockedRandomGates");
        spl.removeModule("Comparator");
        spl.removeModule("Euclid");
        spl.removeModule("EuclidExpanderCV");
        spl.removeModule("EventArranger");
        spl.removeModule("EventTimer");
        spl.removeModule("EventTimer2");
        spl.removeModule("Fade");
        spl.removeModule("FadeExpander");
        spl.removeModule("G2T");
        spl.removeModule("GateDelay");
        spl.removeModule("GateDelayMT");
        spl.removeModule("GateModifier");
        spl.removeModule("GateSequencer16");
        spl.removeModule("GateSequencer16b");
        spl.removeModule("GateSequencer8");
        spl.removeModule("GatedComparator");
        spl.removeModule("HyperManiacalLFO");
        spl.removeModule("HyperManiacalLFOExpander");
        spl.removeModule("LightStrip");
        spl.removeModule("Mangler");
        spl.removeModule("Manifold");
        spl.removeModule("ManualCV");
        spl.removeModule("ManualCV2");
        spl.removeModule("ManualGate");
        spl.removeModule("MasterReset");
        spl.removeModule("MatrixCombiner");
        spl.removeModule("MatrixMixer");
        spl.removeModule("Megalomaniac");
        spl.removeModule("MiniMix");
        spl.removeModule("MinimusMaximus");
        spl.removeModule("Mixer");
        spl.removeModule("MorphShaper");
        spl.removeModule("Mult");
        spl.removeModule("MultiStepSequencer");
        spl.removeModule("Multiplexer");
        spl.removeModule("Mute");
        spl.removeModule("Mute-iple");
        spl.removeModule("NibbleTriggerSequencer");
        spl.removeModule("OctetTriggerSequencer");
        spl.removeModule("OctetTriggerSequencerCVExpander");
        spl.removeModule("OctetTriggerSequencerGateExpander");
        spl.removeModule("OffsetGenerator");
        spl.removeModule("Palette");
        spl.removeModule("PolyChances");
        spl.removeModule("PolyG2T");
        spl.removeModule("PolyGateModifier");
        spl.removeModule("PolyLogic");
        spl.removeModule("PolyMinMax");
        spl.removeModule("PolyMute");
        spl.removeModule("PolyVCPolarizer");
        spl.removeModule("PolyVCSwitch");
        spl.removeModule("PolyrhythmicGenerator");
        spl.removeModule("PolyrhythmicGeneratorMkII");
        spl.removeModule("RackEarLeft");
        spl.removeModule("RackEarRight");
        spl.removeModule("RandomAccessSwitch18");
        spl.removeModule("RandomAccessSwitch81");
        spl.removeModule("Rectifier");
        spl.removeModule("SRFlipFlop");
        spl.removeModule("SampleAndHold");
        spl.removeModule("SampleAndHold2");
        spl.removeModule("SequenceEncoder");
        spl.removeModule("Sequencer16");
        spl.removeModule("Sequencer64");
        spl.removeModule("Sequencer8");
        spl.removeModule("SequencerChannel16");
        spl.removeModule("SequencerChannel8");
        spl.removeModule("SequencerExpanderCV8");
        spl.removeModule("SequencerExpanderLOG8");
        spl.removeModule("SequencerExpanderOut8");
        spl.removeModule("SequencerExpanderRM8");
        spl.removeModule("SequencerExpanderTSG");
        spl.removeModule("SequencerExpanderTrig8");
        spl.removeModule("SequencerGates16");
        spl.removeModule("SequencerGates8");
        spl.removeModule("SequencerTriggers16");
        spl.removeModule("SequencerTriggers8");
        spl.removeModule("ShepardGenerator");
        spl.removeModule("ShiftRegister16");
        spl.removeModule("ShiftRegister32");
        spl.removeModule("SingleDFlipFlop");
        spl.removeModule("SingleSRFlipFlop");
        spl.removeModule("SingleTFlipFlop");
        spl.removeModule("SlopeDetector");
        spl.removeModule("Stack");
        spl.removeModule("StartupDelay");
        spl.removeModule("StepSequencer8");
        spl.removeModule("SubHarmonicGenerator");
        spl.removeModule("Switch16To1");
        spl.removeModule("Switch1To16");
        spl.removeModule("Switch1To8");
        spl.removeModule("Switch2");
        spl.removeModule("Switch3");
        spl.removeModule("Switch4");
        spl.removeModule("Switch8To1");
        spl.removeModule("TFlipFlop");
        spl.removeModule("TriggerSequencer16");
        spl.removeModule("TriggerSequencer8");
        spl.removeModule("VCFrequencyDivider");
        spl.removeModule("VCFrequencyDividerMkII");
        spl.removeModule("VCPolarizer");
        spl.removeModule("VCPulseDivider");
        spl.removeModule("VoltageControlledSwitch");
        spl.removeModule("VoltageInverter");
        spl.removeModule("VoltageScaler");
    }
}

static void initStatic__GrandeModular()
{
    Plugin* const p = new Plugin;
    pluginInstance__GrandeModular = p;

    const StaticPluginLoader spl(p, "GrandeModular");
    if (spl.ok())
    {
        p->addModel(modelMerge8);
        spl.removeModule("Clip");
        spl.removeModule("Compare3");
        spl.removeModule("LFO3");
        spl.removeModule("LFO4");
        spl.removeModule("Logic");
        spl.removeModule("MergeSplit4");
        spl.removeModule("MicrotonalChords");
        spl.removeModule("MicrotonalNotes");
        spl.removeModule("NoteMT");
        spl.removeModule("Peak");
        spl.removeModule("PolyMergeResplit");
        spl.removeModule("PolySplit");
        spl.removeModule("Push");
        spl.removeModule("Quant");
        spl.removeModule("QuantIntervals");
        spl.removeModule("QuantMT");
        spl.removeModule("SampleDelays");
        spl.removeModule("Scale");
        spl.removeModule("Split8");
        spl.removeModule("Tails");
        spl.removeModule("Tails4");
        spl.removeModule("VCA3");
        spl.removeModule("VCA4");
        spl.removeModule("VarSampleDelays");
    }
}

static void initStatic__ImpromptuModular()
{
    Plugin* const p = new Plugin;
    pluginInstance__ImpromptuModular = p;

    const StaticPluginLoader spl(p, "ImpromptuModular");
    if (spl.ok())
    {
        // Mini uses StaticPluginLoader instead of calling the pack's real init(),
        // so the line that normally sets defaultPanelContrast away from its
        // zero-initialized value (making panels render pure black) never runs.
        readThemeAndContrastFromDefault();
        p->addModel(modelClkd);
        p->addModel(modelClocked);
        p->addModel(modelClockedExpander);
        p->addModel(modelPhraseSeq16);
        p->addModel(modelPhraseSeqExpander);
        spl.removeModule("Adaptive-Quantizer");
        spl.removeModule("Big-Button-Seq");
        spl.removeModule("Big-Button-Seq2");
        spl.removeModule("Blank-Panel");
        spl.removeModule("Chord-Key");
        spl.removeModule("Chord-Key-Expander");
        spl.removeModule("Cv-Pad");
        spl.removeModule("Foundry");
        spl.removeModule("Foundry-Expander");
        spl.removeModule("Four-View");
        spl.removeModule("Gate-Seq-64");
        spl.removeModule("Gate-Seq-64-Expander");
        spl.removeModule("Hotkey");
        spl.removeModule("NoteEcho");
        spl.removeModule("NoteFilter");
        spl.removeModule("NoteLoop");
        spl.removeModule("Part-Gate-Split");
        spl.removeModule("Phrase-Seq-32");
        spl.removeModule("Prob-Key");
        spl.removeModule("Semi-ModularSynth");
        spl.removeModule("Sygen");
        spl.removeModule("Tact");
        spl.removeModule("Tact1");
        spl.removeModule("TactG");
        spl.removeModule("Twelve-Key");
        spl.removeModule("Variations");
        spl.removeModule("Write-Seq-32");
        spl.removeModule("Write-Seq-64");
    }
}

static void initStatic__JW_Modules()
{
    Plugin* const p = new Plugin;
    pluginInstance__JW = p;

    const StaticPluginLoader spl(p, "JW-Modules");
    if (spl.ok())
    {
        p->addModel(modelFullScope);
        p->addModel(modelGrains);
        spl.removeModule("0Cat");
        spl.removeModule("1Pattern");
        spl.removeModule("8Seq");
        spl.removeModule("AbcdSeq");
        spl.removeModule("Add5");
        spl.removeModule("Arrange");
        spl.removeModule("Arrange16");
        spl.removeModule("BlankPanel_1HP");
        spl.removeModule("BlankPanel_2HP");
        spl.removeModule("BlankPanel_4HP");
        spl.removeModule("BlankPanel_LG");
        spl.removeModule("BlankPanel_MD");
        spl.removeModule("BlankPanel_SM");
        spl.removeModule("BouncyBalls");
        spl.removeModule("Buffer");
        spl.removeModule("CoolBreeze");
        spl.removeModule("Crawl");
        spl.removeModule("D1v1de");
        spl.removeModule("DivSeq");
        spl.removeModule("FM16Seq");
        spl.removeModule("FM4Dice");
        spl.removeModule("Fract");
        spl.removeModule("GridSeq");
        spl.removeModule("MinMax");
        spl.removeModule("NoteSeq");
        spl.removeModule("NoteSeq16");
        spl.removeModule("NoteSeqFu");
        spl.removeModule("Patterns");
        spl.removeModule("Pete");
        spl.removeModule("Pres1t");
        spl.removeModule("Quantizer");
        spl.removeModule("RandomSound");
        spl.removeModule("SampleGrid");
        spl.removeModule("ShiftRegRnd");
        spl.removeModule("SimpleClock");
        spl.removeModule("StereoSwitch");
        spl.removeModule("StereoSwitchInv");
        spl.removeModule("Str1ker");
        spl.removeModule("Subtract5");
        spl.removeModule("ThingThing");
        spl.removeModule("Timer");
        spl.removeModule("Tree");
        spl.removeModule("Trigs");
        spl.removeModule("Trigs128");
        spl.removeModule("WavHead");
        spl.removeModule("XYPad");
    }
}

static void initStatic__LittleUtils()
{
    Plugin* const p = new Plugin;
    pluginInstance__LittleUtils = p;

    const StaticPluginLoader spl(p, "LittleUtils");
    if (spl.ok())
    {
        p->addModel(modelButtonModule);
        spl.removeModule("BiasSemitone");
        spl.removeModule("MultiplyDivide");
        spl.removeModule("PulseGenerator");
        spl.removeModule("TeleportIn");
        spl.removeModule("TeleportOut");
    }
}

static void initStatic__MindMeldModular()
{
    Plugin* const p = new Plugin;
    pluginInstance__MindMeld = p;

    const StaticPluginLoader spl(p, "MindMeldModular");
    if (spl.ok())
    {
        p->addModel(modelMasterChannel);
        p->addModel(modelMixMasterJr);
        p->addModel(modelAuxExpanderJr);
        p->addModel(modelMSMelder);
        p->addModel(modelBassMaster);
        p->addModel(modelBassMasterJr);
        spl.removeModule("AuxExpander");
        spl.removeModule("EqExpander");
        spl.removeModule("EqMaster");
        spl.removeModule("Meld");
        spl.removeModule("MixMaster");
        spl.removeModule("PatchMaster");
        spl.removeModule("PatchMasterBlank");
        spl.removeModule("RouteMasterMono1to5");
        spl.removeModule("RouteMasterMono5to1");
        spl.removeModule("RouteMasterStereo1to5");
        spl.removeModule("RouteMasterStereo5to1");
        spl.removeModule("ShapeMaster");
        spl.removeModule("Unmeld");
    }
}

static void initStatic__SignalFunctionSet_VCV_Rack()
{
    Plugin* const p = new Plugin;
    pluginInstance__SignalFunctionSet_VCV_Rack = p;

    const StaticPluginLoader spl(p, "SignalFunctionSet-VCV-Rack");
    if (spl.ok())
    {
        p->addModel(modelFill);
        spl.removeModule("Arrange");
        spl.removeModule("Band");
        spl.removeModule("Beat");
        spl.removeModule("Chance");
        spl.removeModule("Chime");
        spl.removeModule("Crystal");
        spl.removeModule("Cycle");
        spl.removeModule("Drift");
        spl.removeModule("Fugue");
        spl.removeModule("FugueX");
        spl.removeModule("Gravity");
        spl.removeModule("Intone");
        spl.removeModule("Key");
        spl.removeModule("Kit");
        spl.removeModule("Loom");
        spl.removeModule("MetaFugue");
        spl.removeModule("Meter");
        spl.removeModule("MeterX");
        spl.removeModule("Muse");
        spl.removeModule("Note");
        spl.removeModule("OpEnv");
        spl.removeModule("OpMorph");
        spl.removeModule("Operator");
        spl.removeModule("Overtone");
        spl.removeModule("Phase");
        spl.removeModule("Play");
        spl.removeModule("Ratio");
        spl.removeModule("Record");
        spl.removeModule("Shift");
        spl.removeModule("Slice");
        spl.removeModule("Slide");
        spl.removeModule("SlideX");
        spl.removeModule("Swell");
        spl.removeModule("Tine");
        spl.removeModule("Trace");
        spl.removeModule("Vac");
        spl.removeModule("Wave");
        spl.removeModule("gsx");
    }
}

static void initStatic__stoermelder_packone()
{
    Plugin* const p = new Plugin;
    pluginInstance__stoermelder_p1 = p;

    const StaticPluginLoader spl(p, "stoermelder-packone");
    if (spl.ok())
    {
        p->addModel(modelGlue);
        spl.removeModule("Affix");
        spl.removeModule("AffixMicro");
        spl.removeModule("Ahab");
        spl.removeModule("Arena");
        spl.removeModule("AudioInterface64");
        spl.removeModule("Bolt");
        spl.removeModule("CVMap");
        spl.removeModule("CVMapCtx");
        spl.removeModule("CVMapMicro");
        spl.removeModule("CVPam");
        spl.removeModule("Dirt");
        spl.removeModule("EightFace");
        spl.removeModule("EightFaceMk2");
        spl.removeModule("EightFaceMk2Ex");
        spl.removeModule("EightFaceX2");
        spl.removeModule("FourRounds");
        spl.removeModule("Goto");
        spl.removeModule("Grip");
        spl.removeModule("Hive");
        spl.removeModule("Infix");
        spl.removeModule("InfixMicro");
        spl.removeModule("Intermix");
        spl.removeModule("IntermixEnv");
        spl.removeModule("IntermixFade");
        spl.removeModule("IntermixGate");
        spl.removeModule("Macro");
        spl.removeModule("Maze");
        spl.removeModule("Mb");
        spl.removeModule("Me");
        spl.removeModule("MidiCat");
        spl.removeModule("MidiCatClk");
        spl.removeModule("MidiCatCtx");
        spl.removeModule("MidiCatEx");
        spl.removeModule("MidiCatFine");
        spl.removeModule("MidiCatXl");
        spl.removeModule("MidiEsx");
        spl.removeModule("MidiKey");
        spl.removeModule("MidiMon");
        spl.removeModule("MidiPlug");
        spl.removeModule("MidiStep");
        spl.removeModule("Mirror");
        spl.removeModule("Orbit");
        spl.removeModule("PanicRoom");
        spl.removeModule("Pile");
        spl.removeModule("PilePoly");
        spl.removeModule("Raw");
        spl.removeModule("ReMoveLite");
        spl.removeModule("RotorA");
        spl.removeModule("Sail");
        spl.removeModule("Sipo");
        spl.removeModule("Siren");
        spl.removeModule("Spin");
        spl.removeModule("Strip");
        spl.removeModule("StripBay4");
        spl.removeModule("StripPp");
        spl.removeModule("Stroke");
        spl.removeModule("Transit");
        spl.removeModule("TransitEx");
        spl.removeModule("X4");
    }
}

static void initStatic__submit_vcv_modules()
{
    Plugin* const p = new Plugin;
    pluginInstance__submit_vcv_modules = p;

    const StaticPluginLoader spl(p, "submit-vcv-modules");
    if (spl.ok())
    {
        p->addModel(modelTag);
        spl.removeModule("Chain");
        spl.removeModule("Chrono");
        spl.removeModule("Circles");
        spl.removeModule("Clang");
        spl.removeModule("Drift");
        spl.removeModule("Flip");
        spl.removeModule("Gain");
        spl.removeModule("Impact");
        spl.removeModule("Loop");
        spl.removeModule("Master");
        spl.removeModule("Orbit");
        spl.removeModule("Pulse");
        spl.removeModule("React");
        spl.removeModule("Set");
        spl.removeModule("Shape");
        spl.removeModule("Squeeze");
        spl.removeModule("Sub");
        spl.removeModule("SumM4");
        spl.removeModule("SumS4");
        spl.removeModule("Sweep");
        spl.removeModule("Sync");
    }
}

static void initStatic__Venom()
{
    Plugin* const p = new Plugin;
    pluginInstance__Venom = p;

    const StaticPluginLoader spl(p, "Venom");
    if (spl.ok())
    {
        p->addModel(modelVenomMixSolo);
        p->addModel(modelVenomPolyUnison);
        p->addModel(modelVenomBayOutput);
        p->addModel(modelVenomPolyScale);
        p->addModel(modelVenomMixFade2);
        p->addModel(modelVenomBayNorm);
        p->addModel(modelVenomPolyOffset);
        p->addModel(modelVenomMixPan);
        p->addModel(modelVenomKnob5);
        p->addModel(modelVenomMixFade);
        p->addModel(modelVenomMixMute);
        p->addModel(modelVenomBayInput);
        p->addModel(modelVenomMixSend);
        p->addModel(modelVenomMix4);
        p->addModel(modelVenomMixOffset);
        p->addModel(modelVenomMix4Stereo);
        p->addModel(modelVenomCloneMerge);
        p->addModel(modelVenomVCAMix4);
        p->addModel(modelVenomPush5);
        p->addModel(modelVenomBypass);
        p->addModel(modelVenomVCAMix4Stereo);
        spl.removeModule("AD_ASR");
        spl.removeModule("AuxClone");
        spl.removeModule("BenjolinGatesExpander");
        spl.removeModule("BenjolinOsc");
        spl.removeModule("BenjolinVoltsExpander");
        spl.removeModule("BernoulliSwitch");
        spl.removeModule("BernoulliSwitchExpander");
        spl.removeModule("Blocker");
        spl.removeModule("Compare2");
        spl.removeModule("CrossFade3D");
        spl.removeModule("HQ");
        spl.removeModule("LinearBeats");
        spl.removeModule("LinearBeatsExpander");
        spl.removeModule("Logic");
        spl.removeModule("Merge4x2");
        spl.removeModule("MergeSplit");
        spl.removeModule("MousePad");
        spl.removeModule("MultiMerge");
        spl.removeModule("MultiSplit");
        spl.removeModule("NORSIQChord2Scale");
        spl.removeModule("NORS_IQ");
        spl.removeModule("NullCable");
        spl.removeModule("Octaver");
        spl.removeModule("Oscillator");
        spl.removeModule("Pan3D");
        spl.removeModule("PolyClone");
        spl.removeModule("PolyFade");
        spl.removeModule("PolyMute");
        spl.removeModule("PolyPrune");
        spl.removeModule("PolySHASR");
        spl.removeModule("QuadVCPolarizer");
        spl.removeModule("REXCV");
        spl.removeModule("Recurse");
        spl.removeModule("RecurseStereo");
        spl.removeModule("Reformation");
        spl.removeModule("RhythmExplorer");
        spl.removeModule("SVF");
        spl.removeModule("ShapedVCA");
        spl.removeModule("Slew");
        spl.removeModule("SphereToXYZ");
        spl.removeModule("Split4x2");
        spl.removeModule("Thru");
        spl.removeModule("VCOUnit");
        spl.removeModule("VenomBlank");
        spl.removeModule("WaveFolder");
        spl.removeModule("WaveMangler");
        spl.removeModule("WaveMultiplier");
        spl.removeModule("WidgetMenuExtender");
        spl.removeModule("WinComp");
        spl.removeModule("XM_OP");
    }
}

static void initStatic__Autinn()
{
    Plugin* const p = new Plugin;
    pluginInstance__Autinn = p;

    const StaticPluginLoader spl(p, "Autinn");
    if (spl.ok())
    {
        p->addModel(modelAutinnSnare);
        p->addModel(modelAmp);
        p->addModel(modelKicker);
        p->addModel(modelAutinnScope);
        spl.removeModule("Alias");
        spl.removeModule("Au");
        spl.removeModule("Bass");
        spl.removeModule("Big");
        spl.removeModule("Boomerang");
        spl.removeModule("CVConverter");
        spl.removeModule("Chord");
        spl.removeModule("Coil");
        spl.removeModule("Deadband");
        spl.removeModule("Digi");
        spl.removeModule("Disee");
        spl.removeModule("Distortion");
        spl.removeModule("Excavi");
        spl.removeModule("Fauna");
        spl.removeModule("Flopper");
        spl.removeModule("Geiger");
        spl.removeModule("Jette");
        spl.removeModule("Melody");
        spl.removeModule("Mixer6");
        spl.removeModule("Non");
        spl.removeModule("Overdrive");
        spl.removeModule("Oxcart");
        spl.removeModule("Retri");
        spl.removeModule("Saw");
        spl.removeModule("Saw2");
        spl.removeModule("Sjip");
        spl.removeModule("Square");
        spl.removeModule("Trace");
        spl.removeModule("TriBand");
        spl.removeModule("Vector");
        spl.removeModule("Vibrato");
        spl.removeModule("Zod");
    }
}

static void initStatic__Biset()
{
    Plugin* const p = new Plugin;
    pluginInstance__Biset = p;

    const StaticPluginLoader spl(p, "Biset");
    if (spl.ok())
    {
        p->addModel(modelBisetBlank);
        spl.removeModule("Biset-Igc");
        spl.removeModule("Biset-Omega3");
        spl.removeModule("Biset-Omega6");
        spl.removeModule("Biset-Gbu");
        spl.removeModule("Biset-Pkm");
        spl.removeModule("Biset-Tracker");
        spl.removeModule("Biset-Tracker-Synth");
        spl.removeModule("Biset-Tracker-Drum");
        spl.removeModule("Biset-Tracker-Clock");
        spl.removeModule("Biset-Tracker-Phase");
        spl.removeModule("Biset-Tracker-Quant");
        spl.removeModule("Biset-Tracker-State");
        spl.removeModule("Biset-Tracker-Control");
        spl.removeModule("Biset-Regex");
        spl.removeModule("Biset-Regex-Condensed");
        spl.removeModule("Biset-Regex-Exp");
        spl.removeModule("Biset-Tree");
        spl.removeModule("Biset-Tree-Seed");
        spl.removeModule("Biset-Segfault");
    }
}

static void initStatic__alefsbits()
{
    Plugin* const p = new Plugin;
    pluginInstance__alefsbits = p;

    const StaticPluginLoader spl(p, "alefsbits");
    if (spl.ok())
    {
        p->addModel(modelLights);
        spl.removeModule("blank6hp");
        spl.removeModule("fibb");
        spl.removeModule("logic");
        spl.removeModule("lucc");
        spl.removeModule("math");
        spl.removeModule("mlt");
        spl.removeModule("noize");
        spl.removeModule("nos");
        spl.removeModule("octsclr");
        spl.removeModule("polycounter");
        spl.removeModule("polyplay");
        spl.removeModule("polyrand");
        spl.removeModule("polyshuffle");
        spl.removeModule("probablynot");
        spl.removeModule("shift");
        spl.removeModule("simplexandhold");
        spl.removeModule("slips");
        spl.removeModule("slipspander");
        spl.removeModule("steps");
        spl.removeModule("turnt");
    }
}

static void initStatic__HetrickCV()
{
    Plugin* const p = new Plugin;
    pluginInstance__HetrickCV = p;

    const StaticPluginLoader spl(p, "HetrickCV");
    if (spl.ok())
    {
#define modelMinMax modelHetrickCVMinMax
#define modelMidSide modelHetrickCVMidSide
        p->addModel(modelMinMax);
        p->addModel(modelMidSide);
#undef modelMinMax
#undef modelMidSide
        spl.removeModule("2To4");
        spl.removeModule("ASR");
        spl.removeModule("AmplitudeShaper");
        spl.removeModule("AnalogToDigital");
        spl.removeModule("BinaryCounter");
        spl.removeModule("BinaryGate");
        spl.removeModule("BinaryNoise");
        spl.removeModule("Bitshift");
        spl.removeModule("BlankPanel");
        spl.removeModule("Boolean3");
        spl.removeModule("Chaos1Op");
        spl.removeModule("Chaos2Op");
        spl.removeModule("Chaos3Op");
        spl.removeModule("ChaoticAttractors");
        spl.removeModule("ClockToPhasor");
        spl.removeModule("ClockedNoise");
        spl.removeModule("Comparator");
        spl.removeModule("Contrast");
        spl.removeModule("Crackle");
        spl.removeModule("DataCompander");
        spl.removeModule("Delta");
        spl.removeModule("DigitalToAnalog");
        spl.removeModule("Dust");
        spl.removeModule("Exponent");
        spl.removeModule("FBSineChaos");
        spl.removeModule("FlipFlop");
        spl.removeModule("FlipPan");
        spl.removeModule("GateDelay");
        spl.removeModule("GateJunction");
        spl.removeModule("GateJunctionExp");
        spl.removeModule("Gingerbread");
        spl.removeModule("LogicCombine");
        spl.removeModule("Normals");
        spl.removeModule("PhaseDrivenSequencer");
        spl.removeModule("PhaseDrivenSequencer32");
        spl.removeModule("PhasorAnalyzer");
        spl.removeModule("PhasorBurstGen");
        spl.removeModule("PhasorDivMult");
        spl.removeModule("PhasorEuclidean");
        spl.removeModule("PhasorFreezer");
        spl.removeModule("PhasorGates");
        spl.removeModule("PhasorGates32");
        spl.removeModule("PhasorGates64");
        spl.removeModule("PhasorGen");
        spl.removeModule("PhasorGeometry");
        spl.removeModule("PhasorHumanizer");
        spl.removeModule("PhasorMixer");
        spl.removeModule("PhasorOctature");
        spl.removeModule("PhasorProbability");
        spl.removeModule("PhasorQuadrature");
        spl.removeModule("PhasorRandom");
        spl.removeModule("PhasorRanger");
        spl.removeModule("PhasorReset");
        spl.removeModule("PhasorRhythmGroup");
        spl.removeModule("PhasorShape");
        spl.removeModule("PhasorShift");
        spl.removeModule("PhasorSplitter");
        spl.removeModule("PhasorStutter");
        spl.removeModule("PhasorSubstepShape");
        spl.removeModule("PhasorSwing");
        spl.removeModule("PhasorTimetable");
        spl.removeModule("PhasorToClock");
        spl.removeModule("PhasorToLFO");
        spl.removeModule("PhasorToRandom");
        spl.removeModule("PhasorToWaveforms");
        spl.removeModule("PolymetricPhasors");
        spl.removeModule("Probability");
        spl.removeModule("RandomGates");
        spl.removeModule("Rotator");
        spl.removeModule("Rungler");
        spl.removeModule("Scanner");
        spl.removeModule("TrigShaper");
        spl.removeModule("VectorMix");
        spl.removeModule("Waveshaper");
        spl.removeModule("XYToPolar");
    }
}

static void initStatic__CellaVCV()
{
    Plugin* const p = new Plugin;
    pluginInstance__CellaVCV = p;

    const StaticPluginLoader spl(p, "CellaVCV");
    if (spl.ok())
    {
        p->addModel(modelLoud);
        p->addModel(modelLoudnessMeter);
        spl.removeModule("2State");
        spl.removeModule("Bezier");
        spl.removeModule("Bytebeat");
        spl.removeModule("CognitiveShift");
        spl.removeModule("Euler");
        spl.removeModule("FrequencyAnalyzer");
        spl.removeModule("Integral");
        spl.removeModule("LoudnessCV");
        spl.removeModule("Resonators");
        spl.removeModule("Rich");
        spl.removeModule("Spectrum");
        spl.removeModule("TwinPeaks");
    }
}

static void initStatic__Kilpatrick_Toolbox()
{
    Plugin* const p = new Plugin;
    pluginInstance__Kilpatrick_Toolbox = p;

    const StaticPluginLoader spl(p, "Kilpatrick-Toolbox");
    if (spl.ok())
    {
        p->addModel(modelStereo_Meter);
        p->addModel(modelMulti_Meter);
        spl.removeModule("MIDI_CC_Note");
        spl.removeModule("MIDI_CV");
        spl.removeModule("MIDI_Channel");
        spl.removeModule("MIDI_Clock");
        spl.removeModule("MIDI_Input");
        spl.removeModule("MIDI_Mapper");
        spl.removeModule("MIDI_Merger");
        spl.removeModule("MIDI_Monitor");
        spl.removeModule("MIDI_Output");
        spl.removeModule("MIDI_Repeater");
        spl.removeModule("Quad_Decoder");
        spl.removeModule("Quad_Encoder");
        spl.removeModule("Quad_Panner");
        spl.removeModule("Test_Osc");
    }
}

static void initStatic__mschack_VCV_Rack_Plugins()
{
    Plugin* const p = new Plugin;
    pluginInstance__mschack_VCV_Rack_Plugins = p;

    const StaticPluginLoader spl(p, "mschack-VCV-Rack-Plugins");
    if (spl.ok())
    {
        p->addModel(modelPingPong);
        spl.removeModule("ARP700");
        spl.removeModule("ASAF8");
        spl.removeModule("Alienz");
        spl.removeModule("Compressor1");
        spl.removeModule("Dronez");
        spl.removeModule("Lorenz");
        spl.removeModule("MasterClockx4");
        spl.removeModule("Maude221");
        spl.removeModule("Mix_16_4_4");
        spl.removeModule("Mix_24_4_4");
        spl.removeModule("Mix_4_0_4");
        spl.removeModule("Mix_9_3_4");
        spl.removeModule("Morze");
        spl.removeModule("OSC_WaveMorph_3");
        spl.removeModule("Osc_3Ch_Widget");
        spl.removeModule("SEQ_Envelope_8");
        spl.removeModule("Seq_6ch_32step");
        spl.removeModule("StepDelay");
        spl.removeModule("SynthDrums");
        spl.removeModule("TriadSeq2");
        spl.removeModule("Windz");
    }
}

static void initStatic__kathode()
{
    Plugin* const p = new Plugin;
    pluginInstance__kathode = p;

    const StaticPluginLoader spl(p, "kathode");
    if (spl.ok())
    {
        p->addModel(modelKathode);
    }
}

void initStaticPlugins()
{
    initStatic__Cardinal();
    initStatic__Fundamental();
    initStatic__Aria();
    initStatic__AudibleInstruments();
    initStatic__BogaudioModules();
    initStatic__MockbaModular();
    initStatic__surgext();
    initStatic__Aluminium();

    initStatic__AmbientModules();

    initStatic__cf();

    initStatic__unless_modules();

    initStatic__ValleyAudio();

    initStatic__ProducerPack();

    initStatic__AS();

    initStatic__VCVRackPlugins();

    initStatic__GrandeModular();

    initStatic__ImpromptuModular();

    initStatic__JW_Modules();

    initStatic__LittleUtils();

    initStatic__MindMeldModular();

    initStatic__SignalFunctionSet_VCV_Rack();

    initStatic__stoermelder_packone();

    initStatic__submit_vcv_modules();


    initStatic__Venom();

    initStatic__Autinn();

    initStatic__Biset();

    initStatic__alefsbits();

    initStatic__HetrickCV();

    initStatic__CellaVCV();

    initStatic__Kilpatrick_Toolbox();

    initStatic__mschack_VCV_Rack_Plugins();

    initStatic__kathode();
}

void destroyStaticPlugins()
{
    for (Plugin* p : plugins)
        delete p;
    plugins.clear();
}

void updateStaticPluginsDarkMode()
{
    const bool darkMode = settings::preferDarkPanels;
    // bogaudio
    {
        Skins& skins(Skins::skins());
        skins._default = darkMode ? "dark" : "light";

        std::lock_guard<std::mutex> lock(skins._defaultSkinListenersLock);
        for (auto listener : skins._defaultSkinListeners) {
            listener->defaultSkinChanged(skins._default);
        }
    }
    // surgext
    {
        surgext_rack_update_theme();
    }
}

}
}
