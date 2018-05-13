#ifndef USU_PED_HPP
#define USU_PED_HPP

#include <set>
#include <map>
#include <utility>
#include "usuario.hpp"
#include "pedido.hpp"



class Usuario_Pedido
{

public:

typedef std::set<Pedido*> Pedidos;

void asocia(Usuario& us, Pedido& ped) ; 
void asocia(Pedido& ped, Usuario& us); 

Pedidos pedidos(Usuario& us) const { return US_PED_.at(&us) ; } ; 
Usuario* cliente(Pedido& ped) { return PED_US_.find(&ped)->second ;} ; 

private:

std::map<Usuario*,Pedidos> US_PED_; 
std::map<Pedido*, Usuario*> PED_US_ ;

};


#endif // USU_PED_HPP