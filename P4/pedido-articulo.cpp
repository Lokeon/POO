
#include "pedido-articulo.hpp"
#include <ostream>
#include <iomanip>



/////////////////////////// LINEA_PEDIDO ////////////////////////////////////////

LineaPedido::LineaPedido(double pre, unsigned cant):precio_venta_(pre),cantidad_(cant) {}

std::ostream& operator <<(std::ostream& os, const LineaPedido& op)
{
	os << std::fixed << std::setprecision(2) << op.precio_venta() << ' ' << "€" << '\t' << op.cantidad() ;

		return os ;
}

/////////////////////////// PEDIDO_ARTICULO ////////////////////////////////////////

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art,double precio, unsigned cantidad)
{
	Ped_Art_[&ped].insert(std::make_pair(&art,LineaPedido(precio,cantidad))) ;
	Art_Ped_[&art].insert(std::make_pair(&ped,LineaPedido(precio,cantidad))) ;
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped,double precio, unsigned cantidad)
{
	pedir(ped,art,precio,cantidad) ;
}


Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art)
{
	 return Art_Ped_[&art] ;
}

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped)
{
	return Ped_Art_[&ped] ;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os)
{

	double precio = 0.0 ;

	for(auto pos = Ped_Art_.begin(); pos != Ped_Art_.end() ; pos++)
	{

		os << "Pedido núm." << (pos->first)->numero() << "\t" ;
		os << "Cliente: " << (pos->first)->tarjeta()->titular()->nombre() << "\t";
		os << "Fecha: " << (pos->first)->fecha() << (pos->second) ;

		precio += (pos->first)->total() ;
	}

	os << std::fixed ;
	os << "TOTAL VENTAS: " << std::setprecision(2) << precio << " €" << std::endl ;

	return os ;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os)
{
	for(auto pos = Art_Ped_.begin(); pos != Art_Ped_.end(); pos++)
	{
		os << "Ventas" << "[" << (pos->first)->referencia() << "]" ;
		os << "\"" << pos->first->titulo() << "\"" ;
		os << pos->second << std::endl ;
	}

	return os ;
}

std::ostream& operator <<(std::ostream& os,const Pedido_Articulo::ItemsPedido& A)
{

	double precio = 0.0 ;

	os << "\n" ;
	os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
	os << "PVP \t Cant.\t Articulo\n" ;
	os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

	for(auto pos = A.begin(); pos != A.end() ; pos++) // auto = Pedido_Articulo::ItemsPedido::const_iterator pos ;
	{

		os << (pos->second).precio_venta() << "€\t" ;
		os << (pos->second).cantidad() << "\t" ;
		os << "[ "<< (pos->first)->referencia() << "]\t";
		os << "\"" << (pos->first)->titulo() << "\"" << std::endl;

		precio += (pos->second).precio_venta() * (pos->second).cantidad() ;
	}


	os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

	os << std::fixed ;

	os << std::setprecision(2) << precio << " €" << std::endl ;

	return os ;
}

std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& B)
{

	double precio = 0.0 ;

	unsigned total = 0  ;

	os << "\n" ;
	os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;
	os << "PVP \t Cant.\t Fecha venta\n" ;
	os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

	for(auto pos = B.begin(); pos != B.end() ; pos++)
	{

		os << " " << (pos->second).precio_venta() << " €\t" ;
		os << (pos->second).cantidad() << "\t" ;
		os << (pos->first)->fecha() << std::endl ;

		precio += (pos->second).precio_venta() * (pos->second).cantidad() ;
		total += (pos->second).cantidad() ;
	}


	os << std::setw(40) << std::setfill('=') << '\n' << std::setfill(' ') << std::endl ;

	os << std::fixed ;

	os << std::setprecision(2) << precio << " €\t" << total << std::endl ;


	return os ;

}
