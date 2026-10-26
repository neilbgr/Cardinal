# DISTRHO Cardinal (neilbgr edition)

## About this fork

This is a personal fork of [DISTRHO Cardinal](https://github.com/DISTRHO/Cardinal), built as "Cardinal (neilbgr edition)". Its purpose is to ship two module packs inside Cardinal: [AmbientModules](https://github.com/neilbgr/AmbientModules) (modules inspired by the Elta Music SOLAR 42F) and [Aluminium](https://github.com/neilbgr/Aluminium) (Zones, Pads, PadX, Fader/Faders2/Faders4 and Buttons, for live performance with MIDI controllers).

[![All AmbientModules panels](https://raw.githubusercontent.com/neilbgr/AmbientModules/main/docs/images/AllModules_Cream.png)](https://github.com/neilbgr/AmbientModules)

[![All Aluminium panels](https://raw.githubusercontent.com/neilbgr/Aluminium/main/docs/images/AllModules_Dark.png)](https://github.com/neilbgr/Aluminium)

The DISTRHO team doesn't accept AI-assisted code, so these modules won't be included in the official Cardinal. Both packs, and the changes this fork makes to Cardinal, were written with an AI coding assistant (Claude Code), under the direction of a human developer who reviewed, tested and approved every change before it was committed. See the "AI disclosure" section of each pack's README for details.

Both packs are also available for free in VCV Rack, from the VCV Library ([AmbientModules](https://library.vcvrack.com/AmbientModules), [Aluminium](https://library.vcvrack.com/Aluminium)). For those who prefer Cardinal (standalone, or as a plugin in their DAW), this fork ships them built in.

This fork also widens the Cardinal Mini module selection, including a few open-source packs not in official Cardinal (marked "Cardinal Mini only" in [Included modules](#included-modules)).

Builds of this fork use their own plugin names and IDs ("Cardinal (neilbgr edition)"), so they install next to an official Cardinal without clashing. Releases: https://github.com/neilbgr/Cardinal/releases.

The rest of this README is the upstream Cardinal README, adapted where this fork differs.

*Cardinal, the Rack!*

Cardinal is a free and open-source virtual modular synthesizer plugin,
available in AudioUnit/CLAP/LV2/VST2/VST3 plugin formats and as a standalone app for FreeBSD, Linux, macOS, Windows and the Web.  
It is based on the popular [VCV Rack](https://vcvrack.com/) but with a focus on being a fully self-contained plugin version.

More specifically, this is a [DPF-based](https://github.com/DISTRHO/DPF/)
plugin wrapper around [VCV Rack](https://github.com/VCVRack/Rack/),
using its code directly instead of forking the project,
with the target of having a **self-contained, fully free and open-source plugin version of Rack**.  
See the [why section](#Why) below for the reasons Cardinal exists,
also for frequently asked questions check this [FAQ document](docs/FAQ.md).

Cardinal contains Rack, some 3rd-party modules and a few internal utilities all in a single binary.  
All "Core" modules from Rack have been replaced by Cardinal equivalents, simplified to better work for an audio plugin.

Cardinal does not load external modules and does not connect to the official Rack library/store.  
All VCV branding has been removed (to the best of our knowledge) in order to avoid any trademark issues.


## Current status

Cardinal should be considered stable, if you spot any bugs please report them.  
Bugs in AmbientModules, Aluminium or this fork's builds go to [this fork's issues](https://github.com/neilbgr/Cardinal/issues), not to upstream Cardinal.  
Currently the following should be noted:

- CLAP support is a work-in-progress [DPF#383](https://github.com/DISTRHO/DPF/issues/383)
- VST3 plugin hosting (inside [Carla](https://github.com/falkTX/Carla/) or [Ildaeil](https://github.com/DISTRHO/Ildaeil) modules) mostly works but is considered experimental
- Windows 32bit builds still have a few problematic modules [#80](https://github.com/DISTRHO/Cardinal/issues/80)

### Stable release

This fork's releases have builds for Linux, macOS, Windows and the Web.  
You can find these under https://github.com/neilbgr/Cardinal/releases.  
Official (upstream) Cardinal releases are under https://github.com/DISTRHO/Cardinal/releases.

#### Installing & Updating releases
Installation works the same as for official Cardinal, see upstream's Wiki [Wiki/Install](https://github.com/DISTRHO/Cardinal/wiki/Install).
There are additional notes in [BUILDING.md#installing](docs/BUILDING.md#installing)

There are Linux builds for various architectures (armhf, arm64, i686 and x86_64), macOS "universal" (arm64 + intel), Windows 32 and 64bit builds and WebAssembly builds (with and without SIMD).
The macOS build is a .pkg installer, Windows builds come both as an installer and as a plain zip.  
Unlike upstream, this fork no longer produces riscv64 and MOD Audio builds (their toolchain sources are no longer available).

Note: Neither the macOS or Windows builds are signed, so expect warnings saying they are from an "untrusted developer".

### Nightly builds

You can find builds for recent commits of this fork [here](https://github.com/neilbgr/Cardinal/actions/workflows/build.yml).  
Just click on any build, and scroll to the bottom to find the builds (a run marked as failed can still hold builds for the platforms that succeeded).  
(note the canvas-like area in the middle prevents mouse wheel scrolling)

A GitHub account is required in order to download these builds.

### Building

Basic building instructions are available in [BUILDING.md](docs/BUILDING.md).

## Plugin variants

Cardinal provides 3 plugin variants - "main", Synth and FX.  
They are all equivalent in performance and behaviour, with only the IO and metadata that changes.  
This is because some hosts are very strict on which plugins are allowed as instruments vs FX, so separate variants of the same plugin are needed.

FX and Synth variants both have 2 audio outputs, while "main" has 8.  
All variants have MIDI input and output support.

### Main

This variant provides 8 audio inputs and outputs and 10 CV inputs and outputs.

NOTE: Due to AU and VST2 formats not supporting CV ports, this variant is not available for those formats.  
NOTE: This variant is not available in CLAP yet, to be added in a later release

### Synth

This variant provides 2 audio outputs but no audio inputs or CV ports.  
Plugin type is set as "instrument".

### FX

This variant provides 2 audio inputs and outputs, but no CV ports.  
Plugin type is set as regular "effect".

### Mini

This is a special variant with a hand-picked module selection and limited IO (2 audio ports plus 5 CV).  
Upstream, it only exists as LV2 and Standalone plugin.
This fork's releases ship it as LV2, plus two VST2 variants with the same module selection: Mini FX (2 audio inputs and outputs) and Mini Synth (2 audio outputs, instrument), without CV ports.

Upstream keeps the module selection very small, with polyphonic modules only.  
This fork widens it: AmbientModules, Aluminium and a selection of modules from other included packs, not all of them polyphonic.

The main reason for this variant to exist is being able to support DSP/UI separation, which is only possible with more simple modules.  
The DSP/UI separation means we can run the DSP on a different machine than the UI.  
This is particularly interesting for running Cardinal on embed systems, being controlled remotely via a web browser or a native desktop application.  
Such setup is already in use in [Cardinal Mini for MOD Audio](https://forum.mod.audio/t/distrho-cardinal-mini/9262/) (upstream only, this fork has no MOD Audio build).


## Screenshots

Because people will ask for it. It is, well... Rack.  
But a couple of modules background's have their colors flipped, because damn we want proper dark mode!

### Module browser

![screenshot](docs/Screenshot_Module-Browser.png "Screenshot")

### Basic patching

![screenshot](docs/Screenshot_Basic-Patching.png "Screenshot")

### [Carla](https://github.com/falkTX/Carla/) and [Ildaeil](https://github.com/DISTRHO/Ildaeil) plugin hosts

![screenshot](docs/Screenshot_Carla+Ildaeil.png "Screenshot")

### Custom Fundamental modules design

![screenshot](docs/Screenshot_Fundamental.png "Screenshot")


## Included modules

At the moment the following 3rd-party modules are provided:

- [21kHz](https://github.com/netboy3/21kHz-rack-plugins)
- [8Mode](https://github.com/8Mode/8Mode-VCV_Modules)
- [Aaron Static](https://github.com/aaronstatic/AaronStatic_modules)
- [Admiral](https://github.com/wapiflapi/admiral)
- [alef's bits](https://github.com/alefnull/alefsbits)
- [AlgoritmArte](https://github.com/algoritmarte/AlgoritmarteVCVPlugin)
- [Aluminium](https://github.com/neilbgr/Aluminium) (this fork only)
- [Amalgamated Harmonics](https://github.com/jhoar/AmalgamatedHarmonics)
- [AmbientModules](https://github.com/neilbgr/AmbientModules) (this fork only)
- [Animated Circuits](https://github.com/AnimatedCircuits/RackModules)
- [Arable Instruments](https://github.com/adbrant/ArableInstruments)
- [Aria Salvatrice](https://aria.dog/modules/)
- [AS](https://github.com/AScustomWorks/AS)
- [Audible Instruments](https://vcvrack.com/AudibleInstruments)
- [Autinn](https://github.com/NikolaiVChr/Autinn)
- [Axioma](https://github.com/kauewerner/Axioma)
- [Bacon Music](https://github.com/baconpaul/BaconPlugs)
- [Befaco](https://github.com/VCVRack/Befaco)
- [Bidoo](https://github.com/sebastien-bouffier/Bidoo)
- [Biset](https://github.com/gibbonjoyeux/VCV-Biset)
- [Bogaudio](https://github.com/bogaudio/BogaudioModules)
- [Catro/Modulo](https://github.com/catronomix/catro-modulo)
- [cf](https://github.com/cfoulc/cf)
- [Cella](https://github.com/victorkashirin/CellaVCV) (this fork only, Cardinal Mini only)
- [ChowDSP](https://github.com/jatinchowdhury18/ChowDSP-VCV)
- [Computerscare](https://github.com/freddyz/computerscare-vcv-modules)
- [CVfunk](https://github.com/codygeary/CVfunk-Modules)
- [dBiz](https://github.com/dBiz/dBiz)
- [DHE Modules](https://github.com/dhemery/DHE-Modules)
- [eightfold](https://github.com/scanner-darkly/eightfold)
- [EnigmaCurry](https://github.com/EnigmaCurry/EnigmaCurry-vcv-pack)
- [E-Series](https://github.com/VCVRack/ESeries)
- [ExpertSleepers Encoders](https://expert-sleepers.co.uk/vcvrack_encoders.html)
- [Extratone](http://extratone.xyz/modules)
- [Fehler Fabrik](https://github.com/RCameron93/FehlerFabrik)
- [forsitan modulare](https://github.com/gosub/forsitan-modulare)
- [Fundamental](https://github.com/VCVRack/Fundamental)
- [Glue the Giant](https://github.com/gluethegiant/gtg-rack)
- [GoodSheperd](https://github.com/jensschulze/GoodSheperd)
- [Grande](https://github.com/dbgrande/GrandeModular)
- [H4N4 Modules](https://github.com/hannakoppelaar/h4n4-modules)
- [Hampton Harmonics](https://gitlab.com/hampton-harmonics/hampton-harmonics-modules)
- [HetrickCV](https://github.com/mhetrick/hetrickcv)
- [ihtsyn](https://github.com/nysthi/ihtsyn)
- [Impromptu](https://github.com/MarcBoule/ImpromptuModular)
- [JW-Modules](https://github.com/jeremywen/JW-Modules)
- [kocmoc](https://github.com/janne808/kocmoc-rack-modules)
- [Kathode](https://github.com/ketodin/kathode) (this fork only, Cardinal Mini only)
- [Kilpatrick Toolbox](https://github.com/kilpatrickaudio/Kilpatrick-Toolbox) (this fork only, Cardinal Mini only)
- [LifeFormModular](https://github.com/TimeControlledOrganism/LifeFormModular)
- [Lilac Loop](https://grough.github.io/lilac-loop-vcv)
- [Little Utils](https://github.com/mgunyho/Little-Utils)
- [Lomas Modules](https://github.com/LomasModules/LomasModules)
- [Lyrae Modules](https://github.com/VegaDeftwing/LyraeModules)
- [Meander](https://github.com/knchaffin/Meander)
- [MindMeld](https://github.com/MarcBoule/MindMeldModular)
- [ML Modules](https://github.com/martin-lueders/ML_modules)
- [Mockba Modular](https://github.com/MockbaTheBorg/MockbaModular)
- [Mog](https://github.com/JustMog/Mog-VCV)
- [mscHack](https://github.com/mschack/VCV-Rack-Plugins)
- [MSM](https://github.com/netboy3/MSM-vcvrack-plugin)
- [MUS-X](https://github.com/Jojosito/MUS-X)
- [Myth](https://github.com/Ahineya/vcv-myth-plugin)
- [Nonlinear Circuits](https://github.com/mhetrick/nonlinearcircuits)
- [Orbits](https://github.com/RareBreeds/Orbits)
- [Parable Instruments](https://github.com/adbrant/ArableInstruments)
- [Path Set](https://github.com/patheros/PathSetModules)
- [PdArray](https://github.com/mgunyho/PdArray)
- [PinkTrombone](https://github.com/VegaDeftwing/PinkTromboneVCV)
- [Prism](https://github.com/SteveRussell33/Prism)
- [ProducerPack](https://github.com/4ms/ProducerPack) (this fork only, Cardinal Mini only)
- [rackwindows](https://github.com/n0jo/rackwindows)
- [RCM](https://github.com/Rcomian/rcm-modules/)
- [RebelTech](https://github.com/hemmer/rebel-tech-vcv)
- [repelzen](https://github.com/wiqid/repelzen)
- [Sapphire](https://github.com/cosinekitty/sapphire)
- [Signal Function Set](https://github.com/stuart78/SignalFunctionSet-VCV-Rack) (this fork only, Cardinal Mini only)
- [Sonus Modular](https://gitlab.com/sonusdept/sonusmodular)
- [stocaudio](https://github.com/aptrn/stocaudio-modules)
- [Starling Via](https://github.com/starlingcode/Via-for-Rack)
- [Stoermelder Pack-One](https://github.com/stoermelder/vcvrack-packone)
- [Submit](https://github.com/submitaudio/submit-vcv-modules) (this fork only, Cardinal Mini only)
- [Surge XT](https://github.com/surge-synthesizer/surge-rack)
- [unless_modules](https://gitlab.com/unlessgames/unless_modules)
- [Valley](https://github.com/ValleyAudio/ValleyRackFree)
- [Venom](https://github.com/DaveBenham/VenomModules)
- [Voxglitch](https://github.com/clone45/voxglitch)
- [WhatTheRack](https://github.com/korfuri/WhatTheRack)
- [WSTD-Drums](https://github.com/Wasted-Audio/WSTD-Drums)
- [ZetaCarinae](https://github.com/mhampton/ZetaCarinaeModules)
- [ZZC](https://github.com/zezic/ZZC)

Additionally Cardinal provides its own modules for DAW/Host automation, time position, audio to CV pitch conversion and internal plugin hosting.

### Adding modules

Installing new modules on a Cardinal build is not possible, but existing open-source modules can be integrated to be part of Cardinal.
For official Cardinal, details on this are available [here](https://github.com/DISTRHO/Cardinal/discussions/28).  
Also check [this wiki page](https://github.com/DISTRHO/Cardinal/wiki/Possible-modules-to-include)
where we discuss possible modules to include.  

### Module restrictions

The rules below are upstream Cardinal's.

All included modules are open-source and have a GPLv3+ compatible license. (GPLv3-only modules are not allowed)  
It is a requirement that the final Cardinal binary is GPLv3+ licensed.

Module dependencies should be kept at a minimum, as otherwise it quickly grows the complexity of the build.  
Online access (such as phone-home) is not allowed.

Worth noting that a few modules have artwork licensed separately from their code.  
These licenses range from CC-0 to CC-NC-ND to custom (used with permission).  
An overview of the included artwork licenses can be seen [here](docs/LICENSES.md#artwork--panel-licenses).

Even though CC-NC is problematic for packaging (some linux distributions are commercial in nature),
Cardinal allows their use because of how prevalent they are across many Rack modules.  
Even the Rack "Component Library" (which can be considered the base widget elements) is CC-NC licensed.

Any artwork that uses a custom license has had explicit permission to be used in Cardinal.

This fork is more tolerant than upstream:

- GPLv3-only modules are accepted (Submit, in Cardinal Mini only), so the Cardinal Mini binaries of this fork are GPLv3, not GPLv3+.
- Artwork with a custom license is accepted without explicit permission when that license allows free, non-commercial redistribution (Kilpatrick Toolbox, in Cardinal Mini only: commercial use requires the author's permission).
- Artwork whose license forbids derivative works or redistribution is still excluded (this is why Count Modula is not included).

See [LICENSES.md](docs/LICENSES.md) for the licenses of the packs added by this fork.


## Why

Cardinal was created first and foremost as a way to have Rack as a **proper open-source audio plugin**.  
A proper audio plugin should be self-contained as much as possible, as to not interfere with the DAW/Host.
Loading external modules clearly goes against this idea.  
Not to mention being **open-source**, otherwise we are at the mercy of the wishes of a company for what we can and cannot do,
which is not something Cardinal's authors wish to abide by.

A self-contained plugin can't be overstated, as DLL/shared-object symbol conflicts can trigger hard-to-debug crashes.  
While Rack tries to mitigate this as much as possible, crashes due to conflicting modules have already been seen in v2 builds.  
On the other side, Cardinal redefines class and function names as needed to avoid as many conflicts as possible.

Support for ARM and non-mainstream platforms (for example BSD) has also always been missing from the official Rack since the start.  
While we can patch the Rack free version to support these, same can't be done with Rack Pro with it being a closed-source product.  
The online library/store only supports a very specific set of platforms too,
so non-supported platforms would need any 3rd-party modules to be manually compiled to make them usable.

Unhappiness with the audio threading behaviour of Rack also plays a role.  
Both audio and MIDI should be locked to the host audio thread as to minimize (or even altogether remove) latency and jitter.  
The use of separate threads for MIDI is bad design, one that has been corrected in DAWs and JACK-MIDI for several years...  
But Rack's use of RtMidi requires separate threading, so Cardinal does not use it.

Other relevant reasons include:

 - LV2 plugin version from the start
 - Proper dark mode support
 - Real CV ports to and from the plugin
 - Removing online access from the plugin and included modules (no phone-home here!)
 - Works as a test case for [DPF](https://github.com/DISTRHO/DPF/) and [Carla](https://github.com/falkTX/Carla/)
 - It is fun :)


## Vs. Rack Pro

It needs to be said that Cardinal project and its author(s) do not wish anything bad to the original/official Rack project.  
In fact, Cardinal wouldn't exist if not for Rack v2 release. (which has many needed things to make a plugin version work)

Cardinal and Rack should be able to co-exist friendly and peacefully, as they clearly have different targets.  
It is likely most people will prefer to use Rack Pro for its official support and its big module collection (including commercial ones).

A feature comparison between Cardinal and Rack Pro can be seen [here](docs/DIFFERENCES.md).


## License

Cardinal is licensed under GPLv3+, see [LICENSE](LICENSE) for more details.  
An overview of the included code and linked submodules can be seen [here](docs/LICENSES.md#code-license--binary).


## Community chat

Currently we are all on #cardinal IRC room in irc.libera.chat server.  
Come join us in your favorite IRC client.  
(This is upstream Cardinal's chat. For this fork, use [its issues](https://github.com/neilbgr/Cardinal/issues).)
