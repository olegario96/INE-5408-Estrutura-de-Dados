// "Copyright [2016] <Gustavo Olegário>"
// "Copyright [2016] <Otto Pires>"
#include <stdexcept>
#include "ElementoDuplo.hpp"

template<typename T>
/*! \brief Uma classe de uma lista duplamente encadeada
 *
 */
class ListaDupla {
 private:
 	/*! \brief A cabeça da lista
 	 *
 	 */
    ElementoDuplo<T> *head;
    /*! \brief Um inteiro que define o tamanho atual da lista
 	 *
 	 */
    int tamanho;

 public:
 	/*! \brief Método construtor
 	 *
 	 */
	ListaDupla() {
		head = nullptr;
		tamanho = 0;
	}

	/*! \brief Método destrutor
 	 *
 	 */
	~ListaDupla() {
		destroiListaDuplo();
	}

	/*! \brief Método para adicionar um elemento no início.
 	 *         Se a lista estiver vazia, coloca os dois ponteiros
 	 *         como nulos.
 	 */
	void adicionaNoInicioDuplo(const T& dado) {
		ElementoDuplo<T> *primeiro;
		if (listaVazia()) {
			primeiro = new ElementoDuplo<T>(dado, nullptr, nullptr);
			head = primeiro;
			++tamanho;
		} else {
			primeiro = new ElementoDuplo<T>(dado, head, nullptr);
			head->setAnterior(primeiro);
			head = primeiro;
			++tamanho;
		}
	}

	/*! \brief Se a lista não estiver vazia, retira o primeiro
 	 *         elemento do início e devolve o dado do elemento
 	 *         destruído.
 	 *
 	 */
	T retiraDoInicioDuplo() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *eliminar;
			T retorna;
			eliminar = head;
			retorna = eliminar->getInfo();
			head = eliminar->getProximo();
			delete eliminar;
			head->setAnterior(nullptr);
			--tamanho;
			return retorna;
		}
	}

	/*! \brief Se a lista não estiver vazia, deleta
 	 *         o primeiro elemento.
 	 *
 	 */
	void eliminaDoInicioDuplo() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *eliminar;
			eliminar = head;
			head = eliminar->getProximo();
			delete eliminar;
			head->setAnterior(nullptr);
			--tamanho;
		}
	}

	/*! \brief Método que adiciona numa posição específica.
 	 *		   Se o a lista estiver vaiza, adicionamos no
 	 *         início.
 	 *
 	 */
	void adicionaNaPosicaoDuplo(const T& dado, int pos) {
		if (pos < 0 || pos > tamanho) {
			throw std::runtime_error("Erro de posição.");
		} else {
			if (listaVazia()) {
				return adicionaNoInicioDuplo(dado);
			} else {
				ElementoDuplo<T> *novo, *anterior, *proximo;
				anterior = head;
				for (int i = 0; i < pos - 1; ++i) {
					anterior = anterior->getProximo();
				}
				proximo = anterior->getProximo();
				novo = new ElementoDuplo<T>(dado, proximo, anterior);
				anterior->setProximo(novo);
				if (proximo != nullptr) {
					proximo->setAnterior(novo);
				}
				++tamanho;
			}
		}
	}

	/*! \brief Método que retorna a posição de um dado
 	 *	 	   caso a lista não esteja vazia.
 	 *
 	 */
	int posicaoDuplo(const T& dado) const {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *atual;
			atual = head;
			for (int i = 0; i < tamanho; ++i) {
				if (dado == atual->getInfo()) {
					return i;
				} else {
					atual = atual->getProximo();
				}
			}
			throw std::runtime_error("Erro dado não existe na lista.");
		}
	}

	/*! \brief Método que retorna a posição de memória de um
 	 *         dado, caso a lista não esteja vazia.
 	 *         Se o dado não for encontrado, uma mensagem será
 	 *         exibida.
 	 *
 	 */
	T* posicaoMemDuplo(const T& dado) const {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *atual;
			atual = head;
			for (int i = 0; i < tamanho; ++i) {
				if (atual->getInfo() == dado) {
					return &atual->getInfo();
				} else {
					atual = atual->getProximo();
				}
			}
			throw std::runtime_error("Erro dado não existe na lista.");
		}
	}

	/*! \brief Método booleano que retorna true ou false
 	 *         dependendo se o dado passado como parâmetro
 	 *         pertencer ou não a lista.
 	 *
 	 */
	bool contemDuplo(const T& dado) {
		if (listaVazia()) {
			return false;
		} else {
			ElementoDuplo<T> *atual;
			atual = head;
			for (int i = 0; i < tamanho; ++i) {
				if (atual->getInfo() == dado) {
					return true;
				} else {
					atual = atual->getProximo();
				}
			}
			return false;
		}
	}

	/*! \brief Método que retira um elemento de uma
 	 *         posição específica caso a lista não
 	 *		   esteja vazia e a posição seja válida.
 	 *
 	 */
	T retiraDaPosicaoDuplo(int pos) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			if (pos < 0 || pos > tamanho - 1) {
				throw std::runtime_error("Erro posição inválida.");
			} else {
				if (pos == 0) {
					return retiraDoInicioDuplo();
				} else {
					ElementoDuplo<T> *eliminar, *anterior, *proximo;
					T retorna;
					anterior = head;
					for (int i = 0; i < pos - 1; ++i) {
						anterior = anterior->getProximo();
					}
					eliminar = anterior->getProximo();
					retorna = eliminar->getInfo();
					proximo = eliminar->getProximo();
					delete eliminar;
					if (proximo == nullptr) {
						anterior->setProximo(nullptr);
					} else {
						anterior->setProximo(proximo);
					}
					if (proximo != nullptr) {
						proximo->setAnterior(anterior);
					}
					--tamanho;
					return retorna;
				}
			}
		}
	}

	/*! \brief Adiciona um elemento no fim da lista.
 	 *
 	 */
	void adicionaDuplo(const T& dado) {
		return adicionaNaPosicaoDuplo(dado, tamanho);
	}

	/*! \brief Retira um elemento do fim da lista.
 	 *
 	 */
	T retiraDuplo() {
		return retiraDaPosicaoDuplo(tamanho - 1);
	}

	/*! \brief Retira um dado específico da lista
 	 *
 	 */
	T retiraEspecificoDuplo(const T& dado) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			int posi = posicaoDuplo(dado);
			return retiraDaPosicaoDuplo(posi);
		}
	}

	/*! \brief Retorna o dado de um certo elemento da lista.
 	 *
 	 */
	T mostra(int pos) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			if (pos < 0 || pos > tamanho - 1) {
				throw std::runtime_error("Posição inválida.");
			} else {
				ElementoDuplo<T> *anterior, *ultimo;
				anterior = head;
				for (int i = 0; i < pos - 1; ++i) {
					anterior = anterior->getProximo();
				}
				ultimo = anterior->getProximo();
				return ultimo->getInfo();
			}
		}
	}

	/*! \brief Adiciona um elemento em ordem na lista.
 	 *
 	 */
	void adicionaEmOrdem(const T& data) {
		if (listaVazia()) {
			return adicionaNoInicioDuplo(data);
		} else {
			ElementoDuplo<T> *anterior, *proximo, *novo;
			anterior = head;
			for (int i = 0; menor(anterior->getInfo(), data)
			    && anterior->getProximo() != nullptr; ++i) {
				anterior = anterior->getProximo();
			}
			proximo = anterior->getProximo();
			novo = new ElementoDuplo<T>(data, proximo, anterior);
			anterior->setProximo(novo);
			if (proximo != nullptr) {
				proximo->setAnterior(novo);
			}
			++tamanho;
		}
	}

	/*! \brief Retorna o tamanho da lista.
 	 *
 	 */
	int verUltimo() {
		return tamanho;
	}

	T ultimo() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T>* ultimo = head;
			T retorna;

			while (ultimo->getProximo() != nullptr) {
				ultimo = ultimo->getProximo();
			}

			retorna = ultimo->getInfo();
			return retorna;
		}
	}

	T primeiro() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ElementoDuplo<T> *primeiro = head;
			T retorna;

			retorna = primeiro->getInfo();
			return retorna;
		}
	}

	/*! \brief Retorna se a lista está vazia.
 	 *
 	 */
	bool listaVazia() const {
		return tamanho == 0;
	}

	/*! \brief Retorna se um dado é igual ao outro.
 	 *
 	 */
	bool igual(T dado1, T dado2) {
		return dado1 == dado2;
	}

	/*! \brief Retorna se um dado é maior do que o outro.
 	 *
 	 */
	bool maior(T dado1, T dado2) {
		return dado1 > dado2;
	}

	/*! \brief Retorna se um dado é menor do que o outro.
 	 *
 	 */
	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}

	/*! \brief Destrói todos os elementos da lista e redefine
 	 *         o tamanho.
 	 *
 	 */
	void destroiListaDuplo() {
	    ElementoDuplo<T> *eliminar;
	    eliminar = head;
	    while (eliminar != nullptr) {
	    head = eliminar->getProximo();
	    delete eliminar;
	    eliminar = head;
	    }
	    tamanho = 0;
	}
};

