#include <allegro5/allegro.h>

//klawisze używane przez graczy (gracz 3 zawsze używa myszki) i ich opisowe nazwy:
#define G0_LEWO		ALLEGRO_KEY_LEFT
#define G0_LEWO_T   "Lewo"
#define G0_PRAWO	ALLEGRO_KEY_RIGHT
#define G0_PRAWO_T  "Prawo"
#define G1_LEWO		ALLEGRO_KEY_Z
#define G1_LEWO_T   "Z"
#define G1_PRAWO	ALLEGRO_KEY_X
#define G1_PRAWO_T  "X"
#define G2_LEWO		ALLEGRO_KEY_FULLSTOP
#define G2_LEWO_T	"."
#define G2_PRAWO	ALLEGRO_KEY_SLASH
#define G2_PRAWO_T	"/"

//font używany do wypisywania
#define FONT		"calibrib.ttf"

//domyslne tryb wyświetlania i rozdzielczość:
#define WYSW_TRYB		ALLEGRO_WINDOWED
#define WYSW_X			1024
#define WYSW_Y			768

/*
	Parametry:
	promien		 - grubość pojazdu graczy i jego śladu
	velocity	 - prędkość pojazdu, wyrażona w pikselach na klatkę
	ang_velocity - prędkość obrotu pojazdu, wyrażona w stopniach na klatkę
	gracze		 - wskaźnik na tablicę logiczną graczy biorących udział w grze. G0-G2 używają klawiszy zdefiniowanych na górze, g3 używa myszki
	punkty		 - wskaźnik na tablicę punktów graczy, modyfikowaną w zależności od przebiegu gry
	przerwy		 - czy mają powstawać przerwy w śladzie?
	odleglosc	 - odleglosc pomiedzy kolejnymi przerwami w sladzie
	wygrana		 - ilość punkjtów to wygranej
*/
typedef struct parametry {
	float promien;
	float velocity;
	float ang_velocity;
	int przerwy;
	int odleglosc;
	int wygrana;
	bool gracze[4];
	int punkty[4];
} parametry;


/*  gra()
	Główna funkcja obsługująca całą rozgrywkę, zwraca:
	-1:  Zakończono grę przedwcześnie (przez naciśnięcie ESC)
	0:   Pomyślne zakończenie gry
*/
int gra(ALLEGRO_DISPLAY *display, parametry *params);

/*  ustal_graczy()
	Funkcja wyświetlająca zdefinowane na górze klawisze przypisane graczom i ustalająca, którzy gracze mają wziąść udział w grzezwraca:
	-1:  Nacisnieto ESC
	0:   Nacisnieto ENTER lub SPACE 
*/
int ustal_graczy(ALLEGRO_DISPLAY *display, parametry *params);

/*  wyniki()
	Funkcja wyświetlająca aktualne wyniki, zwraca:
	-1:  Nacisnieto ESC
	0:   Nacisnieto ENTER lub SPACE 
*/
int wyniki(ALLEGRO_DISPLAY *display, parametry *params);

/*  wstep()
	Funkcja wyświetlająca i obslugujaca ekran poczatkowy, zwraca:
	-1:  Wybrano opcję zakończenia
	0:   Wybrano opcje rozpoczecia gry
*/
int wstep(ALLEGRO_DISPLAY *display, parametry *params);

/*  initialize()
	Funkcja inicjalizuje wszystkie potrzebne moduły i zwraca wskaźnik na utworzony display
*/
ALLEGRO_DISPLAY *initialize(void); 
