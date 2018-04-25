
#include "articulo.hpp"
#include <ostream>


std::ostream& operator <<(std::ostream& os, const Articulo& B)
{
	os << "[" << B.referencia() << "] \""<< B.titulo() << "," << B.f_publi().anno() <<"." << B.precio() << "€" ;

	return os ; 
}