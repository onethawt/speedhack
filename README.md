# Windows speedhack example

## Dependencies
Detours from Microsoft Research

## Instructions
- Add the Detours headers to your include path, and the Detours library to your project. 
- Add the winmm.lib library
- Compile and inject into the target. 

You'll have to handle disabling the speedhack and unloading the DLL yourself. If you rarely reboot, beware that GetTickCount will start returning wrapped values after 49.7 days.

## License
//
// DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// Version 2, December 2004
//
// Copyright(C) 2017 One Thawt <one.thawt@protonmail.ch>
// https://github.com/onethawt
//
// Everyone is permitted to copy and distribute verbatim or modified
// copies of this license document, and changing it is allowed as long
// as the name is changed.
//
// DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
// TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//
// 0. You just DO WHAT THE FUCK YOU WANT TO.
//
