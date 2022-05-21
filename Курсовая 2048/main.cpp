#include "init.h"

int main(int argc, char* args[]) {
    srand(time(NULL));
    int* boardx4 = NULL, 
       * boardx6 = NULL,
       * boardx8 = NULL,
       * previousBoardx4 = NULL,
        * previousBoardx6 = NULL, 
        * previousBoardx8 = NULL;

    unsigned int scorex4 = 0, scorex6 = 0, scorex8 = 0, 
        previousScorex4 = 0, previousScorex6 = 0, previousScorex8 = 0,
        bestScorex4 = 0, bestScorex6 = 0, bestScorex8 = 0;

    SDL_Rect startRect{ 125,185,250,100 },
        settingsRect{ 125,335,250,100 },
        outRect{ 125,485,250,100 },

        x3Rect{ 125,173,250,100 },
        x4Rect{ 125,287,250,100 },
        x5Rect{ 125,401,250,100 },
        backstartRect{ 125,515,250,100 },

        musicOnOffRect{ 125,185,250,100 },
        soundOnOffRect{ 125,335,250,100 },
        backsettingsRect{ 125,485,250,100 };

    int window_mode = 0, x = 0, y = 0, sizeBoard = 0;

    bool volumeMusic = 0,
        volumeSound = 0,
        quit = false,
        getStartx4 = false,
        getStartx6 = false,
        getStartx8 = false,
        continue_gamex4 = false,
        continue_gamex6 = false,
        continue_gamex8 = false;

    Mix_Chunk* Sound = NULL;
    Mix_Init(0);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512);


   
    SDL_Window* window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    //SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 4);
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    SDL_Event event;
    while (!quit)
    {
        while (SDL_PollEvent(&event)) {

           
            
            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                x = event.button.x;
                y = event.button.y;
            }
            if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
                window_mode = ChooseModeWindow(window_mode, x, y, startRect, settingsRect, outRect,
                    x3Rect, x4Rect, x5Rect, backstartRect, musicOnOffRect, soundOnOffRect, backsettingsRect, &volumeMusic, &volumeSound, &sizeBoard);
            }
            if (event.type == SDL_QUIT || window_mode == -1)
            {
                quit = true;
                break;
            }

        }
        if (quit) break;
        SDL_RenderPresent(renderer);
            
        SDL_SetRenderDrawColor(renderer, 190, 190, 190, 0);
        SDL_RenderClear(renderer);
        if (window_mode == 0 || window_mode == 1 || window_mode == 2) Draw2048(renderer, 0);
        if (window_mode == 3 || window_mode == 4 || window_mode == 5) Draw2048(renderer, 1);


        if (window_mode == 0) { 
            initmainblocks(renderer); 
            if (event.type == SDL_QUIT)
            {
                quit = true;
                break;
            }
        }
        else if (window_mode == 1) initstartblocks(renderer);
        else if (window_mode == 2) initsettingsblocks(renderer, volumeMusic, volumeSound);
        else if (sizeBoard == 4) {
            x = 0; y = 0;
            if (!getStartx4) {
                boardx4 = initBoard(sizeBoard);
                previousBoardx4 = initBoard(sizeBoard);
                getStartx4 = true;
            }
            init_best_score(sizeBoard, bestScorex4);
            game(renderer, sizeBoard, getStartx4, boardx4, previousBoardx4, scorex4, previousScorex4, window_mode, quit, bestScorex4, continue_gamex4, volumeSound);
        }
        else if (sizeBoard == 6) {
            x = 0; y = 0;
            if (!getStartx6) {
                boardx6 = initBoard(sizeBoard);
                previousBoardx6 = initBoard(sizeBoard);
                getStartx6 = true;
            }
            init_best_score(sizeBoard, bestScorex6);
            game(renderer, sizeBoard, getStartx6, boardx6, previousBoardx6, scorex6, previousScorex6, window_mode, quit, bestScorex6, continue_gamex6, volumeSound);
        }
        else if (sizeBoard == 8) {
            x = 0; y = 0;
            if (!getStartx8) {
                boardx8 = initBoard(sizeBoard);
                previousBoardx8 = initBoard(sizeBoard);
                getStartx8 = true;
            }
            init_best_score(sizeBoard, bestScorex8);
            game(renderer, sizeBoard, getStartx8, boardx8, previousBoardx8, scorex8, previousScorex8, window_mode, quit, bestScorex8, continue_gamex8, volumeSound);
        }
        else quit = true;
        
    }
    free(boardx4);
    free(boardx6);
    free(boardx8);

    free(previousBoardx8);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 1;
}