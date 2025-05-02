/*************************************************************************/
/*
* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 04
* Tekijä: Mikael Norppa, Lauri Lehtonen & Jussi Kelloniemi
* Opiskelijanumero: 001867462, 00506083 & 001878639
* Päivämäärä: 27.04.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä: 
* 1. https://www.geeksforgeeks.org/quick-sort-in-c/
* 2. https://www.geeksforgeeks.org/quicksort-for-linked-list/
* 3. https://www.geeksforgeeks.org/merge-sort-for-doubly-linked-list/?ref=lbp
* Käytön tarkoitus: 
* 1. Quicksort C-kielellä
* 2. Quickosrt C-kielellä
* 3. MergeSort C-kielellä
*/
/*************************************************************************/
/* Tehtävä L09, tiedoston nimi ProjektiKirjastoSort.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sort.h"
#include "Kirjasto.h"

void vaihto(SUKUNIMI* a, SUKUNIMI* b) {

    int temp_iMaara = a->iMaara;
    char temp_aSukunimi[40];

    // Määrän vaihto
    a->iMaara = b->iMaara;
    b->iMaara = temp_iMaara;

    // Sukunimien vaihto
    strcpy(temp_aSukunimi, a->aSukunimi);
    strcpy(a->aSukunimi, b->aSukunimi);
    strcpy(b->aSukunimi, temp_aSukunimi);
}

SUKUNIMI* viimeinenSolmu(SUKUNIMI* pA) {
    // Haetaan viimeinen solmu rekursiivisesti
    while (pA != NULL && pA->pSeuraava != NULL) {
        pA = pA->pSeuraava;
    }
    return pA;
}

SUKUNIMI* osio(SUKUNIMI* pA, SUKUNIMI* pV) {

    // Asetetaan viimeinen solmu pivotiksi
    int iPivotMaara = pV->iMaara;
    char aPivotSukunimi[40];
    strcpy(aPivotSukunimi, pV->aSukunimi);

    // Luodaan osoitin ennen listan ensimmäistä elementtiä
    SUKUNIMI* i = pA->pEdellinen;

    // Kuljetaan listaa eteenpäin, jotta voidaan järjestää solmut
    for (SUKUNIMI* j = pA; j != pV; j = j->pSeuraava) {

        // Jos tämänhetkisen solmun määrä on pienempi kuin pivotilla
        if (j->iMaara < iPivotMaara) {
            i = (i == NULL) ? pA : i->pSeuraava;
            vaihto(i, j);
        } else if (j->iMaara == iPivotMaara && strcmp(j->aSukunimi, aPivotSukunimi) <= 0) {
            i = (i == NULL) ? pA : i->pSeuraava;
            vaihto(i, j);
        }
    }

    // Siirretään osoitin oikeaan paikkaan pivottiin verrattuna
    i = (i == NULL) ? pA : i->pSeuraava;
    
    vaihto(i, pV);

    return i;
}


void quickSort(SUKUNIMI* pA, SUKUNIMI* pV) {
    if (pA != NULL && pV != NULL && pA != pV && pA != pV->pSeuraava) {

        SUKUNIMI* pivot = osio(pA, pV);

        quickSort(pA, pivot->pEdellinen);
        quickSort(pivot->pSeuraava, pV);
    }
}

SUKUNIMI* tyhjennaSort(SUKUNIMI* pV) {
    SUKUNIMI *ptr = pV;  // listan tyhjennys
    while (ptr != NULL) {
        pV = ptr->pEdellinen;
        free(ptr);
        ptr = pV;
    }
    return(pV);
}

SUKUNIMI* mergeSort(SUKUNIMI* pA) {
    if(pA == NULL || pA->pSeuraava == NULL) {
        return(pA);
    }
    SUKUNIMI* toinenLista = jaaLista(pA);
    pA = mergeSort(pA);
    toinenLista = mergeSort(toinenLista);
    return(merge(pA, toinenLista));
}


SUKUNIMI* jaaLista(SUKUNIMI* pA){
    SUKUNIMI* pNopea = pA;
    SUKUNIMI* pHidas = pA;

    // Siirretään pointtereita siten, että kun pNopea saavuttaa listan lopun, on pHidas listan puolivälissä
    while (pNopea != NULL && pNopea->pSeuraava != NULL) {
        pNopea = pNopea->pSeuraava->pSeuraava;
        if(pNopea != NULL) {
            pHidas = pHidas->pSeuraava; 
        }
    }
    SUKUNIMI* temp = pHidas->pSeuraava;
    pHidas->pSeuraava = NULL;
    return(temp);
}

SUKUNIMI* merge(SUKUNIMI* ensimmainen, SUKUNIMI* toinen) {
    if(ensimmainen == NULL) return(toinen); // jos toinen listoista on tyhjä palautetaan toinen
    if(toinen == NULL) return(ensimmainen);
    // Tarkistetaan kumpi on suurempi luku ja jos luvut ovat samat järjestetään aakkosjärjestyksessä.
    if(ensimmainen->iMaara > toinen->iMaara || (ensimmainen->iMaara == toinen->iMaara && strcmp(ensimmainen->aSukunimi, toinen->aSukunimi) > 0)) {
        ensimmainen->pSeuraava = merge(ensimmainen->pSeuraava, toinen);
        ensimmainen->pSeuraava->pEdellinen = ensimmainen;
        ensimmainen->pEdellinen = NULL;
        return(ensimmainen);
    } else {
        toinen->pSeuraava = merge(ensimmainen, toinen->pSeuraava);
        toinen->pSeuraava->pEdellinen = toinen;
        toinen->pEdellinen = NULL;
        return(toinen);
    }
}