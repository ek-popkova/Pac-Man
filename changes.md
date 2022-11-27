Main changes, that were made to the code:
- Sounds added
- Division into 3 modules implemented: 
	+ calculateFunctions – functions, that are independent from the <windows.h> library, and are used to calculate the coordinates
	+ drawingFunctions – functions, that are dependent on the <windows.h> library, and are responsible for representing the picture on the screen
	+ statusCheckSound – functions, that are dependent on the <windows.h> and winmm.lib libraries and are responsible for checking the state of cells and the game itself and playing the sound when in changes
- constants, entities and enums were moved to separated headers
