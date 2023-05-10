#include <SDL/SDL_image.h>
#include "fonction.h"

void initBack(Background *b) {
    b->image = IMG_Load("background.png");
   b.x = 0;
    b.y = 0;
    b.w = back.image->w;
    b.h = back.image->h;
    TTF_Init();
	b->texte.police=TTF_OpenFont("arial.ttf",50);
	b->texte.couleur.r=0;
	b->texte.couleur.g=0;
	b->texte.couleur.b=0;
	b->texte.pos.x=500;
	b->texte.pos.y=30;
}

void afficherBack(Background b, SDL_Surface *screen) {
    SDL_BlitSurface(b.image, NULL, screen, NULL);
}

void scrolling(SDL_Rect *b, int direction, int pas) {
    if (direction == 0 && b->x + pas < b->w) {
        b->x += pas;
    }
    else if (direction == 1 && b->x - pas > 0) {
        b->x -= pas;
    }
    else if (direction == 2 && b->y + pas < b->h) {
        b->y += pas;
    }
    else if (direction == 3 && b->y - pas > 0) {
        b->y -= pas;
    }
}



void animation(Background *back) {
    static SDL_Surface* frames[3] = {NULL};
    static int current_frame = 0;
    static Uint32 last_time = 0;

    Uint32 current_time = SDL_GetTicks();

    int animation_delay = 200;

    if (frames[0] == NULL) {
        frames[0] = IMG_Load("background.png");
        frames[1] = IMG_Load("back11.png");
        frames[2] = IMG_Load("back12.png");
        if ((frames[0] == NULL) && (frames[1] == NULL) && (frames[2] == NULL)) {
            printf("Unable to load animation %s\n", SDL_GetError());
            return;
        }
    }

    if (current_time > last_time + animation_delay) {
        current_frame = (current_frame + 1) %3;
        back->image = frames[current_frame];
        last_time = current_time;
    }
}
void saveScore(scoreInfo  s,  char *filename)
{
	FILE *f;
	f=fopen(filename,"a");
	if(f==NULL)
		printf("erreur lors de l'ouverture du fichier save %s ",SDL_GetError());
	else 
	{
		fprintf(f,"nom : %s score : %d temps : %d \n",s.playername,s.score,s.temps);
		fclose(f);
	}
	
}

void bestScore(char *filename,  scoreInfo  T[],Background b,SDL_Surface *screen)
{
	scoreInfo s;
	FILE *f;
	int i=-1,p=1,j;
	char ch[50];
	f=fopen(filename,"r");
	if(f==NULL)
		printf("erreur lors de l'ouverture du fichier save %s ",SDL_GetError());
	else 
	{
		while(fscanf(f,"nom : %s score : %d temps : %d \n",s.playername,&s.score,&s.temps)!=EOF)
			{
				i++;
				T[i]=s;
			}
		
		fclose(f);
		while(p)
		{
			p=0;
			for(j=0;j<i-1;j++)
			{
				if(T[j].score<T[j+1].score || (T[j].score==T[j+1].score && T[j].temps>T[j+1].temps))
				{
					s=T[j];
					T[j]=T[j+1];
					T[j+1]=s;
					p=1;
				}
			}
			
		}
		for(j=0;j<3;j++)
		{
			sprintf(ch," le %d : nom : %s score : %d temps : %d \n",j+1,T[j].playername,T[j].score,T[j].temps);
			b.texte.txt=TTF_RenderText_Blended(b.texte.police,ch,b.texte.couleur);
			SDL_BlitSurface(b.texte.txt,NULL,screen,&b.texte.pos);
			SDL_Flip(screen);
			b.texte.pos.y+=50;
		}
			
			
	}
	
}


