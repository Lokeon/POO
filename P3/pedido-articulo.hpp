
#ifndef PED_ART_HPP
#define PED_ART_HPP

#include <map>
#include <utility>
#include "pedido.hpp"
#include "articulo.hpp"


struct OrdenaPedidos: public std::binary_function <Pedido*,Pedido*,bool>
{
	bool operator()(const Pedido* ped1, const Pedido* ped2) const { return ped1->numero() < ped2->numero() ;};
};

struct OrdenaArticulos: public std::binary_function<Articulo*,Articulo*,bool>
{
	bool operator()(const Articulo* art1, const Articulo* art2) const { return art1->referencia() < art2->referencia() ;};
};

class LineaPedido
{

public:

	explicit LineaPedido(double pre, unsigned cant = 1);

	double precio_venta() const ;
    unsigned cantidad() const  ;


private:

	double precio_venta_ ; 
	unsigned cant_vendida_;


};

inline double LineaPedido::precio_venta() const
{
	return precio_venta_ ; 
}

inline unsigned LineaPedido::cantidad() const
{
	return cant_vendida_ ; 
}

std::ostream& operator << (std::ostream& os, const LineaPedido& op) ; 


class Pedido_Articulo
{
public:
	
	typedef std::map <Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido ; 
	typedef std::map <Pedido*, LineaPedido, OrdenaPedidos > Pedidos ; 

	void pedir(Pedido& ped, Articulo& art,double precio, unsigned cantidad = 1) ; 
	void pedir(Articulo& art, Pedido& ped,double precio, unsigned cantidad = 1) ;

	ItemsPedido& detalle(Pedido& ped) ;
	Pedidos ventas(Articulo& art) ;

	std::ostream& mostrarDetallePedidos(std::ostream& os) ;   
	std::ostream& mostrarVentasArticulos(std::ostream& os) ; 

private:

	std::map <Pedido*, ItemsPedido, OrdenaPedidos> Ped_Art_ ;
	std::map <Articulo*, Pedidos, OrdenaArticulos> Art_Ped_ ;  

};


	std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::ItemsPedido& A) ;   
	std::ostream& operator <<(std::ostream& os, const Pedido_Articulo::Pedidos& B) ; 













#endif // PED_ART_HPP