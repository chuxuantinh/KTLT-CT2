//Faculty of Computer Science and Engineering
//Ho Chi Minh City University of Technology
//Initial code for Assignment- Programming Fundamentals
//Hoc vien: Chu Xuan Tinh -1870583
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <iostream>
#include <math.h>

using namespace std;
const int EVENT_SIZE = 1001;
const int MAX_CHARACTER_EACH_LINE = 5001;
//#define _CRT_SECURE_NO_WARNINGS
#define DARTAGNAN  1
#define ATHOS 2
#define PORTHOS 3
#define ARAMIS 4

typedef struct musketeer_t
{
	int ID;
	int HP; // the initial health point
	int nHealthPoint; // the current heath point
	int nGoldCoin; // the current number of gold coins   (Money)
	int nDiamond; // the current number of diamonds
}musketeer;


/*	Read input data from file
 *	Return value:
 *		0: fail
 *		1: successful
 */
char filename[80];

int readFile(musketeer* theMusketeer, int* M, int* N, int* nEvent, int arrEvent[])
{
	FILE* f = 0;

	char* str = (char*)malloc(MAX_CHARACTER_EACH_LINE);
	int start, len, num;

	f = fopen(filename, "r");
	if (f == NULL)
		return 0;

	//read M
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	*M = atoi(str);

	//read N
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	*N = atoi(str);

	//read ID
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	theMusketeer->ID = atoi(str);

	//read nGoldCoin
	fgets(str, MAX_CHARACTER_EACH_LINE, f);
	theMusketeer->nGoldCoin = atoi(str);

	//read nEvent, arrEvent
	*nEvent = 0;
	arrEvent[0] = 0;
    fgets(str, MAX_CHARACTER_EACH_LINE, f);

	char seps[]   = " ,\t\n";
    char *token;

    token = strtok( str, seps );
    while( token != NULL )
    {
        /* While there are tokens in "string" */
        arrEvent[*nEvent] = atoi(token);
        (*nEvent)++;
        /* Get next token: */
        token = strtok( NULL, seps );
    }

	fclose(f);

	free(str);

	return 1;
}

// chutinh add
bool Thang_GWS;

int Giam_HP(int Ei) {
	if (Thang_GWS)
	{
		return (Ei / 10);
	}
	return Ei;
}

// kiem tra so nguyen to nho hơn so nhap - gan nhat
bool isPrime(int n);
int findPrePrime(int n)
{
	int nextPrime = n;
	bool found = false;

	//loop
	while (!found)
	{
		nextPrime--;
		if (isPrime(nextPrime))
			found = true;
	}
	//cout << nextPrime;
	return nextPrime;
}

//kiem tra so nguyen to
bool isPrime(int n)
{
	//loop from 2 to n/2 to check
	for (int i = 2; i <= n / 2; i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

// user defined

int calculate(char fname[])
{
	musketeer theMusketeer;
	int M, N;
	int nEvent; // the number of events
	int arrEvent[EVENT_SIZE]; // used to save events
	int theEvent, nPassedEvent; // the current event and the number of passed events
	int nOut; // output value
	int i;

    strcpy(filename, fname);
	readFile(&theMusketeer, &M, &N, &nEvent, arrEvent);
	theMusketeer.nDiamond = 0;

	int maxHP;
	maxHP = theMusketeer.HP;
	//
	switch (theMusketeer.ID) {
		case DARTAGNAN: // d'Artagnan
			theMusketeer.HP = 999;
			theMusketeer.nHealthPoint = 999;
			break;
		case ATHOS: // Atho
			theMusketeer.HP = 900;
			theMusketeer.nHealthPoint = 900;
			break;
		case PORTHOS: // Porthos
			theMusketeer.HP = 888;
			theMusketeer.nHealthPoint = 888;
			break;
		case ARAMIS: // Aramis
			theMusketeer.HP = 777;
			theMusketeer.nHealthPoint = 777;
			break;
		default:
			break;
	}

	nPassedEvent = 0;
	//tinh add
	int h1, h2;
	bool Porthos_Win;
	int Ei; // xem lai cai nay
	int Count_Thang_Nina = 0;
	//
	while (1) {
		for (i = 0; i < nEvent; i++) {
			theEvent = arrEvent[i]; // case thu i

			switch (theEvent)
				// theEvent   ~ E[i]
			{
			case 0:
				theMusketeer.nDiamond++;
				break;
			case 1: // xem lai c, d
				if (PORTHOS == 3)
				{
					if  (theMusketeer.nGoldCoin > 1 && theMusketeer.nHealthPoint <= maxHP)
					{
						if (Count_Thang_Nina < 3)
						{
							theMusketeer.nHealthPoint += 1;
							theMusketeer.nGoldCoin = theMusketeer.nGoldCoin - 2;
						}
						else
						{
							theMusketeer.nHealthPoint = maxHP;
						}
					}
				}
				else
				{

					if (theMusketeer.nHealthPoint < maxHP && theMusketeer.nGoldCoin > 0)
					{
						if (Count_Thang_Nina < 3)
						{
							theMusketeer.nHealthPoint = theMusketeer.nHealthPoint + 1;
							theMusketeer.nGoldCoin--;

						}
						else
						{
							theMusketeer.nHealthPoint = maxHP;
						}
					}

				}

				break;

			case 100 ... 199:

				//int Ei;
				Ei = theEvent;
				h1 = i % 100;
				h2 = Ei % 100;

				//neu thang , so tien duoc cong them Ei, khong qua 999.
				if (h1 > h2)
				{
					theMusketeer.nGoldCoin += Ei;
					theMusketeer.nGoldCoin = (theMusketeer.nGoldCoin > 999) ? 999 : theMusketeer.nGoldCoin;
				}

				else if (h1 < h2)
					// thua -> giam Ei
				{
					theMusketeer.nHealthPoint = theMusketeer.nHealthPoint - Giam_HP(Ei);

				}
				else
				{
					// làm gi trong truong hop nay nhi?
					theMusketeer.nGoldCoin = theMusketeer.nGoldCoin;
					theMusketeer.nHealthPoint = theMusketeer.nHealthPoint;

				}
				// Xet truong hop dac biet
				switch (theMusketeer.ID) // max HP
				{

				case ATHOS: // thua, ve binh thang h2 >5
					if (h1 <h2 && h2 > theMusketeer.nGoldCoin && h2 > 5)
					{
						theMusketeer.nHealthPoint -= Giam_HP(Ei);
					}

					break ;  // return?
				case PORTHOS:
					if (Porthos_Win)
					{
						break; //return;
					}
					else
						break;

				}
				break;

			case 200 ... 299:
				Ei = theEvent;

				//cout << i <<endl;
				//cout << Ei <<endl;
				h1 = i % 100;
				h2 = Ei % 100;
				// neu thang so tien tang gap doi, thua giam 1/2
				if (h1 > h2)
				{
					theMusketeer.nGoldCoin *= 2;
					theMusketeer.nGoldCoin = (theMusketeer.nGoldCoin > 999) ? 999 : theMusketeer.nGoldCoin;
					Count_Thang_Nina = Count_Thang_Nina + 1;
				}
				else
				{
					theMusketeer.nGoldCoin = theMusketeer.nGoldCoin / 2;


				}
				//cout << Count_Thang_Nina;

				// neu thang tu 3 lan tro len ??
				break;
			case 300 ... 399:
				//cout << Thang_GWS;
				if (Thang_GWS) break;// Neu thang 1 lan Thang_GWS =1 , thi lan sau no bo tron
				Ei = theEvent;
				h1 = i % 100;
				h2 = Ei % 100;
				if (h1 > h2)

				{
					Thang_GWS = 1;

				}
				else
				{
					theMusketeer.nDiamond = 0;
				}
				break;
			// ok ssssssss

			case 500 ... 599:
				Ei = theEvent;
				h1 = i % 100;
				h2 = Ei % 100;
				if (h1 > h2)
				{
					if (PORTHOS)

						Porthos_Win = 1;
				}
				else
				{
					theMusketeer.nHealthPoint -= Giam_HP(Ei);

				}
				//Porthos luôn luôn chiến thắng khi gặp các Titan s- xem lai
				break;

			case 666:
				switch (theMusketeer.ID)
				{
				case DARTAGNAN:
					nOut = -1;
					// Ket thuc -> TH2;
					break;

				case ATHOS:
					theMusketeer.nGoldCoin = 999;
					break;
				case ARAMIS:
				case PORTHOS:
					theMusketeer.nHealthPoint = findPrePrime(theMusketeer.nHealthPoint);
					//cout << theMusketeer.nHealthPoint << endl;
					//cout << theEvent<< endl ;

					break;
				}
				break;

			default:
				break;
			}
			//if (theEvent == 0) // Gather Diamond
			//	theMusketeer.nDiamond++;
			///////////////////////
			// TO DO - Other Cases //
			///////////////////////

			//code here
			nPassedEvent++;
			if (theMusketeer.nDiamond >= N || theMusketeer.nHealthPoint <= 0 || i >= nEvent)
				break;
		}

		if (theMusketeer.nDiamond >= N || theMusketeer.nHealthPoint <= 0 || M == 0)
			break;
	}

	switch (M) {
		case 0: // Mode 0
			if (theMusketeer.nDiamond >= N)
				nOut = theMusketeer.nHealthPoint + theMusketeer.nGoldCoin;
				//nOut = theMusketeer.nGoldCoin;
			else if (theMusketeer.nHealthPoint <= 0)
				nOut = -1;
			else if (i >= nEvent)
				nOut = 0;
			break;
		////////////////////////
		// TO DO - Other Modes //
		////////////////////////
		default:
			break;
	}


	return nOut;
}
int main()
{
	//test so nguyen to
	//int input;
	//cout << "Nhap vao so can kiem tra: ";
	//cin >> input;
	//cout << "\nSo nguyen to truoc  " <<input  << " la " << findNextPrime(input) << ". \n";

	int nOut = calculate("input.txt");
	printf("%d\n", nOut);
	system("pause");
    return 1;
}

