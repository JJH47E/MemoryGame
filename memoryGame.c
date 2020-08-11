/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples in Notepad++, provided with default raylib installer package, 
*   just press F6 and run [raylib_compile_execute] script, it will compile and execute.
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on [C:\raylib\raylib\examples] directory and
*   raylib official webpage: [www.raylib.com]
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2020 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
/*******************************************************************************************
*
*   raylib [core] example - Keyboard input
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

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
    
    Color clickedColors[4] = { clickTriangle, clickCross, clickSquare, clickCircle };
    
    //UNCLICKED COLORS
    Color fadeTriangle = Fade(clickTriangle, 0.4);
    Color fadeCross = Fade(clickCross, 0.4);
    Color fadeSquare = Fade(clickSquare, 0.4);
    Color fadeCircle = Fade(clickCircle, 0.4);
    
    //USED COLORS
    Color triangleColor = fadeTriangle;
    Color crossColor = fadeCross;
    Color squareColor = fadeSquare;
    Color circleColor = fadeCircle;
    
    Color usedColors[4] = { triangleColor, crossColor, squareColor, circleColor };
    
    char debugText[50];
    sprintf(debugText, " ");
    
    bool pressingTriangle = false;
    bool pressingCross = false;
    bool pressingSquare = false;
    bool pressingCircle = false;
    
    bool newPress = false;
    bool takingInput = false;
    
    bool inMenu = false;
    bool inGame = true;
    bool postGame = false;
    bool inGameOneTime = true;
    
    bool addAns = false;
    int ans[75];
    int currentPos = 0;
    int ansPos = 0;
    
    char score[50];
    sprintf(score, "Score: %i", currentPos - 1);
    
    int frameCounter = 0;
    
    float rad = (float) 50;
    
    bool released = true;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        frameCounter++;
        released = false;
        sprintf(score, "Score: %i", currentPos - 1);
        // Inputs
        // ---------------------------------------------------------------------------------
        if(takingInput == true){
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                for (int i = 0; i < posLength; i++){
                    if(calcDistance(GetMousePosition(), buttonPositions[i]) < rad){
                        // sprintf(debugText, "%i", i);
                        if (i == 0){
                           pressingTriangle = true;
                        }
                        else{
                            pressingTriangle = false;
                        }
                        if (i == 1){
                            pressingCross = true;
                        }
                        else{
                            pressingCross = false;
                        }
                        if (i == 2){
                            pressingSquare = true;
                        }
                        else{
                            pressingSquare = false;
                        }
                        if (i == 3){
                            pressingCircle = true;
                        }
                        else{
                            pressingCircle = false;
                        }
                    }
                }
            }
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                newPress = true;
                newPress = false;
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
                // DRAW MENU
            }
            else if(inGame == true){
                if(inGameOneTime == true){
                    inGameOneTime = false;
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
                    if(frameCounter < 120){
                        if (frameCounter > 60){
                            // SHOW ANS BUTTON
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
                DrawText("Game Over", (screenWidth/2) - (MeasureText("GameOver", 60)/2), screenHeight/2 - 120, 60, RAYWHITE);
                DrawText("You Scored:", (screenWidth/2) - (MeasureText("You Scored:", 40)/2), screenHeight/2 - 50, 40, RAYWHITE);
                DrawText(FormatText("%i", currentPos - 1), (screenWidth/2) - (MeasureText(FormatText("%i", currentPos), 60)/2), screenHeight/2, 40, YELLOW);
                DrawText("Press Any Button to Return to the Menu", (screenWidth/2) - (MeasureText("Press Any Button to Return to the Menu", 20)/2), screenHeight * 9/10, 20, RAYWHITE);
            }
            
            // -----------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}