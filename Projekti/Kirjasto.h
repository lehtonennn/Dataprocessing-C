#ifndef KIRJASTO_H
#define KIRJASTO_H

typedef struct sukunimi {
    int iMaara;
    char aSukunimi[40];
    struct sukunimi *pSeuraava;
    struct sukunimi *pEdellinen;
} SUKUNIMI;

SUKUNIMI * lisaaSolmu(SUKUNIMI *pA, char *sukunimi, int maara);
SUKUNIMI * lueTiedosto(SUKUNIMI *pA, char *tiedosto);
void kirjoitaTiedosto(SUKUNIMI *pA, char *tiedosto, int iValinta);
SUKUNIMI *tyhjenna(SUKUNIMI *pA);

#endif