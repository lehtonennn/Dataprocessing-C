/*************************************************************************/
/*
* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 04
* Tekijä: Mikael Norppa, Jussi Kelloniemi
* Opiskelijanumero: 001867462, 001878639
* Päivämäärä: 27.04.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä: 
* Käytön tarkoitus: 
*/
/*************************************************************************/
/* Tehtävä L08,L09,L10,L11,L12 tiedoston nimi Projekti.c */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Kirjasto.h"
#include "Sort.h"
#include "BinaryTree.h"
#include "Graph.h"

int valikko();
SUKUNIMI* alavalikkoLinkitetty(SUKUNIMI* pA, SUKUNIMI* pV);
NODE* alavalikkoBinaari(NODE* pJuuri);
Graph* alavalikkoGraafi(Graph* pGraph);

int main(void) {
    int iValinta = -1;
    SUKUNIMI *pV = NULL;
    SUKUNIMI *pA = NULL;
    NODE *pJuuri = NULL;
    Graph* pGraph = NULL;
    Jono *jono = NULL;
    do {

        iValinta = valikko();
        if (iValinta == 1){
            printf("\n");
            pA = alavalikkoLinkitetty(pA, pV);
        } else if (iValinta == 2) {
            printf("\n");
            pJuuri = alavalikkoBinaari(pJuuri);
        } else if (iValinta == 3) {
            printf("\n");
            pGraph = alavalikkoGraafi(pGraph);
        } else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValinta != 0);
    pA = tyhjenna(pA);
    vapautaMuisti(pJuuri);
    vapautaJono(jono);
    vapautaGraafi(pGraph);
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}

int valikko(){
    int iValinta = 0;
    printf("/           Päävalikko           /\n");
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Mene linkitetty lista valikkoon\n");
    printf("2) Mene binääripuu valikkoon\n");
    printf("3) Mene graafi valikkoon\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return(iValinta);
}

SUKUNIMI* alavalikkoLinkitetty(SUKUNIMI* pA, SUKUNIMI* pV) {
    int iValintaLinkitetty = -1; 
    char tiedosto[100];

    do {
        printf("/     Linkitetty lista valikko     /\n");
        printf("Valitse haluamasi toiminto:\n");
        printf("1) Lue tiedosto\n");
        printf("2) Tallenna lista etuperin\n");
        printf("3) Tallenna lista takaperin\n");
        printf("4) Tyhjennä lista\n");
        printf("5) Järjestä nousevaan järjestykseen\n");
        printf("6) Järjestä laskevaan järjestykseen\n");
        printf("0) Palaa päävalikkoon\n");
        printf("Anna valintasi: ");
        scanf("%d", &iValintaLinkitetty);
        getchar();

        if(iValintaLinkitetty == 1){
            pA = tyhjenna(pA);
            pA = lueTiedosto(pA, tiedosto);
        } else if (iValintaLinkitetty == 2){
            kirjoitaTiedosto(pA, tiedosto, iValintaLinkitetty);
        } else if (iValintaLinkitetty == 3) {
            kirjoitaTiedosto(pA, tiedosto, iValintaLinkitetty);
        } else if (iValintaLinkitetty == 4) {
            pA = tyhjenna(pA);
            pV = viimeinenSolmu(pA);
            pV = tyhjennaSort(pV);
        } else if (iValintaLinkitetty == 5) {
            pV = viimeinenSolmu(pA);
            quickSort(pA,pV);
            printf("Lista lajiteltu nousevaan järjestykseen.\n");
        } else if (iValintaLinkitetty == 6) {
            pA = mergeSort(pA);
            printf("Lista lajiteltu laskevaan järjestykseen.\n");
        } else if (iValintaLinkitetty == 0) {
            printf("Palataan päävalikkoon.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValintaLinkitetty != 0);
    return pA;

}

NODE* alavalikkoBinaari(NODE* pJuuri) {
    int iValintaBinaari = -1; 
    int iEtsittavaMaara = 0;
    char tiedosto[100];
    char aEtsittavaArvo[40] = "";

    do {
        printf("/    Binääripuu Valikko    /\n");
        printf("Valitse haluamasi toiminto:\n");
        printf("1) Lue tiedosto \n");
        printf("2) Kirjoita puun arvot tiedostoon \n");
        printf("3) Syvyyshaku \n");
        printf("4) Leveyshaku \n");
        printf("5) Binääripuuhaku \n");
        printf("6) Poista arvo\n");
        printf("7) Tulosta puumaisemmassa muodossa\n");
        printf("0 Palaa päävalikkoon\n");
        printf("Anna valintasi: ");
        scanf("%d", &iValintaBinaari);
        getchar();

        if (iValintaBinaari == 1 ) {
            pJuuri = lueBinaariTiedosto(pJuuri, tiedosto);
        } else if (iValintaBinaari == 2) {
            syvyysHaku(pJuuri, tiedosto, iValintaBinaari);
        } else if (iValintaBinaari == 3) {
            syvyysHaku(pJuuri, tiedosto, iValintaBinaari);
        } else if (iValintaBinaari == 4) {
            leveysHaku(pJuuri,tiedosto);
        } else if (iValintaBinaari == 5) {
            binaariKysyArvo(pJuuri);
        } else if (iValintaBinaari == 6) {
            printf("Anna poistettava arvo: ");
            scanf("%s",aEtsittavaArvo);
            if (isdigit(aEtsittavaArvo[0]) != 0 ) {
                iEtsittavaMaara = atoi(aEtsittavaArvo);
                pJuuri = poistaNodeInt(pJuuri,iEtsittavaMaara);
            } else {
                pJuuri = poistaNodeString(pJuuri,aEtsittavaArvo);
            }
            printf("Poisto suoritettu.\n");
        } else if (iValintaBinaari == 7) {
            printf("Tulostetaan binääripuu puumaisessa muodossa:\n");
            tulostaPuu(pJuuri, 0);
        } else if (iValintaBinaari == 0) {
            printf("Palataan päävalikkoon.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValintaBinaari != 0);
    return pJuuri;
}

Graph* alavalikkoGraafi(Graph* pGraph) {
    int iValintaGraafi = -1; 
    char tiedosto[100];
    char tiedostoNimi[25] = "";
    char nimi[10];


    do {
        printf("/        Graafi Valikko        /\n");
        printf("Valitse haluamasi toiminto:\n");
        printf("1) Lue tiedosto\n");
        printf("2) Lisää/päivitä kaari\n");
        printf("3) Poista solmu\n");
        printf("4) Etsi lyhin reitti\n");
        printf("5) Tulosta graafi\n");
        printf("0) Palaa päävalikkoon\n");
        printf("Anna valintasi: ");
        scanf("%d", &iValintaGraafi);
        getchar();

        if (iValintaGraafi == 1) {
            pGraph = lueGraafiTiedosto(pGraph, tiedosto);
        } else if (iValintaGraafi == 2) {
            pGraph = paivitaKaari(pGraph);
        } else if (iValintaGraafi == 3) {
            printf("Anna poistettava solmu: ");
            scanf("%9s",nimi);
            printf("Poistetaan solmua %s...\n", nimi);
            pGraph = poistaSolmu(pGraph, nimi);
            printf("Poisto suoritettu.\n");
        } else if (iValintaGraafi == 4) {
            reittiArvot(pGraph, tiedostoNimi);
        } else if (iValintaGraafi == 5) {
            tulostaGraafi(pGraph);
        } else if (iValintaGraafi == 0) {
            printf("Palataan päävalikkoon.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValintaGraafi != 0);
    
    return pGraph;
}