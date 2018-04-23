
#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"
#include <ostream>

class Usuario ; 


/********************** NUMERO ************************************/

class Numero
{
public:

const enum Razon {LONGITUD, DIGITOS, NO_VALIDO} ;

Numero(const Cadena& num) ; 

operator const char*() const; 

	
	class Incorrecto
	{
	public:

	Incorrecto(Razon r):fail_(r) {}

	Razon razon() const ; 

	private:

	Razon fail_ ;
	
	}

private:

Cadena numero_ ; 

Cadena quitar_espacio(const Cadena& A) ;

Cadena mirar_longitud(const Cadena& A) ; 

}

bool operator <(const Numero& A, const Numero& B) ; 

inline Razon Numero::Incorrecto::razon() const
{
	return fail_ ; 
}

/*********************** TARJETA *********************************/ 

class Tarjeta
{

public:

const enum Tipo {Visa, Mastercard, Maestro, JCB, AmericanExpress} ;


/* CONSTRUCTORES */

Tarjeta(Tipo t, const Numero& n, Usuario& us, const Fecha& f) ; 
Tarjeta (const Tarjeta& A) = delete ; 


/* OPERADORES */

Tarjeta& operator =(const Tarjeta& A) = delete ; 




const Usuario* titular() const ; 


void anular_titular() ; 


	class Caducada{

	public:

	Caducada(const Fecha& f)f_(f);

	const Fecha& cuando(const Fecha& f) const { return f; } 

	private:

	Fecha f_ ; 	

	}

	/* OBSERVADORES */

Tipo tipo() const ;

Numero numero() const ;

Usuario* titular () const ;

Fecha caducidad() const ; 

Cadena titular_facial() const ; 


~Tarjeta() ;   

private:

Tipo tipo_ ; 
Numero num_ ; 
Usuario* const us_ ; 
Fecha caducidad_ ;
Cadena titular_facial_ ; 

}


bool operator < (const Tarjeta& A, const Tarjeta& B) ; 
std::ostream& operator << (std::ostream& os, const Tarjeta& A) ; 
std::ostream& operator << (std::ostream& os, const Tarjeta::Tipo& tipo) ;


inline Tarjeta::Tipo Tipo::tipo() const
{
	return tipo_ ; 
}

inline Numero Tarjeta::numero() const
{
	return num_ ; 
}

inline Usuario* Tarjeta::titular() const
{
	return us_ ; 
}

inline Fecha Tarjeta::caducidad() const
{
	return caducidad_ ; 
}

inline Cadena Tarjeta::titular_facial() const
{
	return titular_facial_ ; 
}



#endif //TARJETA_HPP 