#include"IteratorColectie.h"
#include"Colectie.h"
#include<exception>

#define NIL INT_MIN

//Caz fav: Theta(1)
//Caz defavorabil:Theta(m)
//Caz total:O(m)
//este folosită pentru a avansa iteratorul la următorul element valid din colecție
void IteratorColectie::deplasare()
{
	while ((curent < col.m) && col.e[curent] == NIL)
		curent++;
}



//Caz fav: Theta(1)
//Caz defavorabil:Theta(m)
//Caz total:O(m)
//initializează iteratorul
IteratorColectie::IteratorColectie(const Colectie& c) :col(c)
{
	curent = 0;
	deplasare();
}



//Caz fav: Theta(1)
//Caz defavorabil:Theta(m)
//Caz total:O(m)
//repoziționează iteratorul la începutul colecției
void IteratorColectie::prim()
{
	//se determina prima locatie ocupata
	curent = 0;
	deplasare();
}



//Caz fav: Theta(1)
//Caz defavorabil:Theta(m)
//Caz total:O(m)
//avansează iteratorul la următorul element
void IteratorColectie::urmator()
{
	if (!valid())
		throw std::exception();
	curent++;
	deplasare();
}



//Theta(1)
//verifică dacă iteratorul este într-o poziție validă în colecție.
bool IteratorColectie::valid()const
{
	return(curent < col.m);
}



//Theta(1)
//eturnează elementul curent din colecție la care este poziționat iteratorul
TElem IteratorColectie::element() const
{
	if (!valid())
		throw std::exception();
	return col.e[curent];
}