#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <math.h>
#include "logika.h"
#include "grafika.h"

const float PI = 3.14159265358979323846;	//liczba pi, potrzebna do oblicze� skr�cania
const float FPS				= 60;			//liczba po��danych klatek na sekund�
const float d_promien		= 4;			//domy�lna grubo�� �ladu zostawianego przez graczy
const float d_velocity		= 2;			//domy�lna pr�dko�� pojazdu graczy
const float d_ang_velocity	= 2;			//domy�lna pr�dko�� obrotu pojazdu	
const int	d_wygrana		= 20;			//domyslna ilosc punktow potrzebnych do zwyciestwa
const int   d_przerwy		= 2;			//domyslna wielkosc przerw w sladzie
const int	d_odleglosc		= 10;			//domyslna odleglosc pomiedzy przerwami w sladzie

int gra(ALLEGRO_DISPLAY *display, parametry *params)
//zakladam, ze po wejsciu do funkcji gra moduly sa zaladowane: image_addon, primitives_addon, keyboard, mouse, no i samo allegro jest zainicjalizowane
{	
	//zmienne logiczne u�ywane do obs�ugi zdarze� i g��wnej p�tli:
	bool redraw = true;
	bool doexit = false;	
	bool pocz   = true;
	bool wait_for_input = false;
    bool key[8] = { false, false, false, false, false, false, false, false };	
	bool still_alive[4] = { params->gracze[0], params->gracze[1], params->gracze[2], params->gracze[3] };
	
	
	//zmienna oznaczaj�ca stan gry:
	int stan = 0;

	//pobranie rozmiaru aktualnego ekranu:
	int  maxx   = al_get_display_width(display);
	int  maxy   = al_get_display_height(display);
	
	//deklaracja pocz�tkowych ustawie� i k�t�w graczy:
	float x[4]		= { maxx/2-maxx/10, maxx/2-maxx/10, maxx/2+maxx/10, maxx/2+maxx/10 }; 
    float y[4]		= { maxy/2-maxy/10, maxy/2+maxy/10, maxy/2-maxy/10, maxy/2+maxy/10 };
	float angle[4]	= { 225,			135,			315,			45			   };

	//zmienne obs�uguj�ce przerwy w �ladzie:
	bool przer = false;
	bool napraw = false;
	int  n	   = 0;
	float px[4], py[4], pomx[4], pomy[4];
	unsigned char r=0, g=0, b=0;

	//tworzenie kolejki zdarze� oraz timera zapewniaj�cego odpowiedni� cz�stotliwo�� wy�wietlania, oraz bitmapy potrzebnej do wy�wietlania:
	ALLEGRO_TIMER       *timer		 = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_BITMAP		*bufor		 = al_create_bitmap(maxx, maxy);	
	
	//podpi�cie do kolejki zdarze� zwi�zanych z klawatur�, mysz�, timerem i displayem:
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));	
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//wst�pne wyczyszczenie ekranu i bufora - nie jest on czyszczony podczas rozgrywki:
	al_clear_to_color(al_map_rgb(0, 0, 0));	
    al_flip_display();	
	al_clear_to_color(al_map_rgb(0, 0, 0));	
    al_flip_display();
	al_set_target_bitmap(bufor);
	al_clear_to_color(al_map_rgb(0, 0, 0));	
    al_flip_display();	

	//inicjalizacja timera:
	al_start_timer(timer);
	

	while(!doexit)
	{
		//przechwycenie zdarzenia:
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		//instrukcja wykonywana FPS razy na sekund�, obs�uguj�ca wykonane przez graczy naci�ni�cia klawiszy:
		if(ev.type == ALLEGRO_EVENT_TIMER) {
 
			for (int i=0; i<4; i++)
				if (key[2*i] && params->gracze[i] && still_alive[i]) angle[i]-=params->ang_velocity;
			
			for (int i=0; i<4; i++)
				if (key[2*i+1] && params->gracze[i] && still_alive[i]) angle[i]+=params->ang_velocity;

			redraw = true;
		}
		//obs�uga ��dania wy��czenia programu:
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			stan =-1;
			break;
		}
		//sprawdzanie naci�ni�� klawiszy:
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
 
			case G0_LEWO: 
				key[0] = true;
				break; 

			case G0_PRAWO:
				key[1] = true;
				break;

			case G1_LEWO: 
				key[2] = true;
				break;
 
			case G1_PRAWO:
				key[3] = true;
				break;

			case G2_LEWO: 
				key[4] = true;
				break;
 
			case G2_PRAWO:
				key[5] = true;
				break;

			case ALLEGRO_KEY_ENTER:
			case ALLEGRO_KEY_SPACE:
				if (wait_for_input) doexit = true;
				break;
 
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				stan =-1;
				break;
			}
		}
		//sprawdzanie podniesie� klawiszy:
		else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch(ev.keyboard.keycode) {
 
			case G0_LEWO: 
				key[0] = false;
				break;
 
			case G0_PRAWO:
				key[1] = false;
				break;

			case G1_LEWO: 
				key[2] = false;
				break;
 
			case G1_PRAWO:
				key[3] = false;
				break;

			case G2_LEWO: 
				key[4] = false;
				break;
 
			case G2_PRAWO:
				key[5] = false;
				break;
			}
		}
		//sprawdzenie nacisniecia klawiszy myszy:
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			switch(ev.mouse.button){
				case 1:
					key[6] = true;
					break;
				case 2:
					key[7] = true;
					break;
			}
		}
		//sprawdzenie podniesien klawiszy myszy:
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			switch(ev.mouse.button){
				case 1:
					key[6] = false;
					break;
				case 2:
					key[7] = false;
					break;
			}
		}
 
		//naniesienie zmian, rysowanie, wykrywanie kolizji:
		if(redraw && al_is_event_queue_empty(event_queue) )
		{
			redraw = false;

			//blokuj� obecny stan buforu w celu szybkiego pobierania pikseli, bez blokowania al_get_pixel wykonuje si� bardzo wolno, z nim mam sta�e 240 FPS
			al_lock_bitmap(bufor, al_get_bitmap_format(bufor), ALLEGRO_LOCK_READONLY);

			//ca�a logika gry - wykonywana je�li nie oczekuje si� za zako�czenie:
			if (!wait_for_input) {

				//wykrywanie kolizji oraz ich obs�uga:				
				for (int i=0; i<4; i++)
				{
					if (still_alive[i]) {
						
						al_unmap_rgb(al_get_pixel(bufor, x[i]+1.5*params->promien*cos(angle[i]*PI/180), y[i]+1.5*params->promien*sin(angle[i]*PI/180)), &r, &g, &b);							

						if (r !=0 || x[i]>maxx || x[i]<0 || y[i]>maxy || y[i]<0)
						{
							still_alive[i] = false;
							for (int j=0; j<4; j++)
								if (still_alive[j]) params->punkty[j]++;
						}
					}
				}
				
				//obs�uga przerw w �ladzie:
				if (params->przerwy>0) {
					n++;
					if (przer && n>=(3*params->promien*(params->przerwy+1)/params->velocity))     {
						przer = false;
						n	  = 0;			     	 }
					if (!przer && n>=params->promien*6*params->odleglosc/params->velocity) {
						przer = true;
						n	  = 0;     			     }
				}

				//aktualizacja koordynat�w graczy:				
				napraw = false;
				for (int i=0; i<4; i++)
				{
					if (params->gracze[i] && still_alive[i]) {
						pomx[i] = x[i];
						pomy[i] = y[i];
						x[i] = x[i]+params->velocity*cos(angle[i]*PI/180);
						y[i] = y[i]+params->velocity*sin(angle[i]*PI/180);

						//ustalanie pozycji potrzebnch do zaokraglenia krawedzi:
						if (przer) {
							if (n==0) { 
								px[i] = pomx[i];
								py[i] = pomy[i];
							}
							if (n==(int)(2*(params->promien)/params->velocity))
								napraw = true;
						}				
					}
				}	

				//sprawdzenie konca gry:
				int n=0;
				for (int i=0; i<4; i++)
					if (still_alive[i]) n++;
				if (n==1||n==0) wait_for_input = true;				
			}

			//wyswietlanie:
			rysuj_gre(display, bufor, params, still_alive, przer, x, y, px, py, pomx, pomy, napraw);

			al_unlock_bitmap(bufor);

			//oczekiwanie chwil� w pocz�tkowej pozycji
			if (pocz) 
				{
					pocz = false;
					al_rest(0.2);
				}
		}		
	}	
				
	//usuwanie stworzonych obiekt�w:
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(bufor);

	return stan;
}

int ustal_graczy(ALLEGRO_DISPLAY *display, parametry *params)
//zak�adam, �e fonty, prymitywy, klawiatura, mysz i samo allegro s� zainicjalizowane
{
	//zmienne logiczne u�ywane do obs�ugi zdarze� i g��wnej p�tli:
	bool redraw = true;
	bool doexit = false;	

	//zmienna sterujaca stanem funkcji
	int stan = 0;

	//tworzenie kolejki zdarze� oraz timera zapewniaj�cego odpowiedni� cz�stotliwo�� wy�wietlania:
	ALLEGRO_TIMER       *timer		 = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_FONT		*font		 = al_load_ttf_font(FONT,72,0 );
	
	//podpi�cie do kolejki zdarze� zwi�zanych z klawatur�, mysz�, timerem i displayem:
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));	
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());

	//inicjalizacja timera:
	al_start_timer(timer);

	while(!doexit)
	{
		//przechwycenie zdarzenia:
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		//obs�uga timera
		if(ev.type == ALLEGRO_EVENT_TIMER) 
			redraw = true;

		//obs�uga ��dania wy��czenia programu:
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			stan=-1;
			doexit=true;
		}
		//sprawdzanie nacisniec klawiszy:
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch(ev.keyboard.keycode) {
 
			case G0_LEWO: 
			case G0_PRAWO:
				params->gracze[0] = !params->gracze[0];
				break;

			case G1_LEWO: 
			case G1_PRAWO:
				params->gracze[1] = !params->gracze[1];
				break;

			case G2_LEWO: 
			case G2_PRAWO:
				params->gracze[2] = !params->gracze[2];
				break;
			case ALLEGRO_KEY_ENTER:
				{
					int n=0;
					for (int i=0; i<4; i++)
						if (params->gracze[i]) n++;
					if (n>1) doexit = true;
					break;
				}
			case ALLEGRO_KEY_ESCAPE:
				stan=-1;
				doexit=true;
				break;
			}
		}
		//sprawdzenie pnacisniec klawiszy myszy:
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			switch(ev.mouse.button){
				case 1:
				case 2:
					params->gracze[3] = !params->gracze[3];
					break;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			//rysowanie obrazu
			rysuj_wybierz_graczy(display, font, params);
		}
	}

	//usuwanie stworzonych obiekt�w:
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return stan;
}

int wyniki(ALLEGRO_DISPLAY *display, parametry *params)
{
	//utworzenie fontu:
	ALLEGRO_FONT		*font		 = al_load_ttf_font(FONT,72,0 );

	rysuj_wyniki(display, font, params);

	al_rest(0.2);
	//oczekiwanie na naci�ni�cie klawisza ENTER albo SPACJI, lub ESC, sprawdzaj�c klawiatur� co 1/FPS sekundy
	ALLEGRO_KEYBOARD_STATE stat;
	do {
		al_rest(1.0/FPS);
		al_get_keyboard_state(&stat);
		if (al_key_down(&stat, ALLEGRO_KEY_ESCAPE)) return -1;
	}  while (!al_key_down(&stat, ALLEGRO_KEY_ENTER)&&!al_key_down(&stat, ALLEGRO_KEY_SPACE));
	return 0;	
}

int wstep(ALLEGRO_DISPLAY *display, parametry *params)
{
	//zmienne logiczne u�ywane do obs�ugi zdarze� i g��wnej p�tli:
	bool redraw = true;
	bool doexit = false;	

	//zmienne sterujace stanem funkcji
	int stan	= 0;
	int pozycja = 0;

	//ustalenie parametrow na domyslne, je�li jeszcze nie zosta�y ustawione:
	if (params->promien==-1)		params->promien			= d_promien;
	if (params->velocity==-1)		params->velocity		= d_velocity;
	if (params->ang_velocity==-1)	params->ang_velocity	= d_ang_velocity;
	if (params->wygrana==-1)		params->wygrana			= d_wygrana;
	if (params->przerwy==-1)		params->przerwy			= d_przerwy;
	if (params->odleglosc==-1)		params->odleglosc		= d_odleglosc;
	
	//tworzenie kolejki zdarze� oraz timera zapewniaj�cego odpowiedni� cz�stotliwo�� wy�wietlania:
	ALLEGRO_TIMER       *timer		 = al_create_timer(1.0 / FPS);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_FONT		*font		 = al_load_ttf_font(FONT,32,0 );

	//obs�uga t�a menu
	ALLEGRO_BITMAP *background	= NULL;
	background = al_load_bitmap("menu.png");

	//podpi�cie do kolejki zdarze� zwi�zanych z klawatur�, timerem i displayem:
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));	
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	//inicjalizacja timera:
	al_start_timer(timer);

	while(!doexit)
	{
		//przechwycenie zdarzenia:
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		
		//obs�uga timera
		if(ev.type == ALLEGRO_EVENT_TIMER) 
			redraw = true;

		//obs�uga ��dania wy��czenia programu:
		if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			stan = -1;
			doexit = true;
		}
		//sprawdzanie nacisniec klawiszy:
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			bool pom=true;
			switch(ev.keyboard.keycode) {
			
			//zmiana parametr�w rozgrywki klawiszami LEWO i PRAWO
			case ALLEGRO_KEY_LEFT: 
				pom=false;
			case ALLEGRO_KEY_RIGHT:
				{
					switch(pozycja) {
					case 2: 
						if (pom) params->promien+=1;
						else if (params->promien>1) params->promien--;
						break;
					case 3:
						if (pom) params->velocity+=0.5;
						else if ((params->velocity)>0.5) params->velocity-=0.5;
						break;
					case 4:
						if (pom) params->ang_velocity+=0.5;
						else if (params->ang_velocity>0.5) params->ang_velocity-=0.5;
						break;
					case 5:
						if (pom) params->wygrana++;
						else if (params->wygrana>1) params->wygrana--;
						break;
					case 6:
						if (pom) params->przerwy++;
						else if (params->przerwy>0) params->przerwy--;
						break;
					case 7:
						if (pom) params->odleglosc++;
						else if (params->odleglosc>1) params->odleglosc--;
						break;
					}
				}
				break;

			//
			case ALLEGRO_KEY_UP:
				if (pozycja>0) pozycja--;
				else pozycja = 7;
				break;
			case ALLEGRO_KEY_DOWN:
				if (pozycja<7) pozycja++;
				else pozycja = 0;
				break;
			case ALLEGRO_KEY_ENTER:
				if (pozycja==0) doexit = true;
				if (pozycja==1) {
					stan = -1;
					doexit = true;
				}
				break;
			case ALLEGRO_KEY_ESCAPE:
				stan =-1;
				doexit = true;
			}
		}
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;	
			rysuj_wstep(display, font, params, background, pozycja);
		}
	}

	//usuwanie stworzonych obiekt�w:
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_bitmap(background);
	
	return stan;
}

ALLEGRO_DISPLAY *initialize(void)
{		
	ALLEGRO_DISPLAY *display = NULL;

	//inicjalizacja wszystkich potrzebnych modu��w
	al_init();						
	al_init_image_addon();			
	al_init_primitives_addon();		
	al_install_keyboard();			
	al_install_mouse();					
	al_init_font_addon();			
	al_init_ttf_addon();

	//pr�ba otwarcia pliku w trybie odczytu
	FILE *plik = NULL;
	plik = fopen("tron.conf", "r");

	if (plik==NULL)
	{
		//�adowanie domy�lnych ustawie� i tworzenie pliku w wypadku niepowodzenia
		al_set_new_display_flags(WYSW_TRYB);
		display = al_create_display(WYSW_X, WYSW_Y);
		plik = fopen("tron.conf", "w");
		fprintf(plik, "%d\n%d\n%s", WYSW_X, WYSW_Y, WYSW_TRYB==ALLEGRO_WINDOWED?"WINDOWED":"FULLSCREEN");
		fclose(plik);
	}
	else
	{
		//�adowanie ustawie� z pliku
		int x, y;
		char tryb[20];
		fscanf(plik, "%d%d%s", &x, &y, tryb);
		fclose(plik);
		if (tryb[0]=='F'||tryb[0]=='f') al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		else al_set_new_display_flags(ALLEGRO_WINDOWED);
		display = al_create_display(x, y);
	}
	
	//ukrywanie kursora myszy
	al_hide_mouse_cursor(display);

	return display;
}
