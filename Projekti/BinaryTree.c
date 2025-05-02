/*************************************************************************/
/*
* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 04
* Tekijä: Lauri Lehtonen, Mikael Norppa, Jussi Kelloniemi
* Opiskelijanumero: 506083, 001867462, 001878639
* Päivämäärä: 27.04.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä: 
* 1. https://www.geeksforgeeks.org/binary-tree-in-c/
* 2. https://www.geeksforgeeks.org/level-order-traversal-in-c/
* 3. https://code-vault.net/lesson/a985b2dd74cfa127eec967874e00d5a2
* 4. https://www.geeksforgeeks.org/c-program-to-implement-avl-tree/
* 5. https://www.geeksforgeeks.org/deletion-in-an-avl-tree/
* Käytön tarkoitus: 
* 1. Binääripuu C-kielellä
* 2. Leveyshaku binääripuusta
* 3. Syvyyshaku binääripuusta
* 4. AVL-puu C-kielellä
* 5. AVL-puusta poisto
*/
/*************************************************************************/
/* Tehtävä L10 tiedoston nimi BinaryTree.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "BinaryTree.h"

NODE* luoNode(char* sukunimi, int maara) {
    
    NODE *pUusiNode = NULL;
    
    // Varataan muisti solmulle
    if ((pUusiNode = (NODE*)malloc(sizeof(NODE))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }
    
    // Alustetaan solmu tiedoilla
    strcpy(pUusiNode->aSukunimi, sukunimi);
    pUusiNode->iMaara = maara;
    pUusiNode->vasen = NULL;
    pUusiNode->oikea = NULL;
    pUusiNode->iKorkeus = 1; // Uusi node lisätään aluksi lehteen
    return pUusiNode;
}

// Utility funktio jotta saadaan kahden numeron maksimi
int maksimi(int a, int b) {
    return (a > b) ? a : b;
}

// Funktio jolla haetaan noden korkeus
int haeKorkeus(NODE* n) {
    if (n == NULL)
        return 0;
    return n->iKorkeus;
}

// Funktio jolla saadaan noden tasapaino
int haeTasapaino(NODE* n) {
    if (n == NULL)
        return 0;
    return haeKorkeus(n->vasen) - haeKorkeus(n->oikea);
}

// Funktio oikealle käännolle
NODE* oikeaRotate(NODE* y) {

    // Alustetaan käännettävät Nodet
    NODE* x = y->vasen;
    NODE* T2 = x->oikea;

    // Tehdään kääntö
    x->oikea = y;
    y->vasen = T2;

    // Päivitetään korkeudet
    y->iKorkeus
        =maksimi(haeKorkeus(y->vasen), haeKorkeus(y->oikea)) + 1;
    x->iKorkeus
        =maksimi(haeKorkeus(x->vasen), haeKorkeus(x->oikea)) + 1;

    return x;
}

// Funktio vasemmalle käännolle
NODE* vasenRotate(NODE* x) {
    
    // Alustetaan käännettävät Nodet
    NODE* y = x->oikea;
    NODE* T2 = y->vasen;

    // Tehdään kääntö
    y->vasen = x;
    x->oikea = T2;

    // Päivitetään korkeudet
    x->iKorkeus
        =maksimi(haeKorkeus(x->vasen), haeKorkeus(x->oikea)) + 1;
    y->iKorkeus
        =maksimi(haeKorkeus(y->vasen), haeKorkeus(y->oikea)) + 1;

    return y;
}

NODE* lisaaNode(NODE* pJuuri, char* sukunimi, int maara) {
    
    // Jos puu on tyhjä, luodaan pJuuri "root"
    if (pJuuri == NULL) {
        return luoNode(sukunimi, maara);
    }

    /* Suoritetaan vertailu ja rakennetaan puu. Puu vertaa määrää ja asettaa pienemmän
    arvon vasemmalle ja suuremman oikealle. Jos määrät ovat samat verrataan akkosjärjestyksen perusteella. */

    // Määrän vertaus
    if (maara < pJuuri->iMaara) {
        pJuuri->vasen = lisaaNode(pJuuri->vasen, sukunimi, maara);
    } else if (maara > pJuuri->iMaara) {
        pJuuri->oikea = lisaaNode(pJuuri->oikea, sukunimi, maara);
    } else {
        if (strcmp(sukunimi, pJuuri->aSukunimi) < 0) {
            pJuuri->vasen = lisaaNode(pJuuri->vasen, sukunimi, maara);
        } else {
            pJuuri->oikea = lisaaNode(pJuuri->oikea, sukunimi, maara);
        }
    }

    // 2. Päivitetään solmun korkeus
    pJuuri->iKorkeus = 1 + maksimi(haeKorkeus(pJuuri->vasen), haeKorkeus(pJuuri->oikea));

    // 3. Tarkastetaan tasapainotekijä
    int iTasapaino = haeTasapaino(pJuuri);

    // 4. Käsitellään epätasapainotapaukset

    // Vasen–Vasen (LL)
    if (iTasapaino > 1 && haeTasapaino(pJuuri->vasen) >= 0)
        return oikeaRotate(pJuuri);

    // Oikea–Oikea (RR)
    if (iTasapaino < -1 && haeTasapaino(pJuuri->oikea) <= 0)
        return vasenRotate(pJuuri);

    // Vasen–Oikea (LR)
    if (iTasapaino > 1 && haeTasapaino(pJuuri->vasen) < 0) {
        pJuuri->vasen = vasenRotate(pJuuri->vasen);
        return oikeaRotate(pJuuri);
    }

    // Oikea–Vasen (RL)
    if (iTasapaino < -1 && haeTasapaino(pJuuri->oikea) > 0) {
        pJuuri->oikea = oikeaRotate(pJuuri->oikea);
        return vasenRotate(pJuuri);
    }

    // Tarkistetaan, että tasapainotekijä on validi
    assert(abs(haeTasapaino(pJuuri)) <= 1);

    return pJuuri;
}

NODE* pieninArvoNode(NODE* node) {
    NODE* nykyinen = node;
    while (nykyinen->vasen != NULL) {
        nykyinen = nykyinen->vasen;
    }

    return nykyinen;
}

NODE* poistaNodeInt(NODE* pJuuri, int iEtsittavaMaara) {
    
    if (pJuuri == NULL) {
        return pJuuri;
    }

    if ( iEtsittavaMaara < pJuuri->iMaara) {
        pJuuri->vasen = poistaNodeInt(pJuuri->vasen, iEtsittavaMaara);
    } else if ( iEtsittavaMaara > pJuuri->iMaara) {
        pJuuri->oikea = poistaNodeInt(pJuuri->oikea, iEtsittavaMaara);
    } else {

        if (pJuuri->vasen == NULL || pJuuri->oikea == NULL) {
            NODE *ptr = pJuuri->vasen ? pJuuri->vasen : pJuuri->oikea;

        if (ptr == NULL) {
            printf("Poistetaan arvoa %s, %d...\n", pJuuri->aSukunimi, pJuuri->iMaara);
            ptr = pJuuri;
            pJuuri = NULL;
            free(ptr);
        } else {
            *pJuuri = *ptr;
            free(ptr);
        }

        } else {
            printf("Poistetaan arvoa %s, %d...\n", pJuuri->aSukunimi, pJuuri->iMaara);
            NODE* ptr = pieninArvoNode(pJuuri->oikea);
            pJuuri->iMaara = ptr->iMaara;
            strcpy(pJuuri->aSukunimi, ptr->aSukunimi);
            pJuuri->oikea = poistaNodeInt(pJuuri->oikea, ptr->iMaara);
        }
    }

    if (pJuuri == NULL) {
        return pJuuri;
    }

    pJuuri->iKorkeus = 1 + maksimi(haeKorkeus(pJuuri->vasen), haeKorkeus(pJuuri->oikea));

    int tasapaino = haeTasapaino(pJuuri);

    // LL
    if (tasapaino > 1 && haeTasapaino(pJuuri->vasen) >= 0) {
        return oikeaRotate(pJuuri);
    }
    // LR
    if (tasapaino > 1 && haeTasapaino(pJuuri->vasen) < 0) {
        pJuuri->vasen = vasenRotate(pJuuri->vasen);
        return oikeaRotate(pJuuri);
    }
    // RR
    if (tasapaino < -1 && haeTasapaino(pJuuri->oikea) <= 0) {
        return vasenRotate(pJuuri);
    }
    // RL
    if (tasapaino < -1 && haeTasapaino(pJuuri->oikea) > 0) {
        pJuuri->oikea = oikeaRotate(pJuuri->oikea);
        return vasenRotate(pJuuri);
    }
    
    return pJuuri;
}

NODE* poistaNodeString(NODE* pJuuri, char* aEtsittavaArvo) {
    if (pJuuri == NULL) {
        return pJuuri;
    }

    Jono* jono = uusiJono(); 
    lisaaJonoon(jono, pJuuri);


    // Koska sukunimet ei järjestyksessä, käytetään bfs löytääkseen
    // oikean noden.
    while (!jonoTyhja(jono)) {
        NODE* pNykyinen = poistaJonosta(jono);
        
        if (strcmp(aEtsittavaArvo, pNykyinen->aSukunimi) == 0) {
            int iEtsittavaMaara = pNykyinen->iMaara;
            vapautaJono(jono);
            return poistaNodeInt(pJuuri, iEtsittavaMaara);
        }   
        if (pNykyinen->vasen) {
            lisaaJonoon(jono, pNykyinen->vasen);
        }
        
        if (pNykyinen->oikea) {
            lisaaJonoon(jono, pNykyinen->oikea);
        }
    }

    return pJuuri;
}


NODE* lueBinaariTiedosto(NODE* pJuuri, char* tiedosto) {
    char sukunimi[40];
    int maara;
    int i;
    
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s",tiedosto);
    FILE *fp = NULL;
    if ((fp = fopen(tiedosto,"r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Ohitetaan otsikkorivi
    while (i = fgetc(fp), i != '\n' && i != EOF);
    // Luetaan tiedostosta data ja luodaan binääripuu
    while (fscanf(fp, "%39[^;,];%d\n", sukunimi, &maara) == 2) {
        pJuuri = lisaaNode(pJuuri, sukunimi, maara);
    }

    fclose(fp);
    return pJuuri;
}

// leveyshaku

Jono* uusiJono() {
    Jono* pJono = NULL;
    if (( pJono = (Jono*)malloc(sizeof(Jono))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    if (pJono) {
        pJono -> pJonoAlku = NULL;
        pJono -> pJonoLoppu = NULL;
    }
    return pJono;
}

void lisaaJonoon(Jono* jono, NODE* pPuuNode) {
    JonoNode* pUusiJonoNode = NULL;
    if (( pUusiJonoNode = (JonoNode*)malloc(sizeof(JonoNode))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    if (pUusiJonoNode) {
        pUusiJonoNode->pPuuNode = pPuuNode;
        pUusiJonoNode->pLeveysSeuraava = NULL;
        if (jono->pJonoLoppu) {
            jono->pJonoLoppu->pLeveysSeuraava = pUusiJonoNode;
        } else {
            jono->pJonoAlku = pUusiJonoNode;
        }
        jono->pJonoLoppu = pUusiJonoNode;
    }
    return;
}

NODE* poistaJonosta(Jono* jono) {
    if (jono->pJonoAlku) {
        JonoNode* ptr = jono->pJonoAlku;
        NODE* pPuuNode = ptr->pPuuNode;
        jono->pJonoAlku = jono->pJonoAlku->pLeveysSeuraava;
        if (!jono->pJonoAlku) {
            jono->pJonoLoppu = NULL;
        }
        free(ptr);
        return pPuuNode;
    }
    return NULL;
}

int jonoTyhja(Jono* jono) {
    return jono->pJonoAlku == NULL;
}

void leveysHaku(NODE* pJuuri, char* tiedosto) {
    if (pJuuri == NULL) {
        return;
    }

    char aEtsittavaArvo[40] = "";
    int iEtsittavaMaara = 0;
    int iLoytyi = 0;
    printf("Anna etsittävä arvo: ");
    scanf("%s",aEtsittavaArvo);
    
    if (isdigit(aEtsittavaArvo[0]) != 0 ) {
        iEtsittavaMaara = atoi(aEtsittavaArvo);
    }

    printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", tiedosto);

    FILE *fp = NULL;
    if ((fp = fopen(tiedosto,"w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    Jono* jono = uusiJono();
    lisaaJonoon(jono, pJuuri);

    while (!jonoTyhja(jono)) {
        NODE* pNykyinen = poistaJonosta(jono);

        fprintf(fp,"%s,%d\n", pNykyinen->aSukunimi, pNykyinen->iMaara);

        if (iEtsittavaMaara == pNykyinen->iMaara || strcmp(aEtsittavaArvo, pNykyinen->aSukunimi) == 0) {
            printf("Puussa on arvo '%s %d'\n", pNykyinen->aSukunimi, pNykyinen->iMaara);
            iLoytyi = 1;
            break;
        }
        if (pNykyinen->vasen) {
            lisaaJonoon(jono, pNykyinen->vasen);
        }
        
        if (pNykyinen->oikea) {
            lisaaJonoon(jono, pNykyinen->oikea);
        }
    }
    
    if (iLoytyi == 0) {
        printf("Puussa ei ole arvoa '%s'.\n", aEtsittavaArvo);
        }
    
    printf("\n");
    fclose(fp);
    vapautaJono(jono);
    return;
}

// Syvyys haku

void syvyysHaku(NODE* pJuuri, char* tiedosto, int iValintaBinaari) {
    if(pJuuri == NULL) {
        return;
    }

    char aEtsittavaArvo[40] = "";
    int iEtsittavaMaara = 0;

    if (iValintaBinaari == 3) {
        printf("Anna etsittävä arvo: ");
        scanf("%s",aEtsittavaArvo);
    }

    if (isdigit(aEtsittavaArvo[0]) != 0 ) {
        iEtsittavaMaara = atoi(aEtsittavaArvo);
    }

    printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", tiedosto);

    FILE *fp = NULL;
    if ((fp = fopen(tiedosto,"w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    NODE* stack[100];
    int stackNumero = 0;
    stack[0] = pJuuri;
    stackNumero++;

    while(stackNumero > 0) {
        NODE* pNykyinen = stack[stackNumero-1];
        stackNumero--;
        if(iEtsittavaMaara == pNykyinen->iMaara || strcmp(aEtsittavaArvo, pNykyinen->aSukunimi) == 0) {
            if (iValintaBinaari == 3) {
            printf("Puussa on arvo '%s %d'.\n", pNykyinen->aSukunimi, pNykyinen->iMaara);
            }
            fprintf(fp, "%s,%d\n", pNykyinen->aSukunimi, pNykyinen->iMaara);
            break;
        } else {
            fprintf(fp, "%s,%d\n", pNykyinen->aSukunimi, pNykyinen->iMaara);
        }

        if(pNykyinen->oikea != NULL) {
            stack[stackNumero] = pNykyinen->oikea;
            stackNumero++;
        }
        if(pNykyinen->vasen != NULL) {
            stack[stackNumero] = pNykyinen->vasen;
            stackNumero++;
        }
    }
    fclose(fp);
    return;
}   

void tulostaPuu(NODE* pJuuri, int taso) {
    if (pJuuri == NULL) return;

    // Tulostetaan oikea lapsi ensin (näyttää puun käänteisenä)
    tulostaPuu(pJuuri->oikea, taso + 1);

    // Tulostetaan tämä solmu sopivalla sisennyksellä
    for (int i = 0; i < taso; i++) printf("           ");
    printf("%s (%d)\n", pJuuri->aSukunimi, pJuuri->iMaara);

    // Tulostetaan vasen lapsi
    tulostaPuu(pJuuri->vasen, taso + 1);
    return;
}


// Binäärihaku

void binaariKysyArvo(NODE* pJuuri) {
    int iEtsittavaMaara = 0;

    printf("Anna etsittävä arvo: ");
    scanf("%d", &iEtsittavaMaara);

    pJuuri = binaariHaku(pJuuri, iEtsittavaMaara);

    printf("Puussa on arvo '%s;%d'\n", pJuuri->aSukunimi, pJuuri->iMaara);
    return;
}

NODE* binaariHaku(NODE* pJuuri, int iEtsittavaMaara) {

    while(pJuuri != NULL) {
        if (iEtsittavaMaara == pJuuri->iMaara) {
            return(pJuuri);
        }

        if(iEtsittavaMaara < pJuuri->iMaara) {
            pJuuri = pJuuri->vasen;
        } else {
            pJuuri = pJuuri->oikea;
        }
    }

    return(NULL);
}

void vapautaMuisti(NODE* pJuuri) {
    if (pJuuri != NULL) {
        vapautaMuisti(pJuuri->oikea);
        vapautaMuisti(pJuuri->vasen);
        free(pJuuri);
    }
}

void vapautaJono(Jono* jono) {
    if (jono == NULL) {
        return;
    }
    while (!jonoTyhja(jono)) {
        poistaJonosta(jono);
    }
    free(jono);
    return;
}
