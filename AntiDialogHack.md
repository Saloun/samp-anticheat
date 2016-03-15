# Introduction #

Client could send fake `DialogResponse` packets to the server, with fake dialogid, which fires `OnDialogResponse` callback in PAWN.
This include prevents this attack, every `ShowPlayerDialog` is tracked by the server and protects scripts when an `OnDialogResponse` fired.

## Usage ##
`#include <adh>` in every script where you use either `ShowPlayerDialog` or `OnDialogResponse` (or both).

Added a simple function to get a player's current dialog: `GetPlayerDialogID(playerid);`

### Changelog ###

0.0.5 crash fix on empty inputtext variable

0.0.4 fixed a warning caused by fixing a warning.

0.0.3 fixed a critical fault that prevented
script from running in gamemodes **edit: okay, not a critical fault, but it caused a slowdown and a hole in the ALS logic of the include.**

0.0.2 fixed a bug with deleting PVars - now every script gets its corresponding dialogid
fixed a possible warning in pawncc
warning: if `ShowPlayerDialog` used with a dialogid which does not get handled anywhere, PVar won't get reset, and `OnDialogResponse` may be spammed with the "stucked" ID (only when player is sending fake packets)

0.0.1 initial release