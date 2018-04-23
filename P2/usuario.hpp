#include "cadena.hpp"
#include "usuario.hpp"


class Usuario
{

public:

	Usuario

	Usuario(const Usuario& A) = delete ; 



private:

	Cadena id_, nombre_, apellidos_, direccion_ ; 
	Clave password_ ; 
	Tarjeta tarjetas_ ; 
	Articulo articulos_ ; 

}