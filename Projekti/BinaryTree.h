#ifndef BINARYTREE_H
#define BINARYTREE_H

typedef struct Node {
    int iMaara;
    char aSukunimi[40];
    struct Node* vasen;
    struct Node* oikea;
    int iKorkeus;
} NODE;

// leveyshakua varten
typedef struct JonoNode {
    NODE* pPuuNode;
    struct JonoNode* pLeveysSeuraava;
}   JonoNode;

// leveyshakua varten
typedef struct Jono {
    JonoNode* pJonoAlku;
    JonoNode* pJonoLoppu;
} Jono;

NODE* luoNode(char* sukunimi, int maara);
int maksimi(int a, int b);
int haeKorkeus(NODE* n);
int haeTasapaino(NODE* n);
NODE* oikeaRotate(NODE* y);
NODE* vasenRotate(NODE* x);
NODE* lisaaNode(NODE* pJuuri, char* sukunimi, int maara);
NODE* pieninArvoNode(NODE* node);
NODE* poistaNodeInt(NODE* pJuuri, int iEtsittavaArvo);
NODE* poistaNodeString(NODE* pJuuri, char* aEtsittavaArvo);
NODE* lueBinaariTiedosto(NODE* pJuuri, char* tiedosto);
Jono* uusiJono();
void lisaaJonoon(Jono* jono, NODE* pPuuNode);
NODE* poistaJonosta(Jono* jono);
int jonoTyhja(Jono* jono);
void leveysHaku(NODE* pJuuri, char* tiedosto);
void tulostaPuu(NODE* pJuuri, int iTaso);
void syvyysHaku(NODE* pJuuri, char* tiedosto, int iValintaBinaari);
void vapautaMuisti(NODE* pJuuri);
void vapautaJono(Jono* jono);
void binaariKysyArvo();
NODE* binaariHaku(NODE* pJuuri, int iEtsittavaMaara);
#endif