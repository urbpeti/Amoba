#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <string>
#include "Palya.h"
#include "Intelligencia.hpp"



int main(int argc, char *argv[]) {
    SDL_Event ev;
    SDL_Surface *screen;
    Palya palya;
    Esz proba;
    bool vege=0;
    bool nemelso = 0;
    bool inti = false;



    SDL_Init(SDL_INIT_VIDEO);
    screen=SDL_SetVideoMode(SZEL, MAG, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Amoba", "Amoba");
    for(int i = 1; i<SZEL;i++)
        lineColor(screen, SZEL/30 * i ,0,SZEL/30*i ,MAG,0xFFFFFF88);
    for(int i = 1; i<MAG;i++)
        lineColor(screen, 0 ,MAG/30 * i,SZEL ,MAG/30 * i,0xFFFFFF88);


        Elem asdf(0,0,'X');
        asdf = proba.kivalaszt(palya);
        palya.lepes(asdf.x,asdf.y);
        palya.kirajzol(screen);


    SDL_Flip(screen);


    while (SDL_WaitEvent(&ev) && ev.type!=SDL_QUIT) {
    if(!vege){
    if(ev.type == SDL_MOUSEBUTTONDOWN)
    {
        if(ev.button.button == SDL_BUTTON_LEFT)
        {
            string kiiras("VEGE NYERT AZ ");
            boxColor(screen,0,0,SZEL,MAG,0x000000FF);
            for(int i = 1; i<SZEL;i++)
                lineColor(screen, SZEL/30 * i ,0,SZEL/30*i ,MAG,0xFFFFFF88);
            for(int i = 1; i<MAG;i++)
                lineColor(screen, 0 ,MAG/30 * i,SZEL ,MAG/30 * i,0xFFFFFF88);
            int x,y;

            x = ev.button.x;
            y = ev.button.y;
            x = x/(SZEL/30);
            y = y/(MAG/30);
            if(palya.lepes(x,y))
            {
            if(palya.vege(screen))
            {
                vege=1;
                if(!palya.getolep())
                    kiiras = kiiras + "O";
                else
                    kiiras = kiiras + "X";
                stringColor(screen,50,50,kiiras.c_str(),0xFFFFFFFF);
            }
            if(!vege && inti)
            {
            asdf = proba.kivalaszt(palya);
            palya.lepes(asdf.x,asdf.y);
            if(palya.vege(screen))
            {
                vege=1;
                if(!palya.getolep())
                    kiiras = kiiras + "O";
                else
                    kiiras = kiiras + "X";
                stringColor(screen,50,50,kiiras.c_str(),0xFFFFFFFF);
            }
            }
            }
            palya.kirajzol(screen);
            SDL_Flip(screen);
        }
        if(ev.button.button == SDL_BUTTON_RIGHT)
        {
            if(palya.tomb.size()>1)
            {
            palya.visszalepes();
            palya.visszalepes();
            }
            boxColor(screen,0,0,SZEL,MAG,0x000000FF);
            for(int i = 1; i<SZEL;i++)
                lineColor(screen, SZEL/30 * i ,0,SZEL/30*i ,MAG,0xFFFFFF88);
            for(int i = 1; i<MAG;i++)
                lineColor(screen, 0 ,MAG/30 * i,SZEL ,MAG/30 * i,0xFFFFFF88);
            palya.kirajzol(screen);
            SDL_Flip(screen);
        }
    }
    if( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_SPACE )
    {
        inti = !inti;
    }
    }
    }



    SDL_Quit();

    return 0;
}
