#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "fonction.h"

#define BACKGROUND_MUSIC "background.mp3"

int main() {
    SDL_Surface *screen;
    Background back;
    SDL_Rect b;
    scoreInfo T[20];
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    screen = SDL_SetVideoMode(640,500, 32, SDL_SWSURFACE);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Music *music = Mix_LoadMUS(BACKGROUND_MUSIC);
    Mix_PlayMusic(music, -1);

    initBack(&back);
   

    SDL_Event event;
    int continuer = 1;

    while (continuer) {

        animation(&back);

        
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        SDL_BlitSurface(back.image, &b, screen, NULL);
        SDL_Flip(screen);


        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        scrolling(&b, 0, 3);
                        break;
                    case SDLK_LEFT:
                        scrolling(&b, 1, 3);
                        break;
                          case SDLK_UP:
                scrolling(&b, 3, 3);
                break;
            case SDLK_DOWN:
                scrolling(&b, 2,3);
                break;
                    case SDLK_SPACE:
                     bestScore("score.txt",T,b,screen);
                      
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }

    Mix_FreeMusic(music);
    SDL_FreeSurface(back.image);
    
    SDL_Quit();
    return 0;
}




