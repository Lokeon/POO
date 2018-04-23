#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "clave.hpp"

/********************** CLAVE ************************************/

Clave::Clave(const char* s)
{
	char* salt = new char [2] ;
	const char* encrypt = "adcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789./" ; 

	srand()

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


bool Clave::verifica(const char* s)
{
	return crypt(s,cifrada_.c_str()) ; 

	// char* key = new char[13]
	// key = crypt(  . . .)
	// return (key	 == cifrada_)
}

/********************** USUARIO ************************************/