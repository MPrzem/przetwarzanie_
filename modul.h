#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#define DL_LINII 1024
typedef struct {
int wym_x, wym_y, szarosci;
void *piksele;
char nazwa[100];
bool czy_wczytano;
} t_obraz;
void wyswietl_aktualny(t_obraz *);
void czytaj(t_obraz *);
void negatyw(t_obraz *);
void progowanie(t_obraz *);
void wyswietl(t_obraz *);
void korekcja_gamma(t_obraz *);
void zapisz (char*,t_obraz*);
void zapisz_aktualny();

/*Funkcje dzia�aj� analogicznie do funkcji w programie "Przetwarzanie obraz�w 1". Jedyn� r�nic� jest to ze zamiast
przekazywa� funkcjom adresy poszczeg�lnych zmiennych, przekazuje adres struktury.  */
