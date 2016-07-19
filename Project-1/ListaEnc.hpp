// Copyright 2016 <Otto Menegasso Pires>
#ifndef LISTAENC_HPP
#define LISTAENC_HPP
#include "Elemento.hpp"

template<typename T>

//! Uma classe Lista Encadeada
/*! Implementada para a Disciplina de
 *  Estrutura de Dados
 *  \author Otto Menegasso Pires
 *  \since 14/04/16
 */


class ListaEnc {
 private:
    // Ponteiro do início da lista
	Elemento<T>* head;
	// Tamanho atual da Lista
	int size;

 protected:
    //! Função Retorna Cabeça
	/*! Retorna o início da fila
	 */
	Elemento<T> *getHead() const {
		return head;
	}

	//! Função Altera Cabeça
	/*! Altera o início da fila
	 */
	void setHead(Elemento<T> *next) {
		head = next;
	}

	//! Função Retorna Tamanho
	/*! Retorna o valor do tamanho
	 */
	int getSize() const {
		return size;
	}

	//! Função Incrementa
	/*! Incrementa o tamanho
	 */
	void addSize() {
		++size;
	}

	//! Função Decrementa
	/*! decrementa o tamanho
	 */
	void subSize() {
		--size;
	}

 public:
    //! Construtor
    /*! Construtor da Lista Encadeada
     */
	ListaEnc() {
    	    head = nullptr;
    	    size = 0;
	}

    //! Destrutor
    /*! Destrutor da Lista Encadeada
     */
	~ListaEnc() {
	    destroiLista();
	}


	// inicio
    //! Função Adiciona no Inicio
    /*! Um novo ponteiro é criado apontando para o primeiro
     *  a referência da cabeça da lista é então modificada para
     *  apontar para o ponteiro recém-criado e a variável tamanho é incrementada
     */
	void adicionaNoInicio(const T& dado) {
            	Elemento<T> *novo = new Elemento<T>(dado, head);
    	        head = novo;
    	        size += 1;
	}

    //! Função Retira do Início
    /*! Primeiro serão criadas duas variáveis auxiliares, um ponteiro e um
     *  Template. O ponteiro criado receberá o valor da cabeça da lista e o
     *  Template recberá a informação do elemento que a lista aponta. Após isso
     *  a cabeça da lista mudará seu referencial para o próximo elemento, o tamanho
     *  será decrementado, o ponteiro auxiliar será deletado e o Template auxiliar será
     *  retornado. Caso a lista esteja vazia, uma excessão será lançada.
     */
	T retiraDoInicio() {
	    Elemento<T> *saiu;
	    T volta;

	    if (listaVazia()) {
	        throw "A lista está Vazia";
	    } else {
	            saiu = head;
	            volta = saiu->getInfo();
	            head = saiu->getProximo();
	            size -= 1;
	            delete saiu;
	            return volta;
	        }
	}

    //! Função Elimina do Início
    /*! Primeiro será criada um ponteiro auxiliar. O ponteiro criado receberá o 
     *  valor da cabeça da lista. Após isso a cabeça da lista mudará seu referencial para 
     *  o próximo elemento, o tamanho será decrementado e o ponteiro auxiliar será deletado
     *  Caso a lista esteja vazia, uma excessão será lançada.
     */
	void eliminaDoInicio() {
        Elemento<T> *saiu;

        if (listaVazia()) {
            throw "A lista está Vazia";
        } else {
                saiu = head;
                head->setProximo(saiu->getProximo());
                size -= 1;
                delete saiu;
            }
	}

    //! Função Adiciona na Posição
    /*! São criados dois ponteiros auxiliares. Um deles receberá a informação
     *  passada como parâmetro e o outro receberá o valor da cabeça da lista.
     *  Um laço de repitação irá ocorrer um número de vezes igual ao inteiro passado
     *  como parâmetro menos 2. Ao se chegar na posição escolhida, o ponteiro com a
     *  informação receberá a posição do outro ponteiro auxiliar, que será refereciado
     *  como o ponteiro anterior, o tamanho é incrementado. Caso o parâmetro inteiro
     *  da posição seja 1, a função adicionaNoInicio() será chamada, e caso a posição
     *  seja inválida, uma exceção será lançada;
     */
	void adicionaNaPosicao(const T& dado, int pos) {
	    Elemento<T> *novo, *anterior;

	    if (pos > size || pos < 0) {
	        throw "Posição Inválida";
	    } else if (pos == 0 || listaVazia()) {
	            return adicionaNoInicio(dado);
	        } else {
	                novo = new Elemento<T>(dado, nullptr);
	                anterior = head;
	                for (int i = 0; i < pos-1; ++i) {
	                anterior = anterior->getProximo();
	                }
	                novo->setProximo(anterior->getProximo());
	                anterior->setProximo(novo);
	                size += 1;
	            }
	}

    //! Função Retorna Posição
    /*! Um ponteiro auxiliar e um inteiro são criados. Um laço de repetição é feito
     *  comparando a informação do ponteiro auxiliar com o parâmetro dado enquanto o 
     *  inteiro é incrementado. Caso o parâmetro e o auxiliar sejam iguais, o inteiro
     *  é retornado. Caso o dado não tenha sido encontrado na fila, uma exceção será lançada.
     */
	int posicao(const T& dado) const {
        Elemento<T> *procura;

	    if (listaVazia()) {
	        throw "A Lista está Vazia";
	    } else {
        	    procura = head;
        	    for (int pos = 0; pos < size; ++pos) {
        	        if (procura->getInfo() == dado) {
        	            return pos;
                	 } else {
                	       procura = procura->getProximo();
                	    }
        	    }
        	    throw "Elemento não encontrado";
        	 }
	}

    //! Função Retorna Posição na Memória
    /*! Um ponteiro auxiliar é criado. Um laço de repetição é feito
     *  comparando a informação do ponteiro auxiliar com o parâmetro dado
     *  Caso o parâmetro e o auxiliar sejam iguais, a posição na memória é retornada
     *  Caso o dado não tenha sido encontrado na fila, uma exceção será lançada.
     */
	T* posicaoMem(const T& dado) const {
	    Elemento<T> *procura;
	    if (listaVazia()) {
	        throw "A Lista está Vazia";
	    } else {
    	    procura = head;
        	    for (int pos = 0; pos < size; ++pos) {
        	        if (procura->getInfo() == dado) {
        	            return &procura->getInfo();
                	 } else {
                	        procura = procura->getProximo();
                	    }
        	    }
        	    throw "Elemento não encontrado";
        	 }
    }

    //! Função Contém
    /*! Função booleana onde é criado um ponteiro auxiliar em que
     *  se percorre a lista comparando o parâmetro dado com as informações
     *  dos ponteiros. Caso seja igual retorna verdadeiro, caso se chegue no fim
     *  e não for igual, retorna falso.
     */
	bool contem(const T& dado) {
	    Elemento<T> *procura;
	    procura = head;
	    for (int pos = 0; pos < size; ++pos) {
        	        if (procura->getInfo() == dado) {
        	            return true;
                	 } else {
                	        procura = procura->getProximo();
                	    }
        	    }
        return false;
	}

    //! Função Retira da Posição
    /*! São criados dois ponteiros auxiliares onde um recebe o valor da cabeça
     *  da lista. Após um laço de repetição percorrer a lista um número de vezes
     *  igual ao parâmetro menos 2, o segundo ponteiro recebe o valor do próximo
     *  em relação ao anterior, e o ponteiro inicial muda o seu próximo para "pular"
     *  o segundo auxiliar. O Tamanho é decrementado, a informação do segundo ponteiro
     *  é salva numa variável auxiliar e retornada enquanto ele é deletado. Caso o
     *  parâmetro posição seja 1, a função retiraDoInicio() será chamada, e caso a posição
     *  seja inválida, uma exceção será lançada.
     */
	T retiraDaPosicao(int pos) {
	    Elemento<T> *anterior, *eliminar;
	    T retorno;

	    if (listaVazia()) {
	        throw "A lista está Vazia";
	    } else if (pos > size-1 || pos < 0) {
	            throw "Posição Inválida";
    	    } else if (pos == 0) {
    	            return retiraDoInicio();
        	    } else {
        	            anterior = head;
        	            for (int i = 0; i < pos-1; ++i) {
        	                anterior = anterior->getProximo();
        	            }
        	            eliminar = anterior->getProximo();
        	            anterior->setProximo(eliminar->getProximo());
        	            size -= 1;
        	            retorno = eliminar->getInfo();
        	            delete eliminar;
        	            return retorno;
        	        }
	}

    //! Função Adiciona no Fim
    /*! A função adicionaNaPosição será chamada com o parâmetro posição
     *  sendo igual ao tamanho da fila.
     */
	void adiciona(const T& dado) {
	    return adicionaNaPosicao(dado, size);
	}

    //! Função Retira do Fim
    /*! A função retiraDaPosição será chamada com o parâmetro  posição
     *  sendo igual ao tamanho da fila.
     */
	T retira() {
	    return retiraDaPosicao(size-1);
	}

    //! Função Retira Elemento Específico
    /*! é criado um inteiro qu recebe um valor a partir da função posicao()
     *  após o inteiro receber seu valor, a funcao retiraDaPosicao() é chamada.
     */
	T retiraEspecifico(const T& dado) {
	    int pos;

	    if (listaVazia()) {
	        throw "A lista está Vazia";
	    } else {
	            pos = posicao(dado);
	            return retiraDaPosicao(pos);
        	   }
        throw "Elemento não encontrado";
	}

    //! Função Adiciona em Ordem
    /*! Primeiro será criado um ponteiro auxiliar. Um laço de repetição será feito
     *  Comparando o parâmetro com os elementos da fila. Caso o parâmetro seja maior
     *  a função adicionaNaPosicao() será chamada na posicao atual. Caso após percorrer
     *  a lista e o parâmetro for maior, a função adicionaNoFim() será chamada.
     */
	void adicionaEmOrdem(const T& data) {
	    Elemento<T>* atual;
	    int pos;

	    if (listaVazia()) {
	        adicionaNoInicio(data);
	    } else {
	            atual = head;
	            pos = 0;
	            while (atual->getProximo() != nullptr &&
	                   maior(data, atual->getInfo())) {
	                    atual = atual->getProximo();
	                    pos += 1;
	               }

	               if (maior(data, atual->getInfo())) {
	                    adiciona(data);
	               } else {
	                    adicionaNaPosicao(data, pos);
	                    }
	        }
	}

    //! Função Lista Vazia
    /*! Função booleana que retorna verdadeiro caso o tamanho da Fila
     *  seja 0, e falso caso contrário
     */
	bool listaVazia() const {
	    return size == 0;
	}

    //! Função Igual
    /*! Função booleana que retorna verdadeiro caso o primeiro parâmetro seja
     *  igual ao segundo e falso caso contrário.
     */
	bool igual(T dado1, T dado2) {
	    return dado1 == dado2;
	}

    //! Função Maior
    /*! Função booleana que retorna verdadeiro caso o primeiro parâmetro seja
     *  maior ao segundo e falso caso contrário.
     */
	bool maior(T dado1, T dado2) {
	    return dado1 > dado2;
	}

    //! Função Menor
    /*! Função booleana que retorna verdadeiro caso o primeiro parâmetro seja
     *  menor ao segundo e falso caso contrário.
     */
	bool menor(T dado1, T dado2) {
	    return dado1 < dado2;
	}

    //! Função Destrói Lista
    /*! Função feita para se chamar o destrutor de todos os elemento da Lista.
     */
	void destroiLista() {
        Elemento<T> *anterior;
        anterior = head;
        while (anterior != nullptr) {
            anterior = anterior->getProximo();
            delete head;
            head = anterior;
        }
        size = 0;
        delete head;
	}
};
#endif
