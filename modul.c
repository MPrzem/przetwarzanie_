#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include "modul.h"
#define DL_LINII 1024
void czytaj(t_obraz *obrazek)
{
    char buf[DL_LINII];      /* bufor pomocniczy do czytania naglowka i komentarzy */
    int znak;                /* zmienna pomocnicza do czytania komentarzy */
    int koniec=0;            /* czy napotkano koniec danych w pliku */
    int i,j;
    FILE *plik_we;
    plik_we=fopen(obrazek->nazwa,"r");
    if (plik_we==NULL)
    {

        fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");

        return;

    }



    /* Sprawdzenie "numeru magicznego" - powinien bya P2 */

    if (fgets(buf,DL_LINII,plik_we)==NULL)   /* Wczytanie pierwszej linii pliku do bufora */

        koniec=1;                              /* Nie udalo sie? Koniec danych! */



    if ( (buf[0]!='P') || (buf[1]!='2') || koniec)    /* Czy jest magiczne "P2"? */
    {

        fprintf(stderr,"Blad: To nie jest plik PGM\n");

        return;

    }



    /* Pominiecie komentarzy */

    do
    {

        if ((znak=fgetc(plik_we))=='#')           /* Czy linia rozpoczyna sie od znaku '#'? */
        {

            if (fgets(buf,DL_LINII,plik_we)==NULL)  /* Przeczytaj ja do bufora                */

                koniec=1;                   /* Zapamietaj ewentualny koniec danych */

        }
        else
        {

            ungetc(znak,plik_we);                   /* Gdy przeczytany znak z poczatku linii */

        }                                         /* nie jest '#' zwroc go                 */

    }
    while (znak=='#' && !koniec);     /* Powtarzaj dopoki sa linie komentarza */


    if (fscanf(plik_we,"%d %d %d",&(obrazek->wym_x),&(obrazek->wym_y),&(obrazek->szarosci))!=3)
    {

        fprintf(stderr,"Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");

        return;

    }
    free(obrazek->piksele);
    obrazek->czy_wczytano=false;//resetowanie flagi
    obrazek->piksele = malloc(obrazek->wym_x*obrazek->wym_y*sizeof(int));
    if(!(obrazek->piksele))
    {
        fprintf(stderr,"Blad: Nie przydzielono pamieci");
        return;
    }
    int (*piksele)[obrazek->wym_x];
    piksele=(int(*)[obrazek->wym_x]) obrazek->piksele;
    /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/

    for (i=0; i<obrazek->wym_y; i++)
    {

        for (j=0; j<obrazek->wym_x; j++)
        {

            if (fscanf(plik_we,"%d",&(piksele[i][j]))!=1)
            {

                fprintf(stderr,"Blad: Niewlasciwe wymiary obrazu\n");

                return;

            }

        }

    }


    obrazek->czy_wczytano=true;
    fclose(plik_we);

}


void negatyw(t_obraz *obrazek)
{

    int i,j;
    int (*pix)[obrazek->wym_x];
    pix=(int(*)[obrazek->wym_x])obrazek->piksele;
    for (i=0; i<obrazek->wym_y; i++)
    {
        for (j=0; j<obrazek->wym_x; j++)
        {
            pix[i][j]= obrazek->szarosci-pix[i][j]; //tworzenie negatywu poprzez odjecie jego aktualnej wartosci od wartosci maksymalnej */
        }
    }
}

void progowanie(t_obraz *obrazek)
{

    int (*pix)[obrazek->wym_x];                                 //wskaznik na tablice
    pix=(int(*)[obrazek->wym_x])obrazek->piksele;

    int procent;

    int prog;

    int i,j;

    puts("Podaj procentowa wartosc progu(nie wpisuj znaku %).");

    scanf("%d",&procent);

    prog=(obrazek->szarosci*procent)/100 ; /*wpisanie do zmiennej prog zadanego procentu szarosci */

    for (i=0; i<obrazek->wym_y; i++)
    {

        for (j=0; j<obrazek->wym_x; j++)
        {

            if(pix[i][j]>prog)  /*sprawdzenie czy wartosc pixela jest wieksza czy mniejsza od progu i nadanie jej wartosci maxymalnej bieli lub czerni */

                pix[i][j]=obrazek->szarosci;

            else pix[i][j]=0;

        }
    }

}

void wyswietl_aktualny(t_obraz * obrazek)
{

    if(!obrazek->czy_wczytano)
    {
        fprintf(stderr,"Blad: nie wczytano obrazu\n");
        return;
    }

    zapisz("tmp.pgm",obrazek);
    system("display tmp.pgm");             /* wykonanie polecenia        */
    FILE *tmp;
    tmp=fopen("tmp.pgm","w");
    fclose(tmp);
}


void wyswietl(t_obraz *obrazek)
{

    char polecenie[DL_LINII];



    strcpy(polecenie,"display ");

    strcat(polecenie,obrazek->nazwa);

    strcat(polecenie," &");

    printf("%s\n",polecenie);

    system(polecenie);

}

void korekcja_gamma(t_obraz *obrazek)
{

    double gamma,tmp,szaroscid,w;

    int i,j;

    puts("podaj wspolczynnik gamma");

    scanf("%lf",&gamma);

    gamma=1/gamma;

    szaroscid=(double)(obrazek->szarosci);
    int (*pix)[obrazek->wym_x];                                 /*wskaznik na tablice                   */
    pix=(int(*)[obrazek->wym_x])obrazek->piksele;
    for (i=0; i<obrazek->wym_y; i++)
    {

        for (j=0; j<obrazek->wym_x; j++)
        {

            tmp=(double)pix[i][j];

            w=pow((tmp/(szaroscid)),gamma);

            /*wartosc korekcji wyliczana zgodnie ze wzorem z dokumentu o filtrach.

            				 Do pierwiastkowania do dowolnej potêgi u¿y³em funkcji pow z biblioteki math.h */

            w=w*szaroscid;

            pix[i][j]=(int)w;

        }

    }

}
void zapisz_aktualny(t_obraz* Obrazek)
{
    zapisz(Obrazek->nazwa,Obrazek);
}

void zapisz (char* nazwa,t_obraz* obrazek)
{

    int i,j;

    int (*pix)[obrazek->wym_x];                                 /*wskaznik na tablice                   */
    pix=(int(*)[obrazek->wym_x])obrazek->piksele;
    FILE *plik_wy;

    plik_wy = fopen(nazwa,"w");

    if (plik_wy==NULL)
    {

        fprintf(stderr,"Blad: Nie podano uchwytu do pliku\n");

        return;

    }

    fprintf(plik_wy,"P2\n");

    fprintf(plik_wy,"%d %d\n",obrazek->wym_x,obrazek->wym_y);

    fprintf(plik_wy,"%d\n",obrazek->szarosci);

    for (i=0; i<obrazek->wym_y; i++)
    {

        for (j=0; j<obrazek->wym_x; j++)
        {

            fprintf(plik_wy,"%d %c",pix[i][j],9);

        }

        fprintf(plik_wy,"\n");

    }

    fclose(plik_wy);
    return;
}
