/*******************************************************************************************
*
*   MemoryGame by JJH47E
*
*   This game has been created using raylib 3.0 (www.raylib.com)
*
********************************************************************************************/

#include <stdio.h>
#include <math.h>
#include "raylib.h"

float calcDistance(Vector2 mouse, Vector2 button){
    float x = (float) mouse.x - button.x;
    float y = (float) mouse.y - button.y;
    double output = sqrt((x * x) + (y * y));
    return (float) output;
}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "MemoryGame");

    Vector2 triangleButtonPosition = { (float)screenWidth/2, (float)(screenHeight/4) * 1 };
    Vector2 crossButtonPosition = { (float)screenWidth/2, (float)(screenHeight/4) * 3 };
    Vector2 squareButtonPosition = { (float)(screenWidth/2) - ((screenHeight/4) * 1), (float) screenHeight/2 };
    Vector2 circleButtonPosition = { (float)(screenWidth/2) + ((screenHeight/4) * 1), (float) screenHeight/2 };
    
    const int posLength = 4;
    Vector2 buttonPositions[4] = { triangleButtonPosition, crossButtonPosition, squareButtonPosition, circleButtonPosition };
    
    // CLICKED COLORS
    Color clickTriangle = (Color){ 0, 181, 127, 255 };
    Color clickCross = (Color){ 110, 123, 225, 255 };
    Color clickSquare = (Color){ 144, 95, 146, 255 };
    Color clickCircle = (Color){ 186, 96, 120, 255 };
    
    //FADE COLORS
    Color triangleColor = Fade(clickTriangle, 0.4);
    Color crossColor = Fade(clickCross, 0.4);
    Color squareColor = Fade(clickSquare, 0.4);
    Color circleColor = Fade(clickCircle, 0.4);
    
    Sound fxClick = LoadSound("resources/click.wav");
    Texture2D logo = LoadTexture("resources/logo.png");
    
    char debugText[50];
    sprintf(debugText, " ");
    
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
    
    bool oneTime = true;
    
    char score[50];
    sprintf(score, "Score: %i", currentPos - 1);
    
    int frameCounter = 0;
    
    float rad = (float) 50;
    
    InitAudioDevice();
    
    SetMasterVolume((float) 1);
    SetSoundVolume(fxClick, (float) 1);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        frameCounter++;
        sprintf(score, "Score: %i", currentPos - 1);
        // Inputs
        // ---------------------------------------------------------------------------------
        if(inGame == true){
            if(takingInput == true){
                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                    for (int i = 0; i < posLength; i++){
                        if(calcDistance(GetMousePosition(), buttonPositions[i]) < rad){
                            // sprintf(debugText, "%i", i);
                            if (i == 0){
                               pressingTriangle = true;
                               if(oneTime == true){
                                   PlaySound(fxClick);
                               }
                            }
                            else{
                                pressingTriangle = false;
                            }
                            if (i == 1){
                                pressingCross = true;
                                if(oneTime == true){
                                   PlaySound(fxClick);
                               }
                            }
                            else{
                                pressingCross = false;
                            }
                            if (i == 2){
                                pressingSquare = true;
                                if(oneTime == true){
                                   PlaySound(fxClick);
                               }
                            }
                            else{
                                pressingSquare = false;
                            }
                            if (i == 3){
                                pressingCircle = true;
                                if(oneTime == true){
                                   PlaySound(fxClick);
                               }
                            }
                            else{
                                pressingCircle = false;
                            }
                        }
                    }
                }
                if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                    oneTime = true;
                    //sprintf(debugText, "newPress");
                    // CHECK INPUTS
                    if (pressingTriangle == true){
                        if(ans[ansPos] != 0){
                            // END GAME
                            sprintf(debugText, "game over!");
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
                            sprintf(debugText, "game over!");
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
                            sprintf(debugText, "game over!");
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
                            sprintf(debugText, "game over!");
                            inGame = false;
                            postGame = true;
                        }
                        else{
                            ansPos++;
                        }
                    }
                    else{
                        sprintf(debugText, "error");
                    }
                    if (ansPos == currentPos){
                        ansPos = -1;
                        addAns = true;
                        takingInput = false;
                        sprintf(debugText, "DONE");
                    }
                    pressingTriangle = false;
                    pressingCross = false;
                    pressingSquare = false;
                    pressingCircle = false;
                }
            }
        }
        else if(postGame == true){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                inMenu = true;
                postGame = false;
            }
        }
        else if(inMenu == true){
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                inGame = true;
                inMenu = false;
                frameCounter = 0;
                PlaySound(fxClick);
            }
        }
        // ---------------------------------------------------------------------------------
        if (addAns == true){
            addAns = false;
            ans[currentPos] = GetRandomValue(0, 3);
            currentPos++;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);
            
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
                DrawText("MemoryGame", (screenWidth/2) - (MeasureText("MemoryGame", 60)/2), screenHeight/2 - 60, 60, RAYWHITE);
                DrawText("Left Click to Begin", (screenWidth/2) - (MeasureText("Left Click to Begin", 20)/2), screenHeight * 9/10, 20, RAYWHITE);
            }
            else if(inGame == true){
                if(inGameOneTime == true){
                    inGameOneTime = false;
                    inMenuOneTime = true;
                    takingInput = false;
                    addAns = true;
                    sprintf(debugText, "one time");
                }
                // DRAW IN GAME
                DrawText(score, 10, 10, 20, RAYWHITE);
                DrawCircleV(triangleButtonPosition, rad, triangleColor);
                DrawCircleV(crossButtonPosition, rad, crossColor);
                DrawCircleV(squareButtonPosition, rad, squareColor);
                DrawCircleV(circleButtonPosition, rad, circleColor);
                
                if(takingInput == true){
                    if(pressingTriangle == true){
                        DrawCircleV(triangleButtonPosition, rad, clickTriangle);
                    }
                    else if (pressingCross == true){
                        DrawCircleV(crossButtonPosition, rad, clickCross);
                    }
                    else if (pressingSquare == true){
                        DrawCircleV(squareButtonPosition, rad, clickSquare);
                    }
                    else if (pressingCircle == true){
                        DrawCircleV(circleButtonPosition, rad, clickCircle);
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
                                    DrawCircleV(triangleButtonPosition, rad, clickTriangle);
                                }
                                else if (ans[ansPos] == 1){
                                    // SHOW CROSS
                                    DrawCircleV(crossButtonPosition, rad, clickCross);
                                }
                                else if (ans[ansPos] == 2){
                                    // SHOW SQUARE
                                    DrawCircleV(squareButtonPosition, rad, clickSquare);
                                }
                                else if (ans[ansPos] == 3){
                                    // SHOW CIRCLE
                                    DrawCircleV(circleButtonPosition, rad, clickCircle);
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
                DrawText("Game Over", (screenWidth/2) - (MeasureText("Game Over", 60)/2), screenHeight/2 - 120, 60, RAYWHITE);
                DrawText("You Scored:", (screenWidth/2) - (MeasureText("You Scored:", 40)/2), screenHeight/2 - 50, 40, RAYWHITE);
                DrawText(FormatText("%i", currentPos - 1), (screenWidth/2) - (MeasureText(FormatText("%i", currentPos), 60)/2), screenHeight/2, 40, YELLOW);
                DrawText("Left Click to Return to the Menu", (screenWidth/2) - (MeasureText("Left Click to Return to the Menu", 20)/2), screenHeight * 9/10, 20, RAYWHITE);
            }
            else if (splash == true){
                if(frameCounter < 180){
                    DrawTexture(logo, screenWidth/2 - 54, screenHeight/2 - 54 - 40, Fade(RAYWHITE, 0.8));
                    DrawText("Created by JJH47E", (screenWidth/2) - (MeasureText("Created by JJH47E", 60)/2), screenHeight/2 + 40, 60, Fade(RAYWHITE, 0.8));
                }
                else{
                    inMenu = true;
                    splash = false;
                }
            }
            
            // -----------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadSound(fxClick);
    UnloadTexture(logo);
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}