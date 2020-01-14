#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// struktur definieren
typedef struct Product {
	char Bez[50];
	double Preis;
	double Gewicht;
	struct Product* pNext;
	struct Product* pPrev;
} struProduct;

// Funktionsdefinitionen
Product* createList(int AnzahlElemente);

Product* deleteAll(Product* pHead);

Product* deleteElement(Product* pHead, char* Bezeichnung);

void printList(Product* Node, int AnzahlElemente);

Product* bubbleSort(Product* Node, int SortProperty);

char getRandUpperCaseChar();

int getRandomNumber();

int getListLength(Product* Node);

// Enis Hoti
void main() {
	int menu;
	struProduct* Node = NULL;
	do {
		printf("1 - Liste erstellen\n");
		printf("2 - Liste ausgeben\n");
		printf("3 - Liste löschen\n");
		printf("4 - Bestimmtes Element aus Liste löschen\n");
		printf("5 - Liste sortiert ausgeben\n");
		printf("0 - Programm beenden");
		printf("\n");
		scanf_s("%i", &menu);

		switch (menu) {
		case 0:
			printf("Programm wird beendet");
			exit(0);
		case 1:
			system("cls");
			printf("Anzahl Elemente eingeben: \t");
			int Anzahl; scanf_s("%i", &Anzahl);
			Node = createList(Anzahl);
			system("cls");
			break;
		case 2:
			system("cls");
			printf("Anzahl an Elementen zu ausgeben 0 = alle: \t\n");
			int AnzElemente; scanf_s("%i", &AnzElemente);
			printf("Gewicht");
			printf("\t");
			printf("Preis");
			printf("\t");
			printf("Bezeichnung");
			printList(Node, AnzElemente);
			break;
		case 3:
			deleteAll(Node);
			system("cls");
			break;
		case 4:
			system("cls");
			printf("Bezeichnung von Element eingeben: \t");
			char Bezeichnung[40]; scanf_s("%s", Bezeichnung, sizeof(Bezeichnung)); // gets_s(Bezeichnung); // scanf("%s", &Bezeichnung);
			Node = deleteElement(Node, Bezeichnung);
			system("cls");
			break;
		case 5:
		{
			system("cls");
			printf("Nach was sortieren? 1 - Gewicht | 2 - Preis | 3 - Bezeichnung\n");
			int sortAfterField; scanf_s("%i", &sortAfterField);
			clock_t start = clock();
			if (sortAfterField == 1) {
				Node = bubbleSort(Node, sortAfterField);
			}
			else if (sortAfterField == 2) {
				Node = bubbleSort(Node, sortAfterField);
			}
			else if (sortAfterField == 3) {
				Node = bubbleSort(Node, sortAfterField);
			}
			clock_t end = clock();
			int ListLength = getListLength(Node);
			long float ms = end - start;
			printf("Sortieren für Liste von Länge %i hat %lf Millisekunden gedauert\n", ListLength, ms);
			break;
		}
		}
	} while (menu != 0);


	system("pause");
}

// Löschfunktionen


// David Peric
Product* deleteElement(Product* pHead, char* Bezeichnung) {
	struProduct* pTemp = pHead->pPrev;
	do {
		if (strcmp(pTemp->Bez, Bezeichnung) == 0) {
			struProduct* bTemp = pTemp->pPrev;
			struProduct* aTemp = pTemp->pNext;
			bTemp->pNext = pTemp->pNext;
			aTemp->pPrev = pTemp->pPrev;
			// erstes Element in Liste
			if (pTemp == pHead) {
				pHead = aTemp;
			}
			// Speicherblock befreien
			free(pTemp);
			pTemp = aTemp;
		}
		else {
			pTemp = pTemp->pNext;
		}
	} while (pTemp != pHead->pPrev);
	return pHead;
}

// Enis Hoti
Product* deleteAll(Product* pHead) {
	while (pHead->pPrev != pHead) {
		struProduct* pTemp = pHead->pPrev;
		pHead->pPrev = pTemp->pPrev;
		free(pTemp);
	}
	free(pHead);
	return NULL;

}

// Erstellen der Liste

// David Peric
Product* createList(int AnzahlElemente) {
	// Pointers für Erstellung von Liste definieren und Speicher reservieren
	struProduct* pHead = NULL;
	struProduct* pLast = NULL;
	struProduct* pNew = NULL;
	for (int i = 0; i < AnzahlElemente; i++) {
		struProduct* pNew = (struProduct*)malloc(sizeof(struProduct));
		pNew->Bez[0] = getRandUpperCaseChar();
		pNew->Bez[1] = '\0';
		pNew->Preis = getRandomNumber(); // rand() % 100;
		pNew->Gewicht = getRandomNumber();

		if (i == 0) {
			// erstes Element
			pHead = pNew;
			pNew->pNext = pNew;
			pNew->pPrev = pNew;
		}
		else {
			pNew->pNext = pHead;
			pHead->pPrev->pNext = pNew;
			pNew->pPrev = pHead->pPrev;
			pHead->pPrev = pNew;
		}
	}
	return pHead;

}

// Ausgabe von Liste

// David Peric
void printList(Product* Node, int AnzahlElemente = NULL) {
	// Count entspricht, den Anzahl an Elementen in der Liste
	int count = 0;
	struProduct* pTemp = Node;
	do {
		// Wenn AnzahlElemente 0 entspricht, werden alle Elemente angezeigt, sonst, soviele, wie viele man angegeben hat
		if (!AnzahlElemente) {
			printf("\n");
			printf("%f", pTemp->Gewicht);
			printf(" KG");
			printf("\t");
			printf("%f", pTemp->Preis);
			printf(" CHF");
			printf("\t");
			printf(pTemp->Bez);
			printf("\n");
			pTemp = pTemp->pNext;
		}
		else {
			count++;
			if (count == AnzahlElemente + 1) {
				break;
			}
			printf("\n");
			printf("%f", pTemp->Gewicht);
			printf(" KG");
			printf("\t");
			printf("%f", pTemp->Preis);
			printf(" CHF");
			printf("\t");
			printf(pTemp->Bez);
			printf("\n");
			pTemp = pTemp->pNext;
		}
	} while (pTemp != Node);
}

// Sortierung

// David Peric
Product* bubbleSort(Product* Node, int SortProperty) {
	int swapped; // Variable zum Prüfen ob Pointer getauscht
	struProduct* pLeft = Node;
	struProduct* pRight = Node->pNext;

	// Switch case für Property machen 1 = Gewicht 2 = Preis 3 = Bez (strlen brauchen zum vergleichen)

	do {
		swapped = 0;
		while (pLeft->pNext != Node) {
			if (pLeft->Preis > pRight->Preis) {
				if (pLeft == Node) {
					Node = pRight;
				}
				struProduct* pTemp = pLeft->pPrev;
				// Pointer tauschen
				pLeft->pNext = pRight->pNext;
				pLeft->pPrev = pRight;
				pLeft->pNext->pPrev = pLeft;

				pRight->pNext = pLeft;
				pRight->pPrev = pTemp;
				pTemp->pNext = pRight;
				// swapped auf 1 setzen
				swapped = 1;
			}
			pLeft = pRight;
			pRight = pLeft->pNext;
		}
		pLeft = pRight;
		pRight = pLeft->pNext;
	} while (swapped);
	if (SortProperty == 1) {
		do {
			swapped = 0;
			while (pLeft->pNext != Node) {
				if (pLeft->Gewicht > pRight->Gewicht) {
					if (pLeft == Node) {
						Node = pRight;
					}
					struProduct* pTemp = pLeft->pPrev;

					pLeft->pNext = pRight->pNext;
					pLeft->pPrev = pRight;
					pLeft->pNext->pPrev = pLeft;

					pRight->pNext = pLeft;
					pRight->pPrev = pTemp;
					pTemp->pNext = pRight;
					swapped = 1;
				}
				pLeft = pRight;
				pRight = pLeft->pNext;
			}
			pLeft = pRight;
			pRight = pLeft->pNext;
		} while (swapped);
	}
	else if (SortProperty == 2) {
		do {
			swapped = 0;
			while (pLeft->pNext != Node) {
				if (pLeft->Preis > pRight->Preis) {
					if (pLeft == Node) {
						Node = pRight;
					}
					struProduct* pTemp = pLeft->pPrev;

					pLeft->pNext = pRight->pNext;
					pLeft->pPrev = pRight;
					pLeft->pNext->pPrev = pLeft;

					pRight->pNext = pLeft;
					pRight->pPrev = pTemp;
					pTemp->pNext = pRight;
					swapped = 1;
				}
				pLeft = pRight;
				pRight = pLeft->pNext;
			}
			pLeft = pRight;
			pRight = pLeft->pNext;
		} while (swapped);
	}
	else if (SortProperty == 3) {
		do {
			swapped = 0;
			while (pLeft->pNext != Node) {
				if (strlen(pLeft->Bez) > strlen(pRight->Bez)) {
					if (pLeft == Node) {
						Node = pRight;
					}
					struProduct* pTemp = pLeft->pPrev;

					pLeft->pNext = pRight->pNext;
					pLeft->pPrev = pRight;
					pLeft->pNext->pPrev = pLeft;

					pRight->pNext = pLeft;
					pRight->pPrev = pTemp;
					pTemp->pNext = pRight;
					swapped = 1;
				}
				pLeft = pRight;
				pRight = pLeft->pNext;
			}
			pLeft = pRight;
			pRight = pLeft->pNext;
		} while (swapped);
	}
	return Node;
}



// Zufallsgeneratoren

// Enis Hoti
char getRandUpperCaseChar() {
	// Gibt zufälligen Grossbuchstaben von den Buchstaben nach dem Wert 65 in ASCII
	return (char)(rand() % 26 + 65);
}

// Enis Hoti
int getRandomNumber() {
	// Gibt zufällige Zahl zwischen 0 und 100 zurück
	return rand() % 100;
}

// Sonstige funktionen

// Enis Hoti
int getListLength(Product* Node) {
	// Gibt die Länge der Liste zurück
	int count = 1;
	struProduct* pTemp = Node;
	while (pTemp->pNext != Node) {
		pTemp = pTemp->pNext;
		count++;
	}
	return count;
}

