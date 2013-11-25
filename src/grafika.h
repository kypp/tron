#include <allegro5/allegro.h>

void rysuj_wybierz_graczy(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params);

void rysuj_wyniki(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params);

void rysuj_wstep(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params, ALLEGRO_BITMAP *background, int pozycja);

/*  rysuj_gre()
	mnogo�� zmiennych wynika z bliskiego zwi�zania logiki gry z jej grafik�, w szczeg�lno�ci ze sprawdzania kolizji i wykonywania przerw w �ladzie
	przer - czy w�a�nie wykonywana jest przerwa
	x, y - aktualne pozycje graczy
	px, py - poprzednie pozycje graczy, s�u��ce do zamazania przerwy
	pomx, pomy - pozycje pocz�tku przerwy u�ywane do zaokr�glania kraw�dzi
	napraw - czy wykona� zaokr�glenie kraw�dzi?
*/
void rysuj_gre(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bufor, parametry *params, bool *still_alive, bool przer, float *x, float *y, float *px, float *py, float *pomx, float *pomy, bool napraw);