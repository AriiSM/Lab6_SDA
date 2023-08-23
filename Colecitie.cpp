#include"IteratorColectie.h"
#include"Colectie.h"
#include <exception>
#include <iostream>
#include <climits>
#define NIL INT_MIN //indica o locatie libera in memorie
#define STERS INT_MIN+10
using namespace std;



//Theta(1)
//Funcția de dispersie care returnează valoarea hash a elementului 
int hasdCode(TElem e) {
	return abs(e); //modilul numarului
}



//Theta(1)
// Funcția de dispersie care returnează valoarea
//hash a elementului e
int Colectie::d(TElem e, int i) //dispersia dubla
{
	unsigned long c1, c2;
	c1 = hasdCode(e) % m;  //prima dispersie
	c2 = (1 + hasdCode(e) % (m - 2)) % m; // a doua dispersie
	
	return int((c1 + (i * c2) % m) % m);
}



//Theta(m)
Colectie::Colectie()
{
	m = MAXIM;//initializam m cu o valoare predefinita

	e = new TElem[m];//alocam spatiu de memeorie pt vectorul de elemente
	//se marcheaza pozitiile din tabela ca fiin libere
	for (int i = 0; i < m; i++) {
		e[i] = NIL;
	}
}



//Theta(nr)
// Funcția de dispersie care returnează valoarea hash a elementului e
int prim(int nr) {
	if (nr <= 1 || nr % 2 == 0)
		return 0;
	for (int d = 3; d * d <= nr; d = d + 2)
		if (nr % d == 0)
			return 0;
	return 1;
}



//Caz fav: Theta(m)
//Caz defavorabil:Theta(m^2)
//Caz total:O(m^2)

//Metodă care redimensionează tabela de dispersie
//în cazul în care capacitatea sa este depășită.
void Colectie::redim()
{
	int mv = m;
	m = m + 2;
	while (!prim(m))
		m = m + 2;
	//alocam un spatiu de capacitate dubla
	TElem* eNou = new int[m];
	TElem* copie = new int[mv];

	//copiem vechile valori in zona nou auziliara
	for (int i = 0; i < mv; i++) {
		copie[i] = e[i];
	}

	//initializam noul vector
	for (int i = 0; i < m; i++) {
		eNou[i] = NIL;
	}

	//eliberam vechea zona 
	delete[] e;

	//vectorul indica spre noua locatie
	e = eNou;

	//redimensionam capacitatea din tabela
	for (int i = 0; i < mv; i++) {
		adauga(copie[i]);
	}

	delete[] copie;
}



//Caz fav: Theta(m)
//Caz defavorabil:Theta(m^2)-redimensionare
//Caz total:O(m^2)
void Colectie::adauga(TElem el)
{
	//locatia de dispersie a cheii
	int i = 0; //nr de verificare
	bool gasit = false;
	//repetam pana gasim un loc liber pentru a adauga elementul
	do {
		//se calculeaza dispersia pt elementul el
		int j = d(el, i); 
		if (e[j] == NIL || e[j] == STERS) {
			e[j] = el;
			gasit = true;
		}
		else i++;
	} while (i<m && !gasit);

	//În cazul în care se depășește capacitatea tabelei de dispersie, se realizează redimensioneaza
	if (i == m) {
		//depasire tabela
		redim();
		adauga(el);
	}
}



//Caz fav: Theta(1)
//Caz defavorabil:Theta(m)
//Caz total:O(m)
bool Colectie::sterge(TElem el)
{
	int i = 0;
	bool gasit=false;
	//repetă pașii până când se găsește poziția în tabela de dispersie
	do {
		//se calculeaza dispersia pt elementul el
		int j = d(el, i);
		//verificam daca exista acest element in tabela
		if (e[j] == NIL)
			break;
		//daca exista il stergem
		if (e[j] == el) {
			e[j] = STERS;
			gasit = true;
		}
		else i++;
	} while (i < m && !gasit);
	return gasit;
}



//Caz fav: Theta(1)
//Caz defavorabil:Theta(m)
//Caz total:O(m)
bool Colectie::cauta(TElem el)
{
	int i = 0;
	bool gasit = false;
	//repetă pașii până când se găsește poziția în tabela de dispersie
	do {
		//se calculeaza dispersia pt elementul el
		int j = d(el, i);
		//verificam daca exista elementul
		if (e[j] == NIL)
			return false;
		//daca exista margam bool-ul
		if (e[j] == el) {
			gasit = true;
		}
		else i++;
	} while (i < m && !gasit);
	return gasit;	
}



//Theta(m)
int Colectie::nrAparitii(TElem el) const
{
	int nrAparitii = 0;
	for (int i = 0; i < m; i++)
		if (e[i] == el)
			nrAparitii++;
	return nrAparitii;
	
}



//Theta(m)
//!Redo- cu o variabila globala
int Colectie::dim() const
{
	int nrElem = 0;
	for (int i = 0; i < m; i++)
		if (e[i] != NIL && e[i] != STERS)
			nrElem++;
	return nrElem;
}



//Theta(m)
bool Colectie::vida() const
{
	if (dim() == 0)
		return true;
	return false;
}



//Theta(1)
IteratorColectie Colectie::iterator() const
{
	return IteratorColectie(*this);
}



//Theta(1)
Colectie::~Colectie()
{
	delete[] e;
}



//Theta(m)
int Colectie::diferentaMaxMin() const
{
	int min = 999999, max = -9999999;
	if (vida())
		return -1;
	for (int i = 0; i < m; i++)
		if (e[i] != NIL && e[i] != STERS) {
			{
				if (e[i] < min)
					min = e[i];
				if (e[i] > max)
					max = e[i];
			}
		}
	return max - min;
}