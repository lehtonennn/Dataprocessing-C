/*************************************************************************/
/*
* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 04
* Tekijä: Lauri Lehtonen, Jussi Kelloniemi
* Opiskelijanumero: 506083, 001878639
* Päivämäärä: 27.04.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä: 
* 1. https://www.geeksforgeeks.org/implementation-of-graph-in-c/ 
* 2. https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
* 3. 
* 4. 
* 5. 
* Käytön tarkoitus: 
* 1. Graafi C-kielellä
* 2. Lyhimmän reitin etsintä
* 3. 
* 4. 
* 5. 
*/
/*************************************************************************/
/* Tehtävä L12 tiedoston nimi Graph.c */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Graph.h"

#define INT_MAX 20000000

Node* luoAdjNode(int iDest, const char* aNimi, int iValimatka) {

    Node* pU = NULL;

    // Varataan muisti solmulle
    if ((pU = (Node*)malloc(sizeof(Node))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

     // Muistin vauraus nimelle
     pU->aNimi = malloc(strlen(aNimi) + 1); 
     if (pU->aNimi == NULL) {
         free(pU);
         perror("Muistin varaus epäonnistui");
         exit(0);
     }

    // Alustetaan solmu tiedoilla
    pU->iDest = iDest;
    pU->iValimatka = iValimatka;
    strcpy(pU->aNimi, aNimi);
    pU->next = NULL;

    return pU;
}

Graph* luoGraafi(int iV) {

    Graph* pGraph = NULL;

    // Varataan muisti graafille
    if ((pGraph = (Graph*)malloc(sizeof(Graph))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    // Alustetaan graafin tiedot ja tarkastetaan muistinvaraus.
    pGraph->iV = iV;
    pGraph->array = (AdjList*)calloc(iV, sizeof(AdjList));
    pGraph->nimiHakemisto = (char**)malloc(iV * sizeof(char*));
    if (!pGraph->array || !pGraph->nimiHakemisto) {
        perror("Muistin varaus epäonnistui");
        exit(0);
    }
    return pGraph;
}

// Haetaan indeksi nimelle
int haeIndeksi(Graph* pGraph, const char* nimi) {
    for (int i = 0; i < pGraph->iV; i++) {
        if (pGraph->nimiHakemisto[i] && strcmp(pGraph->nimiHakemisto[i], nimi) == 0)
            return i;
    }
    return -1;
}

void lisaaKaari(Graph* pGraph, const char* nimi1, const char* nimi2, int iValimatka) {
    
    int idx1 = haeIndeksi(pGraph, nimi1);
    int idx2 = haeIndeksi(pGraph, nimi2);

    if (idx1 == -1 || idx2 == -1) {
        return;
    }

    Node* pU = luoAdjNode(idx2, nimi2, iValimatka);
    pU->next = pGraph->array[idx1].head;
    pGraph->array[idx1].head = pU;

    pU = luoAdjNode(idx1, nimi1, iValimatka);
    pU->next = pGraph->array[idx2].head;
    pGraph->array[idx2].head = pU;

    return;
}



Graph* lueGraafiTiedosto(Graph* pGraph, char* tiedosto) {
    char node1[50], node2[50];
    int iValimatka = 0;
    int i;
    int nodeCount = 0;
    char* aErilaisetNodet[100];  // Annetaan 100 nodenraja
    int iLoytyi = 0;
    
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s",tiedosto);
    FILE *fp = NULL;
    if ((fp = fopen(tiedosto,"r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Ohitetaan otsikkorivi
    while (i = fgetc(fp), i != '\n' && i != EOF);

    // Pointteri välimatkalle
    int* pValimatka = &iValimatka;
    // Ensimmäinen luku, lasketaan nodet
    while (fscanf(fp, "%49[^;];%49[^;];%d\n", node1, node2, pValimatka) == 3) {
        
        // Tarkastetaan onko node1 uusi.
        iLoytyi = 0;
        for (int i = 0; i < nodeCount; i++) {
            if (strcmp(aErilaisetNodet[i], node1) == 0) {
                iLoytyi = 1;
                break;
            }
        }
        if (!iLoytyi) {
            aErilaisetNodet[nodeCount] = malloc(strlen(node1) + 1);
            if (aErilaisetNodet[nodeCount] == NULL) {
                perror("Muistin varaus epäonnistui");
                exit(0);
            }
            strcpy(aErilaisetNodet[nodeCount], node1);
            nodeCount++;
        }
        
        // Tarkastetaan node2.
        iLoytyi = 0;
        for (int i = 0; i < nodeCount; i++) {
            if (strcmp(aErilaisetNodet[i], node2) == 0) {
                iLoytyi = 1;
                break;
            }
        }
        if (!iLoytyi) {
            aErilaisetNodet[nodeCount] = malloc(strlen(node2) + 1);
            if (aErilaisetNodet[nodeCount] == NULL) {
                perror("Muistin varaus epäonnistui");
                exit(0);
            }
            strcpy(aErilaisetNodet[nodeCount], node2);
            nodeCount++;
        }
    }

    // Luodaan oikean kokoinen graafi
    pGraph = luoGraafi(nodeCount);
    for (int i = 0; i < nodeCount; i++) {
        pGraph->nimiHakemisto[i] = aErilaisetNodet[i];
    }

    // Toinen luku, luodaan reunat
    rewind(fp);
    while (i = fgetc(fp), i != '\n' && i != EOF); // Ohitetaan otsikkorivi
    while (fscanf(fp, "%49[^;];%49[^;];%d\n", node1, node2, &iValimatka) == 3) {
        lisaaKaari(pGraph, node1, node2, iValimatka);
    }

    fclose(fp);
    return pGraph;
}

void tulostaGraafi(Graph* pGraph) {
    if (pGraph == NULL) {
        printf("Graafi on tyhjä!\n");
        return;
    }

    printf("\nGraafin sisältö:\n");
    for (int i = 0; i < pGraph->iV; i++) {
        // Tulosta nykyisen solmun nimi
        if (pGraph->nimiHakemisto[i] == NULL) {
            continue;   
        }
        printf("%s:", pGraph->nimiHakemisto[i]);
        
        // Käy läpi kaikki naapurisolmut
        Node* pNykyinen = pGraph->array[i].head;
        while (pNykyinen != NULL) {
            printf(" -> %s", pGraph->nimiHakemisto[pNykyinen->iDest]);
            pNykyinen = pNykyinen->next;
        }
        printf("\n");
    }
    printf("\n");
    return;
}

Graph* poistaSolmu(Graph* pGraph, const char* nimi) {
    //char nimi[10];
    //printf("Anna poistettava solmu: ");
    //scanf("%9s",nimi);
    //printf("Poistetaan solmua %s...\n", nimi);


    int idxPoista = haeIndeksi(pGraph, nimi);

    for (int i = 0; i < pGraph->iV; i++) {
        Node* temp = pGraph->array[i].head;
        Node* prev = NULL;
    

    while (temp != NULL) {
        if (temp->iDest == idxPoista) {
            Node* poista = temp;
            if (prev == NULL) {
                pGraph->array[i].head = temp->next;
            } else {
                prev->next = temp->next;
            }
            temp = temp->next;
            free(poista->aNimi);
            free(poista);
            continue;
        }
        prev = temp;
        temp = temp->next;
    }
}

    Node* temp = pGraph->array[idxPoista].head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp->aNimi);
        free(temp);
        temp = next;
}
    
    pGraph->array[idxPoista].head = NULL;
    if (pGraph->nimiHakemisto[idxPoista]) {
        free(pGraph->nimiHakemisto[idxPoista]);
        pGraph->nimiHakemisto[idxPoista] = NULL;
    }

    //printf("Poisto suoritettu.\n");
    return pGraph;
}

Graph* paivitaKaari(Graph* pGraph) {
    char aTiedot[10];
    const char s[2] = ";";
    char *sLahto, *sKohde, *sPituus;
    int iPituus = 0;
    printf("Anna päivitettävä kaari (lähtösolmu;kohdesolmu;etäisyys): ");
    scanf("%9s",aTiedot);

    sLahto = strtok(aTiedot,s);
    sKohde = strtok(NULL, s);
    sPituus = strtok(NULL, s);
    iPituus = atoi(sPituus);

    int idxLahto = haeIndeksi(pGraph, sLahto);
    int idxKohde = haeIndeksi(pGraph, sKohde);

    // kasvatetaan graafia

    

    // lisätään toinen nodeista jos ei ole olemassa
    if (idxLahto == -1) {
        kasvataGraafi(pGraph, pGraph->iV + 1);
        idxLahto = pGraph->iV;
        pGraph->nimiHakemisto[idxLahto] = malloc(strlen(sLahto) + 1); 
            if (pGraph->nimiHakemisto[idxLahto] == NULL) {
                free(pGraph);
                perror("Muistin varaus epäonnistui");
                exit(0);
            }
        strcpy(pGraph->nimiHakemisto[idxLahto], sLahto);
        pGraph->array[idxLahto].head = NULL;
        pGraph->iV++;
    }

    if (idxKohde == -1) {
        kasvataGraafi(pGraph, pGraph->iV + 1);
        idxKohde = pGraph->iV;
        pGraph->nimiHakemisto[idxKohde] = malloc(strlen(sKohde) + 1); 
            if (pGraph->nimiHakemisto[idxKohde] == NULL) {
                free(pGraph);
                perror("Muistin varaus epäonnistui");
                exit(0);
            }
        strcpy(pGraph->nimiHakemisto[idxKohde], sKohde);
        pGraph->array[idxKohde].head = NULL;
        pGraph->iV++;
    }

    Node* pNykyinen = pGraph->array[idxLahto].head;
    while (pNykyinen != NULL) {
        if (pNykyinen->iDest == idxKohde) {
            pNykyinen->iValimatka = iPituus;
            return pGraph;
        }
        pNykyinen = pNykyinen->next;
    }

    lisaaKaari(pGraph, sLahto, sKohde, iPituus);
    return pGraph;
}

void kasvataGraafi(Graph* pGraph, int uusiKoko) {
    pGraph->array = realloc(pGraph->array, uusiKoko * sizeof(AdjList));
    pGraph->nimiHakemisto = realloc(pGraph->nimiHakemisto, uusiKoko * sizeof(char*));

    if (!pGraph->array || !pGraph->nimiHakemisto) {
        exit(EXIT_FAILURE);
    }

    for (int i = pGraph->iV; i < uusiKoko; i++) {
        pGraph->array[i].head = NULL;
        pGraph->nimiHakemisto[i] = NULL;
    }
    return;
}

void reittiArvot(Graph* pGraph, char* tiedostoNimi){
    char alku[35];
    char loppu[35];
    if (tiedostoNimi[0] == '\0'){
        printf("Anna reittitiedoston nimi: ");
        scanf("%s", tiedostoNimi);
    }
    printf("Anna lähtösolmu: ");
    scanf("%s", alku);
    printf("Anna kohdesolmu: ");
    scanf("%s", loppu);
    lyhyinReitti(pGraph, alku, loppu, tiedostoNimi);
    return;
}

void lyhyinReitti(Graph* pGraph, char* alku, char* loppu, char* tiedostoNimi) {
    int* pituus;
    int* vierailtu;
    int* edellinen;
    int* lyhyinReitti;
    int alkuIndeksi = haeIndeksi(pGraph, alku);
    int loppuIndeksi = haeIndeksi(pGraph, loppu);

    if ((pituus = (int*)malloc(pGraph->iV*sizeof(int))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    if((edellinen = (int*)malloc(pGraph->iV*sizeof(int))) == NULL){
        perror("Muistin varaus epäonnistui, lopetetaan.");
        exit(0);
    }
    if((vierailtu = (int*)calloc(pGraph->iV, sizeof(int))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan.");
        exit(0);
    }

    for(int i=0; i < pGraph->iV; i++){ // Alustetaan etäisyydet
        pituus[i] = INT_MAX;
        edellinen[i] = -1;
    }
    pituus[alkuIndeksi] = 0;

    for (int i=0; i < pGraph->iV; i++) {
        int j = minimiPituus(pituus, vierailtu, pGraph->iV);
        if (j == -1 || j == loppuIndeksi) {
            break;
        }
        vierailtu[j] = 1;
        Node* pNaapuri = pGraph->array[j].head;

        while (pNaapuri != NULL) {
            int k = pNaapuri->iDest;

            if (!vierailtu[k] && pituus[j] != INT_MAX && pituus[j] + 1 < pituus[k]) {
                pituus[k] = pituus[j] + + pNaapuri->iValimatka;
                edellinen[k] = j;
            }
            pNaapuri = pNaapuri->next;
        }
    }
    
    FILE* tiedosto = NULL;

    if((tiedosto = fopen(tiedostoNimi, "a+")) == NULL){
        perror("Tiedoston avaaminen epäonnistui, lopetetaan.");
        exit(0);
    }
    
    if((lyhyinReitti = (int*)malloc(pGraph->iV*sizeof(int))) == NULL){
        perror("Muistin varaus epäonnistui, lopetetaan.");
        exit(0);
    }
    int reittipituus = 0;

    for (int i = loppuIndeksi; i != -1; i = edellinen[i]) {
        lyhyinReitti[reittipituus++] = i;
    }

    for (int i = reittipituus - 1; i >= 0; i--) {
        fprintf(tiedosto, "%s", pGraph->nimiHakemisto[lyhyinReitti[i]]);
        if (i > 0) {
            fprintf(tiedosto, " -> ");
        }
    }
    fprintf(tiedosto, " = %d\n", pituus[loppuIndeksi]);
    fclose(tiedosto);
    
    free(lyhyinReitti);
    free(pituus);
    free(vierailtu);
    free(edellinen);
    return;
}

int minimiPituus(int pituus[], int vierailtu[], int iV){
    int minimi = INT_MAX;
    int minimiIndeksi = -1;

    for (int i=0; i < iV; i++){
        if(vierailtu[i] == 0 && pituus[i] < minimi){
            minimi = pituus[i];
            minimiIndeksi = i;
        }
    }
    return minimiIndeksi;
}

void vapautaGraafi(Graph* pGraph) {
    if (pGraph == NULL)
    return;

    for (int i = 0; i < pGraph->iV; i++) {
        Node* nykyinen = pGraph->array[i].head;
        while (nykyinen != NULL) {
            Node* temp = nykyinen;
            nykyinen = nykyinen->next;
            free(temp->aNimi);
            free(temp);
        }

        if (pGraph->nimiHakemisto[i] != NULL) {
            free(pGraph->nimiHakemisto[i]);
        }
    }

    free(pGraph->array);
    free(pGraph->nimiHakemisto);
    free(pGraph);
    return;
}