
#include "numero.hpp"
#include <iostream> 
#include <cstring>

	

bool luhn(const Cadena& numero) ;


Numero::Numero(const Cadena& num):numero_(mirar_longitud(num)) // NO SE
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

	return strcmp(A.c_str(),B.c_str()) < 0  ; 

}

Numero::operator const char*() const
{
	return numero_.c_str() ; 
}