#include <cstdlib>
#include "life.h"
#include "ltimer.h"
#include "SDL.h"
#define SCALE 15
#define FRAMES_PER_SECOND 15
#define SCREEN_TICKS_PER_FRAME  (1000 / FRAMES_PER_SECOND)

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
SDL_Renderer* gRender = NULL;
    

// Main loop flag
bool b_quit = false;

//Event handler
SDL_Event event;

bool fn_init() {
    //Initialization flag
    bool b_success = true;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        b_success = false;
    }
    else {
        // Create window the size of the game * the scale factor
        gWindow = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,GAME_COL_SIZE * SCALE, GAME_ROW_SIZE * SCALE, SDL_WINDOW_SHOWN);
        gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

        if((gWindow == NULL) || (gRender == NULL)) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            b_success = false;
        } else {
            b_success = true;
        }
    }
    return b_success;
}

void fn_close() {
    //Deallocate surface
    SDL_DestroyRenderer(gRender);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

bool buttonPressed = 0;
int main () {
    life myGame;
    uint32_t u32_countedFrames = 0;
    float avgFPS = 0;
    uint32_t u32_frameTicks = 0;

    LTimer fpsTimer;
    LTimer capTimer; 

    if(!fn_init()) {
            printf( "Failed to initialize!\n" );
    } else {
        // Scale the window for visibility
        SDL_RenderSetScale(gRender, SCALE , SCALE);

        SDL_SetRenderDrawColor(gRender, 255, 255, 255, 255); // White
        SDL_RenderClear(gRender);

        while(!b_quit) {
            capTimer.start();

            while(SDL_PollEvent(&event) != 0) {
                //User requests quit
                if(event.type == SDL_QUIT) {
                    b_quit = true;
                } else if (event.type == SDL_KEYDOWN) {
                    switch(event.key.keysym.sym) {                             
                        case SDLK_SPACE:
                            myGame.fn_restart();
                            break;
                    }
                }
            }

                //Calculate and correct fps
                avgFPS = u32_countedFrames / (fpsTimer.getTicks() / 1000.f);

                if( avgFPS > 2000000 ) {
                    avgFPS = 0;
                }

                // Clear the screen after a new cycle
                SDL_SetRenderDrawColor(gRender, 255, 255, 255, 255); // White
                SDL_RenderClear(gRender);

                // Set color for the points
                SDL_SetRenderDrawColor(gRender, 255, 0, 0, 255); //  Red

                /* Draw the points */
                for(int row = 0; row < GAME_ROW_SIZE; row++) {
                    for (int col = 0; col < GAME_COL_SIZE; col++) {
                        if (myGame.fn_getCellStatusAtCoords(col, row)) {
                            SDL_RenderDrawPoint(gRender, col, row);
                        }
                    }
                }

                // Show the newwly drawn game
                SDL_RenderPresent(gRender);
                // Calculate the next state
                myGame.fn_tick();

                u32_countedFrames++;
                u32_frameTicks = capTimer.getTicks();
                if(u32_frameTicks < SCREEN_TICKS_PER_FRAME) {
                    //Wait remaining time
                    SDL_Delay(SCREEN_TICKS_PER_FRAME - u32_frameTicks);
                }
                
        }
        fn_close();
    }
    return 0;
}