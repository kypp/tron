#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "logika.h"

int main()
{
	//inicjalizacja grafiki:
	ALLEGRO_DISPLAY	*display = initialize();
	
	//parametry rozgrywki
	parametry params = {-1, -1, -1, -1, -1, -1, {false, false, false, false} };
	
	//maksymalne punkty gracza
	int max;

	//g³ówna pêtla obs³uguj¹ca ca³y program:
	while (wstep(display, &params)==0)
	{
		for (int i=0; i<4; i++)
			params.punkty[i] = 0;
		max = 0;
		if (ustal_graczy(display, &params)==0)
			do {			
				if (gra(display, &params)==-1) break;
				if (wyniki(display, &params)==-1) break;
				for (int i=0; i<4; i++)
					if (params.punkty[i]>max) max = params.punkty[i];
			} while (max < params.wygrana);
	}	
	
	al_destroy_display(display);	
	return 0;
}