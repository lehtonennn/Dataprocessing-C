# Tekijä: Mikael Norppa, Lauri Lehtonen
# Päivämäärä: 27.04.2025

SRC_DIR = Projekti
TEST_DIR = Testi
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall

projekti: Projekti.o ProjektiKirjasto.o ProjektiKirjastoSort.o BinaryTree.o Graph.o
	$(CC) -o projekti Projekti.o ProjektiKirjasto.o ProjektiKirjastoSort.o BinaryTree.o Graph.o

Projekti.o: $(SRC_DIR)/Projekti.c $(SRC_DIR)/Kirjasto.h $(SRC_DIR)/Sort.h $(SRC_DIR)/BinaryTree.h $(SRC_DIR)/Graph.h
	$(CC) -c $(SRC_DIR)/Projekti.c $(CFLAGS)

ProjektiKirjasto.o: $(SRC_DIR)/ProjektiKirjasto.c $(SRC_DIR)/Kirjasto.h $(SRC_DIR)/Sort.h $(SRC_DIR)/BinaryTree.h $(SRC_DIR)/Graph.h
	$(CC) -c $(SRC_DIR)/ProjektiKirjasto.c $(CFLAGS)

ProjektiKirjastoSort.o: $(SRC_DIR)/ProjektiKirjastoSort.c $(SRC_DIR)/Sort.h $(SRC_DIR)/Kirjasto.h $(SRC_DIR)/BinaryTree.h $(SRC_DIR)/Graph.h
	$(CC) -c $(SRC_DIR)/ProjektiKirjastoSort.c $(CFLAGS)

BinaryTree.o: $(SRC_DIR)/BinaryTree.c $(SRC_DIR)/BinaryTree.h $(SRC_DIR)/Graph.h
	$(CC) -c $(SRC_DIR)/BinaryTree.c $(CFLAGS)

Graph.o: $(SRC_DIR)/Graph.c $(SRC_DIR)/Graph.h
	$(CC) -c $(SRC_DIR)/Graph.c $(CFLAGS)

# Unit test build rule
test:
	$(CC) -I$(SRC_DIR) -o testi $(SRC_DIR)/ProjektiKirjasto.c $(TEST_DIR)/ProjektiTestiKirjasto.c $(SRC_DIR)/ProjektiKirjastoSort.c $(SRC_DIR)/BinaryTree.c $(SRC_DIR)/Graph.c $(CFLAGS) -lcunit
clean:
	rm -f *.o projekti testi