#ifndef GRAPH_H
#define GRAPH_H

typedef struct AdjListNode {
    char* aNimi;
    int iDest;
    int iValimatka;
    struct AdjListNode* next;
} Node;

typedef struct AdjList {
    struct AdjListNode* head;
} AdjList;

typedef struct Graph {
    int iV; // Solmujen määrä
    char** nimiHakemisto;
    struct AdjList* array;
} Graph;

struct AdjListNode* luoAdjNode(int iDest, const char* aNimi, int iValimatka);
Graph* luoGraafi(int iV);
int haeIndeksi(Graph* pGraph, const char* nimi);
void lisaaKaari(Graph* pGraph, const char* nimi1, const char* nimi2, int iValimatka);
Graph* lueGraafiTiedosto(Graph* pGraph, char* tiedosto);
void tulostaGraafi(Graph* pGraph);
Graph* poistaSolmu(Graph* pGraph, const char* nimi);
Graph* paivitaKaari(Graph* pGraph);
void kasvataGraafi(Graph* pGraph, int uusiKoko);
void reittiArvot(Graph* pGraph, char* tiedostoNimi);
void lyhyinReitti(Graph* pGraph, char* alku, char* loppu, char* tiedostoNimi);
int minimiPituus(int pituus[], int vierailtu[], int iV);
void vapautaGraafi(Graph* pGraph);
#endif