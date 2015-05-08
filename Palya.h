#ifndef PALYA_H
#define PALYA_H
#include <vector>

using namespace std;

const int MAG=600,SZEL=600;

struct Elem{
    int x,y;
    char ertek;
    Elem(int x,int y,char ertek):x(x),y(y),ertek(ertek){};
    bool operator==(const Elem& jobb)const{
        if( x==jobb.x && y==jobb.y && ertek ==jobb.ertek)
            return true;
        return false;
    }
    bool operator!=(const Elem& jobb){return ! ((*this) == jobb);}
    void operator++(){x++; if(x > 29){x=0;y++;}if(y > 29){x=0;y=0;}}
};

class Palya{
public:
    vector<Elem> tomb;
    bool olep;
    Palya():olep(0){};
    void kirajzol(SDL_Surface*);
    bool lepes(int,int);
    bool visszalepes();
    bool bennevan(const Elem&);
    bool vege(SDL_Surface*);
    bool egymasmellet(int,const Elem&,int,int);
    int mintafelismero(const char*,const Elem&,int,int);
    bool getolep()const{return olep;}
    int mintadb(const char*);
    vector<Elem> gettomb()const{return tomb;}
};


#endif
