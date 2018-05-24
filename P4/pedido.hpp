#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <utility>
#include <iomanip>
#include <iostream>
#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"


class Pedido_Articulo;
class Usuario_Pedido;


class Pedido
{

public:

	Pedido(Usuario_Pedido& userped, Pedido_Articulo& pedart, Usuario& user,
		     const Tarjeta& tar, const Fecha& f = Fecha() );


	int numero() const { return num_ ;}

	const Tarjeta* tarjeta() const {return tarjeta_ ;}

	Fecha fecha() const { return fecha_;}

	double total() const { return total_;}

	static int n_total_pedidos() ;



	class Vacio
	{

	public:

	Vacio(Usuario* us):user_(us) {}

	Usuario& usuario() const { return *user_ ;} ;

	private:

	Usuario* user_;

	};


	class Impostor
	{
	public:

	Impostor(Usuario* us):user_(us) {}

	Usuario& usuario() const { return *user_ ; };

	private:

	Usuario* user_ ;
	};

	class SinStock
	{

	public:

	SinStock(Articulo* art):ar_(art) {}

	Articulo& articulo() const { return *ar_ ;} ;

	private:

	Articulo* ar_ ;

	};

private:

int num_ ;
const Tarjeta* tarjeta_ ;
Fecha fecha_ ;
double total_ ;
static int num_pedido_ ;

};



std::ostream& operator << (std::ostream& os, const Pedido& ped);
































































#endif //PEDIDO_HPP
