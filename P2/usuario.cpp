
#include "usuario.hpp"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <iomanip>

/********************** CLAVE ************************************/

Clave::Clave(const char* s)
{
	char* salt = new char [2] ;
	const char* encrypt = "adcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789./" ; 

	if(strlen(s) < 5 )
	{
		throw Clave::Incorrecta(CORTA) ; 	
	}
	
	salt[0] = encrypt[rand() % 64] ;
	salt[1] = encrypt[rand() % 64] ;

	if(crypt(s,salt) == NULL)
	{
		throw Clave::Incorrecta(ERROR_CRYPT) ; 
	}

	cifrada_ = crypt(s,salt) ; 
}


bool Clave::verifica(const char* s)
{
	return std::strcmp(crypt(s,cifrada_.c_str()), cifrada_.c_str()) == 0 ; 

	
}

/********************** USUARIO ************************************/

Usuario::Usuario(const Cadena& id, const Cadena& n, const Cadena& ap, const Cadena& dir, const Clave& c):id_(id), nombre_(n), apellidos_(ap),
																										 direccion_(dir), password_(c)
{

	if(!user_.insert(id_).second)
	{
		throw Id_duplicado(id_) ;
	}

}


void Usuario::compra(const Articulo& A, unsigned cantidad)
{
	if( cantidad == 0)
	{
		articulos_.erase(const_cast <Articulo*>(&A)) ; 
	}
	else
	{
		articulos_[const_cast <Articulo*>(&A)] = cantidad ; 
	}
}


void Usuario::es_titular_de(const Tarjeta& tar)
{
	if(tar.titular() != this)
	{
		tarjetas_[tar.numero()] = const_cast < Tarjeta* >(&tar) ;
	}
}


void Usuario::no_es_titular_de(const Tarjeta& tar)
{
	tarjetas_.erase(tar.numero()) ;
}


std::ostream& operator <<(std::ostream& os, const Usuario& user)
{
	os << user.id_ << "[" << user.password_.clave() << "]" << user.nombre_ << user.apellidos_ << "\n"
	<< user.direccion_ << "\n"
	<<"Tarjetas:" ;
	for(auto pos = user.tarjetas_.begin(); pos != user.tarjetas_.end(); pos++)
	{
		os << pos->second->tipo() ;
	}

	return os ; 
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user)
{
  os << "Carrito de compra de " << user.id() << " [Artículos: "<< user.n_articulos() << "]" << "\n" 
  		<< "Cant.Artículo"
  		<< std::setw(95) << std::setfill('=') << '\n' << std::setfill(' ');
  		for(auto pos = user.articulos_.begin(); pos != user.articulos_.end(); pos++)
  		{
  			os << "	" << pos->second << " [" << pos->first->referencia() << "] " << "\"" << pos->first->titulo() << "\", "
				<< pos->first->f_publi().anno() << ". " << pos->first->precio() << " €\n";
  		}
  
  	return os ; 
}


Usuario::~Usuario()
{
	for(auto pos = tarjetas_.begin() ; pos != tarjetas_.end() ; pos++ )
	{
		pos->second->anular_titular() ; 
	}
}