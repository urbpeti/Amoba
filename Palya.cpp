#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include "Palya.h"
#include "string.h"
#include <string>

int hanyszor=0;

void Palya::kirajzol(SDL_Surface* screen){
    for(vector<Elem>::iterator it = tomb.begin();it != tomb.end();it++)
    {
        switch((*it).ertek){
        case 'X':
            lineColor(screen,SZEL/30*(*it).x,MAG/30*(*it).y,SZEL/30*((*it).x+1),MAG/30*((*it).y+1),0xFF0000FF);
            lineColor(screen,SZEL/30*((*it).x+1),MAG/30*((*it).y),SZEL/30*((*it).x),MAG/30*((*it).y+1),0xFF0000FF);
            break;
        case 'O':
            circleColor(screen,SZEL/30*((*it).x+0.5),MAG/30*((*it).y+0.5),SZEL/60,0x00FF00FF);
            break;
        default:
            throw "Hiba";
        }
    }
};

bool Palya::bennevan(const Elem& elem){
    for(vector<Elem>::iterator it = tomb.begin();it != tomb.end();it++)
    {
        if( (*it).x == elem.x && (*it).y == elem.y)
            return true;
    }
    return false;
}


bool Palya::lepes(int x,int y){
    char c;
    if(olep)
        c='O';
    else
        c='X';
    Elem uj(x,y,c);
    if(bennevan(uj)){
        return false;
    }
    else{
        tomb.push_back(uj);
    }
    olep = !olep;
    return true;
}

bool Palya::visszalepes(){
    tomb.pop_back();
    olep = !olep;
}


bool Palya::vege(SDL_Surface* screen){
    bool nyert;
    int x,y;
    int g = 0;
    for(int i = 0; i< tomb.size();i++)
    {
        for(int j=0;j<4;j++)
        {
            switch(j){
            case 0:x=1;y=0;break;
            case 1:x=1;y=1;break;
            case 2:x=0;y=1;break;
            case 3:x=-1;y=1;break;
            }
        if( mintafelismero("XXXXX",tomb[i],x,y ) + mintafelismero( "OOOOO",tomb[i],x,y) > 0)
        {
            lineColor(screen,SZEL/30*(tomb[i].x+0.5),MAG/30*(tomb[i].y+0.5),SZEL/30*(tomb[i].x+0.5+4*x),MAG/30*(tomb[i].y+0.5+4*y),0xFFFFFFFF);

            return true;
        }
        }
    }
    return false;
}

bool Palya::egymasmellet(int ert,const Elem& elem,int x, int y)
{
    Elem uj(elem.x+x,elem.y+y,elem.ertek);
    if(ert == 0)
        return ert;
    for(vector<Elem>::iterator it = tomb.begin();it != tomb.end();it++)
    {
        if( *it != elem && uj == *it)
            return egymasmellet(ert-1,(*it),x,y);
    }
    return ert;
}

int Palya::mintafelismero(const char* minta,const Elem& kezdo,int x,int y)
{
    if(minta[0]=='-')
    {
        Elem uj(kezdo.x-x,kezdo.y-y,'-');
        Elem uj1(kezdo.x,kezdo.y,minta[1]);
        if(!bennevan(uj))
            return mintafelismero(minta+1,uj1,x,y);
        return 0;
    }
    if(minta[0]!= '_')
    {
    if(minta[0]=='\0')
        return 1;
    if(minta[0] != kezdo.ertek)
        return 0;
    Elem uj(kezdo.x+x,kezdo.y+y,minta[1]);
    for(vector<Elem>::iterator it = tomb.begin();it != tomb.end();it++)
    {
        if(*it == kezdo)
            return mintafelismero(minta+1,uj,x,y);
    }
    }
    else
    {
        Elem uj(kezdo.x+x,kezdo.y+y,minta[1]);
        if(!bennevan(kezdo))
            return mintafelismero(minta+1,uj,x,y);
    }

    return 0;
}

int Palya::mintadb(const char* minta)
{
    int x,y;
    int db = 0;
    for(int i = 0; i< tomb.size();i++)
    {
        for(int j=0;j<8;j++)
        {
            switch(j){
            case 0:x=1;y=0;break;
            case 1:x=1;y=1;break;
            case 2:x=0;y=1;break;
            case 3:x=-1;y=1;break;
            case 4:x=-1;y=0;break;
            case 5:x=-1;y=-1;break;
            case 6:x=0;y=-1;break;
            case 7:x=1;y=-1;break;
            }
            db += mintafelismero(minta,tomb[i],x,y);
        }
    }
    return db;

}
