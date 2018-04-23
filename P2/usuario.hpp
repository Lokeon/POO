#ifndef USUARIO_HPP
#define USUARIO_HPP



#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include <unistd.h>


/********************** CLAVE ************************************/



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

/********************** USUARIO ************************************/

class Usuario
{

public:

	Usuario

	Usuario(const Usuario& A) = delete ; 



private:

	Cadena id_, nombre_, apellidos_, direccion_ ; 
	Clave password_ ; 
	Tarjeta tarjetas_ ; 
	Articulo articulos_ ; 

}



#endif //USUARIO_HPP