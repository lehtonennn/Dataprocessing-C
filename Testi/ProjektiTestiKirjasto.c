/*************************************************************************/
/*
* CT60A2600 Ohjelmakehitys C-kielellä
* Tiimi: 04
* Tekijä: Lauri Lehtonen, Mikael Norppa, Jussi Kelloniemi
* Opiskelijanumero: 00506083, 001867462, 001878639
* Päivämäärä: 27.04.2025
* Tämän ohjelman tekemisessä on käytetty kurssilla annettujen materiaalien
* ja ohjeiden lisäksi seuraavia lähteitä, työkaluja ja henkilöitä: 
* 1. https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks 
* 2. https://stackoverflow.com/questions/5248915/execution-time-of-c-program
* 3. https://www.geeksforgeeks.org/inputoutput-external-file-cc-java-python-competitive-programming/
* Käytön tarkoitus: 
* 1. Kuinka voidaan tarkistaa muistivuotoja käyttäen valgrindia.
* 2. Kuinka funktioiden aika voidaan mitata.
* 3. Syötteiden luku tiedostosta test_syvyysHakua varten
*/
/*************************************************************************/
/* Tehtävä L09, tiedoston nimi ProjektiTestiKirjasto.c */


// JOS TEET ITSE TESTEJÄ, LUO TESTEISSÄ OLEVAT TIEDOSTOT VALMIIKSI, TESTIT EIVÄT LUO NIITÄ.
// Näin runaat gcc -o Testi ProjektiKirjasto.c ProjektiTestiKirjasto.c ProjektiKirjastoSort.c BinaryTree.c Graph.c -Wall -pedantic -lcunit
// Pitää olla cunit asennettuna, sudo apt install libcunit1-dev

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "Sort.h"
#include "Kirjasto.h"
#include "BinaryTree.h"
#include "Graph.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void test_lisaaSolmu();
void test_lueTiedosto();
void test_tyhjenna();
void test_kirjoitaTiedosto2();
void test_pitkaNimi();
void test_suorituskyky();
void test_vaihto();
void test_vaihtoTyhjaNimi();
void test_listaNULL();
void test_viimeinenSolmu();
void test_osio();
void test_quickSort();
void test_mergeSort();
void test_jaaLista();
void test_luoNode();
void test_lisaaNode();
void test_muistiVapautus();
void test_poistaJonostaTyhja();
void test_syvyysHaku();
void test_haeKorkeus();
void test_oikeaRotate();
void test_vasenRotate();
void test_haeTasapaino_null();
void test_binaariHaku();
void test_pieninArvo();
void test_poistaSolmu();
void test_luoGraafi();
void test_luoAdjNode();
void test_lisaaKaari();
void test_luoAdjNodeNimiTyhja();
void test_haeIndeksiNimi();
void test_vapautaGraafiNull();
void test_pieninArvoNodeYksiSolmu();
void test_binaariHakuEiOlemassa();

int main() {
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Test Suite", 0, 0);

    CU_add_test(suite, "test_lisaaSolmu", test_lisaaSolmu);
    CU_add_test(suite, "test_tyhjenna", test_tyhjenna);
    CU_add_test(suite, "test_lueTiedosto", test_lueTiedosto);
    CU_add_test(suite, "test_kirjoitaTiedosto2", test_kirjoitaTiedosto2);
    CU_add_test(suite, "test_viimeinenSolmu", test_viimeinenSolmu); 
    CU_add_test(suite, "test_osio", test_osio);
    CU_add_test(suite, "test_quickSort", test_quickSort);
    CU_add_test(suite, "test_mergeSort", test_mergeSort);
    CU_add_test(suite, "test_jaaLista", test_jaaLista);
    CU_add_test(suite, "test_luoNode", test_luoNode);
    CU_add_test(suite, "test_lisaaNode", test_lisaaNode);
    CU_add_test(suite, "test_muistiVapautus", test_muistiVapautus);
    CU_add_test(suite, "test_poistaJonostaTyhja", test_poistaJonostaTyhja);
    CU_add_test(suite, "test_syvyysHaku", test_syvyysHaku);
    CU_add_test(suite, "test_haeKorkeus", test_haeKorkeus);
    CU_add_test(suite, "test_oikeaRotate", test_oikeaRotate);
    CU_add_test(suite, "test_vasenRotate", test_vasenRotate);
    CU_add_test(suite, "test_haeTasapino_null", test_haeTasapaino_null);
    CU_add_test(suite, "test_binaariHaku", test_binaariHaku);
    CU_add_test(suite, "test_pieninarvo", test_pieninArvo);
    CU_add_test(suite, "test_poistaSolmu", test_poistaSolmu);

    CU_add_test(suite, "test_luoGraafi", test_luoGraafi);
    CU_add_test(suite, "test_luoAdjNode", test_luoAdjNode);
    CU_add_test(suite, "test_lisaaKaari", test_lisaaKaari);
    CU_add_test(suite, "test_luoAdjNodeNimiTyhja", test_luoAdjNodeNimiTyhja);
    CU_add_test(suite, "test_haeIndeksiNimi",test_haeIndeksiNimi);
    CU_add_test(suite, "test_vapautaGraafiNull",test_vapautaGraafiNull);
    CU_add_test(suite, "test_pieninArvoNodeYksiSolmu",test_pieninArvoNodeYksiSolmu);
    CU_add_test(suite, "test_binaariHakuEiOlemassa",test_binaariHakuEiOlemassa);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}

void test_lisaaSolmu() {
    // Testi-ID : AT-01
    // Testataan funktion lisaaSolmu toimiminen.
    SUKUNIMI *pA = NULL;

    // Luodaan uusi solmu listaan, ja tarkistetaan se.
    pA = lisaaSolmu(pA, "TESTI", 1);

    CU_ASSERT_PTR_NOT_NULL(pA);
    CU_ASSERT_STRING_EQUAL(pA->aSukunimi, "TESTI");
    CU_ASSERT(pA->iMaara == 1);
}

void test_tyhjenna() {
    // Testi-ID : AT-03
    // Testataan osoittimen tyhjennys
    SUKUNIMI *pA = NULL;
    pA = lisaaSolmu(pA, "Testi", 1);
    pA = tyhjenna(pA);

    CU_ASSERT_PTR_NULL(pA);
}

void test_lueTiedosto() {
    // Testi-ID : AT-02
    // Testataan funktion lueTiedosto toiminen.
    SUKUNIMI *pA = NULL;
    char tiedosto[] = "sukunimet_2025.txt";

    pA = lueTiedosto(pA, tiedosto);

    CU_ASSERT_PTR_NOT_NULL(pA);
}


void test_kirjoitaTiedosto2() {
    // Testi-ID : AT-04
    // Testataan funktion kirjoitaTiedosto toiminen, kun valinta on 2.
    SUKUNIMI *pA = NULL;
    char tiedosto[] = "testi_tiedosto.txt";

    pA = lisaaSolmu(pA, "TESTI", 1);
    kirjoitaTiedosto(pA, tiedosto, 2);

    FILE *fp = fopen(tiedosto, "r");
    CU_ASSERT_PTR_NOT_NULL(fp);
    if (fp != NULL) {
        fclose(fp);
    }
}


/* void test_pitkaNimi() {
    // Testi-ID : AT-06
    // Testataan solmun luontia liian pitkällä nimellä

    SUKUNIMI *pA = NULL;
    char cPitkaNimi[70] = "TämäOnErittäinPitkäSukunimiJokaylittääSallitunRa";

    pA = lisaaSolmu(pA, cPitkaNimi, 1);
    if (pA != NULL && strlen(pA->aSukunimi) < 20) {
        printf("test_pitkaNimi onnistui.\n");
    } else {
        printf("test_pitkaNimi epäonnistui.\n");
    }

    ###### Tämä testaus ei toiminut, mutta käsin blackboxilla, ohjelma vain jättää liian pitkän
    ###### nimen huomioimatta.
} */


void test_suorituskyky() {
    // Testi-ID : BT-02
    // Testataan suorituskykyä suurella tiedostolla (100 000 riviä)

    SUKUNIMI *pA = NULL;
    clock_t alku, loppu;
    double dKesto;

    char cIsoTiedosto[] = "isotiedosto.txt";
    char cTulosteTiedosto[] = "tyhja.txt";

    // Testataan tiedoston lukuaika
    alku = clock();
    pA = lueTiedosto(pA, cIsoTiedosto);
    loppu = clock();
    dKesto = ((double)(loppu - alku)) / CLOCKS_PER_SEC;
    printf("LueTiedosto: %.3f sekuntia\n", dKesto);

    // Testataan tiedoston kirjoitusaika
    alku = clock();
    kirjoitaTiedosto(pA, cTulosteTiedosto, 2);
    loppu = clock();
    dKesto = ((double)(loppu - alku)) / CLOCKS_PER_SEC;
    printf("KirjoitaTiedosto: %.3f sekuntia\n", dKesto);

}

void test_vaihto() {
    // Testi ID : AT-08
    // Testataan vaihtofunktion toimivuus

    SUKUNIMI a = {1, "TESTI"};
    SUKUNIMI b = {2, "ITSET"};
    vaihto(&a, &b);

    CU_ASSERT(a.iMaara == 2);
    CU_ASSERT(b.iMaara == 1);
    CU_ASSERT_STRING_EQUAL(a.aSukunimi, "ITSET");
    CU_ASSERT_STRING_EQUAL(b.aSukunimi, "TESTI");
}

void test_vaihtoTyhjaNimi() {
    // Testi ID : AT-09
    // Testataan vaihtofunktion toimivuus tyhjällä nimellä

    SUKUNIMI a = {1, "TESTI"};
    SUKUNIMI b = {2, ""};
    vaihto(&a, &b);

    assert(a.iMaara == 2);
    assert(b.iMaara == 1);
    assert(strcmp(a.aSukunimi, "") == 0);
    assert(strcmp(b.aSukunimi, "TESTI") == 0);
    
    printf("test_vaihtoTyhjaNimi onnistui.\n");
}

void test_listaNULL() {
    // Testi ID : AT-10
    // Testataan sort funktiota NULL osoittimilla.
    
    SUKUNIMI* test_NULL = NULL;
    quickSort(test_NULL, test_NULL);

    printf("test_listaNULL onnistui.\n");
}

void test_viimeinenSolmu() {
    // Testi-ID : AT-11
    // Testataan viimeisen solmun löytämistä
    SUKUNIMI a = {1, "Norppa"};
    SUKUNIMI b = {1, "Lehtonen"};
    a.pSeuraava = &b;

    CU_ASSERT_PTR_EQUAL(viimeinenSolmu(&a), &b);
}

void test_osio() {
    // Testi-ID : AT-12
    // Testataan osiofunktiota
    SUKUNIMI a = {1, "Norppa"};
    SUKUNIMI b = {2, "Lehtonen"};
    SUKUNIMI c = {3, "Kellomäki"};
    a.pSeuraava = &b;
    b.pSeuraava = &c;

    SUKUNIMI *pivot = osio(&a, &c);

    CU_ASSERT(pivot->iMaara == 3);
    CU_ASSERT_STRING_EQUAL(pivot->aSukunimi, "Kellomäki");
}

void test_quickSort() {
    // Testi-ID : AT-13
    // Testataan quickSort funktiota
    SUKUNIMI a = {3, "Norppa"};
    SUKUNIMI b = {1, "Lehtonen"};
    SUKUNIMI c = {2, "Kellomäki"};
    a.pSeuraava = &b;
    b.pSeuraava = &c;

    SUKUNIMI *pV = viimeinenSolmu(&a);
    quickSort(&a, pV);

    CU_ASSERT(a.iMaara == 1);
    CU_ASSERT_STRING_EQUAL(a.aSukunimi, "Lehtonen");
    CU_ASSERT(b.iMaara == 2);
    CU_ASSERT_STRING_EQUAL(b.aSukunimi, "Kellomäki");
    CU_ASSERT(c.iMaara == 3);
    CU_ASSERT_STRING_EQUAL(c.aSukunimi, "Norppa");
}

void test_mergeSort() {
    // Testi-ID : AT-14
    // Testataan mergeSort-funktion toimivuus
    SUKUNIMI *pA = NULL;
    pA = lisaaSolmu(pA, "D", 3);
    pA = lisaaSolmu(pA, "A", 3);
    pA = lisaaSolmu(pA, "C", 4);
    pA = lisaaSolmu(pA, "B", 2);

    pA = mergeSort(pA);

    while (pA != NULL && pA->pSeuraava != NULL) {
        CU_ASSERT(pA->iMaara >= pA->pSeuraava->iMaara);
        if (pA->iMaara == pA->pSeuraava->iMaara) {
            CU_ASSERT(strcmp(pA->aSukunimi, pA->pSeuraava->aSukunimi) > 0);
        }
        pA = pA->pSeuraava;
    }
}

void test_jaaLista() {
    // Testi-ID : AT-15
    // Testataan jaaLista-funktion toimivuus
    SUKUNIMI *pA = NULL;
    SUKUNIMI *pB = NULL;
    pA = lisaaSolmu(pA, "A", 1);
    pA = lisaaSolmu(pA, "B", 2);
    pA = lisaaSolmu(pA, "C", 3);
    pA = lisaaSolmu(pA, "D", 4);
    pA = lisaaSolmu(pA, "E", 5);
    pA = lisaaSolmu(pA, "F", 6);

    pB = jaaLista(pA);

    CU_ASSERT_STRING_EQUAL(pA->aSukunimi, "A");
    CU_ASSERT_STRING_EQUAL(pA->pSeuraava->pSeuraava->aSukunimi, "C");

    CU_ASSERT_STRING_EQUAL(pB->aSukunimi, "D");
    CU_ASSERT_STRING_EQUAL(pB->pSeuraava->pSeuraava->aSukunimi, "F");
}

void test_luoNode() {
    // Testi-ID : AT-16
    // Testataan Noden luomista.

    NODE* pNode = luoNode("Test", 10);
    CU_ASSERT_PTR_NOT_NULL(pNode);
    CU_ASSERT_STRING_EQUAL(pNode->aSukunimi, "Test");
    CU_ASSERT_EQUAL(pNode->iMaara, 10);
    CU_ASSERT_PTR_NULL(pNode->vasen);
    CU_ASSERT_PTR_NULL(pNode->oikea);
    free(pNode);
}

void test_lisaaNode() {
    // Testi-ID : AT-17
    NODE *pJuuri = NULL;
    pJuuri = lisaaNode(pJuuri, "C", 3);
    pJuuri = lisaaNode(pJuuri, "A", 2);
    pJuuri = lisaaNode(pJuuri, "B", 2);
    pJuuri = lisaaNode(pJuuri, "D", 4);
    
    NODE* tulos = binaariHaku(pJuuri, 3);
    CU_ASSERT_PTR_NOT_NULL(tulos);
    CU_ASSERT_STRING_EQUAL(tulos->aSukunimi, "C");
    tulos = binaariHaku(pJuuri, 2);
    CU_ASSERT_PTR_NOT_NULL(tulos);
    tulos = binaariHaku(pJuuri, 4);
    CU_ASSERT_PTR_NOT_NULL(tulos);
    CU_ASSERT_STRING_EQUAL(tulos->aSukunimi, "D");
    vapautaMuisti(pJuuri);
}


void test_muistiVapautus() {
    // Testi-ID : AT-18
    // Testataan muistinvapautukset
    NODE* pJuuri = NULL;
    pJuuri = lisaaNode(pJuuri, "A", 1);
    pJuuri = lisaaNode(pJuuri, "B", 2);
    pJuuri = lisaaNode(pJuuri, "C", 3);
    pJuuri = lisaaNode(pJuuri, "D", 4);
    pJuuri = lisaaNode(pJuuri, "E", 5);
    pJuuri = lisaaNode(pJuuri, "F", 6);

    vapautaMuisti(pJuuri);

    pJuuri = NULL;

    vapautaMuisti (pJuuri);
}


void test_poistaJonostaTyhja() {
    // Testi-ID : AT-19
    // Testataan poistaJonosta toimintaa

    // Tyhjän jonon poisto
    Jono* jono = uusiJono();
    NODE* tulos = poistaJonosta(jono);
    CU_ASSERT_PTR_NULL(tulos);
    vapautaJono(jono);
}

void test_syvyysHaku() {
    // Testi-ID : AT-20
    // Testataan syvyysHaku-funktion toimivuus

    NODE* pJuuri = NULL;
    char tiedosto[] = "testi_tiedosto.txt";
    char rivi[50] = "";
    pJuuri = lisaaNode(pJuuri, "C", 3);
    pJuuri = lisaaNode(pJuuri, "B", 2);
    pJuuri = lisaaNode(pJuuri, "D", 4);
    pJuuri = lisaaNode(pJuuri, "E", 5);
    pJuuri = lisaaNode(pJuuri, "A", 1);
    pJuuri = lisaaNode(pJuuri, "F", 6);
    freopen("testiSyote.txt", "r", stdin); // Luetaan syötteet tiedostosta
    syvyysHaku(pJuuri, tiedosto, 3);
    FILE* testiTiedosto = fopen("testi_tiedosto.txt", "r");
    CU_ASSERT_PTR_NOT_NULL(testiTiedosto);

    while(fgets(rivi, sizeof(rivi), testiTiedosto)) {} // Luetaan tiedoston loppuun

    CU_ASSERT_STRING_EQUAL(rivi, "D,4\n"); // Tarkastetaan, että viimeinen rivi on etsitty arvo
    fclose(testiTiedosto);
}

void test_haeKorkeus() {
    // Testi-ID : AT-21
    // Testataan haeKorkeus funktio

    NODE *n = luoNode("Testi", 5);
    CU_ASSERT_EQUAL(haeKorkeus(n), 1);
    
    n->iKorkeus = 3;
    CU_ASSERT_EQUAL(haeKorkeus(n), 3);
    
    vapautaMuisti(n);
}

void test_oikeaRotate() {
    // Test ID: AT-22
    // Testataan oikea kääntö

    NODE *y = luoNode("y", 1);
    NODE *x = luoNode("x", 1);
    NODE *T2 = luoNode("T2", 1);

    y->vasen = x;
    x->oikea = T2;

    NODE *n = oikeaRotate(y);

    CU_ASSERT_PTR_EQUAL(n, x);
    CU_ASSERT_PTR_EQUAL(x->oikea, y);
    CU_ASSERT_PTR_EQUAL(y->vasen, T2);

    CU_ASSERT_EQUAL(haeKorkeus(T2), 1);
    CU_ASSERT_EQUAL(haeKorkeus(y), 2);
    CU_ASSERT_EQUAL(haeKorkeus(x), 3);

}

void test_vasenRotate() {
    // Test ID: AT-23
    // Testataan vasen kääntö

    NODE *x = luoNode("x", 1);
    NODE *y = luoNode("y", 1);
    NODE *T2 = luoNode("T2", 1);

    x->oikea = y;
    y->vasen = T2;

    NODE *n = vasenRotate(x);

    CU_ASSERT_PTR_EQUAL(n, y);
    CU_ASSERT_PTR_EQUAL(y->vasen, x);
    CU_ASSERT_PTR_EQUAL(x->oikea, T2);

    CU_ASSERT_EQUAL(haeKorkeus(T2), 1);
    CU_ASSERT_EQUAL(haeKorkeus(x), 2);
    CU_ASSERT_EQUAL(haeKorkeus(y), 3);

}

void test_haeTasapaino_null() {
    // Test ID: AT-24
    // Testataan tasapainon haku NULL-pointterista

    CU_ASSERT_EQUAL(haeTasapaino(NULL), 0);
}

void test_binaariHaku() {
    // Test ID: AT-25
    // Testataan, että binääri haku toimii oikein
    int iEtsittavaMaara = 10;
    NODE* pJuuri = luoNode("A", 5);
    pJuuri->vasen = luoNode("B", 3);
    pJuuri->oikea = luoNode("C", 8);
    pJuuri->oikea->oikea = luoNode("D", 10);
    pJuuri->oikea->vasen = luoNode("E", 6);

    pJuuri = binaariHaku(pJuuri, iEtsittavaMaara);
    CU_ASSERT_EQUAL(pJuuri->iMaara, 10);
}

void test_pieninArvo() {
    // Testi-ID: AT-26
    // Testataan pienimmän arvon hakua
    NODE* pJuuri = NULL;
    pJuuri = lisaaNode(pJuuri, "C", 3);
    pJuuri = lisaaNode(pJuuri, "B", 2);
    pJuuri = lisaaNode(pJuuri, "D", 4);
    pJuuri = lisaaNode(pJuuri, "E", 5);
    pJuuri = lisaaNode(pJuuri, "A", 1);
    pJuuri = lisaaNode(pJuuri, "F", 6);

    NODE* pienin = pieninArvoNode(pJuuri);

    CU_ASSERT_PTR_NOT_NULL(pienin);
    CU_ASSERT_EQUAL(pienin->iMaara,1);
}

void test_poistaSolmu() {
    // Testi-ID: AT-27
    // Testataan solmun poisto

    Graph* pGraph = luoGraafi(4);

    pGraph->nimiHakemisto[0] = strdup("A");
    pGraph->nimiHakemisto[1] = strdup("B");
    pGraph->nimiHakemisto[2] = strdup("C");
    pGraph->nimiHakemisto[3] = strdup("D");

    lisaaKaari(pGraph, "A", "B", 5);
    lisaaKaari(pGraph, "B", "C", 5);
    lisaaKaari(pGraph, "C", "D", 5);

    int idxA = haeIndeksi(pGraph, "A");
    CU_ASSERT_PTR_NOT_NULL(pGraph);
    CU_ASSERT_NOT_EQUAL(idxA, -1);
    poistaSolmu(pGraph, "A");
    CU_ASSERT_EQUAL(haeIndeksi(pGraph, "A"),-1);
}

void test_luoGraafi() {
    // Testi-ID AT-28
    // Testataan graafin luonti

    Graph* pGraph = luoGraafi(4);
    
    CU_ASSERT_PTR_NOT_NULL(pGraph);
    if (pGraph) {
        CU_ASSERT_EQUAL(pGraph->iV, 4);
        CU_ASSERT_PTR_NOT_NULL(pGraph->array);
        CU_ASSERT_PTR_NOT_NULL(pGraph->nimiHakemisto);
        
        // Tarkistetaan, että naapurilista alustettu oikein
        for (int i = 0; i < pGraph->iV; i++) {
            CU_ASSERT_PTR_NULL(pGraph->array[i].head);
        }
    }
}

void test_luoAdjNode() {
    // Testi-ID AT-29
    // Testataan solmun luontia

    Node* node = luoAdjNode(2, "Test", 0);

    CU_ASSERT_PTR_NOT_NULL(node);
    if (node) {
        CU_ASSERT_EQUAL(node->iDest, 2);
        CU_ASSERT_STRING_EQUAL(node->aNimi, "Test");
        CU_ASSERT_EQUAL(node->iValimatka, 0);
        CU_ASSERT_PTR_NULL(node->next);
    }
    
    free(node->aNimi);
    free(node);
}

void test_lisaaKaari() {
    // Testi-ID: AT-30
    // Testataan kaaren lisäystä ja kaksisuuntaisuutta
    
    Graph* pGraph = luoGraafi(2);
    pGraph->nimiHakemisto[0] = strdup("A");
    pGraph->nimiHakemisto[1] = strdup("B");
    
    // Lisää kaari solmujen A ja B välille, etäisyys 5
    lisaaKaari(pGraph, "A", "B", 5);

    // Tarkistetaan solmun A naapuri
    CU_ASSERT_PTR_NOT_NULL(pGraph->array[0].head);
    if (pGraph->array[0].head) {
        CU_ASSERT_EQUAL(pGraph->array[0].head->iDest, 1);
        CU_ASSERT_STRING_EQUAL(pGraph->array[0].head->aNimi, "B");
        CU_ASSERT_EQUAL(pGraph->array[0].head->iValimatka, 5);
    }

    // Tarkistetaan solmun B naapuri
    CU_ASSERT_PTR_NOT_NULL(pGraph->array[1].head);
    if (pGraph->array[1].head) {
        CU_ASSERT_EQUAL(pGraph->array[1].head->iDest, 0);
        CU_ASSERT_STRING_EQUAL(pGraph->array[1].head->aNimi, "A");
        CU_ASSERT_EQUAL(pGraph->array[1].head->iValimatka, 5);
    }

    // Vapautetaan muisti
    vapautaGraafi(pGraph);
}


void test_luoAdjNodeNimiTyhja() {
    // Testi-ID: AT-31
    // Testataan luoAdjNode funktiota tyhjällä nimellä

    Node* node = luoAdjNode(1, "", 0);
    CU_ASSERT_PTR_NOT_NULL(node);
    CU_ASSERT_STRING_EQUAL(node->aNimi, "");
    CU_ASSERT_EQUAL(node->iDest, 1);
    CU_ASSERT_EQUAL(node->iValimatka, 0);
    CU_ASSERT_PTR_NULL(node->next);


}

void test_haeIndeksiNimi() {
    // Testi-ID: AT-32
    // Testataan haeIndeksi-funktiota kun haettavaa nimeä ei ole olemassa

    Graph* graph = luoGraafi(2);
    graph->nimiHakemisto[0] = strdup("A");
    graph->nimiHakemisto[1] = strdup("B");

    int idx = haeIndeksi(graph, "C");
    CU_ASSERT_EQUAL(idx, -1);

    vapautaGraafi(graph);

}

void test_vapautaGraafiNull() {
    // Testi-ID: AT-33
    // Testataan vapautaGraafi-funktion toimintaa NULL-osoittimella

    Graph* pGraph = NULL;
    vapautaGraafi(pGraph); // Ei saa kaatua
}

void test_pieninArvoNodeYksiSolmu() {
    // Testi-ID: AT-34
    // Testataan pieninArvoNode-funktiota kun puussa on vain yksi solmu

    NODE* pNode = luoNode("Testi", 1);
    NODE* pienin = pieninArvoNode(pNode);

    CU_ASSERT_PTR_EQUAL(pienin, pNode);
    vapautaMuisti(pNode);
}

void test_binaariHakuEiOlemassa() {
    // Testi-ID: AT-35
    // Testataan binaariHaun toimintaa, kun arvoa ei löydy

    NODE* pJuuri = NULL;
    pJuuri = lisaaNode(pJuuri, "A", 1);
    pJuuri = lisaaNode(pJuuri, "B", 2);

    NODE* tulos = binaariHaku(pJuuri, 10); // Ei pitäisi löytyä
    CU_ASSERT_PTR_NULL(tulos);

    vapautaMuisti(pJuuri);

}
