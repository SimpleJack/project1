#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>

int main()                  // "int main() {" bedeutet, dass ich eine Funktion starte und alles in ihr auch dazu gehört.
{
    int i, j, k;            // Hier rufe ich das erste mal die Variablen i, j und k auf. Ich sage praktisch nur, dass sie demnächst verwendet werden. int steht für integral und ist die Variablenart
    
	i = 0x00;               // Nun weise ich den Vaiablen einen Wert zu.
	j = 0x00;               // In diesem Fall ist es jedes mal der Hexadecimalwert
	k = 0x00;               // für 0. i, j und k sind jetzt alle null.

    
	do {                    // An dieser stelle mache ich eine Schleife, in der alles passiert, was zwischen den { } eingeklammert ist.
                            // Dies passiert solange die Bedingung erfüllt wird, die ich am Ende der Schleife angebe. Nämlich in Zeile 95.
		do {                    // In der ersten Schleife starte ich eine zweite Schleife
                                // Und darin...
			do {                    // ... starte ich noch eine Schleife.
                                    // Diese drei Schleifen brauche ich, weil ich alle möglichen Werte der hinteren 3 Abschnitte der mac Adresse ersellen will.
                                    // Also fängt es mit 00:00:00 an und endet mit ff:ff:ff.
                                    // In jeder Schleife erhöhe ich einen Abschnitt um 1 (++)
                                    // i ist für den ersten Abschnitt zuständig. das ganze läuft so ab, dass die erste Schlefe startet und so lange läuft, wie i kleiner oder gleich 0xFF (was in decimal 255 ist) ist.
                                    // Das bedeutet, dass bei ii:jj:kk i von 0x00 bis 0xFF laufen kann, sprich alle möglichen Werte einmal vorkommen.
                                    // Bevor die erste Schleife aber überhaupt einmal rum ist, muss noch die zweite Schleife gelaufe sein und darn voher noch die dritte Schleife.
                                    // Das kann man sich vorstellen, wie bei einem Zahlenschloss, bei dem man jede möglichkeit ausprobieren möchte.
                                    // Man steht bei 0 0 0 0 und dreht das rechte Rad. 0 0 0 1, 0 0 0 2, 0 0 0 3 usw. Wenn man bei 0 0 1 0 angekommen ist, hat man das rechte Rad schon einmal komplett
                                    // herumgedreht. Und wenn man bei 0 1 0 0 ist, hat man es schon zehn mal rum drehen müssen und das zweite Rad von rechts musste man einmal komplett von 0 bis 9 drehen und einen weiter.
                                    // Genau so ist es auch hier, man muss k schon einmal komplett herumgedreht haben, bevor man j um einen erhöhen kann.
                                    // In zeile 52 wird k nachdem es einmal komplett durchgelaufen ist wieder auf null gesetzt, damit man neu anfangen kann. Ansonsten würde beim Zahlenschloss
                                    // nach 0 0 0 9 die zahl 0 0 0 10 kommen.
                
                
                    {
                    
                    
                    unsigned  int mac_4, mac_5, mac_6;
                    
                    mac_4 = i;
                    mac_5 = j;
                    mac_6 = k;
                    
                        printf(mac_4 ":" mac_5 ":" mac_6)       // Hier werden jedes mal wenn die dritte Schleife einmal durchgelaufen ist alle Werte ausgegeben.
                    
                    };
                
                k++;                    // k einfach um einen erhöhen. aus 0x00 wird 0x01.
                
            } while(k <= 0xFF);         // while sagt hier, dass die Schleife nur solange läuft, wie die Bedingung erfüllt ist, nämlich dass k kleiner oder gleich 0xFF ist. ist dies nicht mehr erfüllt,
                                        // zum Beispiel wenn k 0x1FF ist.
            
            j++;
            k = 0x00;
            
        } while(j <= 0xFF);
        
        i++;
        j = 0x00;
        
    } while(i <= 0xFF);
    
    
    
    return 0;           // das programm wird einfach nur beendet und gibt aus, dass es ohne Fehler abgelaufen ist. würde es 1 ausgeben, bedeutete das fehler.
}
