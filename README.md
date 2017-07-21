# Windows speedhack example

## Dependencies
Detours from Microsoft Research

## Instructions
- Add the Detours headers to your include path, and the Detours library to your project. 
- Add the winmm.lib library
- Compile and inject into the target. 

You'll have to handle disabling the speedhack and unloading the DLL yourself. If you rarely reboot, beware that GetTickCount will start returning wrapped values after 49.7 days.
