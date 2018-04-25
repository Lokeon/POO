
#include "tarjeta.hpp"
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cstring>

/*** LUHN **/

bool luhn(const Cadena& numero) ;

/********************** NUMERO ************************************/

Numero::Numero(const Cadena& num):numero_(mirar_longitud(num))  
{

	while(!numero_.end())
	{
		if(numero_ < "0" || numero_ > "9")
		{
			throw Incorrecto(Razon::DIGITOS) ; 
		}
	}

	if(!luhn(numero_))
	{
		throw Incorrecto(Razon::NO_VALIDO);
	}

}

Cadena Numero::quitar_espacio(const Cadena& A)
{
	Cadena aux (A) ; 

	std::remove_if(aux.begin(),aux.end()+1,[](char x){return isspace(x);});

	return Cadena(aux.c_str()) ; 

}


Cadena Numero::mirar_longitud(const Cadena& A)
{
	

	Cadena aux = quitar_espacio(A) ; 

 	if(aux.length() < 13 || aux.length() > 19)
 	{
 		throw Incorrecto(Razon::LONGITUD) ; 
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



Tarjeta::Tarjeta(Tipo t, const Numero& n, Usuario& us, const Fecha& f):tipo_(t), num_(n), us_(nullptr), caducidad_(f)
{

	if (caducidad_ < Fecha())
	{
		throw Caducada(caducidad_) ; 
	}

	us.es_titular_de(*this);
	titular_facial_ = us.nombre() + " "+ us.apellidos();

}



Tarjeta::~Tarjeta()
{

	if(Usuario* us = const_cast<Usuario*&>(us_) )
	{
		us_->no_es_titular_de(*this) ; 
	}

}




void Tarjeta::anular_titular()
{
	const_cast<Usuario*&>(us_)  = nullptr ; 
}


bool operator <(const Tarjeta& A, const Tarjeta& B)
{
	return A.numero() < B.numero() ; 
}


std::ostream& operator << (std::ostream& os, const Tarjeta& A) 
{

	os << A.tipo() << "\n"
	   << A.numero() << "\n"
	   << A.titular_facial() << "\n" 
	   << "Caduca: " 
	   << std::setfill('0') << std::setw(2) 
	   <<A.caducidad().mes() 
	   << "/" 
	   << std::setw(2) 
	   << A.caducidad().anno() % 100 << "\n";

	return os ; 

}

std::ostream& operator << (std::ostream& os ,const Tarjeta::Tipo& tipo)
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