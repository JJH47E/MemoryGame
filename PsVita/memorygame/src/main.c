/*******************************************************************************************
*
*   MemoryGame by JJH47E
*
*   This game has been created using VitaSDK (https://vitasdk.org/)
*
********************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>

#include <vita2d.h>

#include "debugScreen.h"

#define printf psvDebugScreenPrintf

/* TODO: why touch[port].report[i].force is always at 128 ? */

int main(int argc, char *argv[]) {
    int screenHeight = 544;
    int screenWidth = 960;
    SceCtrlData pad;
    psvDebugScreenInit();
    printf("drawing test\n");
    printf("press start to exit\n");
    printf("This is a test application made my JJ\n");
    /* to enable analog sampling */
    do{
        sceCtrlPeekBufferPositive(0, &pad, 1);
        
        vita2d_start_drawing();
        vita2d_clear_screen();

        vita2d_draw_fill_circle(200, 420, 100, RGBA8(0, 255,0 ,255));

        vita2d_end_drawing();
        vita2d_swap_buffers();
    }while(!(SCE_CTRL_START) );
    sceKernelExitProcess(0);
    return 0;
}