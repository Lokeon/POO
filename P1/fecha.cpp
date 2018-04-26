	
#include <ctime>
#include <cstdio>
#include <cstring>
#include <stdexcept>
#include "fecha.hpp"


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

 	valida() ;

}

Fecha::Fecha(const char* f):dia_(20),mes_(20),anno_(20) // Constructor Fecha cad 
{

	int conta ,contd, contm   ;

    int cad = sscanf(f,"%d/%d/%d",&contd,&contm,&conta) ; 

    	if(cad !=3) 
    	{

    		throw Invalida("Error formato dd/mm/aaaa ") ; 

    	} 
		else
		{
			Fecha a(contd,contm,conta) ; 
			
			dia_ = a.dia_ ; 
			mes_ = a.mes_ ; 
			anno_ = a.anno_ ;
		}
 		

 }

 const char* Fecha::cadena() const
{
	
	static char fecha_escrita [40] ; 

	const char* DIASEM[] = {"domingo","lunes","martes","miércoles","jueves","viernes","sábado"} ; 

	const char* MES[] = {"enero","febrero","marzo","abril","mayo","junio","julio","agosto","septiembre","octubre","noviembre","diciembre"} ;

	
	tm fecha = {0} ; 
	
	fecha.tm_year = anno() - 1900 ; 
	fecha.tm_mon = mes() - 1 ; 
	fecha.tm_mday = dia() ;

	mktime(&fecha) ; 

	
	sprintf(fecha_escrita,"%s %d de %s de %d", DIASEM[fecha.tm_wday],
		fecha.tm_mday,MES[fecha.tm_mon],fecha.tm_year + 1900) ;

	return  fecha_escrita ;		 

}

void Fecha::valida()
{
	int bisiesto = static_cast<int>(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) ; 	

	static const int diam [] = {0,31,28,31,30,31,30,31,31,30,31,30,31} ;

	if(anno_ < Fecha::AnnoMinimo || anno_ > Fecha::AnnoMaximo)
	{
		throw Invalida("Año inválido") ;
	}

	if(mes_ < 1 || mes_ > 12)
	{
		throw Invalida("Mes inválido") ;
	}

	if(dia_ < 1 || dia_ > diam[mes_] + bisiesto)
	{
		throw Invalida("Día inválido") ; 
	}

}

//Operadores


bool operator <(const Fecha& fecha1 , const Fecha& fecha2) 
{

	if ( fecha1.anno() < fecha2.anno() ) return true;
    else if ( fecha1.anno() > fecha2.anno() ) return false;
         else if ( fecha1.mes() < fecha2.mes() ) return true;
                else if ( fecha1.mes() > fecha2.mes() ) return false;
                     else return fecha1.dia() < fecha2.dia();
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
	
	Fecha m = *this ; 
     
    m += d  ; 
	 
	return m ; 

}	

Fecha Fecha::operator -(int d) const
{
	Fecha m = *this ; 
	
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
	return *this += 1  ; 
}

Fecha& Fecha::operator --() 
{
	return *this += -1  ; 
}

Fecha& Fecha::operator +=(int d)
{
	if(d != 0)
	{
	
	tm t2 = {0} ; 
	
	t2.tm_mday = dia_ + d  ;
	t2.tm_mon  = mes_ - 1 ; 
	t2.tm_year = anno_ - 1900 ;

	mktime(&t2) ; 

	dia_ = t2.tm_mday ;
	mes_ = t2.tm_mon + 1 ; 
	anno_ = t2.tm_year + 1900 ; 

	valida();

	}
	
	return *this ; 

}

Fecha& Fecha::operator -=(int d) 
{
	return *this += -d ; 
}



std::ostream& operator << (std::ostream& os, const Fecha& f1)
{
	os << f1.cadena() ; 

	return os ; 
}

std::istream& operator >> (std::istream& is, Fecha& f1)
{

	char* fecha = new char[11] ;
	
	is.getline(fecha,11) ;

	try{
	
	f1 = Fecha(fecha) ;

	delete [] fecha ; 
	
	}catch(Fecha::Invalida &e)
	{
		is.setstate(std::ios_base::failbit) ;

		throw ; 
	}

	 return is ; 
}