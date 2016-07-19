// "Copyright [2016] <Gustavo Olegário>"
#include <stdexcept>
#include "ElementoDuplo.hpp"

template<typename T>
/*! \brief Uma classe de uma lista circular duplamente encadeada
 *
 */
class ListaDuplaCirc {
 private:
 	/*! \brief A cabeça de lista
 	 *
     */
    ElementoDuplo<T> *head;

    /*! \brief O tamanho da lista
 	 *
     */
    int size;

 public:
 	/*! \brief Método construtor
 	 *
     */
	ListaDuplaCirc() {
		head = nullptr;
		size = 0;
	}

	/*! \brief Método destrutor
 	 *
     */
	~ListaDuplaCirc() {
		destroiListaDuplo();
	}

	/*! \brief Método para adicionar um novo elemento no ínicio da lista.
 	 *
     */
	void adicionaNoInicioDuplo(const T& dado) {
		if (listaVazia()) {
			ElementoDuplo<T> *novo;
			novo = new ElementoDuplo<T>(dado, nullptr, nullptr);
			novo = new ElementoDuplo<T>(dado, novo, novo);
			head = novo;
		} else {
			ElementoDuplo<T> *novo;
			novo = new ElementoDuplo<T>(dado, head, head->getAnterior());
			head->getAnterior()->setProximo(novo);
			head->getProximo()->setAnterior(novo);
			head = novo;
		}
		++size;
	}

	/*! \brief Método para remover o primeiro elemento da lista e
	 * 		   que retorna o dado T do elemento removido
 	 *
     */
	T retiraDoInicioDuplo() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *eliminar, *primeiro;
			T retorna;
			eliminar = head;
			primeiro = eliminar->getProximo();
			retorna = eliminar->getInfo();
			eliminar->getProximo()->setAnterior(eliminar->getAnterior());
			eliminar->getAnterior()->setProximo(eliminar->getProximo());
			delete eliminar;
			--size;
			head = primeiro;
			return retorna;
		}
	}

	/*! \brief Método para eliminar o primeiro elemento da lista
 	 *
     */
	void eliminaDoInicioDuplo() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *eliminar, *primeiro;
			eliminar = head;
			primeiro = eliminar->getProximo();
			eliminar->getProximo()->setAnterior(eliminar->getAnterior());
			eliminar->getAnterior()->setProximo(eliminar->getProximo());
			delete eliminar;
			--size;
			head = primeiro;
		}
	}

	/*! \brief Método para adicionar um novo elemento em uma determinada posição.
	 * 		   Testa se a posição é válida e depois faz a adição.
 	 *
     */
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
		if (pos < 0 || pos > size) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			if (pos == 0) {
				return adicionaNoInicioDuplo(dado);
			} else {
				ElementoDuplo<T> *anterior, *novo;
				anterior = head;
				for (int i = 0; i < pos - 1; ++i) {
					anterior = anterior->getProximo();
				}
				novo = new ElementoDuplo<T>(dado, anterior->getProximo(), anterior);
				anterior->getProximo()->setAnterior(novo);
				anterior->setProximo(novo);
				++size;
			}
		}
	}

	/*! \brief Método que retorna posição de um determinado dado
	 *         se ele estiver na lista.
 	 *
     */
	int posicaoDuplo(const T& dado) const {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *atual;
			atual = head;
			for (int i = 0; i < size; ++i) {
				if (igual(atual->getInfo(), dado)) {
					return i;
				} else {
					atual = atual->getProximo();
				}
			}
			throw std::runtime_error("Erro dado inválido.");
		}
	}

	/*! \brief Método que retorna a posição de memória de um determinado
	 *         dado, se ele estiver na lista.
 	 *
     */
	T* posicaoMemDuplo(const T& dado) const {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *atual;
			atual = head;
			for (int i = 0; i < size; ++i) {
				if (igual(atual->getInfo(), dado)) {
					return &atual->getInfo();
				} else {
					atual = atual->getProximo();
				}
			}
			throw std::runtime_error("Erro dado não existe.");
		}
	}

	/*! \brief Método para verificar se um dado pertece ou não a lista.
 	 *
     */
	bool contemDuplo(const T& dado) {
		if (listaVazia()) {
			return false;
		} else {
			ElementoDuplo<T> *atual;
			atual = head;
			for (int i = 0; i < size; ++i) {
				if (igual(atual->getInfo(), dado)) {
					return true;
				} else {
					atual = atual->getProximo();
				}
			}
			return false;
		}
	}

	/*! \brief Método para retirar um elemento da lista de acordo
	 *         com a sua posição. Primeiro verifica se a posição é
	 *         válida e depois faz a remoção. Devolve o dado T do
	 *         elemento removido.
 	 *
     */
	T retiraDaPosicaoDuplo(int pos) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			if (pos < 0 || pos > size - 1) {
				throw std::runtime_error("Erro posição inválida.");
			} else {
				if (pos == 0) {
				    return retiraDoInicioDuplo();
				} else {
				    ElementoDuplo<T> *eliminar, *anterior;
				    T retorna;
				    anterior = head;
				    for (int i = 0; i < pos - 1; ++i) {
    					anterior = anterior->getProximo();
	    			}
		    		eliminar = anterior->getProximo();
			    	eliminar->getAnterior()->setProximo(eliminar->getProximo());
			    	eliminar->getProximo()->setAnterior(eliminar->getAnterior());
			    	retorna = eliminar->getInfo();
			    	delete eliminar;
			    	--size;
			    	return retorna;
				}
			}
		}
	}

	/*! \brief Método para adicionar um elemento no final da lista.
 	 *
     */
	void adicionaDuplo(const T& dado) {
		return adicionaNaPosicaoDuplo(dado, size);
	}

	/*! \brief Método para remover um elemento do final da lista.
	 *         Retorna o dado T que o último elemento possuía.
 	 *
     */
	T retiraDuplo() {
		return retiraDaPosicaoDuplo(size - 1);
	}

	/*! \brief Retira um elemento específico da lista de acordo
	 *         com o seu dado.
 	 *
     */
	T retiraEspecificoDuplo(const T& dado) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			int aux = posicaoDuplo(dado);
			return retiraDaPosicaoDuplo(aux);
		}
	}

	/*! \brief Retorna o dado T de um elemento de uma determinada posição.
 	 *
     */
	T mostra(int pos) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			if (pos < 0 || pos > size - 1) {
				throw std::runtime_error("Erro de posição.");
			} else {
				ElementoDuplo<T> *atual;
				atual = head;
				for (int i = 0; i < size; ++i) {
					if (pos == i) {
						return atual->getInfo();
					} else {
						atual = atual->getProximo();
					}
				}
				throw std::runtime_error("Erro");
			}
		}
	}

	/*! \brief Adiciona um novo elemento na lista, em ordem.
 	 *
     */
	void adicionaEmOrdem(const T& data) {
		if (listaVazia()) {
			return adicionaNoInicioDuplo(data);
		} else {
			ElementoDuplo<T> *novo, *anterior, *proximo;
			proximo = head;
			int i;
			for (i = 0; menor(proximo->getInfo(), data) && i < size; ++i) {
				proximo = proximo->getProximo();
			}
			if (i == 0) {
			    return adicionaNoInicioDuplo(data);
			} else {
			    anterior = proximo->getAnterior();
			    novo = new ElementoDuplo<T>(data, proximo, anterior);
			    novo->getAnterior()->setProximo(novo);
			    novo->getProximo()->setAnterior(novo);
			    ++size;
		    }
	    }
	}

	/*! \brief Método para ver o índice do último elemento.
 	 *
     */
	int verUltimo() {
		return size - 1;
	}

	/*! \brief Método para verificar se a lista está vazia.
 	 *
     */
	bool listaVazia() const {
		return size == 0;
	}

	/*! \brief Método para verificar se dois dados são iguais.
 	 *
     */
	bool igual(T dado1, T dado2) const {
		return dado1 == dado2;
	}

	/*! \brief Método para ver se um dado é maior do que outro.
 	 *
     */
	bool maior(T dado1, T dado2) {
		return dado1 > dado2;
	}

	/*! \brief Método para ver se um dado é menor do que outro.
 	 *
     */
	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}

	/*! \brief Método para destruir a lista.
 	 *
     */
	void destroiListaDuplo() {
	    ElementoDuplo<T> *eliminar, *aux;
	    eliminar = head;
	    while (size > 0) {
	        aux = eliminar->getProximo();
	        delete eliminar;
	        eliminar = aux;
	        --size;
	    }
	    head = nullptr;
	}
};
