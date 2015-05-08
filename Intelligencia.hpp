#ifndef INTELLIGENCIA_HPP
#define INTELLIGENCIA_HPP
#include "Palya.h"
#include "stdlib.h"
#include "time.h"

class Esz{
public:
    static bool voltsrand;
    char c;
    int x,y;
    int pontozas;
    Elem valasztott;
    Esz(char c='O',int pontozas = 0):c(c),pontozas(pontozas),valasztott(10,10,c){};
    double Xpontoz(Palya& palya)
    {
        if(!voltsrand)
            srand(time(NULL));
        voltsrand = true;
        double pont=0;
        pont += 1000000 *   palya.mintadb("XXXXX");
        if(pont > 0)
            return pont;
        pont -= 800000  * ( palya.mintadb("OOOO_") + palya.mintadb("O_OOO") + palya.mintadb("OO_OO")/2);
        if(pont != 0)
            return pont;
        pont += 80000   *   palya.mintadb("-XXXX_");
        if(pont != 0)
            return pont;
        int IOIOOI = palya.mintadb("-O_OO_");
        int OXIXXI = palya.mintadb("OX_XX_");
        int IXIXXI = palya.mintadb("-X_XX_");
        int XXXIX = palya.mintadb("XXX_X");
        int OXXIXI = palya.mintadb("OXX_X_");
        pont -= 8000    * ( IOIOOI + palya.mintadb("-OOO_")/2 );
        pont += 1800   * ( palya.mintadb("XXXX_") + XXXIX + palya.mintadb("XX_XX")/2);
        pont += 1500    * ( palya.mintadb("-XXX_") / 5.0  + IXIXXI / 2.0);
        pont -= 1800  * ( palya.mintadb("XOO_O_") + palya.mintadb("XOOO__") + palya.mintadb("XO_OO_"));
        pont += 750    * ( OXXIXI + palya.mintadb("OXXX__") - XXXIX + OXIXXI);
        pont -= 800        * ( palya.mintadb("-OO_") - 2 * IOIOOI) + palya.mintadb("-O_O_" );
        pont += 100     * ( palya.mintadb("-XX_") - 2 * (OXIXXI + IXIXXI + OXXIXI)  + palya.mintadb("-X_X_")/2 );
        pont += 10      * ( palya.mintadb("-OXX_") - OXXIXI - palya.mintadb("-XOO_"));
        pont -= 2       *  palya.mintadb("-O_");
        return pont * (1 - (rand() % 3)/100.0 );
    }

    double Opontoz(Palya& palya)
    {
    }


    Elem kivalaszt(Palya& palya){
        int i = 100;
        int k = 100;
        double pont = 0;
        int j = 0;
        int l = 0;
        for(int g = 0; g< palya.tomb.size(); g++)
        {
            if( i + 2 > palya.tomb[g].x )
                i = palya.tomb[g].x - 2;
            if(k +2 > palya.tomb[g].y )
                k = palya.tomb[g].y - 2;
            if(j - 2 < palya.tomb[g].x )
                j = palya.tomb[g].x + 2;
            if(l - 2 < palya.tomb[g].y )
                l = palya.tomb[g].y + 2;
        }
        int x=15,y=15;
        double maxpont=-1000000000;
        if(palya.lepes(15,15))
        {
           pont = maxpont = Xpontoz(palya);
            palya.visszalepes();
        }
        for(; i<j; i++)
        {
            for(int cs = k;  cs< l; cs++)
            {
                if(palya.lepes(i,cs))
                {
                    pont = Xpontoz(palya);
                    if(maxpont < pont)
                    {
                        maxpont = pont;
                        x=i;
                        y=cs;
                    }
                    palya.visszalepes();
                }
            }
        }
        Elem uj(x,y,'X');
        return uj;
    }
};

bool Esz::voltsrand = false;

#endif
