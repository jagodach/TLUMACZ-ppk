//
//  funkcje.cpp
//  TLUMACZ
//
//  Created by Jagoda Chmielewska on 13/01/2019.
//  Copyright © 2019 Jagoda Chmielewska. All rights reserved.

#include "funkcje.hpp"
#include <iostream>
#include <string.h>
#include <vector>
#include <cstdio>
#include <fstream>
#include <stdlib.h>

using namespace std;

void wypelnij_konfiguracje(int argc, char **argv, konfiguracja &konfig) {
    for (int i = 1; i < argc-1; i++){//argc-1 zeby kolejnosc wpisywania przelacznikow nie byla wazna
        if (strcmp(argv[i], "") == 0) {//strcmp porownuje dwa lancuchy znakow
            cout<< "Pusty parametr, przechodzimy dalej..."<< endl;
            continue;
            
        } else if (strcmp(argv[i], "-s") == 0){//strcmp porownanie dwoch lancuchow znakow
            i++;
            konfig.plikslownika = argv[i];
            
        } else if (strcmp(argv[i], "-i") == 0){
            i++;
            konfig.plikoryginalny = argv[i];
            
        } else if (strcmp(argv[i], "-o") == 0){
            i++;
            konfig.plikprzetlumaczony = argv[i];
            
        } else if (strcmp(argv[i], "-k") == 0){
            i++;
            konfig.kierunek = argv[i];
            
        } else {
            cout<< "Nieznany argument" << argv[i];
            break;
        };
    };
};

void dodaj(slownik * &pKorzen, slownik * nowy_wezel)
{
    if (pKorzen == nullptr) { // drzewo puste
        pKorzen = nowy_wezel;
        return;
    };
    
    // w drzewie juz cos jest
    
    // wskaźnik na nowy węzeł należy dodać dwa razy:
    // dla drzewa polskich wyrazów i dla drzewa angielskich wyrazów
    slownik * wezel_pol = pKorzen;
    slownik * wezel_ang = pKorzen;
    
    // dodawanie w drzewie polskich wyrazów
    while(wezel_pol){
        if (nowy_wezel->slowo < wezel_pol->slowo){
            
            // idziemy w lewo drzewa polskich wyrazów
            if (wezel_pol->lewypol == nullptr){
                // w lewej czesci drzewa jeszcze nic nie ma
                // Wsadzamy nowy_wezel do drzewa polskich wyrazow
                wezel_pol->lewypol = nowy_wezel;
                break;
            } else {
                // w lewej czesci drzewa juz jest wezel, przenosimy sie na niego
                wezel_pol = wezel_pol->lewypol;
                continue;
            };
        } else if (nowy_wezel->slowo > wezel_pol->slowo){
            
            // idziemy w prawo drzewa polskich wyrazów
            if (wezel_pol->prawypol == nullptr){
                // w prawej czesci drzewa jeszcze nic nie ma
                // wsadzamy nowy_wezel do drzewa
                wezel_pol->prawypol = nowy_wezel;
                break;
            }
            else {
                // w prawej czesci drzewa juz jest wezel, przenosimy sie na niego
                wezel_pol = wezel_pol->prawypol;
                continue;
            };
            
        } else {
            cout << " Wystąpił błąd " << endl;
            break;
        }
    }
    
    // dodawanie w drzewie angielskich wyrazów
    while(wezel_ang){
        
        if (nowy_wezel->tlumaczenie < wezel_ang->tlumaczenie){
            
            if (wezel_ang->lewyang == nullptr){
                wezel_ang->lewyang = nowy_wezel;
                break;
            } else {
                // w lewej czesci drzewa juz jest wezel, przenosimy sie  na niego
                wezel_ang = wezel_ang->lewyang;
                continue;
            };
            
        } else if (nowy_wezel->tlumaczenie > wezel_ang->tlumaczenie){
            
            if (wezel_ang->prawyang == nullptr){
                wezel_ang->prawyang = nowy_wezel;
                break;
            } else {
                wezel_ang = wezel_ang->prawyang;
                continue;
            }
        } else {
            cout << " Wystąpił błąd " << endl;
            break;
        }
    }
    
}

void wczytaj_plik(slownik * &pKorzen, const string nazwa_pliku)
{
    fstream plik;
    plik.open(nazwa_pliku, ios::in);//otwarcie pliku do odczytu
    while( plik.good() == true )//jesli plik istnieje i jest poprawny
    {
        string slowo;
        string tlumaczenie;
        plik >> slowo >> tlumaczenie;
        
        if (slowo.empty() || tlumaczenie.empty()){
            // jeśli w słowniku znajdzie się pusta linia, przerwać wczytywanie
            break;
        } else {
            slownik * nowy_wezel = new slownik { slowo, tlumaczenie, nullptr, nullptr, nullptr, nullptr };
            dodaj(pKorzen, nowy_wezel);
        }
    }
    plik.close();
}


void usunDrzewo (slownik *&pKorzen)//usuwa drzewo
{
    if (pKorzen)
    {
        usunDrzewo(pKorzen->lewypol);//wystarczy usuniecie dla pol poniewaz ang jest doczepiony do pol
        usunDrzewo(pKorzen->prawypol);
        
        delete pKorzen;
        pKorzen = nullptr;
    }
}

void wyswietl(slownik *pKorzen) {// wyswietla caly slownik
    
    if (pKorzen == nullptr) {
        cout << "Nie udalo sie wczytac slownika!" << endl;
    }
    
    cout << pKorzen->slowo << " " << pKorzen->tlumaczenie << endl;
    if (pKorzen->lewypol != nullptr) {// do wypisania wystarczy przejście po węzłach tylko według jednego jezyka (i tak przejdzie się po wszystkich).
        wyswietl(pKorzen->lewypol);
    }
    if(pKorzen->prawypol != nullptr){
        wyswietl(pKorzen->prawypol);
    }
}


string przetlumaczpl(slownik *pKorzen, const string &podane)
// zwraca tlumaczenie lub oryginalne slowo w [], jesli nie znaleziono tlumaczenia
{
    if (pKorzen == nullptr) {
        cout << "Nie udalo sie wczytac slownika!" << endl;
    }
    
    while (true)
    {// petla porownuje dwa slowa czy sa takie same zeby sprawdzic czy po lewej czy prawej jest podane slowo
        
        if (pKorzen->slowo < podane) {
            // szukaj prawo
            
            if (pKorzen->prawypol == nullptr){//jesli nie ma danego slowa w slowniku 
                return "[" + podane + "]";
            } else {
                pKorzen = pKorzen->prawypol;
                continue;
            }
            
        } else if (pKorzen->slowo > podane){
            
            if (pKorzen->lewypol == nullptr){
                return "[" + podane + "]";
            } else {
                pKorzen = pKorzen->lewypol;
                continue;
            }
            
        } else {
            return pKorzen->tlumaczenie;
            break;
        }
        
    }
}

string przetlumaczang(slownik *pKorzen, const string &podane)
// zwraca tlumaczenie lub oryginalne slowo w [], jesli nie znaleziono tlumaczenia
{
    if (pKorzen == nullptr) {
        cout << "!!! Slownik nie zostal wczytany !!!" << endl;
    }
    
 while(true)
    {// petla porownuje dwa slowa czy sa takie same zeby sprawdzic czy po lewej czy prawej jest podane slowo
        
        if (pKorzen->tlumaczenie < podane) {
            // szukaj prawo
            
            if (pKorzen->prawyang == nullptr){
                return "[" + podane + "]";
            } else {
                pKorzen = pKorzen->prawyang;
                continue;
            }
            
        } else if (pKorzen->tlumaczenie > podane){
            
            if (pKorzen->lewyang == nullptr){
                return "[" + podane + "]";
            } else {
                pKorzen = pKorzen->lewyang;
                continue;
            }
            
        } else {
            return pKorzen->slowo;
            break;
        }
        
    }
}


string przetlumacz_slowo(slownik *pKorzen, string slowo, const string kierunek)
{
    if (kierunek == "enpl"){
        return przetlumaczang(pKorzen, slowo);
        
    } else if (kierunek== "plen") {
        return przetlumaczpl(pKorzen, slowo);
        
    }
    return 0;
}


void przetlumacz_slowo_po_slowie(fstream &plik_oryginalny, fstream &plik_z_tlumaczeniem, slownik *slow, string kierunek)
{
    // tlumaczy slowo po slowie z pliku.
    //Jeśli napotka biały znak lub interpunkcję zamiast kolejnej litery słowa,
    //tłumaczy słowo z dotychczas zebranych liter i wpisuje je do pliku z tlumaczeniem, po czym wpisuje równieź interpunkcję.
    
    char slowo[256];// bo dlugosc linii nie przekracza 256 znakow
    int rozmiar_slowa = 0;
    char znak;
    
    while (plik_oryginalny.good()) {
        znak = plik_oryginalny.get();//.get() odczytuje z pliku znak po znaku(takze spacje, znaki nowego wiersza itp)
        
        if (isalpha(znak)){//Sprawdza czy znak przekazany jako argument jest literą alfabetu
            slowo[rozmiar_slowa] = znak;
            rozmiar_slowa++;
        } else {
            if (rozmiar_slowa != 0) {
                slowo[rozmiar_slowa] = NULL;
                plik_z_tlumaczeniem << przetlumacz_slowo(slow, slowo, kierunek);//wpisuje do pliku z tlumaczeniem
                rozmiar_slowa = 0;
            }// napotkalismy "znak" nie-literę, wiec zeby zachowac interpunkcje nalezy ja przepisac
            plik_z_tlumaczeniem << znak;
        }
    }
}
//wycieki cmd + I
