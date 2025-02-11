# remoteStick
software for a remote Stick for gliders, similar to the Stefly or xcNav remote Sticks, 
working with XCSOAR.

Most of the work ist already published by Stefan Langer (stefly remote stick) and Markus Immig (xcnav remote stick).
Here, it's baked into a common software with best of both, IMHO.

The Stick connects to an Android device by USB cable.
It implements Click, doubleClick and longClick on every button (except up/down/left/right).

The arduino acts as an USB keyboard and sends keystrokes to the connected android device.
In XCSOAR, the file GLB-XCI-xcremote.xci acts as a "translator" that converts the keystrokes
to XCSOAR-Commands.

In the current version, it works with an micro 32u4 processor (aka Leonardo), 
and can (for instance ) replace the software of the stefly remote stick, 
which has 3 buttons (beside the up/down/right/left and center), namely fn, menu and cancel.
