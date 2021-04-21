#include <winbgim.h>

/*
See programm paneb ruudu liikuma nagu progressiivne skanneerimine

Ruudu algpunkt mõjutab ka kui akna äärde võib ta minna, näide:
Kui ruudu algpunkt on 20 pixlit ekraani vasakpoolsest äärest paremal
ning 0 pixlit ülemisest äärest all, siis võib ruut läheneda
paremale äärele maksimaalselt 20 pixlit ja alumisele äärele 0 pixlit
*/

// Algandmed
    // Akna andmed
const int varvTagataust = COLOR(0,128,128); // Sinakasroheline
const int aknaSuurus[2] =
{640, 480}; // [0] - Laius; [1] - kõrgus
    // Joonistamise andmed
const int algPunkt[2] =
{50, 20};   // [0] - x; [1] - y
const int kuljeSuurus = 20;
const int ooteAeg = 20; // millisekundites


void JoonistaRuut(int alustusPunkt[2], int kulg,
                  int varv = COLOR(128, 0, 64))
{
    // Külje suurus on pixlites
    // muudab kordinaadi array eraldi elementideks
    int x = alustusPunkt[0];
    int y = alustusPunkt[1];

    setfillstyle(1, varv); // Ruudu värvi seadistamine
    bar(x, y,
         x + kulg, y + kulg); // Ruudu tekitamine
}

int LiigutaKastiParemale(int punkt[2])
{
    // Puhastab akna
    cleardevice();
    // Teeb uue joonistused
    JoonistaRuut(punkt, kuljeSuurus);

    // Tagastab uue x koordinaadi
    return punkt[0] + kuljeSuurus;
}

main ()
{
    // Algtegevused
        // Defineerib kasti joonistamise algpunkti
    int punkt[2] = {algPunkt[0], algPunkt[1]};
        // Tekitab akna kuhu joonistada
    initwindow(aknaSuurus[0], aknaSuurus[1]);
        // Täidab ekraani tagatausta värvi
    setbkcolor(varvTagataust);
    cleardevice();

    // Kastiga seotud animatsiooni osa
    while (punkt[1] + kuljeSuurus < aknaSuurus[1] - algPunkt[1])
    {
        while(punkt[0] + kuljeSuurus < aknaSuurus[0] - algPunkt[0])
        {
            if (kbhit())
                if (getch() == 27)
                    exit(0);

            punkt[0] = LiigutaKastiParemale(punkt);
            delay(ooteAeg);
        }
        punkt[0] = algPunkt[0];
        punkt[1] += kuljeSuurus;
    }

    // Lõpetab programmi
    closegraph();
}


