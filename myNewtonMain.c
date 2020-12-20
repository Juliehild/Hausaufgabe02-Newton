//Mein main-Code zu der zweiten Hausaufgabe des Newton Algorithmus
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "myNewton.h"

int main() {
	//Pointer auf die jeweiligen Funktionen 
	void (*ptrAnalytisch) (void) = &analytsich;
	void (*ptrNummerisch) (void) = &nummerisch;
	int eingabe = 0;
	printf("---Das Newton Programm---\n");
	//Menüauswahl mit Hilfe der Eingabe
	while (eingabe < 5) {
		printf("------------------------------------------------\n");
		printf("Was moechten Sie machen?\n");
		printf("1) Die hinterlegte Funktion ausgeben\n");
		printf("2) Eine analytische Berechnung der Nullstellen\n");
        printf("3) Eine nummerische Berechnung der Nullstellen\n");
		printf("4) Das Programm beenden\n");
		printf("------------------------------------------------\n");
		scanf("%d", &eingabe);
			switch (eingabe) {
			case 1: //Aufruf der Funktion: funktionsvorschrift
				printf("Die momentan hinterlegte Funktion, mit welcher Sie rechnen, lautet:\n");
    			printf("f(x) = (x - 3)^2\n");
				printf("\n");
				break;
			case 2: //Aufruf der Funktion: analytisch
				(*ptrAnalytisch)();
				printf("\n");
				break;
			case 3: //Aufruf der Funktion: numerisch
				(*ptrNummerisch)();
				printf("\n");
				break;
			case 4:
				return 0;
			default:
				printf("Bitte geben Sie 1, 2, 3 oder 4 ein\n");
				printf("\n");
				break;
		}
	}
	return 0;
}