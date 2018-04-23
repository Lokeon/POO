
#include "articulo.hpp"
#include <iostream>


std::osteam& operator <<(std::ostream& os, const Articulo& B)
{
	os << "[" << B.referencia() << "] \""<< B.titulo()"," << B.f_publi().anno()"." << B.precio()"€" ;

	return os ; 
}