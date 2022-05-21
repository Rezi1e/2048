#include "SDL.h"
#include "SDL_mixer.h"
Mix_Chunk* Sound;
Mix_Music* fon;
void loadmusic()
{
    Mix_FreeMusic(fon);
    fon = Mix_LoadMUS("fonmusic.wav");;
    Mix_PlayMusic(fon, -1);
}

void sound1()
{
    Mix_FreeChunk(Sound);
    Sound = Mix_LoadWAV("whoosh.wav");
    Mix_PlayChannel(-1, Sound, 0);
}

int ChooseModeWindow(int window_mode, int x, int y, SDL_Rect startRect, SDL_Rect settingsRect, SDL_Rect outRect, 
    SDL_Rect x4Rect, SDL_Rect x6Rect, SDL_Rect x8Rect, SDL_Rect backstartRect, 
    SDL_Rect musicOnOffRect, SDL_Rect soundOnOffRect, SDL_Rect backsettingsRect,
    bool* volumeMusic, bool* volumeSound, int* sizeBoard) {
    if (window_mode == 0) { // Главное меню
        if ((startRect.x <  x) && (startRect.x + startRect.w >  x) && (startRect.y + startRect.h >  y) && (startRect.y <  y)) {
            window_mode = 1;
            if (*volumeSound) sound1();
        }
        if ((settingsRect.x <  x) && (settingsRect.x + settingsRect.w >  x) && (settingsRect.y + settingsRect.h >  y) && (settingsRect.y <  y)) {
            window_mode = 2;
            if (*volumeSound) sound1();
        }
        if ((outRect.x <  x) && (outRect.x + outRect.w >  x) && (outRect.y + outRect.h >  y) && (outRect.y <  y)) {
            window_mode = -1;
            if (*volumeSound) sound1();
        }
    }

    else if (window_mode == 1) { // меню в Начать игру

        if ((x4Rect.x <  x) && (x4Rect.x + x4Rect.w >  x) && (x4Rect.y + x4Rect.h >  y) && (x4Rect.y <  y)) {
            window_mode = 3;
            *sizeBoard = 4;
            if (*volumeSound) sound1();
        }
        if ((x6Rect.x <  x) && (x6Rect.x + x6Rect.w >  x) && (x6Rect.y + x6Rect.h >  y) && (x6Rect.y <  y)) {
            window_mode = 4;
            *sizeBoard = 6;
            if (*volumeSound) sound1();
        }
        if ((x8Rect.x <  x) && (x8Rect.x + x8Rect.w >  x) && (x8Rect.y + x8Rect.h >  y) && (x8Rect.y <  y)) {
            window_mode = 5;
            *sizeBoard = 8;
            if (*volumeSound) sound1();
        }
        if ((backstartRect.x <  x) && (backstartRect.x + backstartRect.w >  x) && (backstartRect.y + backstartRect.h >  y) && (backstartRect.y <  y)) {
            window_mode = 0;
            if (*volumeSound) sound1();
        }

    }

    else if (window_mode == 2) { // меню в Настройки

        if ((musicOnOffRect.x <  x) && (musicOnOffRect.x + musicOnOffRect.w >  x) && (musicOnOffRect.y + musicOnOffRect.h >  y) && (musicOnOffRect.y <  y)) {
            if (*volumeMusic == true) {
                *volumeMusic = false;
                Mix_PauseMusic();
            }
            else if (*volumeMusic == false) { 
                *volumeMusic = true; 
                Mix_ResumeMusic();
                loadmusic();
            }
            
        }
        if ((soundOnOffRect.x <  x) && (soundOnOffRect.x + soundOnOffRect.w >  x) && (soundOnOffRect.y + soundOnOffRect.h >  y) && (soundOnOffRect.y <  y)) {
            if (*volumeSound == true) *volumeSound = false;
            else if (*volumeSound == false) {
                *volumeSound = true;
                sound1();
            }
        }
        if ((backsettingsRect.x <  x) && (backsettingsRect.x + backsettingsRect.w >  x) && (backsettingsRect.y + backsettingsRect.h >  y) && (backstartRect.y <  y)) {
            window_mode = 0;
            if(*volumeSound) sound1();
        }




    }
    return window_mode;
}
