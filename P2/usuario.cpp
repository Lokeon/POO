#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include "clave.hpp"

/********************** CLAVE ************************************/

Clave::Clave(const char* s)
{
	char* salt = new char [2] ;
	const char* encrypt = "adcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ0123456789./" ; 

	srand()

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

	if(!user_.insert().second)
	{
		throw Id_duplicado(id_) ;
	}

}


void Usuario::comprar(const Articulo& A, unsigned cantidad)
{
	if( cantidad == 0)
	{
		articulos_.erase((const_cast<Articulo* >(&A))) ; 
	}
	else
	{
		articulos_[const_cast<Articulo*> (&A)] = cantidad ; 
	}
}


void Usuario::es_titular(const Tarjeta& tar)
{
	if(tar.titular() != this)
	{
		tarjetas_[tar.numero()] = const_cast < Tarjeta* >(&tar) ;
	}
}


void Usuario::no_es_titular(const Tarjeta& tar)
{
	tarjetas_.erase(tar.numero()) ;
}

Usuario::~Usuario()
{
	for(Tarjetas::iterator pos = tarjeta_.begin() ; pos != tarjetas_.end() ; pos++ )
	{
		pos->second.anula_titular() ; 
	}
}


std::ofstream& operator <<(std::ofstream& os, const Usuario& user)
{
	os << user.id_ << "[" << user.password_.clave() << "]" << user.nombre_ << user.apellidos_ << "\n"
	<< user.direccion_ << "\n"
	<<"Tarjetas:" << for(Tarjetas::iterator pos = tarjeta_.begin(); pos != tarjeta_.end(); pos++)
	os << pos->second.tipo() ;

	return os ; 
}

void mostrar_carro(std::ostream& os, const Usuario& user)
{
  os << "Carrito de compra de " << user.id() << " [Artículos: "
     << user.n_articulos() << "]" << std::endl;
  while(user.n_articulos())
  {
    os << " Cant. Artículo" << std::endl
       << std::setw(95) << std::setfill('=') << '\n'  << std::setfill(' ');

    for (auto const& i : user.compra())
        os << std::setw(4) << i.second << "   "<< *i.first << std::endl;

    os << std::endl;
  }
}