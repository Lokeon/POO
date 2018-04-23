#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unistd.h>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include "../P1/cadena.hpp"
#include "usuario.hpp"
#include "articulo.hpp"

class Tarjeta ; 
class Numero ;

/********************** CLAVE ************************************/

class Clave
{

public:

Clave(const char* c) ; 

const enum Razon{CORTA, ERROR_CRYPT} ; 
Cadena clave() const ;
bool verifica(const char* c);


	class Incorrecta
	{
	public:

	Incorrecta(const Razon r ):fail_(r) {}
	Razon razon() const ;
	
	private:

	Razon fail_ ; 	

	}

	

private:

Cadena cifrada_ ; 


}


inline Cadena Clave::clave() const
{
	return cifrada_ ; 
}



inline Razon Clave::Incorrecta::razon() const
{
	return fail_ ; 
}

 

/********************** USUARIO ************************************/

class Usuario
{

public:

	typedef std::map<Numero, Tarjeta*> Tarjetas ; 

	typedef std::unordered_map<Articulo*, unsigned > Articulos ;

	typedef std::unordered_set <Cadena> Usuarios ; 

	Usuario(const Cadena& id, const Cadena& n, const Cadena& ap, const Cadena& dir, const Clave& c);

	Usuario(const Usuario& A) = delete ; 

	Usuario& operator =(const Usuario& A) = delete ; 

	
	Cadena id() const ;
	Cadena nombre() const ; 
	Cadena apellidos() const ; 
	Cadena direccion() const ; 
	const Tarjetas& tarjetas() const ; 
	const Articulos& compra() const ; 
	size_t n_articulos() const ;




	void comprar(const Articulo& A, unsigned cantidad);

	void es_titular(const Tarjeta& tar) ; 

	void no_es_titular(const Tarjeta& tar) ;

	friend std::ofstream& operator << (std::ofstream& os, const Usuario& user) ;


	~Usuario() ; 


	class Id_duplicado
	{
	public:

	Id_duplicado(const Cadena& cad):id_(cad) {}	

	const Cadena& idd() const { return id_ } ;

	private:

	Cadena id_ ; 

	}


private:

	Cadena id_, nombre_, apellidos_, direccion_ ; 
	Clave password_ ; 
	Tarjetas tarjetas_ ; 
	Articulos articulos_ ; 
	static Usuarios user_ ; 

}


inline Cadena Usuario::id() const 
{
	return id_ ;
}

inline Cadena Usuario::nombre() const 
{
	return nombre_ ; 
}

inline Cadena Usuario::apellidos() const 
{
	return apellidos_ ; 
}

inline Cadena Usuario::direccion() const
{
	return direccion_ ; 
}

inline const Tarjetas& Usuario::tarjetas() const
{
	return tarjetas_ ;
}

inline const Articulos& Usuario::compra() const
{
	return articulos_ ; 
}

inline size_t Usuario::n_articulos() const
{
	return tarjetas_.size() ; 
}



 
	





#endif //USUARIO_HPP