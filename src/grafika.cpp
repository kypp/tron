#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "logika.h"
#include "grafika.h"

const int gr = 10;	//grubosc ramek

const unsigned char kolor[4][3] = {			//kolory graczy
	{ 129, 0,   0   },						//rgb(127, 0, 0)
	{ 1,   127, 0   },						//rgb(0, 127, 0)
	{ 1,   0,   127 },						//rgb(0, 0, 127)
	{ 127, 0,   127 } };					//rgb(127, 0, 127)


void rysuj_wybierz_graczy(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params)
{
	
	//pobranie rozmiaru aktualnego ekranu:
	int  maxx   = al_get_display_width(display);
	int  maxy   = al_get_display_height(display);

	al_clear_to_color(al_map_rgb(0, 0, 0));
	//rysowanie kwadratów jeśli gracz jest wybrany:
	for (int i=0; i<4; i++)
		if (params->gracze[i])
			al_draw_rectangle(	(i<2)		?(0+gr)		  :(maxx/2+gr), 
								((i+1)%2==0)?(maxy/2+gr)  :(0+gr),	
								(i<2)		?(maxx/2-gr/2):(maxx-gr/2), 
								((i+1)%2==1)?(maxy/2-gr/2):(maxy-gr/2), 
			al_map_rgb(kolor[i][0], kolor[i][1], kolor[i][2]), gr);
	//wypisywanie klawiszy kraczy:
	char buf[20];
	strcpy(buf, G0_LEWO_T); strcat(buf, " "); strcat(buf, G0_PRAWO_T);
	al_draw_text(font, al_map_rgb(kolor[0][0], kolor[0][1], kolor[0][2]), maxx/4,   maxy/4,ALLEGRO_ALIGN_CENTRE,   buf);
	strcpy(buf, G1_LEWO_T); strcat(buf, " "); strcat(buf, G1_PRAWO_T);
	al_draw_text(font, al_map_rgb(kolor[1][0], kolor[1][1], kolor[1][2]), maxx/4,   3*maxy/4,ALLEGRO_ALIGN_CENTRE,   buf);
	strcpy(buf, G2_LEWO_T); strcat(buf, " "); strcat(buf, G2_PRAWO_T);
	al_draw_text(font, al_map_rgb(kolor[2][0], kolor[2][1], kolor[2][2]), 3*maxx/4,   maxy/4,ALLEGRO_ALIGN_CENTRE, buf);
	al_draw_text(font, al_map_rgb(kolor[3][0], kolor[3][1], kolor[3][2]), 3*maxx/4, 3*maxy/4,ALLEGRO_ALIGN_CENTRE, "MYSZ");

	al_flip_display();


}

void rysuj_wyniki(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params)
{
	//pobranie rozmiaru aktualnego ekranu:
	int  maxx   = al_get_display_width(display);
	int  maxy   = al_get_display_height(display);

	//wyświetlenie wyników graczy biorących udział w grze:
	al_clear_to_color(al_map_rgb(0, 0, 0));
	char str[5];
	for (int i=0; i<4;i++)
		if (params->gracze[i])
		{
			sprintf(str, "%d", params->punkty[i]);
			al_draw_rectangle(	(i<2)		?(0+gr)		  :(maxx/2+gr), 
								((i+1)%2==0)?(maxy/2+gr)  :(0+gr),	
								(i<2)		?(maxx/2-gr/2):(maxx-gr/2), 
								((i+1)%2==1)?(maxy/2-gr/2):(maxy-gr/2), 
				al_map_rgb(kolor[i][0], kolor[i][1], kolor[i][2]), gr);
			al_draw_text(font, al_map_rgb(kolor[i][0], kolor[i][1], kolor[i][2]), ((i<2)?1:3)*maxx/4, ((i+1)%2==0?3:1)*maxy/4,ALLEGRO_ALIGN_CENTRE, str);
		}
	al_flip_display();

}

void rysuj_wstep(ALLEGRO_DISPLAY *display, ALLEGRO_FONT *font, parametry *params, ALLEGRO_BITMAP *background, int pozycja)
{
	
	//pobranie rozmiaru aktualnego ekranu:
	int  maxx   = al_get_display_width(display);
	int  maxy   = al_get_display_height(display);

	
	al_clear_to_color(al_map_rgb(0, 0, 0));

	//rysowanie tla (jesli istnieje)
	if (background != NULL)
		al_draw_bitmap(background, 0, 0, 0);

	//wypisyanie menu (z podswietleniem wybranego elementu)
	char str[40]; 
	al_draw_text(font, al_map_rgb(pozycja==0?25:250, 250, 0), maxx/2, 2*maxy/12,  ALLEGRO_ALIGN_CENTRE, "Rozpocznij gre");
	al_draw_text(font, al_map_rgb(pozycja==1?25:250, 250, 0), maxx/2, 3*maxy/12,  ALLEGRO_ALIGN_CENTRE, "Koniec");
	sprintf(str, "Grubosc linii: %.0f", params->promien);
	al_draw_text(font, al_map_rgb(pozycja==2?25:250, 250, 0), maxx/2, 5*maxy/12,  ALLEGRO_ALIGN_CENTRE, str);
	sprintf(str, "Predkosc pojazdu: %.1f", params->velocity);
	al_draw_text(font, al_map_rgb(pozycja==3?25:250, 250, 0), maxx/2, 6*maxy/12,  ALLEGRO_ALIGN_CENTRE, str);
	sprintf(str, "Predkosc obrotu: %.1f", params->ang_velocity);
	al_draw_text(font, al_map_rgb(pozycja==4?25:250, 250, 0), maxx/2, 7*maxy/12,  ALLEGRO_ALIGN_CENTRE, str);
	sprintf(str, "Punkty do wygranej: %d", params->wygrana);
	al_draw_text(font, al_map_rgb(pozycja==5?25:250, 250, 0), maxx/2, 8*maxy/12,  ALLEGRO_ALIGN_CENTRE, str);
	sprintf(str, "Wielkosc przerw w sladzie: %d", params->przerwy);
	al_draw_text(font, al_map_rgb(pozycja==6?25:250, 250, 0), maxx/2, 9*maxy/12, ALLEGRO_ALIGN_CENTRE, str);
	sprintf(str, "Odleglosc miedzy przerwami: %d", params->odleglosc);
	al_draw_text(font, al_map_rgb(pozycja==7?25:250, 250, 0), maxx/2, 10*maxy/12,  ALLEGRO_ALIGN_CENTRE, str);

	al_flip_display();
}

void rysuj_gre(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *bufor, parametry *params, bool *still_alive, bool przer, float *x, float *y, float *px, float *py, float *pomx, float *pomy, bool napraw)
{

	//obraz rozgrywki jest zapisywany do bitmapy:
	al_set_target_bitmap(bufor);

	//rysowanie pozycji graczy i ewentualnych przerw:
	for (int i=0; i<4; i++)
	{
		if (params->gracze[i] && still_alive[i]) {

			//zarysowywanie śladu jeśli ma wystąpić przerwa:
			if (przer) 
				al_draw_filled_circle(pomx[i], pomy[i], params->promien, al_map_rgb(0, 0, 0));

			//zaokrąglenie krawędzi po przerwie:
			if (napraw)
				al_draw_filled_circle(px[i], py[i], params->promien, al_map_rgb(kolor[i][0], kolor[i][1], kolor[i][2]));

			//normalne rysowanie śladu:
			al_draw_filled_circle(x[i], y[i], params->promien, al_map_rgb(kolor[i][0], kolor[i][1], kolor[i][2]));					
		}
	}			

	//wyswietlanie:
	al_set_target_bitmap(al_get_backbuffer(display));
	al_draw_bitmap(bufor, 0, 0, 0);
	al_flip_display();
}