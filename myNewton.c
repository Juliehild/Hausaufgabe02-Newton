#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "myNewton.h"


// Funktion f(x) = (x−3)^2 -> (x - 3) * (x - 3) 
double funktion(double x) { 
    double y;
    //Berechnung der Funktion mit dem übergebenen x-Wert
    y = (x-3) * (x-3);                                         
    return y; 
} 

// analytische Ableitung der Funktion f'(x) = 2(x-3) 
double funktionsAbleitung(double x) {   
    double y;
    //Berechnung der analytischen Ableitung mit dem übergebenen x-Wert
    y = 2*(x-3);                                                
    return y; 
} 

// numerische Ableitung der Funktion f'(x) = 2(x-3) -> f'(x) = f(x+h)-f(x)/h  
double numAbleitung(double (*function) (double), double x) {  
    double h = 0.00000001;
    double y;
    //Berechnung der numerischen Ableitung
    y = ( (*function) (x+h) - (*function)(x) ) / h;
    return y; 
} 

//Berechnung der Nullstelle mit Hilfe der anaytischen Ableitung
void analytsich(void){
    int i;
    double ableitung, erg, start, vergleich, x, y;
    double (*ptrFunktion) (double) = &funktion;
	printf("Bitte geben Sie einen Startwert ein: ");
	scanf("%lf", &start);
    x = start;
    //Berechnung des Scnittpunktes der Tangente mit der x-Achse, bis Nullstelle gefunden wird
    for (i = 0; i < 1000; i++) {
        y = funktion(x);
        ableitung = funktionsAbleitung(x);
        //eigentliche Newton-Raphson-Formel
        erg = x - (y/ableitung);   
        //zum vergleich wir x vom neuen ergebnis abgezogen                             
        vergleich = erg - x;
        //dann wird vergeleich mit Hilfe des Integers auf 10 Nachkommastellen gerundet
        vergleich = ((int) (vergleich*100000000000)) / 10000000000.0;
        //falls dann kein Unterschied besteht, also gleich Null ist, so wurde die Nullstelle gefunden
        if (vergleich == 0){                                    
            break;
        }
        //es wird mit dem zweiten ergebnis, also erg, als x im nächsten durchlauf weiter gerechnet
        x = erg;
    }
    y = (*ptrFunktion)(x);
    //Nullstelle auf 8 Nachkommastellen ausgeben
    printf("Die Nullstelle lautet (%.8f/%.8f) \n", x, y); 
    printf("Dazu wurden %lf Iterationen benoetigten\n", i + 1);          
} 

//Berechnung der Nullstelle mit Hilfe der numerischen Ableitung
void nummerisch(void){
    int i;
    double ableitung, erg, start, vergleich, x, y;
    double (*ptrFunktion) (double) = &funktion;
	printf("Bitte geben Sie einen Startwert ein: ");
	scanf("%lf", &start);
    x = start;
    //Berechnung des Scnittpunktes der Tangente mit der x-Achse, bis Nullstelle gefunden wird
    for (i = 0; i < 1000; i++){
        y = funktion(x);
        ableitung = numAbleitung(ptrFunktion,x);
        //eigentliche Newton-Raphson-Formel
        erg = x - (y/ableitung);
        //zum vergleich wir x vom neuen ergebnis abgezogen                                  
        vergleich = erg - x;
        //dann wird vergeleich mit Hilfe des Integers auf 10 Nachkommastellen gerundet
        vergleich = ((int) (vergleich*100000000000)) / 10000000000.0;
        //falls dann kein Unterschied besteht, also gleich Null ist, so wurde die Nullstelle gefunden
        if (vergleich == 0){                                    
            break;
        }
        //es wird mit dem zweiten ergebnis, also erg, als x im nächsten durchlauf weiter gerechnet
        x = erg;
    }
    y = (*ptrFunktion)(x);
    //Nullstelle auf 8 Nachkommastellen und Anzahl der benötigten Iterationen ausgeben
    printf("Die Nullstelle lautet (%.8f/%.8f) \n", x, y);  
    printf("Dazu wurden %lf Iterationen benoetigten\n", i + 1);        
} 