#include "life.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

life::life() {
    std::srand(std::time(0));
    uint16_t u16_randNum;

    for (int row = 0; row < GAME_COL_SIZE; row++) {
        for (int col = 0; col < GAME_ROW_SIZE; col++) { 
            u16_randNum = (std::rand() % 5) + 1; // Num between 1 & 5
            
            if (u16_randNum == 1) { 
                au8_curGameArray[row][col] = POPULATED;
            } else {
                au8_curGameArray[row][col] = UNPOPULATED;
            }
        }
    }
}

life::~life() {
}

void life::fn_restart() {
    std::srand(std::time(0));
    uint16_t u16_randNum;

    for (int row = 0; row < GAME_COL_SIZE; row++) {
        for (int col = 0; col < GAME_ROW_SIZE; col++) { 
            u16_randNum = (std::rand() % 5) + 1; // Num between 1 & 5
            
            if (u16_randNum == 1) { 
                au8_curGameArray[row][col] = POPULATED;
            } else {
                au8_curGameArray[row][col] = UNPOPULATED;
            }
        }
    }
}

bool life::fn_getCellStatusAtCoords(uint32_t u32_x, uint32_t u32_y) {
    /*
     * y => rows
     * x => cols
     */
    return au8_curGameArray[u32_y][u32_x];   
}

void life::fn_tick() {
    int u8_adjacentPopulatedCells = 0;

    /* Copy over the current game array over to the previous */
    /*     
    for (int row = 0; row < GAME_COL_SIZE; row++) {
        for (int col = 0; col < GAME_ROW_SIZE; col++) {
               au8_prevGameArray[row][col] = au8_curGameArray[row][col];
        }
    }
    */
    std::memcpy(&(au8_prevGameArray[0][0]), &(au8_curGameArray[0][0]), \
        GAME_ROW_SIZE * GAME_COL_SIZE * sizeof(au8_curGameArray[0][0]));

    for (int row = 0; row < GAME_ROW_SIZE; row++) {
        for (int col = 0; col < GAME_COL_SIZE; col++) {
            /* Reset adjacent cell counter */
            u8_adjacentPopulatedCells = 0;

            /* If col is not at the left edge, check cells to the left */
            if (col) {
                /* Left Cell */
                if (au8_prevGameArray[row][col - 1]) {
                    u8_adjacentPopulatedCells++;
                }

                /* Top-Left Cell */
                if ((row) && au8_prevGameArray[row - 1][col - 1]) {
                    u8_adjacentPopulatedCells++;
                }

                /* Bottom-Left Cell */
                if ((row != (GAME_ROW_SIZE - 1)) && 
                    au8_prevGameArray[row + 1][col - 1]) {

                    u8_adjacentPopulatedCells++;
                }
            }

            /* If col is not at the right edge, check cells to the right */
            if (col != (GAME_COL_SIZE - 1)) {
                /* Right Cell */
                if (au8_prevGameArray[row][col+1]) {
                    u8_adjacentPopulatedCells++;
                }

                /* Top-Right Cell*/
                if(row && (au8_prevGameArray[row - 1][col + 1])) {
                    u8_adjacentPopulatedCells++;
                }

                /* Bottom-Right Cell */
                if ((row != (GAME_ROW_SIZE - 1)) &&
                    au8_prevGameArray[row + 1][col + 1]) {

                    u8_adjacentPopulatedCells++;
                }
            }

            /* If row is not at the top, check the cell above it */
            if (row) {
                if (au8_prevGameArray[row - 1][col]) {
                    u8_adjacentPopulatedCells++;
                }
            }

            /* If row is not at the bottom, check the cell below it */
            if (row != (GAME_ROW_SIZE - 1)) {
                if (au8_prevGameArray[row + 1][col]) {
                    u8_adjacentPopulatedCells++;
                }
            }

            /* Start checking if current cell lives or dies */

            /*
             * If the current cell is populated, and has 2 or 3 
             * populated neighbors, it lives. Otherwise it dies
             */
            if (au8_prevGameArray[row][col] == POPULATED) {
                if ((u8_adjacentPopulatedCells == 2) || 
                        (u8_adjacentPopulatedCells == 3)) {

                    au8_curGameArray[row][col] = POPULATED;
                } else {
                    au8_curGameArray[row][col] = UNPOPULATED;
                }
            } else {
                /*
                 * If the cell is unpopulated and has exaclty 3
                 * living neighbors, it lives
                 */
                if (u8_adjacentPopulatedCells == 3) {
                    au8_curGameArray[row][col] = POPULATED;
                } else {
                    au8_curGameArray[row][col] = UNPOPULATED;
                }
            }

        } /* End of col for loop */
    } /* End of row for loop */
} /* End of void life::fn_tick() */
