
#include <iosteam>
#include "tarjeta.hpp"


Tarjeta::Tarjeta(Tipo t, const Numero& n, Usuario& us, const Fecha& f):tipo_(t), num_(n), titular_(&us), caducidad_(f)
{

	Fecha actual ;

	if (caducidad_ < actual)
	{
		throw Tajeta::Caducada(caducidad_) ; 
	}

	us.es_titular(*this);

	titular_facial_ = us.apellidos();
	titular_facial_ += ' ' ;
	titular_facial_ += us.nombre() ; 

}



Tarjeta::~Tarjeta()
{

}




void Tarjeta::anular_titular()
{
	titular_ = nullptr ; 
}


bool Tarjeta::operator <(const Tarjeta& A, const Tarjeta& B)
{
	return A.numero() < B.numero() ; 
}


std::ofstream& operator << (std::ofstream& os, const Tarjeta& A) // arreglar esto
{

	os << A.tipo() << A.numero() << A.titular_facial_() << "Caduca: " << setfill('0') << setw(2) <<A.caducidad().mes() << "/" << setw(2) << A.caducidad().anno() % 100 ;

	return os ; 

}

std::ofstream& operator << (std::ofstream& os ,const Tarjeta::Tipo& tipo)
{

	switch(tipo)
	{
		case 0: os << "VISA" ; break ; 
		case 1: os << "Mastercard"; break ; 
		case 2: os << "Maestro"; break ; 
		case 3: os << "JCB" ; break ; 
		case 4: os << "AmericanExpress" ; break ; 
		
		default: os << "Tarjeta no Identificada"; break ; 
	}

	return os ; 

}