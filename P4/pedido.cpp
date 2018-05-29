
#include <stdexcept>
#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"


int Pedido::num_pedido_ = 0 ;

int Pedido::n_total_pedidos()
{
	return num_pedido_ ;
}

Pedido::Pedido(Usuario_Pedido& userped, Pedido_Articulo& pedart, Usuario& user,
	       const Tarjeta& tar,const Fecha& f):num_(num_pedido_ + 1),tarjeta_(&tar)
			   ,fecha_(f), total_(0)
{

	if(user.n_articulos() == 0)
	{
		throw Vacio(&user) ;
	}

	if(tar.titular() != &user)
	{
		throw Impostor(&user) ;
	}

	if(tar.caducidad() < f)
	{
		throw Tarjeta::Caducada(tar.caducidad()) ;
	}

	Usuario::Articulos carro = user.compra() ;

	bool pedido_final_vacio = true ;

	for( auto pos = carro.begin(); pos!= carro.end(); pos++) // pair Articulo/unsigned
	{
		Articulo* pa = (pos->first) ;

		unsigned cantidad = pos->second ;

		if(ArticuloAlmacenable* const aa =
				dynamic_cast<ArticuloAlmacenable* const>(pa))
		{
				 if(aa->stock() < cantidad)
				 {
					const_cast<Usuario::Articulos&>(user.compra()).clear() ; // quitamos el const para poder usar clear()

					throw SinStock(pos->first) ;
				 }


		double precio = aa->precio() ;

		aa->stock() -= cantidad ;

		total_ += cantidad * precio ;

		pedart.pedir(*this,*aa,precio,cantidad);

		pedido_final_vacio = false ;
	  }

	else
	{
		if(LibroDigital* const ld = dynamic_cast<LibroDigital* const>(pa))
			{
				if(ld->f_expir() > fecha_)
			  {

				 total_ += ld->precio() * cantidad ;
				 pedart.pedir(*this,*ld,ld->precio(),cantidad) ;
				 pedido_final_vacio = false ;

				}
      }

			else
			{
				throw std::logic_error("Pedido::Pedido: error,"
																	"tipo de Articulo desconocido") ;
			}
	  }
		    user.compra(*pos->first,0) ;
   }

	 if(pedido_final_vacio)
	 {
		 throw Vacio(&user) ;
	 }

	userped.asocia(user,*this) ;

	++num_pedido_ ;

}

std::ostream& operator << (std::ostream& os, const Pedido& ped)
{
	os << "Núm. pedido:" << ped.numero() << std::endl ;
	os << "Fecha:" << ped.fecha() << std::endl;
	os << "Pagado con:" << *ped.tarjeta() << std::endl ;
	os << "Importe:" << std::fixed << std::setprecision(2) << ped.total() << " €"
	   << std::endl ;

	return os ;
}
