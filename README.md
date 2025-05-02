# Tiimi 04 - Ohjelmakehitys C-kielellä
Tämä projekti on osa **CT60A2600 Ohjelmakehitys C-kielellä** -kurssia, jossa toteutimme monipuolisen ohjelman, joka sisältää linkitettyjen listojen, binääripuiden ja graafien käsittelyä. Ohjelma tarjoaa käyttäjälle mahdollisuuden suorittaa erilaisia toimintoja, kuten tiedostojen lukemista ja kirjoittamista, tietorakenteiden järjestämistä ja lyhimmän reitin laskemista graafissa.

# Miten ohjelma on toteutettu
**Käytetyt teknologiat:** C-kieli, CUnit-kirjasto

Ohjelma koostuu useista moduuleista, jotka on jaettu eri tiedostoihin:

- **Linkitetyt listat:** Toteutettu tiedostossa **Kärjasto.**, sisältää toimintoja, kuten tiedostojen lukeminen ja listan lajittelu.  
- **Binääripuut:** Toteutettu tiedostossa **BinaryTree.c**, sisältää AVL-puun toteutuksen ja hakuoperaatiot.  
- **Graafit:** Toteutettu tiedostossa **Graph.c**, sisältää graafien käsittelyä, kuten lyhimmän reitin laskeminen Dijkstran algoritmilla.  

Ohjelma käyttää myös **CUnit-kirjastoa** yksikkötestaukseen, jolla varmistetaan ohjelman eri osien toimivuus.

## Optimoinnit:

Ohjelman suorituskykyä on parannettu seuraavilla tavoilla:

- **Muistin tehokas hallinta:** Kaikki dynaamiset tietorakenteet, kuten linkitetyt listat ja graafft, vapautetaan käytön jälkeen.  
- **Algoritmien optimointi:** Binääripuun tasapainotus AVL-puuna takaa tehokkaat haku- ja lisäysoperaatiot. Graafien lyhimmän reitin laskenta hyödyntää Dijkstran algoritmia.  
- **Testaus:** Yksikkötestit kattavat ohjelman keskeiset toiminnot, mikä vähentää virheiden mahdollisuutta.  

# Esimerkkejä:
Tässä muutamia esimerkkejä ohjelman toiminnallisuuksista

- **Binääripuun tulostus puumaisessa muodossa:**

><pre> |-10 (Smith)<br>
>    |-5 (Johnson)<br>
>    |-15 (Brown)</pre>

- **Graafin tulostus:**
> A: -> B -> C<br>
> B: -> A -> D<br>
> C: -> A -> D<br>
> D: -> B -> C

- **Lyhimmän reitin laskenta:**
> A -> B -> D = 7


# Opitut asiat:
Tämän projektin aikana opimme paljon C-kielen tehokkaasta käytöstä ja tietorakenteiden toteutuksesta. Erityisesti seuraavat asiat nousivat esiin:

- Dynaamisten tietorakenteiden, kuten linkitettyjen listojen, binääripuiden ja graafien, toteutus ja hallinta.
- Algoritmien, kuten lajittelun ja lyhimmän reitin laskennan, implementointi ja optimointi.
- Yksikkötestauksen merkitys ohjelman laadun varmistamisessa.