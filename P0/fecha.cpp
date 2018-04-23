#include "fecha.hpp"
#include <ctime>
#include <cstdio>
#include <cstring>

Fecha::Fecha(int d, int m , int a): dia_(d), mes_(m), anno_(a)  // Constructor Fecha int 
{
	std::time_t tiempo_calendario = std::time(nullptr);
    std::tm*  tiempo_descompuesto = std::localtime(&tiempo_calendario);

	if(dia_== 0 || mes_ == 0 || anno_ == 0)   
	{
		if(dia_ == 0 )
		{
		dia_ = tiempo_descompuesto->tm_mday ;
		}
   
    	if(mes_ == 0 )
    	{
			mes_ = tiempo_descompuesto->tm_mon +1 ;
		}
 
    	if(anno_ == 0 )
    	{
			anno_ = tiempo_descompuesto->tm_year +1900 ; 
    	}

 	}  

 	valida(dia_, mes_, anno_) ;

	
}

Fecha::Fecha(const char* f) // Constructor Fecha cad 
{

	std::time_t tiempo_calendario = std::time(nullptr);
    std::tm*  tiempo_descompuesto = std::localtime(&tiempo_calendario);    

    int conta ,contd, contm   ;

    int cad = sscanf(f,"%d/%d/%d",&contd,&contm,&conta) ; 

    	if(cad !=3) 
    	{

    		throw Invalida("Fallo en la conversion") ; 

    	} 
    	
    	else
    	{
			dia_ = contd ; 
    		mes_ = contm ; 
    		anno_ = conta ; 

    		if(dia_== 0 || mes_ == 0 || anno_ == 0)   
			{
				if(dia_ == 0 )
				{
					dia_ = tiempo_descompuesto->tm_mday ;
				}
   
    			if(mes_ == 0 )
    			{
					mes_ = tiempo_descompuesto->tm_mon +1 ;
				}
 
   				if(anno_ == 0 )
    			{
					anno_ = tiempo_descompuesto->tm_year +1900 ; 
    			}
			}  


  			valida(dia_, mes_, anno_) ;
		}
   
}

Fecha::operator const char*() const
{
	char* fecha_escrita = new char [40] ; 

	const char* DIASEM[] = {"domingo","lunes","martes","miércoles","jueves","viernes","sábado"} ; 

	const char* MES[] = {"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"} ;

	
	tm tiempo_descompuesto = {0} ; 
	
	tiempo_descompuesto.tm_year = anno() - 1900 ; 
	tiempo_descompuesto.tm_mon = mes() - 1 ; 
	tiempo_descompuesto.tm_mday = dia() ;

	mktime(&tiempo_descompuesto) ; 

	
	sprintf(fecha_escrita,"%s %d de %s de %d ", DIASEM[tiempo_descompuesto.tm_wday],
		tiempo_descompuesto.tm_mday,MES[tiempo_descompuesto.tm_mon],tiempo_descompuesto.tm_year + 1900 ) ;

	return (const char*) fecha_escrita ;	 

}

void Fecha::valida(int dia_, int mes_ , int anno_)
{
	int bisiesto = static_cast<int>(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) ; 	

	static const int diam [] = {0,31,28,31,30,31,30,31,31,30,31,30,31} ;

	if(anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo)
	{
		throw Fecha::Invalida("Año inválido") ;
	}

	if(mes_ < 1 || mes_ > 12)
	{
		throw Fecha::Invalida("Mes inválido") ;
	}

	if(dia_ < 1 || dia_ > diam[mes_] + bisiesto)
	{
		throw Fecha::Invalida("Día inválido") ; 
	}

}

//Operadores

bool operator <(const Fecha& f1 , const Fecha& f2) 
{

	if(f1.anno() < f2.anno())
	{
		return true ;
	}	
	else
	{
		if(f1.mes() < f2.mes())
		{
			return true ;
		}	
		else
		{
			if(f1.dia() < f2.dia())
			{
				return true ;
			}
		}
	}  

		return false ; 
}

bool operator >(const Fecha& f1 , const Fecha& f2) 
{
	return (f2 < f1 ); 
}
bool operator ==(const Fecha& f1 , const Fecha& f2) 
{
	return ( f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno()) ;
}
bool operator <=(const Fecha& f1 , const Fecha& f2) 
{
	return ( f1 < f2 || f1 == f2 ) ;
}

bool operator >=(const Fecha& f1 , const Fecha& f2) 
{
	return (f2 < f1 || f1 == f2) ;
}

bool operator !=(const Fecha& f1 , const Fecha& f2) 
{
	return !(f1 == f2) ; 
}

Fecha Fecha::operator +(int d) const
{
	
	Fecha m(*this) ;
     
    m += d  ; 
	 
	return m ; 

}	

Fecha Fecha::operator -(int d) const
{
	Fecha m(*this) ;
	
	m += -d ; 

	return m ; 
}

Fecha Fecha::operator ++(int) 
{
	Fecha m = *this ; 
	
	*this += 1 ; 

	return m ; 
}

Fecha Fecha::operator --(int) 
{

	Fecha m = *this ; 
	
	*this += -1 ; 

	return m ; 
}

Fecha& Fecha::operator ++() 
{
	return (*this += 1 ) ; 
}

Fecha& Fecha::operator --() 
{
	return (*this += -1 ) ; 
}

Fecha& Fecha::operator +=(int d)
{

	tm t2 = {0} ; 
	
	t2.tm_mday = (this->dia_ + d ) ;
	t2.tm_mon  = (this->mes_ - 1) ; 
	t2.tm_year = (this->anno_ - 1900) ;

	mktime(&t2) ; 

	this->dia_ = t2.tm_mday ;
	this->mes_ = t2.tm_mon + 1 ; 
	this->anno_ = t2.tm_year + 1900 ; 

	valida(dia_,mes_,anno_) ; 

	return *this ; 

}

Fecha& Fecha::operator -=(int d)
{
	return (*this += - d) ; 
}


inline int Fecha::dia() const noexcept
{
	return dia_ ; 
} 

inline int Fecha::mes() const noexcept
{
	return mes_ ; 
}

inline int Fecha::anno() const noexcept
{
	return anno_ ; 
}


