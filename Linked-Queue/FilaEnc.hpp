// Copyright [2016] <Gustavo Olegário>
#include <stdexcept>
#include "Elemento.hpp"

template <typename T>
class FilaEnc{
 private:
    Elemento<T> *inicio;
    Elemento<T> *fim;
    int tamanho;

 public:
	FilaEnc() {
		inicio = nullptr;
		fim = nullptr;
		tamanho = 0;
	}

	~FilaEnc() {
		limparFila();
	}

	void inclui(const T& dado) {
		Elemento<T> *novo;
		novo = new Elemento<T>(dado, nullptr);
		if (novo == nullptr) {
		    throw std::runtime_error("Erro fila cheia");
		}
		if (filaVazia()) {
		    inicio = novo;
		} else {
		    fim->setProximo(novo);
		}
		fim = novo;
		++tamanho;
	}

	T retira() {
		if (filaVazia()) {
			throw std::runtime_error("Erro fila vazia.");
		} else {
			Elemento<T> *eliminar;
			T retorna;
			eliminar = inicio;
			inicio = eliminar->getProximo();
			retorna = eliminar->getInfo();
			delete eliminar;
			--tamanho;
			return retorna;
		}
	}

	T ultimo() {
		if (filaVazia()) {
			throw std::runtime_error("Erro fila vaiza.");
		} else {
			return fim->getInfo();
		}
	}

	T primeiro() {
		if (filaVazia()) {
			throw std::runtime_error("Erro fila vazia.");
		} else {
			return inicio->getInfo();
		}
	}
	bool filaVazia() {
		return tamanho == 0;
	}
	void limparFila() {
		Elemento<T> *eliminar;
		eliminar = inicio;
		while (eliminar != nullptr) {
			inicio = eliminar->getProximo();
			delete eliminar;
			eliminar = inicio;
		}
		tamanho = 0;
	}
};

