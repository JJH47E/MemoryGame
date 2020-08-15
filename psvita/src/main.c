/*******************************************************************************************
*
*   MemoryGame by JJH47E
*
*   This game has been created using raylib 3.0 (www.raylib.com)
*
********************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/types.h> 

#include <vita2d.h>

extern unsigned char _binary_image_png_start;


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------

    SceCtrlData pad;
    vita2d_texture *image;
    vita2d_texture *logo;
    vita2d_font *font;

    const int screenWidth = 960;
    const int screenHeight = 544;

    vita2d_init();
    vita2d_set_clear_color(RGBA8(0, 0, 0, 255));

    font = vita2d_load_font_file("app0:src/resources/font.otf");

    image = vita2d_load_PNG_file("app0:src/resources/image.png");
    logo = vita2d_load_PNG_file("app0:src/resources/logo.png");

    memset(&pad, 0, sizeof(pad));

    //SceFVector2 may work, otherwise it needs to pe replaced by a float[] -- .x and .y variables would need to be rewritten as well

    SceFVector2 triangleButtonPosition = { (float)screenWidth/2, (float)(screenHeight/4) * 1 };
    SceFVector2 crossButtonPosition = { (float)screenWidth/2, (float)(screenHeight/4) * 3 };
    SceFVector2 squareButtonPosition = { (float)(screenWidth/2) - ((screenHeight/4) * 1), (float) screenHeight/2 };
    SceFVector2 circleButtonPosition = { (float)(screenWidth/2) + ((screenHeight/4) * 1), (float) screenHeight/2 };
    
    bool pressingTriangle = false;
    bool pressingCross = false;
    bool pressingSquare = false;
    bool pressingCircle = false;
    
    bool takingInput = false;
    
    bool splash = true;
    bool inMenu = false;
    bool inGame = false;
    bool postGame = false;
    bool inGameOneTime = true;
    bool inMenuOneTime = true;
    
    bool addAns = false;
    int ans[75];
    int currentPos = 0;
    int ansPos = 0;
    int rngInt = 0;
    bool noButtons = true;
    bool fromPostGame = true;
    int rngCounter = 0;
    
    char score[50];
    sprintf(score, "Score: %i", currentPos - 1);
    
    int frameCounter = 0;
    
    float rad = (float) 75;
    
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (1)
    {
        sceCtrlPeekBufferPositive(0, &pad, 1);
        // Update
        //----------------------------------------------------------------------------------
        if(rngCounter >= 400){
            rngCounter = 0;
        }
        frameCounter++;
        rngCounter++;
        sprintf(score, "Score: %i", currentPos - 1);
        if(currentPos >= 70){
        	inGame = false;
        	postGame = true;
        }
        // Inputs
        // ---------------------------------------------------------------------------------
        if(inGame == true){
            if(takingInput == true){
                noButtons = true;
                if (pad.buttons & SCE_CTRL_TRIANGLE){
                    //if triangle is down
                    pressingTriangle = true;
                    noButtons = false;
                }
                if (pad.buttons & SCE_CTRL_CROSS){
                    //if cross is down
                    pressingCross = true;
                    noButtons = false;
                }
                if (pad.buttons & SCE_CTRL_SQUARE){
                    //if sqaure is down
                    pressingSquare = true;
                    noButtons = false;
                }
                if (pad.buttons & SCE_CTRL_CIRCLE){
                    //if circle is down
                    pressingCircle = true;
                    noButtons = false;
                }
                if((noButtons == true) && (pressingCross == true || pressingCircle == true || pressingTriangle == true || pressingSquare == true)){//WHEN BUTTON IS RELEASED
                    //first push bool = true
                    if (pressingTriangle == true){
                        if(ans[ansPos] != 0){
                            // END GAME
                            inGame = false;
                            postGame = true;
                        }
                        else{
                            ansPos++;
                        }
                    }
                    else if (pressingCross == true){
                        if(ans[ansPos] != 1){
                            // END GAME
                            inGame = false;
                            postGame = true;
                        }
                        else{
                            ansPos++;
                        }
                    }
                    else if (pressingSquare == true){
                        if(ans[ansPos] != 2){
                            // END GAME
                            inGame = false;
                            postGame = true;
                        }
                        else{
                            ansPos++;
                        }
                    }
                    else if (pressingCircle == true){
                        if(ans[ansPos] != 3){
                            // END GAME
                            inGame = false;
                            postGame = true;
                        }
                        else{
                            ansPos++;
                        }
                    }
                    else{
                        inGame = false;
                        splash = true;
                    }
                    if (ansPos == currentPos){
                        ansPos = -1;
                        addAns = true;
                        takingInput = false;
                    }
                    pressingTriangle = false;
                    pressingCross = false;
                    pressingSquare = false;
                    pressingCircle = false;
                }
            }
        }
        else if(postGame == true){
            if(pad.buttons & SCE_CTRL_CROSS){
                inMenu = true;
                postGame = false;
                fromPostGame = true;
            }
        }
        else if(inMenu == true){
            if(pad.buttons & SCE_CTRL_CROSS){
                if(fromPostGame == false){
                    inGame = true;
                    inMenu = false;
                    frameCounter = 0;
                }
            }
            else{
                fromPostGame = false;
            }
        }
        // ---------------------------------------------------------------------------------
        if (addAns == true){
            addAns = false;
            rngInt = rngCounter % 4;//should be random enough
            ans[currentPos] = rngInt;
            rngInt = 0;
            currentPos++;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        vita2d_start_drawing();
            vita2d_clear_screen();
            
            // SCENE
            // -----------------------------------------------------------------------------
            if(inMenu == true){
                if(inMenuOneTime == true){
                    inMenuOneTime = false;
                    addAns = false;
                    currentPos = 0;
                    inGameOneTime = true;
                    ansPos = 0;
                }
                // DRAW MENU
                vita2d_draw_fill_circle(triangleButtonPosition.x, triangleButtonPosition.y, rad, RGBA8( 0, 181, 127, 102 ));
                vita2d_draw_fill_circle(crossButtonPosition.x, crossButtonPosition.y, rad, RGBA8( 110, 123, 225, 102 ));
                vita2d_draw_fill_circle(squareButtonPosition.x, squareButtonPosition.y, rad, RGBA8( 144, 95, 146, 102 ));
                vita2d_draw_fill_circle(circleButtonPosition.x, circleButtonPosition.y, rad, RGBA8( 186, 96, 120, 102 ));
                vita2d_draw_texture(logo, screenWidth/2 - 231.5,  70);
                vita2d_font_draw_text(font, screenWidth/2 - 75, screenHeight - 25, RGBA8(255, 255, 255, 255), 20, "Press X to play");
            }
            else if(inGame == true){
                if(inGameOneTime == true){
                    inGameOneTime = false;
                    inMenuOneTime = true;
                    takingInput = false;
                    addAns = true;
                }
                // DRAW IN GAME
                vita2d_font_draw_text(font, 10, 20, RGBA8(255, 255, 255, 255), 20, score);//FormatText() if this fails the build
                vita2d_draw_fill_circle(triangleButtonPosition.x, triangleButtonPosition.y, rad, RGBA8( 0, 181, 127, 102 ));
                vita2d_draw_fill_circle(crossButtonPosition.x, crossButtonPosition.y, rad, RGBA8( 110, 123, 225, 102 ));
                vita2d_draw_fill_circle(squareButtonPosition.x, squareButtonPosition.y, rad, RGBA8( 144, 95, 146, 102 ));
                vita2d_draw_fill_circle(circleButtonPosition.x, circleButtonPosition.y, rad, RGBA8( 186, 96, 120, 102 ));
                
                if(takingInput == true){
                    if(pressingTriangle == true){
                        vita2d_draw_fill_circle(triangleButtonPosition.x, triangleButtonPosition.y, rad, RGBA8( 0, 181, 127, 255 ));
                    }
                    else if (pressingCross == true){
                        vita2d_draw_fill_circle(crossButtonPosition.x, crossButtonPosition.y, rad, RGBA8( 110, 123, 225, 255 ));
                    }
                    else if (pressingSquare == true){
                        vita2d_draw_fill_circle(squareButtonPosition.x, squareButtonPosition.y, rad, RGBA8( 144, 95, 146, 255 ));
                    }
                    else if (pressingCircle == true){
                        vita2d_draw_fill_circle(circleButtonPosition.x, circleButtonPosition.y, rad, RGBA8( 186, 96, 120, 255 ));
                    }
                }
                else{
                    // PLAYING ANS
                    if(frameCounter < 90){
                        if (frameCounter > 60){
                            // SHOW ANS BUTTON
                            if(ansPos > currentPos){
                                ansPos = 0;
                                takingInput = true;
                            }
                            else{
                                if (ans[ansPos] == 0){
                                    // SHOW TRIANGLE
                                    vita2d_draw_fill_circle(triangleButtonPosition.x, triangleButtonPosition.y, rad, RGBA8( 0, 181, 127, 255 ));
                                }
                                else if (ans[ansPos] == 1){
                                    // SHOW CROSS
                                    vita2d_draw_fill_circle(crossButtonPosition.x, crossButtonPosition.y, rad, RGBA8( 110, 123, 225, 255 ));
                                }
                                else if (ans[ansPos] == 2){
                                    // SHOW SQUARE
                                    vita2d_draw_fill_circle(squareButtonPosition.x, squareButtonPosition.y, rad, RGBA8( 144, 95, 146, 255 ));
                                }
                                else if (ans[ansPos] == 3){
                                    // SHOW CIRCLE
                                    vita2d_draw_fill_circle(circleButtonPosition.x, circleButtonPosition.y, rad, RGBA8( 186, 96, 120, 255 ));
                                }
                            }
                        }
                    }
                    else{
                        frameCounter = 0;
                        ansPos++;
                        if(ansPos == currentPos){
                            ansPos = 0;
                            takingInput = true;
                        }
                    }
                }
                    
            }
            else if(postGame == true){
                // DRAW POST GAME
                vita2d_font_draw_text(font, screenWidth/2 - 76, screenHeight/2 - 40, RGBA8(255, 255, 255, 255), 28, "GameOver");
                vita2d_font_draw_text(font, screenWidth/2 - 84, screenHeight/2, RGBA8(255, 255, 255, 255), 28, "You Scored:");
                sprintf(score, "%i", currentPos - 1);
                vita2d_font_draw_text(font, screenWidth/2 - 8.5, screenHeight/2 + 40, RGBA8(255, 216, 0, 255), 28, score);
                vita2d_font_draw_text(font, screenWidth/2 - 144, screenHeight - 25, RGBA8(255, 255, 255, 255), 20, "Press X to return to the menu");
            }
            else if (splash == true){
                if(frameCounter < 180){
                    vita2d_draw_texture(image, screenWidth/2 - 56,  screenHeight/2 - 54);
                    vita2d_font_draw_text(font, screenWidth/2 - 83, screenHeight - 25, RGBA8(255, 255, 255, 255), 20, "Made by JJH47E");
                }
                else{
                    inMenu = true;
                    fromPostGame = true;
                    splash = false;
                }
            }
            
            // -----------------------------------------------------------------------------

        vita2d_end_drawing();
        vita2d_swap_buffers();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    vita2d_fini();
    vita2d_free_texture(image);
    vita2d_free_texture(logo);
    vita2d_free_font(font);
    //--------------------------------------------------------------------------------------
    sceKernelExitProcess(0);
    return 0;
}