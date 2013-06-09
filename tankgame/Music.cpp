#include "Music.h"
#include <iostream>

#include <Windows.h>
#include <pxtone.h>

Music::Music() {
    char* song = "danube.pttune";
    pxtone_Ready(NULL, 2, 44100, 16, 0.1, false, NULL);
    pxtone_Tune_Load(NULL, NULL, song); /* ^ - this had to be false for me, for it to make sound. */
    pxtone_Tune_SetVolume(1.0f);
    pxtone_Tune_Start(0, 0);

	std:: cout << pxtone_GetLastError();
}