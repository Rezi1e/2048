#include "SDL_Image.h"
#include <string>
#include <SDL_ttf.h>
#include "iostream"
#include <ctime>
#include "SDL_mixer.h"
using namespace std;

#define WIDTH 500
#define HEIGHT 700

Mix_Chunk* Soundd = NULL;
void sound2(int n)
{
	Mix_FreeChunk(Soundd);
	if (n) Soundd = Mix_LoadWAV("whoosh2.wav");
	else Soundd = Mix_LoadWAV("whoosh2.wav");
	Mix_PlayChannel(-1, Soundd, 0);
}


void new_best_score(int sizeBoard, int BestScore) {
	FILE* ff;
	if (sizeBoard == 4) fopen_s(&ff, "BestScore4.txt", "wt");
	else if (sizeBoard == 6) fopen_s(&ff, "BestScore6.txt", "wt");
	else fopen_s(&ff, "BestScore8.txt", "wt");
	fprintf_s(ff, "%d", BestScore);

	fclose(ff);
}


int* initBoard(int sizeBoard) {
	srand(time(NULL));
	int* board = (int*)malloc(sizeBoard * sizeBoard * sizeof(int));

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			*(board + i * sizeBoard + j) = 0;
		}
	}
	int X = rand() % sizeBoard;
	int Y = rand() % sizeBoard;
	*(board + X * sizeBoard + Y) = 2;

	while (*(board + X * sizeBoard + Y) != 0) {
		X = rand() % sizeBoard;
		Y = rand() % sizeBoard;
	}
	*(board + X * sizeBoard + Y) = 2;

	return board;
}



bool checkFree(int*& board, int sizeBoard) {
	bool free = 0;

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) == 0) free = 1;
		}
	}

	return free;
}



bool Lose(int*& board, int sizeBoard) {
	bool lose = 1;

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard - 1; j++) {
			if (*(board + i * sizeBoard + j) == *(board + i * sizeBoard + j + 1)) lose = 0;
		}
	}
	for (int i = 0; i < sizeBoard - 1; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) == *(board + (i + 1) * sizeBoard + j)) lose = 0;
		}
	}

	if (checkFree(board, sizeBoard)) lose = 0;

	return lose;
}



bool Win(int*& board, int sizeBoard) {
	bool win = 0;

	for (int i = 0; i < sizeBoard;  i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) == 2048) win = 1;
		}
	}

	return win;
}



bool checkToRandom(int*& board, int*& previousBoard, int sizeBoard) {
	int can_put = 0;
	for (int i = 0; i < sizeBoard; ++i) {
		for (int j = 0; j < sizeBoard; ++j) {
			if (*(board + i * sizeBoard + j) != *(previousBoard + i * sizeBoard + j)) can_put = 1;
		}
	}
	return can_put;
}



void randomOnBoard(int*& board, int sizeBoard) {

	if (checkFree(board, sizeBoard)) {
		
		int numbers[10] = { 4, 4, 2, 2, 2, 2, 2, 2, 2, 2 };
		
		int number = numbers[rand() % 10];

		int X = rand() % sizeBoard;
		int Y = rand() % sizeBoard;
		if (*(board + X * sizeBoard + Y) == 0) { *(board + X * sizeBoard + Y) = number; }
		else {
			while (*(board + X * sizeBoard + Y) != 0) {
				X = rand() % sizeBoard;
				Y = rand() % sizeBoard;
			}
			*(board + X * sizeBoard + Y) = number;
		}
	}
}



void Up(int*& board, int sizeBoard, unsigned int& score) {
	for (int i = 1; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) != 0) {
				for (int k = i; k > 0; --k) {
					if (*(board + (k - 1) * sizeBoard + j) == 0) {
						*(board + (k - 1) * sizeBoard + j) = *(board + k * sizeBoard + j);
						*(board + k * sizeBoard + j) = 0;
					}
				}
			}
		}
	}

	for (int i = 1; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) != 0) {
				if (*(board + (i - 1) * sizeBoard + j) == *(board + i * sizeBoard + j)) {
					*(board + (i - 1) * sizeBoard + j) += *(board + i * sizeBoard + j);
					score += *(board + (i - 1) * sizeBoard + j);
					*(board + i * sizeBoard + j) = 0;

				}
			}
		}
	}

	for (int i = 1; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) != 0) {
				for (int k = i; k > 0; --k) {
					if (*(board + (k - 1) * sizeBoard + j) == 0) {
						*(board + (k - 1) * sizeBoard + j) = *(board + k * sizeBoard + j);
						*(board + k * sizeBoard + j) = 0;
					}
				}
			}
		}
	}
}



void Down(int*& board, int sizeBoard, unsigned int& score) {
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = sizeBoard - 2; j >= 0; j--) {
			if (*(board + j * sizeBoard + i) != 0) {
				for (int k = j; k < sizeBoard - 1; ++k) {
					if (*(board + (k + 1) * sizeBoard + i) == 0) {
						*(board + (k + 1) * sizeBoard + i) = *(board + k * sizeBoard + i);
						*(board + k * sizeBoard + i) = 0;
					}
				}
			}
		}
	}

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = sizeBoard - 2; j >= 0; j--) {
			if (*(board + j * sizeBoard + i) != 0) {
				if (*(board + j * sizeBoard + i) == *(board + (j + 1) * sizeBoard + i)) {
					*(board + (j + 1) * sizeBoard + i) += *(board + j * sizeBoard + i);
					score += *(board + (j + 1) * sizeBoard + i);
					*(board + j * sizeBoard + i) = 0;
				}
			}
		}
	}

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = sizeBoard - 2; j >= 0; j--) {
			if (*(board + j * sizeBoard + i) != 0) {
				for (int k = j; k < sizeBoard - 1; ++k) {
					if (*(board + (k + 1) * sizeBoard + i) == 0) {
						*(board + (k + 1) * sizeBoard + i) = *(board + k * sizeBoard + i);
						*(board + k * sizeBoard + i) = 0;
					}
				}
			}
		}
	}
}



void Right(int*& board, int sizeBoard, unsigned int& score) {
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = sizeBoard - 2; j >= 0; j--) {
			if (*(board + i * sizeBoard + j) != 0) {
				for (int k = j; k < sizeBoard - 1; ++k) {
					if (*(board + i * sizeBoard + (k + 1)) == 0) {
						*(board + i * sizeBoard + (k + 1)) = *(board + i * sizeBoard + k);
						*(board + i * sizeBoard + k) = 0;
					}
				}
			}
		}
	}

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = sizeBoard - 2; j >= 0; j--) {
			if (*(board + i * sizeBoard + j) != 0) {
				if (*(board + i * sizeBoard + j) == *(board + i * sizeBoard + (j + 1))) {
					*(board + i * sizeBoard + (j + 1)) += *(board + i * sizeBoard + j);
					score += *(board + i * sizeBoard + (j + 1));
					*(board + i * sizeBoard + j) = 0;
				}
			}
		}
	}

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = sizeBoard - 2; j >= 0; j--) {
			if (*(board + i * sizeBoard + j) != 0) {
				for (int k = j; k < sizeBoard - 1; ++k) {
					if (*(board + i * sizeBoard + (k + 1)) == 0) {
						*(board + i * sizeBoard + (k + 1)) = *(board + i * sizeBoard + k);
						*(board + i * sizeBoard + k) = 0;
					}
				}
			}
		}
	}
}



void Left(int*& board, int sizeBoard, unsigned int& score) {

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 1; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) != 0) {
				for (int k = j; k > 0; --k) {
					if (*(board + i * sizeBoard + (k - 1)) == 0) {
						*(board + i * sizeBoard + (k - 1)) = *(board + i * sizeBoard + k);
						*(board + i * sizeBoard + k) = 0;
					}
				}
			}
		}
	}

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 1; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) != 0) {
				if (*(board + i * sizeBoard + j) == *(board + i * sizeBoard + (j - 1))) {
					*(board + i * sizeBoard + (j - 1)) += *(board + i * sizeBoard + j);
					score += *(board + i * sizeBoard + (j - 1));
					*(board + i * sizeBoard + j) = 0;
				}
			}
		}
	}

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 1; j < sizeBoard; j++) {
			if (*(board + i * sizeBoard + j) != 0) {
				for (int k = j; k > 0; --k) {
					if (*(board + i * sizeBoard + (k - 1)) == 0) {
						*(board + i * sizeBoard + (k - 1)) = *(board + i * sizeBoard + k);
						*(board + i * sizeBoard + k) = 0;
					}
				}
			}
		}
	}
}



void copyboard(int*& board1, int*& board2, int sizeBoard) {
	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) *(board1 + i * sizeBoard + j) = *(board2 + i * sizeBoard + j);
	}
}



void move(SDL_Event event, int*& board, int sizeBoard, int*& previousBoard, unsigned int& score, unsigned int& previousScore, bool volumeSound) {
	int* checkBoard = initBoard(sizeBoard);
	int checkScore = previousScore;
	copyboard(checkBoard, previousBoard, sizeBoard);

	copyboard(previousBoard, board, sizeBoard);
	previousScore = score;


	if (event.key.keysym.sym == SDLK_UP) Up(board, sizeBoard, score);
	else if (event.key.keysym.sym == SDLK_DOWN) Down(board, sizeBoard, score);
	else if (event.key.keysym.sym == SDLK_LEFT) Left(board, sizeBoard, score);
	else if (event.key.keysym.sym == SDLK_RIGHT) Right(board, sizeBoard, score);

	if (checkToRandom(board, previousBoard, sizeBoard)) {
		randomOnBoard(board, sizeBoard);
		if (volumeSound) sound2(1);
	}
	else {
		copyboard(previousBoard, checkBoard, sizeBoard);
		previousScore = checkScore;
	}

	free(checkBoard);
}



void drawDeck(SDL_Renderer* renderer, int sizeBoard) {
	SDL_Rect deck; 
	SDL_Surface* Surf2048 = NULL;
	if (sizeBoard == 4) {
		deck = { 36, 200, 425, 425 };
		Surf2048 = IMG_Load("deck4.bmp");
	}
	else if (sizeBoard == 6) {
		deck = { 40, 204, 418, 418 };
		Surf2048 = IMG_Load("deck6.bmp");
	}
	else if (sizeBoard == 8) {
		deck = { 35, 199, 428, 428 };
		Surf2048 = IMG_Load("deck8.bmp");
	}
	SDL_Texture* Texture2048 = SDL_CreateTextureFromSurface(renderer, Surf2048);
	SDL_FreeSurface(Surf2048);
	if (!Texture2048) { cout << "Failed to initialize deck\n"; }
	SDL_RenderCopy(renderer, Texture2048, NULL, &deck);
	SDL_DestroyTexture(Texture2048);
}



void DrawBackAndHome(SDL_Renderer* renderer) {
	SDL_Rect
		rect_home{ 33, 130, 40, 40 },
		rect_back{ 95, 130, 40, 40 },
		rect_new{ 155, 130, 40, 40 };

	SDL_Surface
		* SurfHome = IMG_Load("homewhite.bmp"),
		* SurfBack = IMG_Load("backdeckwhite.bmp"),
		* SurfNew = IMG_Load("newdeckwhite.bmp");
	SDL_Texture* Texture;
	SDL_SetColorKey(SurfHome, SDL_TRUE, SDL_MapRGB(SurfHome->format, 255, 255, 255));
	Texture = SDL_CreateTextureFromSurface(renderer, SurfHome);
	SDL_FreeSurface(SurfHome);
	if (!Texture) { cout << "Failed to initialize home\n"; }
	SDL_RenderCopy(renderer, Texture, NULL, &rect_home);
	SDL_DestroyTexture(Texture);

	SDL_SetColorKey(SurfBack, SDL_TRUE, SDL_MapRGB(SurfBack->format, 255, 255, 255));
	Texture = SDL_CreateTextureFromSurface(renderer, SurfBack);
	SDL_FreeSurface(SurfBack);
	if (!Texture) { cout << "Failed to initialize icon backdeck\n"; }
	SDL_RenderCopy(renderer, Texture, NULL, &rect_back);
	SDL_DestroyTexture(Texture);
	SDL_SetColorKey(SurfNew, SDL_TRUE, SDL_MapRGB(SurfNew->format, 255, 255, 255));
	Texture = SDL_CreateTextureFromSurface(renderer, SurfNew);
	SDL_FreeSurface(SurfNew);
	if (!Texture) { cout << "Failed to initialize icon newdeck\n"; }
	SDL_RenderCopy(renderer, Texture, NULL, &rect_new);


	SDL_DestroyTexture(Texture);

}



void drawScore(SDL_Renderer* renderer, unsigned int score, unsigned int& bestScore, int sizeBoard, TTF_Font* font) {
	SDL_Rect rect_textScore = { 210, 120, 260, 60 },
		rect_score{ 280, 120, 0, 30 },
		rect_textBestScore{ 210, 150, 120, 30 },
		rect_bestScore{ 340, 150, 0, 30 };

	string str_score = to_string(score);
	int lenScore = size(str_score);
	rect_score.w = 15 * lenScore;
	SDL_Color fore_color = { 0,0,0 };
	SDL_Surface* textSurface = TTF_RenderUTF8_Blended_Wrapped(font, str_score.c_str(), fore_color, 10);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_SetRenderDrawColor(renderer, 220, 220, 220, 0);
	SDL_SetRenderDrawColor(renderer, 190, 190, 190, 0);
	SDL_RenderFillRect(renderer, &rect_textScore);
	rect_textScore.w = 60;
	rect_textScore.h = 30;
	SDL_RenderCopy(renderer, texture, NULL, &rect_score);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
	textSurface = TTF_RenderUTF8_Blended_Wrapped(font, "Score", fore_color, 10);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, texture, NULL, &rect_textScore);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
	textSurface = TTF_RenderUTF8_Blended_Wrapped(font, "Best Score", fore_color, 1000);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, texture, NULL, &rect_textBestScore);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
	if (bestScore < score) {
		bestScore = score;
	}
	string str_bestScore = to_string(bestScore);
	int lenBestScore = size(str_bestScore);
	rect_bestScore.w = 15 * lenBestScore;
	textSurface = TTF_RenderUTF8_Blended_Wrapped(font, str_bestScore.c_str(), fore_color, 10);
	texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_RenderCopy(renderer, texture, NULL, &rect_bestScore);
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(texture);
	DrawBackAndHome(renderer);
}



void DrawFillBlocks(SDL_Renderer* renderer, int* board, int sizeBoard, SDL_Rect* Blocks, TTF_Font* font) {
	SDL_Rect rect;
	SDL_Color fore_color = { 0,0,0 };
	SDL_Surface* textSurface = NULL;
	SDL_Texture* texture = NULL;

	for (int i = 0; i < sizeBoard; i++) {
		for (int j = 0; j < sizeBoard; j++) {

			int x = *(board + i * sizeBoard + j);
			string number = to_string(x);

			textSurface = TTF_RenderUTF8_Blended_Wrapped(font, number.c_str(), fore_color, 1000);
			texture = SDL_CreateTextureFromSurface(renderer, textSurface);
			rect = { Blocks[i * sizeBoard + j].x + 10 , Blocks[i * sizeBoard + j].y + 10,
				Blocks[i * sizeBoard + j].w - 20, Blocks[i * sizeBoard + j].h - 20 };

			int color = 0;
			while (x != 0) {
				x = x / 2;
				color++;
			}

			if (*(board + i * sizeBoard + j) != NULL){ 
				
				SDL_SetRenderDrawColor(renderer, 90, 90 + 10 * color, 156 + 20 * color, 0);
				SDL_RenderFillRect(renderer, Blocks + i*sizeBoard +j); 
				SDL_RenderCopy(renderer, texture, NULL, &rect);
			}

			SDL_FreeSurface(textSurface);
			SDL_DestroyTexture(texture);
		}
	}
}



void drawend(SDL_Renderer* renderer, int endd, SDL_Rect end) {

	SDL_Surface* Surf = NULL;
		if (endd == 1) Surf = IMG_Load("lose.bmp");
		else if (endd == 2) Surf = IMG_Load("win.bmp");
	SDL_Texture* Texture;

	Texture = SDL_CreateTextureFromSurface(renderer, Surf);
	SDL_FreeSurface(Surf);
	if (!Texture) { cout << "Failed to initialize home\n"; }
	SDL_RenderCopy(renderer, Texture, NULL, &end);
	SDL_DestroyTexture(Texture);
}



void initRect(int sizeBoard, SDL_Rect* x4Blocks, SDL_Rect* x6Blocks, SDL_Rect* x8Blocks) {
	if (sizeBoard == 4) {
		for (int i = 0; i < sizeBoard; i++) {
			for (int j = 0; j < sizeBoard; j++) {
				x4Blocks[i * sizeBoard + j].x = 42 + j * 100 + j * 5;
				x4Blocks[i * sizeBoard + j].y = 205 + i * 100 + i* 5;
				x4Blocks[i * sizeBoard + j].w = 100;
				x4Blocks[i * sizeBoard + j].h = 100;
			}
		}
	}
	else if (sizeBoard == 6) {
		
		for (int i = 0; i < sizeBoard; i++) {
			for (int j = 0; j < sizeBoard; j++) {
				x6Blocks[i * sizeBoard + j].x = 44 + j * 65 + j * 4;
				x6Blocks[i * sizeBoard + j].y = 208 + i * 65 + i * 4;
				x6Blocks[i * sizeBoard + j].w = 65;
				x6Blocks[i * sizeBoard + j].h = 65;
			}
		}
		
	}
	else if (sizeBoard == 8) {
		for (int i = 0; i < sizeBoard; i++) {
			for (int j = 0; j < sizeBoard; j++) {
				x8Blocks[i * sizeBoard + j].x = 39 + j * 49 + j * 4;
				x8Blocks[i * sizeBoard + j].y = 203 + i * 49 + i * 4;
				x8Blocks[i * sizeBoard + j].w = 49;
				x8Blocks[i * sizeBoard + j].h = 49;
			}
		}
	}
}





void game(SDL_Renderer* renderer, int sizeBoard, bool& getStart, int*& board,
	int* previousBoard, unsigned int& score, unsigned int& previousScore, int& window_mode, bool& quit, unsigned int& bestScore, bool& continue_game, bool volumeSound) {
	
	SDL_Rect x4Blocks[16], x6Blocks[36], x8Blocks[64], rect_home{ 33, 130, 40, 40 }, rect_back{ 95, 130, 40, 40 }, rect_new{ 155, 130, 40, 40 }, end{ 45, 250, 410, 164 },
		end_left{130,330,80,75}, end_right{290,325,75,80};

	initRect(sizeBoard, x4Blocks, x6Blocks, x8Blocks);


	if (!getStart) {
		board = initBoard(sizeBoard);
		getStart = true;
	}

	TTF_Init();
	TTF_Font* font = TTF_OpenFont("Text.ttf", 100);
	int qq = 0;
	SDL_Event event;
	bool quitt = 0;
	while (!quitt) {

			if ((!Lose(board, sizeBoard) && !Win(board, sizeBoard)) || continue_game) {
				
				drawDeck(renderer, sizeBoard);
				drawScore(renderer, score, bestScore, sizeBoard, font);

				while (SDL_PollEvent(&event)) {
					
					if (event.type == SDL_KEYDOWN) {
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
							event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT) move(event, board, sizeBoard, previousBoard, score, previousScore, volumeSound);
					}
					else if (event.type == SDL_QUIT) {
						quit = true;
						quitt = true;
					}
					if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
						if ((rect_back.x < event.motion.x) && (rect_back.x + rect_back.w > event.motion.x) && (rect_back.y + rect_back.h > event.motion.y) && (rect_back.y < event.motion.y)) {
							copyboard(board, previousBoard, sizeBoard);
							score = previousScore;
							if (volumeSound) sound2(0);
						}
						if ((rect_home.x < event.motion.x) && (rect_home.x + rect_home.w > event.motion.x) && (rect_home.y + rect_home.h > event.motion.y) && (rect_home.y < event.motion.y)) {
							window_mode = 0;
							quitt = 1;
							if (volumeSound) sound2(0);
						}
						if ((rect_new.x < event.motion.x) && (rect_new.x + rect_new.w > event.motion.x) && (rect_new.y + rect_new.h > event.motion.y) && (rect_new.y < event.motion.y)) {

							board = initBoard(sizeBoard);
							previousBoard = initBoard(sizeBoard);
							score = 0;
							previousScore = 0;
							continue_game = false;
							if (volumeSound) sound2(0);
						}
					}
				}


				if (sizeBoard == 4) DrawFillBlocks(renderer, board, sizeBoard, x4Blocks, font);
				else if (sizeBoard == 6)DrawFillBlocks(renderer, board, sizeBoard, x6Blocks, font);
				else if (sizeBoard == 8)DrawFillBlocks(renderer, board, sizeBoard, x8Blocks, font);


				SDL_RenderPresent(renderer);

				if (Lose(board, sizeBoard)) {
					continue_game = false;

				}

			}
			else if(Lose(board, sizeBoard)){
				if (bestScore < score) {

					new_best_score(sizeBoard, bestScore);
				}

					drawend(renderer, 1, end);
					while (SDL_PollEvent(&event)) {
						if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
							if ((end_left.x < event.motion.x) && (end_left.x + end_left.w > event.motion.x) && (end_left.y + end_left.h > event.motion.y) && (end_left.y < event.motion.y)) {
								board = initBoard(sizeBoard);
								previousBoard = initBoard(sizeBoard);
								score = 0;
								previousScore = 0;
								window_mode = 0;
								quitt = 1;
								if (volumeSound) sound2(0);
								
							}
							if ((end_right.x < event.motion.x) && (end_right.x + end_right.w > event.motion.x) && (end_right.y + end_right.h > event.motion.y) && (end_right.y < event.motion.y)) {
								board = initBoard(sizeBoard);
								previousBoard = initBoard(sizeBoard);
								score = 0;
								previousScore = 0;
								if (volumeSound) sound2(0);
							}
						}
						if (event.type == SDL_QUIT) {
							quit = true;
							quitt = true;
						}

					}
					SDL_RenderPresent(renderer);
			}
			else if (Win(board, sizeBoard)) {
				if (bestScore < score) {

					new_best_score(sizeBoard, bestScore);
				}
				drawend(renderer, 2, end);
				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT) {
						if ((end_left.x < event.motion.x) && (end_left.x + end_left.w > event.motion.x) && (end_left.y + end_left.h > event.motion.y) && (end_left.y < event.motion.y)) {
							board = initBoard(sizeBoard);
							previousBoard = initBoard(sizeBoard);
							score = 0;
							previousScore = 0;
							window_mode = 0;
							quitt = 1;
							if (volumeSound) sound2(0);

						}
						if ((end_right.x-5 < event.motion.x) && (end_right.x + end_right.w-4 > event.motion.x) && (end_right.y + end_right.h > event.motion.y) && (end_right.y < event.motion.y)) {
							continue_game = true;
							if (volumeSound) sound2(0);
						}
					}
					if (event.type == SDL_QUIT) {
						quit = true;
						quitt = true;
					}

				}
				SDL_RenderPresent(renderer);
			}
			if (bestScore < score) {

				new_best_score(sizeBoard, bestScore);
			}
		
	}
		TTF_CloseFont(font);
		TTF_Quit();

}




