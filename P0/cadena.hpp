
#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstring> 

class Cadena
{

public:

	// Constructores 

	explicit Cadena(size_t t = 0 , char s = ' ') ; 
	Cadena(const Cadena& c) ; 
	Cadena(const char* cad ) ; 
	Cadena(const Cadena& cad , size_t i ,size_t t) ; 

	//Operadores && Sobrecargas

	
	Cadena& operator=(const Cadena& cad) ; 
	Cadena& operator=(const char* cad) ; 
	Cadena& operator+=(const Cadena& cad) ; 
	Cadena substr(size_t i , size_t t) const  ; 
	char operator[](size_t t) const ;
	char& operator[](size_t t) ; 
	const char at(size_t t) const ;
	char& at(size_t t) ;
	
	operator const char*()const ;

	// Metodo Destructor

	~Cadena() ; 

	//Metodo Observador

	size_t length() const noexcept;

private:

	char* s_ ; 
	size_t tam_ ; 


};


inline size_t Cadena::length() const noexcept 
{
	return tam_ ; 
}
	Cadena operator+(const Cadena& cad1, const Cadena& cad2)  ;
	bool operator < (const Cadena& f1 , const Cadena& f2) ;
	bool operator > (const Cadena& f1 , const Cadena& f2) ;
	bool operator !=(const Cadena& f1 , const Cadena& f2) ;
	bool operator <=(const Cadena& f1 , const Cadena& f2) ;
	bool operator >=(const Cadena& f1 , const Cadena& f2) ;
	bool operator ==(const Cadena& f1 , const Cadena& f2) ;



#endif // CADENA_HPP