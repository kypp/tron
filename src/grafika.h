#include <allegro5/allegro.h>

void rysuj_wybierz_graczy(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params);

void rysuj_wyniki(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params);

void rysuj_wstep(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params, ALLEGRO_BITMAP *background, int pozycja);

/*  rysuj_gre()
	mnogość zmiennych wynika z bliskiego związania logiki gry z jej grafiką, w szczególności ze sprawdzania kolizji i wykonywania przerw w śladzie
	przer - czy właśnie wykonywana jest przerwa
	x, y - aktualne pozycje graczy
	px, py - poprzednie pozycje graczy, służące do zamazania przerwy
	pomx, pomy - pozycje początku przerwy używane do zaokrąglania krawędzi
	napraw - czy wykonać zaokrąglenie krawędzi?
*/
void rysuj_gre(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bufor, parametry *params, bool *still_alive, bool przer, float *x, float *y, float *px, float *py, float *pomx, float *pomy, bool napraw);