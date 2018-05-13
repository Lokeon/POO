
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <random>
#include "usuario.hpp"

/********************** CLAVE ************************************/

Clave::Clave(const char* s)
{
	char* salt = new char [2] ;
	const char* encrypt = "zyxwvutsrqponmlkjihgfedcbaZYXWVUTSRQPONMLKJIHGFEDCBA9876543210/." ;


	if(strlen(s) < 5 )
	{
		throw Incorrecta(Razon::CORTA) ;
	}

	salt[0] = encrypt[rand() % 64] ;
	salt[1] = encrypt[rand() % 64] ;

	if(crypt(s,salt) == NULL)
	{
		throw Incorrecta(Razon::ERROR_CRYPT) ;
	}

	cifrada_ = crypt(s,salt) ;
}

bool Clave::verifica(const char* s) const
{

	return std::strcmp(crypt(s,cifrada_.c_str()), cifrada_.c_str()) == 0 ;


}

/********************** USUARIO ************************************/

Usuario::Usuarios Usuario::user_; // Definicion

Usuario::Usuario(const Cadena& id,const Cadena& n,const Cadena& ap,const Cadena& dir,const Clave& c):id_(id),nombre_(n),apellidos_(ap),
																									 direccion_(dir),pass_(c)
{
	 if(!user_.insert(id).second)
	 {
	   throw Id_duplicado(id_);
	 }
}


void Usuario::compra(Articulo& A, unsigned cantidad)
{
	if( cantidad == 0)
	{
		articulos_.erase(&A) ;
	}
	else
	{
		articulos_[&A] = cantidad ;
	}
}


void Usuario::es_titular_de( Tarjeta& tar)
{
	 if(this == tar.titular())
	{
	   tarjetas_.insert(std::make_pair(tar.numero(),&tar));
	}
}


void Usuario::no_es_titular_de(Tarjeta& tar)
{
	tar.anula_titular() ;
	tarjetas_.erase(tar.numero()) ;
}


std::ostream& operator <<(std::ostream& os, const Usuario& user)
{
	os << user.id_ << "[" << user.pass_.clave().c_str() << "]" << user.nombre_ << user.apellidos_ << "\n"
	<< user.direccion_ << std::endl;
	os <<"Tarjetas:" ;
	for(auto pos = user.tarjetas().begin(); pos != user.tarjetas().end(); pos++)
	{
		os << *pos->second << std::endl ;
	}

	return os ;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user)
{
  os << "Carrito de compra de " << user.id() << " [Artículos: "<< user.n_articulos() << "]" << "\n"
  		<< "Cant.Artículo"<< std::endl
  		<< std::setw(95) << std::setfill('=') << '\n' << std::setfill(' ');

  		int stock = user.n_articulos() ;

  		while( stock > 0 )
  		{
  			for(auto pos = user.compra().begin(); pos != user.compra().end(); pos++)
  			{
  				os << std::setw(4) << pos->second << "    "
  					<< " [" << (*pos->first).referencia() << "] " << "\""
  					<< (*pos->first).titulo() << "\", "
					<< (*pos->first).f_publi().anno()
					<< ". " << std::fixed << std::setprecision(2) << (*pos->first).precio() << " €" << std::endl ;
  			
					--stock  ;
  			}
  		}

  	return os ;
}



Usuario::~Usuario()
{

for(auto pos = tarjetas_.begin() ; pos != tarjetas_.end() ; pos++ )
	{
		pos->second->anula_titular() ; 
	}
  
  	user_.erase(id_);
}
