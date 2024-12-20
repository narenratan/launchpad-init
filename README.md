LAUNCHPAD INIT
==============
Automatically switch a Novation Launchpad X, a grid MIDI controller, into its
'programmer mode' as soon as it is connected. This is for convenience; by
default the Launchpad starts in a different mode, but I always use it in
programmer mode (so each pad sends a different MIDI note). Switching only takes
a few pad-presses, but this program saves that trouble by sending the MIDI
sysex message to switch to programmer mode as soon as the Launchpad is
connected.

Uses the hotplug support in
[libremidi](https://github.com/celtera/libremidi?tab=readme-ov-file).

Builds for Windows, Mac, and Linux are available on the [releases
page](https://github.com/narenratan/launchpad-init/releases).

Build
-----
```console
$ git clone --recurse-submodules https://github.com/narenratan/launchpad-init
$ cd launchpad-init
$ cmake -B build
$ cmake --build build
```
