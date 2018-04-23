
#include <iosteam>
#include "tarjeta.hpp"
#include "numero.hpp"
#include <iostream> 
#include <cstring>
#include <algorithm>
#include <string>


/*** LUHN **/

bool luhn(const Cadena& numero) ;

/********************** NUMERO ************************************/

Numero::Numero(const Cadena& num):numero_(mirar_longitud(num))  
{

	while(!numero_.end())
	{
		if(numero_ < "0" || numero_ > "9")
		{
			throw Numero::Incorrecto(DIGITO) ; 
		}
	}

	if(!luhn(numero_))
	{
		throw Numero::Incorrecto(NO_VALIDO);
	}

}

Cadena Numero::quitar_espacio(const Cadena& A)
{
	Cadena aux (A) ; 

	remove_if(aux.begin(),aux.end()+1,[](char x){return isspace(x);});

	return Cadena(aux.c_str()) ; 

}


Cadena NUmero::mirar_longitud(const Cadena& A)
{
	

	Cadena aux = quitar_espacio(A) ; 

 	if(aux.length() < 13 || auz.length() > 19)
 	{
 		throw Numero::Incorrecto(LONGITUD) ; 
 	}

	return aux ; 
}


bool operator <(const Numero& A , const Numero& B)
{
	return strcmp(A,B ) < 0 ;  
}

Numero::operator const char*() const
{
	return numero_.c_str() ; 
}



/*********************** TARJETA *********************************/ 



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

	if(us_ != nullptr)
	{
		us_.no_es_titular(*this) ; 
	}

}




void Tarjeta::anular_titular()
{
	titular_ = nullptr ; 
}


bool Tarjeta::operator <(const Tarjeta& A, const Tarjeta& B)
{
	return A.numero() < B.numero() ; 
}


std::ofstream& operator << (std::ofstream& os, const Tarjeta& A) 
{

	os << A.tipo() << "\n"
	   << A.numero() << "\n"
	   << A.titular_facial_() << "\n" 
	   << "Caduca: " 
	   << setfill('0') << setw(2) 
	   <<A.caducidad().mes() 
	   << "/" 
	   << setw(2) 
	   << A.caducidad().anno() % 100 << "\n";

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