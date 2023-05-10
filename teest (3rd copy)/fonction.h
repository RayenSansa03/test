#ifndef FONCTION_H
#define FONCTION_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
typedef struct {
    SDL_Surface *image;
} Background;
typedef struct 
{
	SDL_Surface *txt;
	SDL_Rect pos;
	SDL_Colour couleur;
	TTF_Font *police;
}text;



typedef struct
{
	int score,temps;
	char playername[20];	
}scoreInfo;

void initBack(Background *b);
void afficherBack(Background b, SDL_Surface *screen);
void scrolling(SDL_Rect *b, int direction, int pas);
void animation(Background *back);
void saveScore(scoreInfo  s,  char *filename);
void bestScore(char *filename,  scoreInfo  T[],Background b,SDL_Surface *screen);







#endif /* FONCTION_H */

