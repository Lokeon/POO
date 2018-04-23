
#include "../cadena.hpp"
#include "../fecha.hpp"
#include "usuario.hpp"
#include "numero.hpp"


class Usuario ; 

class Tarjeta
{

public:

const enum Tipo {Visa, Mastercard, Maestro, JCB, AmericanExpress} ;



Tarjeta(Tipo t, const Numero& n, Usuario& us, const Fecha& f) ; //Constructor 



Tarjeta& operator =(const Tarjeta& A) ; 


const Usuario* titular() const ; 

void anular_titular() ; 


	class Caducada{

	public:

	Caducada(const Fecha& f)f_(f);

	Fecha cuando(const Fecha& f) const { return f; } 

	private:

	Fecha f_ ; 	

	}




	// OBSERVADORES

Tipo tipo() const ;

Numero numero() const ;

const Usuario* titular () const ;

Fecha caducidad() const ; 

Cadena titular_facial() const ; 


~Tarjeta() ;  //Me falta destructor de los cojones 

private:

Tipo tipo_ ; 
Numero num_ ; 
const Usuario* us_ ; 
Fecha caducidad_ ;
Cadena titular_facial_ ; 

}


bool operator < (const Tarjeta& A, const Tarjeta& B) ; 
std::ostream& operator << (std::ostream& os, const Tarjeta& A) ; 
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& tipo) ;


inline Tarjeta::Tipo Tipo::tipo() const
{
	return tipo_ ; 
}

inline Numero Tarjeta::numero() const
{
	return num_ ; 
}

inline const Usuario* Tarjeta::titular() const
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

