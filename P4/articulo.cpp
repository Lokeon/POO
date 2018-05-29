
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


std::ostream& operator <<(std::ostream& os, const Articulo& B)
{
	os << "[" << B.referencia() << "] \""<< B.titulo() << ", de";

	Articulo::Autores::const_iterator pos ;

	for(pos = B.autores().begin(); pos != B.autores().end() ; pos++)
	{
		  os << (*pos)->apellidos() << "," << (*pos)->nombre() <<".";
	}

  int anno = B.f_publi().anno() ;

	os << anno << ". " << std::fixed << std::setprecision(2) << B.precio() << " €"
		 << std::endl ;

	B.impresion_especifica(os) ;

	 return os ;
}

void Libro::impresion_especifica(std::ostream& os) const
{
		os << "\t" << n_pag_ << " págs.," << stock_ << " unidades." << std::endl ;
}

void Cederron::impresion_especifica(std::ostream& os) const
{
		os << "\t" << tam_ << " MB, " << stock_ << " unidades." << std::endl ;
}

void LibroDigital::impresion_especifica(std::ostream& os) const
{
		os << "\t" <<"A la venta hasta el" << f_expir_ <<" ." << std::endl ;
}
