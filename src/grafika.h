#include <allegro5/allegro.h>

void rysuj_wybierz_graczy(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params);

void rysuj_wyniki(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params);

void rysuj_wstep(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params, ALLEGRO_BITMAP *background, int pozycja);

/*  rysuj_gre()
	mnogoœæ zmiennych wynika z bliskiego zwi¹zania logiki gry z jej grafik¹, w szczególnoœci ze sprawdzania kolizji i wykonywania przerw w œladzie
	przer - czy w³aœnie wykonywana jest przerwa
	x, y - aktualne pozycje graczy
	px, py - poprzednie pozycje graczy, s³u¿¹ce do zamazania przerwy
	pomx, pomy - pozycje pocz¹tku przerwy u¿ywane do zaokr¹glania krawêdzi
	napraw - czy wykonaæ zaokr¹glenie krawêdzi?
*/
void rysuj_gre(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bufor, parametry *params, bool *still_alive, bool przer, float *x, float *y, float *px, float *py, float *pomx, float *pomy, bool napraw);