// Copyright 2016 <Otto Menegasso Pires>

#ifndef ELEMENTO_HPP
#define ELEMENTO_HPP

template<typename T>
class Elemento {
 private:
    //! Dado guardado pelo elemento
	T *info;
	//! Ponteiro para o próximo elemento
	Elemento<T>* _next;

 public:
    //! Construtor
    /*! Construtor do Elemento
     */
	Elemento(const T& info, Elemento<T>* next) : info(new T(info)), _next(next) {}

    //! Destrutor
    /*! Destrutor do Elemento
     */
	~Elemento() {
		delete info;
	}

    //! Função Retorna Próximo
    /*! Função que retorna o ponteiro para o próximo elemento
     */
	Elemento<T>* getProximo() const {
		return _next;
	}

    //! Função Retorna Info
    /*! Função que retorna o valor do dado armazenado
     */
	T getInfo() const {
		return *info;
	}

    //! Função Altera próximo
    /*! Função que altera o ponteiro para o próximo para
     *  o parâmetro
     */
	void setProximo(Elemento<T>* next) {
		_next = next;
	}
};

#endif
