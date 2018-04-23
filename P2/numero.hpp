
#include "../cadena.hpp"


class Numero
{
public:

const enum Razon {LONGITUD, DIGITOS, NO_VALIDO} ;

Numero(const Cadena& num) ; // me falta hacer lo del luhn raro 

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


}

bool operator <(const Numero& A, const Numero& B) ; 

inline Razon Numero::Incorrecto::razon() const
{
	return fail_ ; 
}