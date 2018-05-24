#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <set>



class Autor
{
public:

	Autor(const Cadena& nom,const Cadena& apell, const Cadena& dir): nom_(nom),
				apell_(apell),dir_(dir) {}

	const Cadena& nombre() const { return nom_;}
	const Cadena& apellidos() const { return apell_ ;}
	const Cadena& direccion() const  { return dir_;}

private:

	Cadena nom_;
	Cadena apell_;
	Cadena dir_ ;

};


class Articulo
{
public:

	typedef std::set<Autor*> Autores ;

	class Autores_vacios {} ;

Articulo(const Autores& aut ,const Cadena& r, const Cadena& t, const Fecha& fp,
				double p);


	virtual void impresion_especifica(std::ostream& os) const  = 0 ;



	Cadena referencia() const ;
	Cadena titulo() const ;
	Fecha f_publi() const ;
	double precio() const ;
	double& precio() ;
	const Autores& autores() const { return aut_;};

	virtual ~Articulo() ;

protected:

	Cadena cod_referencia_ ;
	Cadena titulo_ ;
	Fecha fec_pub_ ;
	double precio_ ;
	Autores aut_ ;

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


std::ostream& operator <<(std::ostream& os, const Articulo& a);

	//////////////// JERARQUIA DE HERENCIA /////////////////



class LibroDigital: public Articulo
{

public:

	LibroDigital(const Autores& aut ,const Cadena& r, const Cadena& t,
		const Fecha& fp, double p, const Fecha& fexp):
		Articulo(aut,r,t,fp,p),f_expir_(fexp) {}

	void impresion_especifica(std::ostream& os) const ;

	const Fecha& f_expir() const { return f_expir_ ; }

private:

	const Fecha f_expir_ ;

};



class ArticuloAlmacenable: public Articulo
{
public:

	ArticuloAlmacenable(const Autores& aut, const Cadena& r, const Cadena& t,
		const Fecha& fp, double p, unsigned stock = 0): Articulo(aut,r,t,fp,p),
		stock_(stock) {}

		unsigned stock() const {return stock_ ; }
		unsigned& stock() {return stock_ ; }

protected:
		unsigned stock_ ;

};

class Libro: public ArticuloAlmacenable
{
public:

	Libro(const Autores& aut, const Cadena& r, const Cadena& t,const Fecha& fp,
		   double p, unsigned pag, unsigned stock = 0):
			 ArticuloAlmacenable(aut,r,t,fp,p,stock),n_pag_(pag) {}

	void impresion_especifica(std::ostream& os) const ;

	const unsigned n_pag() const { return n_pag_  ;}

private:

	const unsigned n_pag_ ;

};


class Cederron: public ArticuloAlmacenable
{

public:

	Cederron(const Autores& aut, const Cadena& r, const Cadena& t,const Fecha& fp,
		   double p, unsigned tam, unsigned stock = 0):
			 ArticuloAlmacenable(aut,r,t,fp,p,stock),tam_(tam) {}

	const unsigned tam() const { return tam_ ;}

	void impresion_especifica(std::ostream& os) const ;

private:

	const unsigned tam_ ;

};









#endif // ARTICULO_HPP
