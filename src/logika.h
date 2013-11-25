#include <allegro5/allegro.h>

//klawisze u¿ywane przez graczy (gracz 3 zawsze u¿ywa myszki) i ich opisowe nazwy:
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

//font u¿ywany do wypisywania
#define FONT		"calibrib.ttf"

//domyslne tryb wyœwietlania i rozdzielczoœæ:
#define WYSW_TRYB		ALLEGRO_WINDOWED
#define WYSW_X			1024
#define WYSW_Y			768

/*
	Parametry:
	promien		 - gruboœæ pojazdu graczy i jego œladu
	velocity	 - prêdkoœæ pojazdu, wyra¿ona w pikselach na klatkê
	ang_velocity - prêdkoœæ obrotu pojazdu, wyra¿ona w stopniach na klatkê
	gracze		 - wskaŸnik na tablicê logiczn¹ graczy bior¹cych udzia³ w grze. G0-G2 u¿ywaj¹ klawiszy zdefiniowanych na górze, g3 u¿ywa myszki
	punkty		 - wskaŸnik na tablicê punktów graczy, modyfikowan¹ w zale¿noœci od przebiegu gry
	przerwy		 - czy maj¹ powstawaæ przerwy w œladzie?
	odleglosc	 - odleglosc pomiedzy kolejnymi przerwami w sladzie
	wygrana		 - iloœæ punkjtów to wygranej
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
	G³ówna funkcja obs³uguj¹ca ca³¹ rozgrywkê, zwraca:
	-1:  Zakoñczono grê przedwczeœnie (przez naciœniêcie ESC)
	0:   Pomyœlne zakoñczenie gry
*/
int gra(ALLEGRO_DISPLAY *display, parametry *params);

/*  ustal_graczy()
	Funkcja wyœwietlaj¹ca zdefinowane na górze klawisze przypisane graczom i ustalaj¹ca, którzy gracze maj¹ wzi¹œæ udzia³ w grzezwraca:
	-1:  Nacisnieto ESC
	0:   Nacisnieto ENTER lub SPACE 
*/
int ustal_graczy(ALLEGRO_DISPLAY *display, parametry *params);

/*  wyniki()
	Funkcja wyœwietlaj¹ca aktualne wyniki, zwraca:
	-1:  Nacisnieto ESC
	0:   Nacisnieto ENTER lub SPACE 
*/
int wyniki(ALLEGRO_DISPLAY *display, parametry *params);

/*  wstep()
	Funkcja wyœwietlaj¹ca i obslugujaca ekran poczatkowy, zwraca:
	-1:  Wybrano opcjê zakoñczenia
	0:   Wybrano opcje rozpoczecia gry
*/
int wstep(ALLEGRO_DISPLAY *display, parametry *params);

/*  initialize()
	Funkcja inicjalizuje wszystkie potrzebne modu³y i zwraca wskaŸnik na utworzony display
*/
ALLEGRO_DISPLAY *initialize(void); 
