#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <stdio.h>
using namespace std;
#define WIDTH 500
#define HEIGHT 700

int* initBoard(int sizeBoard);

int ChooseModeWindow(int window_mode, int x, int y, SDL_Rect startRect, SDL_Rect settingsRect, SDL_Rect outRect,
    SDL_Rect x3Rect, SDL_Rect x4Rect, SDL_Rect x5Rect, SDL_Rect backstartRect,
    SDL_Rect musicOnOffRect, SDL_Rect soundOnOffRect, SDL_Rect backsettingsRect,
    bool* volumeMusic, bool* volumeSound, int* sizeBoard);

void game(SDL_Renderer* renderer, int sizeBoard, bool& getStart, int*& board,
    int* previousBoard, unsigned int& score, unsigned int& previousScore, int& window_mode, bool& quit, unsigned int& bestScore, bool& continue_game, bool volumeSound);

 
void init_best_score(int sizeBoard, unsigned int&BestScore) {
    FILE* f;
    if (sizeBoard == 4) fopen_s(&f, "BestScore4.txt", "rt");
    else if(sizeBoard == 6) fopen_s(&f, "BestScore6.txt", "rt");
    else fopen_s(&f, "BestScore8.txt", "rt");
    fscanf_s(f, "%d", &BestScore);
    
    fclose(f);

} 


void Draw2048( SDL_Renderer* renderer, int w) {

    SDL_Rect main2048;
    if (w == 0) main2048 = { 0, -50, 500, 225 };
    if (w == 1) main2048 = { 45, -35, 410, 185 };

    SDL_Surface* Surf2048 = IMG_Load("2048_2.bmp");
    SDL_SetColorKey(Surf2048, SDL_TRUE,
        SDL_MapRGB(Surf2048->format, 255, 255, 255));
    SDL_Texture* Texture2048 = SDL_CreateTextureFromSurface(renderer, Surf2048);
    SDL_FreeSurface(Surf2048);
    if (!Texture2048) { cout << "Failed to initialize mainstart\n"; }
    SDL_RenderCopy(renderer, Texture2048, NULL, &main2048);
    SDL_DestroyTexture(Texture2048);
    }

void initmainblocks(SDL_Renderer* renderer) {
    SDL_Rect startRect{ 125,185,250,100 };                                      //кнопка начать игру 
    SDL_Surface* startSurf = IMG_Load("mainstart.bmp");
    SDL_SetColorKey(startSurf, SDL_TRUE, SDL_MapRGB(startSurf->format, 255, 255, 255));
    SDL_Texture* mainstartTexture = SDL_CreateTextureFromSurface(renderer, startSurf);
    SDL_FreeSurface(startSurf);
    SDL_RenderCopy(renderer, mainstartTexture, NULL, &startRect);

    SDL_Rect settingsRect{ 125,335,250,100 };
    SDL_Surface* settingsSurf = IMG_Load("mainsettings.bmp");                       //Кнопка Настройки
    SDL_SetColorKey(settingsSurf, SDL_TRUE, SDL_MapRGB(settingsSurf->format, 255, 255, 255));
    SDL_Texture* settingTexture = SDL_CreateTextureFromSurface(renderer, settingsSurf);
    SDL_FreeSurface(settingsSurf); 
    SDL_RenderCopy(renderer, settingTexture, NULL, &settingsRect);

    SDL_Rect outRect{ 125,485,250,100 };
    SDL_Surface* outSurf = IMG_Load("mainquit.bmp");                            //Кнопка Закрытия программы
    SDL_SetColorKey(outSurf, SDL_TRUE, SDL_MapRGB(outSurf->format, 255, 255, 255));
    SDL_Texture* mainoutTexture = SDL_CreateTextureFromSurface(renderer, outSurf);
    SDL_FreeSurface(outSurf);
    SDL_RenderCopy(renderer, mainoutTexture, NULL, &outRect);

    SDL_DestroyTexture(mainstartTexture);
    SDL_DestroyTexture(settingTexture);
    SDL_DestroyTexture(mainoutTexture);

}


void initstartblocks(SDL_Renderer* renderer) {
    SDL_Rect x4Rect{ 125,173,250,100 };
    SDL_Surface* _4x4Surf = IMG_Load("4x4.bmp");                                  
    SDL_SetColorKey(_4x4Surf, SDL_TRUE,
        SDL_MapRGB(_4x4Surf->format, 255, 255, 255));
    SDL_Texture* texture4x4 = SDL_CreateTextureFromSurface(renderer, _4x4Surf);
    SDL_FreeSurface(_4x4Surf);
    SDL_RenderCopy(renderer, texture4x4, NULL, &x4Rect);

    SDL_Rect x6Rect{ 125,287,250,100 };
    SDL_Surface* _6x6Surf = IMG_Load("6x6.bmp");
    SDL_SetColorKey(_6x6Surf, SDL_TRUE,
        SDL_MapRGB(_6x6Surf->format, 255, 255, 255));
    SDL_Texture* texture6x6 = SDL_CreateTextureFromSurface(renderer, _6x6Surf);
    SDL_FreeSurface(_6x6Surf);
    SDL_RenderCopy(renderer, texture6x6, NULL, &x6Rect);

    SDL_Rect x8Rect{ 125,401,250,100 };
    SDL_Surface* _8x8Surf = IMG_Load("8x8.bmp");
    SDL_SetColorKey(_8x8Surf, SDL_TRUE,
        SDL_MapRGB(_8x8Surf->format, 255, 255, 255));
    SDL_Texture* texture8x8 = SDL_CreateTextureFromSurface(renderer, _8x8Surf);
    SDL_FreeSurface(_8x8Surf);
    SDL_RenderCopy(renderer, texture8x8, NULL, &x8Rect);

    SDL_Rect backRect{ 125,515,250,100 };
    SDL_Surface* backSurf = IMG_Load("back.bmp");
    SDL_SetColorKey(backSurf, SDL_TRUE,
        SDL_MapRGB(backSurf->format, 255, 255, 255));
    SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, backSurf);
    SDL_FreeSurface(backSurf);
    SDL_RenderCopy(renderer, backTexture, NULL, &backRect);
  
    SDL_DestroyTexture(texture4x4);
    SDL_DestroyTexture(texture6x6);
    SDL_DestroyTexture(texture8x8);
    SDL_DestroyTexture(backTexture);
}


void initsettingsblocks(SDL_Renderer* renderer,bool volumeMusic, bool volumeSound) {

    SDL_Rect MusicRect{ 125,185,250,100 };
    SDL_Surface* MusicOnOffSurf;
    if (volumeMusic == 1) MusicOnOffSurf = IMG_Load("musicOn.bmp");
    else MusicOnOffSurf = IMG_Load("musicOff.bmp");
    SDL_SetColorKey(MusicOnOffSurf, SDL_TRUE,
        SDL_MapRGB(MusicOnOffSurf->format, 255, 255, 255));
    SDL_Texture* MusicOnOffTexture = SDL_CreateTextureFromSurface(renderer, MusicOnOffSurf);
    SDL_FreeSurface(MusicOnOffSurf);
    SDL_RenderCopy(renderer, MusicOnOffTexture, NULL, &MusicRect);

    SDL_Rect  SoundOnOffRect{ 125,335,250,100 };
    SDL_Surface* SoundOnOffSurf;
    if (volumeSound == 1) SoundOnOffSurf = IMG_Load("soundOn.bmp");
    else SoundOnOffSurf = IMG_Load("soundOff.bmp");
    SDL_SetColorKey(SoundOnOffSurf, SDL_TRUE,
        SDL_MapRGB(SoundOnOffSurf->format, 255, 255, 255));
    SDL_Texture* SoundOnOffTexture = SDL_CreateTextureFromSurface(renderer, SoundOnOffSurf);
    SDL_FreeSurface(SoundOnOffSurf);
    SDL_RenderCopy(renderer, SoundOnOffTexture, NULL, &SoundOnOffRect);

    SDL_Rect backRect{ 125,485,250,100 };
    SDL_Surface* backSurf = IMG_Load("back.bmp");
    SDL_SetColorKey(backSurf, SDL_TRUE,
        SDL_MapRGB(backSurf->format, 255, 255, 255));
    SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, backSurf);
    SDL_FreeSurface(backSurf);
    SDL_RenderCopy(renderer, backTexture, NULL, &backRect);
       
    SDL_DestroyTexture(MusicOnOffTexture);
    SDL_DestroyTexture(SoundOnOffTexture);
    SDL_DestroyTexture(backTexture);
}
