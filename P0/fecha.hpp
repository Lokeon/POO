#ifndef FECHA_HPP
#define FECHA_HPP



class Fecha
{

public:

	static const int AnnoMinimo = 1902 , AnnoMaximo = 2037 ;

	explicit Fecha(int d =0, int m =0, int a =0) ; 
	Fecha(const char* f) ; //Cadena . . . 
	
	 

	// Operadores 

	operator char const*() const ; //Conversion 
	
	Fecha operator +(int d) const  ;   // Suma dias
	Fecha operator -(int d) const  ;   // Resta dias
	Fecha& operator ++()  ; 	  // PreIncremento pos
	Fecha& operator --()  ; 	  // Preincremento nega
	Fecha  operator ++(int)  ;    // Posincremento pos
	Fecha  operator --(int)  ;    // Posincremento nega
	Fecha&  operator +=(int d) ;  // The BOSS 
	Fecha&  operator -=(int d) ;  // eso 
	
	

	// Clase Invalida- por_que

	  class Invalida
	{

	public :
		Invalida(const char* f):inva_(f){}
		const char* por_que() const { return inva_ ;} ;
	private:
		const char* inva_ ; 
	} ; 

	// Metodos Observadores 

	int dia() const noexcept  ; 
	int mes() const noexcept  ; 
	int anno() const noexcept ; 

private:

int dia_, mes_, anno_ ; 
void valida(int d, int m , int a) ;
 
};
	
	 
	bool operator <(const Fecha& f1 , const Fecha& f2) ;
	bool operator >(const Fecha& f1 , const Fecha& f2) ;
	bool operator !=(const Fecha& f1 , const Fecha& f2) ;
	bool operator <=(const Fecha& f1 , const Fecha& f2) ;
	bool operator >=(const Fecha& f1 , const Fecha& f2) ;
	bool operator ==(const Fecha& f1 , const Fecha& f2) ;
    





















#endif // FECHA_HPP