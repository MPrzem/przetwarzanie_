#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "modul.h"
#define MAX 512            /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024      /* Dlugosc buforow pomocniczych */


int main()
{
    int decyzja;
    t_obraz Obraz;
    do
    {
        puts("Przetwazanie obrazow.\nWybierz pozycje z menu wpisujac cyfre od 1 do 6 ""k"" konczy dzialanie programu");
        printf("1.Wczytanie obrazu\n2.Wyswietlenie obraz\n3.Wyswietl aktualny\n4.negatyw obrazy\n5.Progowanie obrazu\n6.korekcja gamma\n7.Zapisz\n");
        scanf("%d",&decyzja);
        system("clear");

        switch(decyzja)
        {
        case 1:
            printf("Podaj nazwe pliku:\n");
            scanf("%s",Obraz.nazwa);
            czytaj(&Obraz);
            break;
        case 2:
            puts("podaj nazwe pliku ktory chcesz wyswietlic");
            scanf("%s",Obraz.nazwa);
            wyswietl(&Obraz);
            break;
        case 3:
            wyswietl_aktualny(&Obraz);
            break;
        case 4:
            negatyw(&Obraz);
            break;
        case 5:
            progowanie(&Obraz);
            break;
        case 6:
            korekcja_gamma(&Obraz);
            break;
        case 7:
            puts("Podaj nazwe pod jaką chcesz zapisać plik");
            scanf("%s",Obraz.nazwa);
            zapisz_aktualny(&Obraz);
            break;
        }
        while(!('\n'==getchar()));
    }while(1);
    return 0;
}
