
#ifndef TARJETA_HPP
#define TARJETA_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <ostream>
#include "usuario.hpp"

class Usuario;


/********************** NUMERO ************************************/

class Numero
{
public:

enum Razon {LONGITUD, DIGITOS, NO_VALIDO} ;

Numero(const Cadena& num) ; 

operator const char*() const; 

friend bool operator <(const Numero& A, const Numero& B) ; 
	
	class Incorrecto
	{
	public:

	Incorrecto(Razon r):fail_(r) {}

	Razon razon() const { return fail_ ;}; 

	private:

	Razon fail_ ;
	
	};

private:

Cadena numero_ ; 

Cadena quitar_espacio(const Cadena& A) ;

Cadena mirar_longitud(const Cadena& A) ; 

 };





/*********************** TARJETA *********************************/ 



class Tarjeta
{

public:

 enum Tipo {VISA, Mastercard, Maestro, JCB, AmericanExpress} ;


/* CONSTRUCTORES */

Tarjeta(Tipo t, const Numero& n, Usuario& us, const Fecha& f) ; 
Tarjeta (const Tarjeta& A) = delete ; 


/* OPERADORES */

Tarjeta& operator =(const Tarjeta& A) = delete ; 

void anular_titular() ; 

/* OBSERVADORES */

Tipo tipo() const {return tipo_ ; };

Numero numero() const {return num_ ;} ;

const Usuario* titular () const {return us_ ;} ;
 
Fecha caducidad() const { return caducidad_ ;}  ; 

Cadena titular_facial() const { return titular_facial_; } ; 


~Tarjeta() ;   


class Caducada{

	public:

	Caducada(const Fecha& f):f_(f) {} 

	const Fecha& cuando() const { return f_; } 

	private:

	Fecha f_ ; 	

	};




private:

Tipo tipo_ ; 
Numero num_ ; 
const Usuario* us_ ; 
Fecha caducidad_ ;
Cadena titular_facial_ ; 

};


bool operator < (const Tarjeta& A, const Tarjeta& B) ; 
std::ostream& operator << (std::ostream& os, const Tarjeta& A) ; 
std::ostream& operator << (std::ostream& os, const Tarjeta::Tipo& tipo) ;





#endif //TARJETA_HPP 