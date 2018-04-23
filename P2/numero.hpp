
#include "../cadena.hpp"
#include <algorithm>
#include <string>


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