#include <cstdint>

#define GAME_ROW_SIZE 25
#define GAME_COL_SIZE 25
#define POPULATED 1
#define UNPOPULATED 0

class life {
    private:
        bool au8_prevGameArray[GAME_COL_SIZE][GAME_ROW_SIZE];
        bool au8_curGameArray[GAME_COL_SIZE][GAME_ROW_SIZE];
    public:
        void fn_tick();
        void fn_restart();
        bool fn_getCellStatusAtCoords(uint32_t u32_x, uint32_t u32_y);
        life();
        ~life();
};
