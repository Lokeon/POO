#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo
{
public:

Articulo(const Cadena& r, const Cadena& t, const Fecha& fp, const double p, const unsigned s):
	cod_referencia_(r), titulo_(t),
	fec_pub_(fp), precio_(p), stock_(s)  {}
																							 
Cadena referencia() const ; 
Cadena titulo() const ; 
Fecha f_publi() const ;
double precio() const ; 
double& precio() ; 
unsigned stock() const ; 
unsigned& stock() ;

 
private:

Cadena cod_referencia_ ; 
Cadena titulo_ ; 
Fecha fec_pub_ ; 
double precio_ ; 
unsigned stock_ ; 


};



inline Cadena Articulo::referencia() const
{
	return cod_referencia_ ; 
}

inline Cadena Articulo::titulo() const
{
	return titulo_;
}

inline Fecha Articulo::f_publi() const
{
	return fec_pub_ ; 
}

inline double Articulo::precio() const
{
	return precio_ ; 
}

inline double& Articulo::precio() 
{
	return precio_ ; 
}

inline unsigned Articulo::stock() const
{
	return stock_ ; 
}

inline unsigned& Articulo::stock()
{
	return stock_ ; 
}


std::ostream& operator <<(std::ostream& os, const Articulo& a);


#endif // ARTICULO_HPP