// "Copyright [2016] <Gustavo Olegário>"
#include <stdexcept>
#include "Elemento.hpp"

template<typename T>
// Classe de uma Lista Encadeada
class ListaEnc {
// Atributos da Lista Encadeada
 private:
    // A cabeça da Lista
	Elemento<T>* head;
	// O tamanho da Lista
	int size;

 public:
    // Métodos construtor
	ListaEnc() {
		head = nullptr;
		size = 0;
	}

	// Método destrutor
	~ListaEnc() {
		destroiLista();
	}

	// Método para adicionar um novo elemento no início
	void adicionaNoInicio(const T& dado) {
		Elemento<T> *novo;
		novo = new Elemento<T>(dado, head);
		head = novo;
		++size;
	}

	// Método que retira um elemento do início se a lista não estiver vazia
	T retiraDoInicio() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			Elemento<T> *eliminar;
			T retorna;
			eliminar = head;
			retorna = eliminar->getInfo();
			head = eliminar->getProximo();
			delete eliminar;
			--size;
			return retorna;
		}
	}

	// Método que elimina um elemento do início se a lista não estiver vazia
	void eliminaDoInicio() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			Elemento<T> *eliminar;
			eliminar = head;
			head = eliminar->getProximo();
			delete eliminar;
			--size;
		}
	}

	// Método que adiciona um elemento numa determinada posição
	void adicionaNaPosicao(const T& dado, int pos) {
		if (listaVazia() || pos == 0) {
			return adicionaNoInicio(dado);
		} else {
			// Verifica se a posição é válida.
			if (pos < 0 || pos > size) {
			    throw std::runtime_error("Erro de posição");
			} else {
			    Elemento<T> *atual, *anterior;
			    atual = new Elemento<T> (dado, nullptr);
			    anterior = head;
			    for (int i = 0; i < pos - 1; ++i) {
				    anterior = anterior->getProximo();
			    }
			    atual->setProximo(anterior->getProximo());
			    anterior->setProximo(atual);
			    ++size;
			}
		}
	}

	// Verifica em qual posição um determinado dado se encontra
	int posicao(const T& dado) const {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			Elemento<T> *atual;
			atual = head;
			for (int i = 0; i < size; ++i) {
				if (atual->getInfo() == dado) {
					return i;
				} else {
					atual = atual->getProximo();
				}
			}
			throw std::runtime_error("Elemento não existe.");
		}
	}

	// Retorna a posição de memória de um determinado dado.
	T* posicaoMem(const T& dado) const {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			Elemento<T> *atual;
			atual = head;
			for (int i = 0; i < size; ++i) {
				if (atual->getInfo() == dado) {
					return &atual->getInfo();
				} else {
					atual = atual->getProximo();
				}
			}
			throw std::runtime_error("Elemento inválido.");
		}
	}

	// Verifica se um dado pertecen ou não a lista.
	bool contem(const T& dado) {
		if (listaVazia()) {
			return false;
		} else {
			Elemento<T> *atual;
			atual = head;
			for (int i = 0; i < size; ++i) {
				if (atual->getInfo() == dado) {
					return true;
				} else {
					atual = atual->getProximo();
				}
			}
			return false;
		}
	}

	// Se a posição for válida, retira um elemento de uma posição determinada.
	T retiraDaPosicao(int pos) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			// Verifica se a posição é válida
			if (pos < 0 || pos > size - 1) {
				throw std::runtime_error("Erro de posição.");
			} else {
				if (pos == 0) {
					return retiraDoInicio();
				} else {
					Elemento<T> *eliminar, *anterior;
					T retorna;
					anterior = head;
					for (int i = 0; i < pos - 1; ++i) {
						anterior = anterior->getProximo();
					}
					eliminar = anterior->getProximo();
					retorna = eliminar->getInfo();
					anterior->setProximo(eliminar->getProximo());
					delete eliminar;
					--size;
					return retorna;
				}
			}
		}
	}

	// Adiciona um elemento no fim da lista
	void adiciona(const T& dado) {
		 return adicionaNaPosicao(dado, size);
	}

	// Retira um elemento no fim da lista
	T retira() {
	    return retiraDaPosicao(size - 1);
	}

	// Retira um elemento específico usando métodos anteriores
	T retiraEspecifico(const T& dado) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			int posi = posicao(dado);
			return retiraDaPosicao(posi);
		}
		throw std::runtime_error("Erro elemento inválido.");
	}

	// Adiciona um elemetno na ordem crescente
	void adicionaEmOrdem(const T& data) {
		if (listaVazia()) {
			adicionaNoInicio(data);
		} else {
		    Elemento<T> *atual = head;
		    int pos = 0;
		    while (atual->getProximo() != nullptr && maior(data, atual->getInfo())) {
		        atual = atual->getProximo();
		        ++pos;
		    }
		    if (maior(data, atual->getInfo())) {
		        return adicionaNaPosicao(data, pos + 1);
		    } else {
		        return adicionaNaPosicao(data, pos);
		    }
		}
	}

	// Verifica se a lista está vazia
	bool listaVazia() const {
		return size == 0;
	}

	// Verifica se um dado é igual ao outro
	bool igual(T dado1, T dado2) {
		return dado1 == dado2;
	}

	// Verifica se um dado é maior do que outro
	bool maior(T dado1, T dado2) {
		return dado1 > dado2;
	}

	// Verifica se um dado é menor do que outro
	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}

	// Destroi a lista
	void destroiLista() {
	  	Elemento<T> *anterior;
		anterior = head;
		while(anterior != nullptr) {
			anterior = anterior->getProximo();
			delete head;
			head = anterior;
		}
		size = 0;
	}
};
