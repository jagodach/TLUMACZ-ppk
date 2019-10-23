//
//  funkcje.hpp
//  TLUMACZ
//
//  Created by Jagoda Chmielewska on 13/01/2019.
//  Copyright © 2019 Jagoda Chmielewska. All rights reserved.
//

#ifndef funkcje_hpp
#define funkcje_hpp

#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;

/** węzeł drzewa poszukiwań binarnych */
struct slownik {
    string slowo; // słowo polskie
    string tlumaczenie; // słowo angielskie
    slownik *lewyang;// wskaźnik na lewy potomek angielski
    slownik *prawyang;//wskaźnik na prawy potomek angielski
    slownik *lewypol;//wskaźnik na lewy potomek polski
    slownik *prawypol;// wskaźnik na prawy potomek polski
}; // średnik jest niezbędny


/** struktura przechowujaca argumenty z linii poleceń */
struct konfiguracja {
    string kierunek; // kierunek tłumaczenia
    string plikoryginalny; // plik z tekstem do przetłumaczenia
    string plikprzetlumaczony;// plik z przetłumaczonym tekstem
    string plikslownika;// plik ze słownikiem
};

/** Funkcja wypełnia konfigurację wiersza poleceń.
 @param argc liczba argumentów.
 @param argv wektor argumentu.
 @param konfig skonfiguruj
 */
void wypelnij_konfiguracje(int argc, char **argv, konfiguracja &konfig) ;

/** Funkcja dodaje do drzewa poszukiwań binarnych podane wartości.
 @param pKorzen korzeń drzewa
 @param nowy_wezel nowy węzeł drzewa binarnego
 */
void dodaj(slownik * &pKorzen, slownik * nowy_wezel);

/** Funkcja wczytuje plik słownika
 @param pKorzen korzeń drzewa
 @param nazwa_pliku nazwa pliku do wczytania
 */
void wczytaj_plik(slownik * &pKorzen, const string nazwa_pliku);

/** Funkcja usuwa drzewo z pamięci
 @param pKorzen korzeń drzewa do usunięcia, po usunięciu ma wartość nullptr.
 */
void usunDrzewo (slownik * & pKorzen);

/** Funkcja wypisuje cały słownik.
 @param pKorzen korzeń drzewa do wyświetlenia.
 */
void wyswietl(slownik *pKorzen);

/** Funkcja wyszukuje element o podanej wartości podane w drzewie o podanym korzeniu i tłumaczy go na język polski.
 @param pKorzen korzeń drzewa
 @param podane wartość do wyszukania
 @return Funkcja zwraca przetłumaczone słowo lub słowo oryginalne w []
 */
string przetlumaczpl(slownik *pKorzen, const string &podane);

/** Funkcja wyszukuje element o podanej wartości podaneang w drzewie o podanym korzeniu i tłumaczy go na język angielski.
 @param pKorzen korzeń drzewa
 @param podane wartość do wyszukania
 @return Funkcja zwraca przetłumaczone słowo lub słowo oryginalne w []
 */
string przetlumaczang(slownik *pKorzen, const string &podane);


/** Funkcja tłumaczy słowo
 @param pKorzen korzeń drzewa
 @param slowo słowo do przetłumaczenia
 @param kierunek kierunek w jakim tłumaczymy (enpl lub plen)
 @return Funkcja zwraca tłumaczenie słowa
 */
string przetlumacz_slowo(slownik *pKorzen, string slowo, const string kierunek);


/** Funkcja tłumaczy słowo po słowie dany plik i zapisuje tłumaczenie do drugiego
  @param plik_oryginalny wskaźnik na plik z tekstem do przetłumaczenia
  @param plik_z_tlumaczeniem wskaźnik na plik do zapisania tłumaczenia
  @param slow słownik
  @param kierunek kierunek tłumaczenia
 */
void przetlumacz_slowo_po_slowie(fstream &plik_oryginalny, fstream &plik_z_tlumaczeniem, slownik *slow, string kierunek);

#endif /* funkcje_hpp */
