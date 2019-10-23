//
//  main.cpp
//  TLUMACZ
//
//  Created by Jagoda Chmielewska on 13/01/2019.
//  Copyright © 2019 Jagoda Chmielewska. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include "funkcje.hpp"


using namespace std;


int main(int argc, char **argv)//argc i argv daja dostep do argumentow z linii komend
{
    konfiguracja konfig;
    wypelnij_konfiguracje(argc, argv, konfig);
    slownik *slow=nullptr;
    wczytaj_plik(slow, konfig.plikslownika);
    fstream plik_przetlumaczony;
    fstream plik_oryginalny;
    plik_przetlumaczony.open(konfig.plikprzetlumaczony, ios::out);//do zapisu
    plik_oryginalny.open(konfig.plikoryginalny, ios::in);//do odczytu
    przetlumacz_slowo_po_slowie(plik_oryginalny, plik_przetlumaczony, slow, konfig.kierunek);
    plik_oryginalny.close();
    plik_przetlumaczony.close();
    usunDrzewo(slow);
    return 0;
};
