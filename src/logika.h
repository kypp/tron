#include <allegro5/allegro.h>

//klawisze u�ywane przez graczy (gracz 3 zawsze u�ywa myszki) i ich opisowe nazwy:
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

//font u�ywany do wypisywania
#define FONT		"calibrib.ttf"

//domyslne tryb wy�wietlania i rozdzielczo��:
#define WYSW_TRYB		ALLEGRO_WINDOWED
#define WYSW_X			1024
#define WYSW_Y			768

/*
	Parametry:
	promien		 - grubo�� pojazdu graczy i jego �ladu
	velocity	 - pr�dko�� pojazdu, wyra�ona w pikselach na klatk�
	ang_velocity - pr�dko�� obrotu pojazdu, wyra�ona w stopniach na klatk�
	gracze		 - wska�nik na tablic� logiczn� graczy bior�cych udzia� w grze. G0-G2 u�ywaj� klawiszy zdefiniowanych na g�rze, g3 u�ywa myszki
	punkty		 - wska�nik na tablic� punkt�w graczy, modyfikowan� w zale�no�ci od przebiegu gry
	przerwy		 - czy maj� powstawa� przerwy w �ladzie?
	odleglosc	 - odleglosc pomiedzy kolejnymi przerwami w sladzie
	wygrana		 - ilo�� punkjt�w to wygranej
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
	G��wna funkcja obs�uguj�ca ca�� rozgrywk�, zwraca:
	-1:  Zako�czono gr� przedwcze�nie (przez naci�ni�cie ESC)
	0:   Pomy�lne zako�czenie gry
*/
int gra(ALLEGRO_DISPLAY *display, parametry *params);

/*  ustal_graczy()
	Funkcja wy�wietlaj�ca zdefinowane na g�rze klawisze przypisane graczom i ustalaj�ca, kt�rzy gracze maj� wzi��� udzia� w grzezwraca:
	-1:  Nacisnieto ESC
	0:   Nacisnieto ENTER lub SPACE 
*/
int ustal_graczy(ALLEGRO_DISPLAY *display, parametry *params);

/*  wyniki()
	Funkcja wy�wietlaj�ca aktualne wyniki, zwraca:
	-1:  Nacisnieto ESC
	0:   Nacisnieto ENTER lub SPACE 
*/
int wyniki(ALLEGRO_DISPLAY *display, parametry *params);

/*  wstep()
	Funkcja wy�wietlaj�ca i obslugujaca ekran poczatkowy, zwraca:
	-1:  Wybrano opcj� zako�czenia
	0:   Wybrano opcje rozpoczecia gry
*/
int wstep(ALLEGRO_DISPLAY *display, parametry *params);

/*  initialize()
	Funkcja inicjalizuje wszystkie potrzebne modu�y i zwraca wska�nik na utworzony display
*/
ALLEGRO_DISPLAY *initialize(void); 
