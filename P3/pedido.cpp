
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"


int Pedido::num_pedido_ = 0 ; 

int Pedido::n_total_pedidos()
{
	return num_pedido_ ; 
}

Pedido::Pedido(Usuario_Pedido& userped, Pedido_Articulo& pedart, Usuario& user,const Tarjeta& tar,const Fecha& f):num_(num_pedido_ + 1),tarjeta_(&tar)
																												 ,fecha_(f), total_(0)
{

	if(user.n_articulos() == 0)
	{
		throw Vacio(user) ; 
	}
	
	if(tar.titular() != &user)
	{
		throw Impostor(user) ; 
	}

	if(tar.caducidad() < f)
	{
		throw Tarjeta::Caducada(tar.caducidad()) ; 
	}

	for(auto pos = user.compra().begin(); pos != user.compra().end(); pos++)
	{
		if((pos->second) > (pos->first)->stock())
		{
			const_cast<Usuario::Articulos&>(user.compra()).clear() ; // quitamos el const para poder usar clear() 

			throw SinStock(pos->first) ; 
		}
	}

	Usuario::Articulos carro = user.compra() ; 

	for( auto pos = carro.begin(); pos!= carro.end(); pos++)
	{

		Articulo* pa = (pos->first) ; 

		unsigned int cantidad = pos-> second ;

		double precio = pa->precio() ; 

		
		pa->stock() -= cantidad ; 

		pedart.pedir(*this,*pa,total_,cantidad);

		total_ += cantidad * precio ; 

		user.compra(*pa,0) ; 
	}


	userped.asocia(user,*this) ;

	++num_pedido_ ;  

}



std::ostream& operator << (std::ostream& os, const Pedido& ped)
{
	os << "Núm. pedido:" << ped.numero() << std::endl ; 
	os << "Fecha:" << ped.fecha() << std::endl; 
	os << "Pagado con:" << *ped.tarjeta() << std::endl ; 
	os << "Importe:" << std::fixed << std::setprecision(2) << ped.total() << "€"; 

	return os ; 
}