
#include <ostream>
#include "articulo.hpp"


std::ostream& operator <<(std::ostream& os, const Articulo& B)
{
	os << "[" << B.referencia() << "] \""<< B.titulo() << "," << B.f_publi().anno() <<"." << B.precio() << "€" ;

	return os ; 
}