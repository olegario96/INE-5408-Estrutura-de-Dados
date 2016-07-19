// Copyright 2016 <Otto Menegasso Pires>
#ifndef FILAENC_HPP
#define FILAENC_HPP
#include "ListaEnc.hpp"
#include "Elemento.hpp"

template <typename T>

//! Uma classe Fila Encadeada
/*! Implementada para a Disciplina de
 *  Estrutura de Dados
 *  \author Otto Menegasso Pires
 *  \since 20/04/16
 */

class FilaEnc:private ListaEnc<T> {
 private:
    // Ponteiro para o fim da fila
    Elemento<T>* tail;

 public:
    //! Construtor
    /*! Construtor da fila
     */
	FilaEnc<T>(): ListaEnc<T>::ListaEnc(), tail(nullptr) {}

    //! Destrutor
    /*! Destrutor da fila
     */
	~FilaEnc() {
	    limparFila();
	}

    Elemento<T> *getHead() {
        return ListaEnc<T>::getHead();
    }

    int getSize() {
        return ListaEnc<T>::getSize();
    }

    //! Função Incluir
    /*! Um novo dado é acrescentado ao final da fila
     *  e o índice será incrementado.
     */
	void inclui(const T& dado) {
	Elemento<T> *novo = new Elemento<T>(dado, nullptr);

	    if (filaVazia()) {
				ListaEnc<T>::setHead(novo);
				tail = novo;
			} else {
				tail->setProximo(novo);
				tail = novo;
			}
			ListaEnc<T>::addSize();
	}

    //! Função Retirar
    /*! O elemento do começo da fila, Índice 0,
     *  será retirado, com todos os elementos restantes
     *  sendo realocados uma posição à frente. O índice
     *  do final será decrementado.
     */
	T retira() {
	    T retorno = ListaEnc<T>::retiraDoInicio();
		if(filaVazia()) {
			tail = nullptr;
		}
		return retorno;
	}

    //! Função Último
    /*! Retorna o dado que está no fim da fila.
     */
	T ultimo() {
	    if (filaVazia()) {
			throw "A Fila está vazia";
		} else {
			return tail->getInfo();
		}
	}

    //! Função Primeiro
    /*! Retorna o dado que está no início da fila.
     */
    T primeiro() {
	    if (filaVazia()) {
			throw "A fila está Vazia";
		} else {
			return ListaEnc<T>::getHead()->getInfo();
		}
	}

    //! Função Fila Vazia
    /*! Função booleana de verificação da Fila
     *  retorna verdadeiro se a Fila estiver Vazia.
     */
	bool filaVazia() {
	    return ListaEnc<T>::listaVazia();
	}

    //! Função Inicializar Fila
    /*! Muda o valor do índice do último elemento para 0
     *  reinicializando a Fila.
     */
	void limparFila() {
	    ListaEnc<T>::destroiLista();
	    tail = nullptr;
    }
};
#endif
