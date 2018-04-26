#ifndef FECHA_HPP
#define FECHA_HPP

#include <iostream>



class Fecha
{

public:

	static const int AnnoMinimo = 1902 , AnnoMaximo = 2037 ;

	explicit Fecha(int d =0, int m =0, int a =0) ; 
	Fecha(const char* f); //Cadena . . . 
	Fecha(const Fecha& a) = default ; 
	
	// Operadores 

	const char* cadena() const ; //Metodo Conversion 
	Fecha& operator = (const Fecha&) = default;
	Fecha operator +(int d) const  ;   // Suma dias
	Fecha operator -(int d) const  ;   // Resta dias
	Fecha& operator --()  ; 	  // Preincremento nega
	Fecha& operator ++()  ; 	  // Preincremento pos
	Fecha  operator ++(int)   ;    // Posincremento pos
	Fecha  operator --(int)   ;    // Posincremento nega
	Fecha&  operator +=(int d) ;  // The BOSS 
	Fecha&  operator -=(int d) ;  // eso 
	
	~Fecha() = default ; 

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

	int dia() const noexcept ; 
	int mes() const noexcept; 
	int anno() const noexcept;  

private:

	int dia_, mes_, anno_ ; 
	void valida() ;

 
};
	
	inline int Fecha::dia() const noexcept { return dia_ ; }

	inline int Fecha::mes() const noexcept { return mes_ ; }	

	inline int Fecha::anno() const noexcept { return anno_ ; }


	bool operator <(const Fecha& f1 , const Fecha& f2) ;
	bool operator >(const Fecha& f1 , const Fecha& f2) ;
	bool operator !=(const Fecha& f1 , const Fecha& f2) ;
	bool operator <=(const Fecha& f1 , const Fecha& f2) ;
	bool operator >=(const Fecha& f1 , const Fecha& f2) ;
	bool operator ==(const Fecha& f1 , const Fecha& f2) ;
    
    std::ostream& operator << (std::ostream& os, const Fecha& f1) ; 
	std::istream& operator >> (std::istream & is, Fecha& f2) ;




















#endif // FECHA_HPP