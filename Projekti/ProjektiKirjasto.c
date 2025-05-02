/*************************************************************************/
/*
* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 04
* Tekijä: Mikael Norppa
* Opiskelijanumero: 001867462
* Päivämäärä: 27.04.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä: 
* 1. https://www.reddit.com/r/C_Programming/comments/m16drz/what_is_a_proper_and_effective_way_to_skip_lines/
* 2. https://stackoverflow.com/questions/39281646/using-delimiters-for-fscanf-in-c
* 3. https://www.geeksforgeeks.org/doubly-linked-list-in-c/, https://www.geeksforgeeks.org/doubly-linked-list/
* Käytön tarkoitus: 
* 1. ProjektiKirjasto.c rivi 71
* 2. ProjektiKirjasto.c rivi 73, käytetty ymmärtämään tiedon erottamiseen fscanf:llä
* 3. Käytetty kaksisuuntaisen listan tekemisen apuna 
*/
/*************************************************************************/
/* Tehtävä L08,L09 tiedoston nimi ProjektiKirjasto.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kirjasto.h"

SUKUNIMI * lisaaSolmu(SUKUNIMI *pA, char *sukunimi, int maara) {

    SUKUNIMI *pUusi = NULL, *ptr = NULL;

    // muistin varaus
    if ((pUusi = (SUKUNIMI*)malloc(sizeof(SUKUNIMI))) == NULL ) {
        perror("Muistin varaus epäonnistui, lopeteaan");
        exit(0);
    }

    // stcpy ottaa sukunimen, iMaara sukunimien määrän

    strcpy(pUusi->aSukunimi, sukunimi);
    pUusi->iMaara = maara;
    pUusi->pSeuraava = NULL;
    pUusi->pEdellinen = NULL;

    // jos lista on tyhjä, aloitetaan heti alusta
    if (pA == NULL) {
        pA = pUusi;
    } else {
        ptr = pA;
        while (ptr->pSeuraava != NULL) {
            ptr = ptr->pSeuraava;
        }

        ptr->pSeuraava = pUusi;
        pUusi->pEdellinen = ptr;
    }
    return (pA);
}

SUKUNIMI * lueTiedosto(SUKUNIMI *pA, char *tiedosto) {
    char tempTiedosto[100];

    if (tiedosto == NULL || tiedosto[0] == '\0') {
        printf("Anna luettavan tiedoston nimi: ");
        scanf("%s", tempTiedosto);
        tiedosto = tempTiedosto;
    }

    char sukunimi[40];
    int maara;
    int i;


    FILE *fp = NULL;
    if ((fp = fopen(tiedosto,"r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    // ohitetaan otsikko
    while (i = fgetc(fp), i != '\n' && i != EOF);
    // tiedot tiedostosta muuttuujiin sukunimi, maara, lisätään linkitettyyn listaan lisaaSolmu aliohjelman kautta
    while (fscanf(fp,"%39[^;,];%d\n", sukunimi, &maara) == 2) {
        pA = lisaaSolmu(pA, sukunimi, maara);
    }

    fclose(fp);
    return (pA);
}



void kirjoitaTiedosto(SUKUNIMI *pA, char *tiedosto, int iValintaLinkitetty) {
    char tempTiedosto[100];

    if (tiedosto == NULL || tiedosto[0] == '\0') {
        printf("Anna luettavan tiedoston nimi: ");
        scanf("%s", tempTiedosto);
        tiedosto = tempTiedosto;
    }

    FILE *fp = NULL;
    if ((fp = fopen(tiedosto,"w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }  
    // kirjoitetaan linkitetty lista alusta loppuun tiedostoon
    if (iValintaLinkitetty == 2) {
        while (pA != NULL) {
            fprintf(fp,"%s,%d\n", pA->aSukunimi, pA->iMaara);
            pA = pA->pSeuraava;
        }
    } else {  // kirjoitetaan linkitetty lista lopusta -> alkuun tiedostoon
        while (pA != NULL && pA->pSeuraava != NULL) {
            pA = pA->pSeuraava;
        }
        while (pA != NULL) {
            fprintf(fp,"%s,%d\n", pA->aSukunimi, pA->iMaara);
            pA = pA->pEdellinen;
        }
    }

    fclose(fp);
    return;
}

SUKUNIMI *tyhjenna(SUKUNIMI *pA) {
    SUKUNIMI *ptr = pA;  // listan tyhjennys
    while (ptr != NULL) {
        pA = ptr->pSeuraava;
        free(ptr);
        ptr = pA;
    }
    return(pA);
}
