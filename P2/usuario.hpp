#ifndef USUARIO_HPP
#define USUARIO_HPP

#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include <unordered_map>
#include <unordered_set>
#include <map>


/********************** CLAVE ************************************/

class Clave
{

public:

Clave(const char* c) ; 

enum Razon{CORTA, ERROR_CRYPT} ; 

Cadena clave() const ;

bool verifica(const char* c) const;


	class Incorrecta
	{
	public:

	Incorrecta(const Razon r ):fail_(r) {}
	Razon razon() const {return fail_ ; } ;
	
	private:

	Razon fail_ ; 	

	};

	

private:

Cadena cifrada_ ; 


};


inline Cadena Clave::clave() const
{
	return cifrada_ ; 
}


 

/********************** USUARIO ************************************/

class Tarjeta ; 
class Numero ;

class Usuario
{

public:

	typedef std::map<Numero, Tarjeta*> Tarjetas ; 

	typedef std::unordered_map<Articulo*, unsigned > Articulos ;

	typedef std::unordered_set<Cadena> Usuarios ; 

	Usuario(const Cadena& id, const Cadena& n, const Cadena& ap, const Cadena& dir, const Clave& c);

	Usuario(const Usuario& A) = delete ; 

	Usuario& operator =(const Usuario& A) = delete ; 

	
	Cadena id() const {return id_; };
	Cadena nombre() const {return nombre_ ; } ; 
	Cadena apellidos() const {return apellidos_; }; 
	Cadena direccion() const {return direccion_; }; 
	
	const Tarjetas& tarjetas() const {return tarjetas_ ;} ; 
	const Articulos& compra() const {return articulos_;} ;

	size_t n_articulos() const { return articulos_.size();};

	void compra(const Articulo& A, unsigned cantidad = 1);

	void es_titular_de(const Tarjeta& tar) ; 

	void no_es_titular_de(const Tarjeta& tar) ;

	friend std::ostream& mostrar_carro(std::ostream& os, const Usuario& U);
	friend std::ostream& operator << (std::ostream& os, const Usuario& U);


	~Usuario() ; 


	class Id_duplicado
	{
	public:

	Id_duplicado(const Cadena& cad):id_(cad) {}	

	const Cadena& idd() const { return id_; } ;

	private:

	Cadena id_ ; 

	};


private:

	Cadena id_, nombre_, apellidos_, direccion_ ; 
	Clave password_ ; 
	Tarjetas tarjetas_ ; 
	Articulos articulos_ ; 
	static Usuarios user_ ; 
	
};







#endif //USUARIO_HPP