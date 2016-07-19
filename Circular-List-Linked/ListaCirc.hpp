// "Copyright [2016] <Gustavo Olegário>"
#include <stdexcept>
#include "Elemento.hpp"

template<typename T>
/*! \brief Uma classe de uma lista circular simples encadeada
 *
 */
class ListaCirc {
 private:
    /*! \brief A cabeça de lista e a sentinela.
     *
     */
     Elemento<T> *head, *sentinela;
     /*! \brief Tamanho da lista.
     *
     */
     int size;

 public:
    /*! \brief Método construtor
     *
     */
	ListaCirc() {
		sentinela = new Elemento<T>(0, nullptr);
		head = sentinela;
		size = 0;
	}

    /*! \brief Método destrutor
     *
     */
	~ListaCirc() {
		destroiLista();
	}

    /*! \brief Método para adicionar um elemento no início da lista.
     *
     */
	void adicionaNoInicio(const T& dado) {
		if (listaVazia()) {
			Elemento<T> *novo;
			novo = new Elemento<T>(dado, sentinela);
			sentinela->setProximo(novo);
		} else {
			Elemento<T> *novo, *aux;
			aux = sentinela->getProximo();
			novo = new Elemento<T>(dado, aux);
			sentinela->setProximo(novo);
		}
		++size;
	}

    /*! \brief Método para remover o primeiro elemento da lista.
     *         Retorna o dado T do elemento removido.
     *
     */
    T retiraDoInicio() {
        if (listaVazia()) {
            throw std::runtime_error("Erro lista vazia.");
        } else {
            Elemento<T> *eliminar;
            T retorna;
            eliminar = sentinela->getProximo();
            retorna = eliminar->getInfo();
            sentinela->setProximo(eliminar->getProximo());
            delete eliminar;
            --size;
            return retorna;
        }
    }

    /*! \brief Método para eliminar da lista o primeiro elemento.
     *
     */
    void eliminaDoInicio() {
        if (listaVazia()) {
            throw std::runtime_error("Erro lista vazia.");
        } else {
            Elemento<T> *eliminar;
            eliminar = sentinela->getProximo();
            sentinela->setProximo(eliminar->getProximo());
            delete eliminar;
            --size;
        }
    }

    /*! \brief Método para adicionar na lista um novo elemento.
     *         Verifica se a posição é válida e depois faz a adição.
     *
     */
    void adicionaNaPosicao(const T& dado, int pos) {
        if (pos < 0 || pos > size) {
            throw std::runtime_error("Erro de posição.");
        } else {
            if (pos == 0) {
                return adicionaNoInicio(dado);
            } else {
                if (pos == size) {
                   Elemento<T> *novo, *ultimo;
                   novo = new Elemento<T>(dado, nullptr);
                   ultimo = sentinela->getProximo();
                   for (int i = 0; i < pos - 1; ++i) {
                        ultimo = ultimo->getProximo();
                    }
                    novo->setProximo(ultimo->getProximo());
                    ultimo->setProximo(novo);
                } else {
                    Elemento<T> *anterior, *novo;
                    novo = new Elemento<T>(dado, nullptr);
                    anterior = sentinela->getProximo();
                    for (int i = 0; i < pos - 1; ++i) {
                        anterior = anterior->getProximo();
                    }
                    novo->setProximo(anterior->getProximo());
                    anterior->setProximo(novo);
                }
                ++size;
            }
        }
    }

    /*! \brief Método que retorna a posição de um determinado
     *         dado na lista.
     *
     */
    int posicao(const T& dado) const {
        if (listaVazia()) {
            throw std::runtime_error("Erro lista vazia.");
        } else {
            Elemento<T> *atual;
            atual = sentinela->getProximo();
            for (int i = 0; i < size; ++i) {
                if (igual(atual->getInfo(), dado)) {
                    return i;
                } else {
                    atual = atual->getProximo();
                }
            }
            throw std::runtime_error("Erro dado não existe.");
        }
    }

    /*! \brief Método que retorna a posição de memória de um
     *         determinado dado na lista.
     *
     */
    T* posicaoMem(const T& dado) const {
        if (listaVazia()) {
            throw std::runtime_error("Erro lista vazia.");
        } else {
            Elemento<T> *atual;
            atual = sentinela->getProximo();
            for (int i = 0; i < size; ++i) {
                if (igual(atual->getInfo(), dado)) {
                    return &atual->getInfo();
                } else {
                    atual = atual->getProximo();
                    if (atual == sentinela) {
                        break;
                    }
                }
            }
            throw std::runtime_error("Erro dado não existe.");
        }
    }

    /*! \brief Método para verificar se um dado pertence a lista.
     *
     */
    bool contem(const T& dado) {
        if (listaVazia()) {
            return false;
        } else {
            Elemento<T> *atual;
            atual = sentinela->getProximo();
            for (int i = 0; i < size; ++i) {
                if (igual(atual->getInfo(), dado)) {
                    return true;
                } else {
                    atual = atual->getProximo();
                    if (atual == sentinela) {
                        break;
                    }
                }
            }
            return false;
        }
    }

    /*! \brief Retira um elemento da lista de acordo com sua posição.
     *         Retorna o dado T do elemento removido.
     *
     */
    T retiraDaPosicao(int pos) {
        if (listaVazia()) {
            throw std::runtime_error("Erro lista vazia.");
        } else {
            if (pos < 0 || pos > size - 1) {
                throw std::runtime_error("Erro de posição");
            } else {
                if (pos == 0) {
                    return retiraDoInicio();
                } else {
                    if (pos == size - 1) {
                        Elemento<T> *anterior, *eliminar;
                        T retorna;
                        anterior = sentinela->getProximo();
                        for (int i = 0; i < pos - 1; ++i) {
                            anterior = anterior->getProximo();
                        }
                        eliminar = anterior->getProximo();
                        retorna = eliminar->getInfo();
                        anterior->setProximo(sentinela);
                        delete eliminar;
                        --size;
                        return retorna;
                    } else {
                        Elemento<T> *anterior, *eliminar;
                        T retorna;
                        anterior = sentinela->getProximo();
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
    }

    /*! \brief Adiciona um novo elemento no fim da lista.
     *
     */
    void adiciona(const T& dado) {
        return adicionaNaPosicao(dado, size);
    }

    /*! \brief Remove da lista o último elemento.
     *         Retorna o dado T do elemento removido.
     *
     */
    T retira() {
        return retiraDaPosicao(size - 1);
    }

    /*! \brief Remove um determinado elemento da lista de
     *         acordo com o seu dado.
     *
     */
    T retiraEspecifico(const T& dado) {
        if (listaVazia()) {
            throw std::runtime_error("Erro lista vazia.");
        } else {
            int aux = posicao(dado);
            return retiraDaPosicao(aux);
        }
    }

    /*! \brief Mostra o dado de um elemento de acordo com sua posição.
     *
     */
    T mostra(int pos) {
        if (listaVazia()) {
            throw std::runtime_error("Erro lista vazia.");
        } else {
            if (pos < 0 || pos > size - 1) {
                throw std::runtime_error("Erro de posição");
            } else {
                Elemento<T> *atual;
                atual = sentinela->getProximo();
                for (int i = 0; i < size; ++i) {
                    if (i == pos) {
                        return atual->getInfo();
                    } else {
                        atual = atual->getProximo();
                        if (atual == sentinela) {
                            break;
                        }
                    }
                }
                throw std::runtime_error("Erro posição inválida.");
            }
        }
    }

    /*! \brief Adiciona umn novo elemento, em ordem.
     *
     */
    void adicionaEmOrdem(const T& data) {
        if (listaVazia()) {
            return adicionaNoInicio(data);
        } else {
            Elemento<T> *atual = sentinela->getProximo();
		    int pos = 0;
		    while (atual->getProximo() != sentinela &&
		           maior(data, atual->getInfo())) {
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

    /*! \brief Retorna o tamanho da lista.
     *
     */
	int verUltimo() {
		return size;
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

    /*! \brief Método para verificar se um dado é maior do que outro.
     *
     */
    bool maior(T dado1, T dado2) {
        return dado1 > dado2;
    }

    /*! \brief Método para verificar se um dado é menor do que outro.
     *
     */
    bool menor(T dado1, T dado2) {
        return dado1 < dado2;
    }

    /*! \brief Método para destruir a lista.
     *
     */
    void destroiLista() {
        Elemento<T> *eliminar, *aux;
        eliminar = sentinela->getProximo();
        while (size > 0) {
            aux = eliminar->getProximo();
            delete eliminar;
            eliminar = aux;
            --size;
        }
    }
};
