
#include "numero.hpp"
#include <iostream> 
#include <cstring>

	

bool luhn(const Cadena& numero) ;


Numero::Numero(const Cadena& num)
{

	Cadena::const_iterator t = num.begin() ; 
	
	unsigned cdig = 0 ;


	while(t != num.end())
	{
		if(t != ' ')
		{
			if(t < 48 || t > 57)
			{
				throw Numero::Incorrecto(DIGITOS) ; 
			}
			else
			{
				cdig ++ ; 
			}
		}

	}	
		if(cdig < 13 || cdig > 19)
		{
			throw Numero::Incorrecto(LONGITUD) ; 
		}

	



}









bool operator <(const Numero& A , const Numero& B)
{

	return strcmp(A.c_str(),B.c_str()) < 0  ; 

}

Numero::operator const char*() const
{
	return numero_.c_str() ; 
}