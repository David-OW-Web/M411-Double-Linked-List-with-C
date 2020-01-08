#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Product* deleteElement(Product* pHead, Product* pDel, char* Bezeichnung);

void printList(Product* Node, int AnzahlElemente);

void bubbleSort(Product* Node)

char getRandUpperCaseChar();

int getRandomNumber();


void main() {
	int menu;
	struProduct* Node = NULL;
	do {
		printf("1 - Liste erstellen\n");
		printf("2 - Liste ausgeben\n");
		printf("3 - Liste l�schen\n");
		// printf("4 - Pr�fen ob Liste existiert\n");
		printf("4 - Bestimmtes Element aus Liste l�schen\n");
		printf("5 - Liste sortiert ausgeben\n");
		printf("10 - Konsole leeren\n");
		printf("20 - Tests\n");
		printf("0 - Programm beenden");
		printf("\n");
		scanf_s("%i", &menu);

		switch (menu) {
		case 0:
			printf("Programm wird beendet");
			exit(0);
		case 1:
			printf("Anzahl Elemente eingeben: \t");
			int Anzahl; scanf_s("%i", &Anzahl);
			Node = createList(Anzahl);
			break;
		case 2:
			printf("Anzahl an Elementen zu ausgeben: \t\n");
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
			printf("Bezeichnung von Element eingeben: \t");
			char Bezeichnung[40]; scanf_s("%s", Bezeichnung, sizeof(Bezeichnung)); // gets_s(Bezeichnung); // scanf("%s", &Bezeichnung);
			deleteElement(Node, Node, Bezeichnung);
			break;
		case 10:
			system("cls");
			break;
		case 20:
			printf("String eingeben:\t");
			printf("\n");
			char String[10]; scanf_s("%s", String, sizeof(String));
			printf("%s", String);
			printf("\n");
			printf("%i", sizeof(Node));
			printf("\n");
		}
	} while (menu != 0);


	system("pause");
}

// L�schfunktionen

Product* deleteElement(Product* pHead, Product* pDel, char* Bezeichnung) {
	struProduct* pTemp = pHead->pPrev;
	do {
		if (strcmp(pTemp->Bez, Bezeichnung) == 0) {
			struProduct* bTemp = pTemp->pPrev;
			struProduct* aTemp = pTemp->pNext;
			bTemp->pNext = pTemp->pNext;
			aTemp->pPrev = pTemp->pPrev;
			if (pTemp == pHead) {
				pHead = aTemp;
			}
			free(pTemp);
			pTemp = aTemp;
		}
		else {
			pTemp = pTemp->pNext;
		}
	} while (pTemp->pNext != pHead);
	return NULL;
}

Product* deleteAll(Product* pHead) {
	// tmp entspricht der Node
	while (pHead->pPrev != pHead) {
		struProduct* pTemp = pHead->pPrev;
		pHead->pPrev = pTemp->pPrev;
		free(pTemp);
	}
	free(pHead);
	return NULL;

}

// Erstellen der Liste

Product* createList(int AnzahlElemente) {
	// struProduct* pHead = NULL; Pointers f�r Erstellung von Liste definieren und Speicher reservieren
	struProduct* pHead = (struProduct*)malloc(sizeof(struProduct));
	struProduct* pLast = NULL;
	struProduct* pNew = NULL;
	for (int i = 0; i < AnzahlElemente; i++) {
		if (i == 0) {
			pHead->Bez[0] = getRandUpperCaseChar();
			pHead->Bez[1] = '\0';
			pHead->Preis = getRandomNumber(); // rand() % 100;
			pHead->Gewicht = getRandomNumber();
			pHead->pNext = pHead;
			pHead->pPrev = pHead;
		}
		pLast = pHead->pPrev;
		// Speicher reservieren
		pNew = (struProduct*)malloc(sizeof(struProduct));
		// pHead = pHead->pNext;
		pHead->pPrev = pNew;
		pLast->pNext = pNew;
		pNew->pPrev = pLast;
		pNew->pNext = pHead;
		pNew->Gewicht = getRandomNumber();
		pNew->Bez[0] = getRandUpperCaseChar();
		pNew->Bez[1] = '\0';
		pNew->Preis = getRandomNumber();
	}
	return pHead;
}

// Ausgabe von Liste

void printList(Product* Node, int AnzahlElemente = NULL) {
	int count = 0;
	struProduct* pTemp = Node;
	while (pTemp->pNext != Node) {
		if (!AnzahlElemente) {
			printf("\n");
			printf("%f", pTemp->Gewicht);
			printf("\t");
			printf("%f", pTemp->Preis);
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
			printf("\t");
			printf("%f", pTemp->Preis);
			printf("\t");
			printf(pTemp->Bez);
			printf("\n");
			pTemp = pTemp->pNext;
		}
	}
}

// Sortierung

void bubbleSort(Product* Node) {
	int swapped, i;
	struProduct* pLeft = NULL;
	struProduct* pRight = NULL;

	do {
		swapped = 0;
		// pRight zu einem Wert zuweisen
		while (pRight->pNext != pLeft) {
			if (pRight->Bez > pRight->pNext->Bez) {
				// Swap pointers and set swapped to 1
			}
			pRight = pRight->pNext
		}
		pLeft = pRight;
	} while (swapped);
}



// Zufallsgeneratoren

char getRandUpperCaseChar() {
	/* Return a random of the 26 chars after the value of 65 in ASCII. */
	return (char)(rand() % 26 + 65);
}

int getRandomNumber() {
	return rand() % 100;
}

