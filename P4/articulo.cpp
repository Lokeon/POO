
#include <ostream>
#include <iomanip>
#include "articulo.hpp"

Articulo::Articulo(const Autores& aut ,const Cadena& r, const Cadena& t,
	const Fecha& fp,double p):cod_referencia_(r), titulo_(t),fec_pub_(fp),
				precio_(p),aut_(aut)
{

	if(aut_.empty())
	{
		throw Autores_vacios{} ;
	}

}


std::ostream& operator <<(std::ostream& os, const Articulo& B) noexcept
{
	os << "[" << B.referencia() << "] \""<< B.titulo() << "\", de ";

	Articulo::Autores::const_iterator pos = B.autores().begin() ;

	os << (*pos)->apellidos();

	for(++pos; pos != B.autores().end() ; ++pos)
	{
		 os << ", " << (*pos)->apellidos()  ;
	}

	os << ". " ;

	os <<  B.f_publi().anno() << ". " << std::fixed << std::setprecision(2)
	   <<  B.precio() << " €\n\t";

	B.impresion_especifica(os) ;

	 return os ;
}

void Libro::impresion_especifica(std::ostream& os) const noexcept
{
		os  << n_pag_ << " págs., " << stock_<< " unidades." ;
}

void Cederron::impresion_especifica(std::ostream& os) const noexcept
{
		os << tam_ << " MB, " << stock_ << " unidades." ;
}

void LibroDigital::impresion_especifica(std::ostream& os) const noexcept
{
		os <<"A la venta hasta el " << f_expir_ <<"." ;
}
