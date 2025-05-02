#ifndef SORT_H
#define SORT_H
#include "Kirjasto.h"

void vaihto(SUKUNIMI* a, SUKUNIMI* b);
SUKUNIMI* viimeinenSolmu(SUKUNIMI* pA);
SUKUNIMI* osio(SUKUNIMI* pA, SUKUNIMI* pV);
void quickSort(SUKUNIMI* pA, SUKUNIMI* pV);
void kirjoitaSortTiedosto();
SUKUNIMI* tyhjennaSort(SUKUNIMI* pV);
SUKUNIMI* mergeSort(SUKUNIMI* pA);
SUKUNIMI* jaaLista(SUKUNIMI* pA);
SUKUNIMI* merge(SUKUNIMI* ensimmainen, SUKUNIMI* toinen);
#endif