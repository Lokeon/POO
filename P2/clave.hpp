#ifndef CLAVE_HPP
#define CLAVE_HPP

#include <unistd.h>

class Clave
{

public:

Clave(const char* c) ; 

const enum Razon{CORTA, ERROR_CRYPT} ; 
Cadena clave() const ;
bool verifica(const char* c);


	class Incorrecta
	{
	public:

	Incorrecta(const Razon r ):fail_(r) {}
	Razon razon() const ;
	
	private:

	Razon fail_ ; 	

	}

	

private:

Cadena cifrada_ ; 


}


inline Cadena Clave::clave() const
{
	return cifrada_ ; 
}



inline Razon Clave::Incorrecta::razon() const
{
	return fail_ ; 
}




#endif //CLAVE_HPP