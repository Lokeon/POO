
#include "clave.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>

Clave::Clave(const char* s)
{
	char* salt = new char [2] ;
	const char* encrypt = "adcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789" ; 


	if(strlen(s) < 5 )
	{
		throw Clave::Incorrecta(CORTA) ; 	
	}
	
	salt[0] = encrypt[rand() % 64] ;
	salt[1] = encrypt[rand() % 64] ;

	if(crypt(s,salt) == NULL)
	{
		throw Clave::Incorrecta(ERROR_CRYPT) ; 
	}

	cifrada_ = crypt(s,salt) ; 
}


bool Clave::cifrada(const char* s)
{
	return crpyt(s,fail_.c_str()) ; 
}