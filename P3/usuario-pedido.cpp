
#include "usuario-pedido.hpp"


void Usuario_Pedido::asocia(Usuario& us, Pedido& ped)
{

	US_PED_[&us].insert(&ped) ; 

	PED_US_[&ped] = &us ; 

}

void Usuario_Pedido::asocia(Pedido& ped, Usuario& us)
{
	return asocia(us,ped) ;
}

