//  "Copyright [2016] <Gustavo Figueira Olegário>"
#ifndef NO_AVL_HPP
#define NO_AVL_HPP
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
/**
 * @brief      Implementação Árvore AVL
 *
 * @param      dado       Ponteiro do dado genérico do vértice
 * @param      esquerda   Ponteiro para o vértice a esquerda
 * @param      direita    Ponteiro para o vértice a direita
 * @param      elementos  Vetor de elementos percorridos nas recursões
 * @param      altura     Altura do nó
 */
class NoAVL {
 private:
    int altura;  //!< Representa a altura do nó AVL
    T* dado;
    NoAVL<T>* esquerda;
    NoAVL<T>* direita;
    std::vector<NoAVL<T>* > elementos;

 public:
    /**
     * @brief                 Método construtor. Ponteiros apontados para
     *                        nulo por padrão e altura 0.
     *
     * @param      data       Dado que o nó guardará
     */
    explicit NoAVL(const T& data) {
        dado = new T (data);
        esquerda = nullptr;
        direita = nullptr;
        altura = 0;
    }

    /**
     * @brief              Método para realizar uma rotação simples baseado no nodo
     *                     deasbalanceado, quando o problema está do lado esquerdo.
     *                     Depois de realizar a troca dos nodos,
     *                     a altura é atualizada e retornamos a nova raiz
     *
     * @param      x       Nodo desbalanceado
     */
    NoAVL<T>* simp_roda_esq(NoAVL<T>* x) {
        NoAVL<T>* y = x->getDireita();
        NoAVL<T>* t2 = y->getEsquerda();

        y->esquerda = x;
        x->direita = t2;

        atualiza_altura(x);
        atualiza_altura(y);

        return y;
    }

    /**
     * @brief              Método para realizar uma rotação simples baseado no nodo
     *                     deasbalanceado, quando o problema está do lado direito.
     *                     Depois de realizar a troca dos nodos,
     *                     a altura é atualizada e retornamos a nova raiz
     *
     * @param      y       Nodo desbalanceado.
     */
    NoAVL<T>* simp_roda_dir(NoAVL<T>* y) {
        NoAVL<T>* x = y->getEsquerda();
        NoAVL<T>* t2 = x->getDireita();

        x->direita = y;
        y->esquerda = t2;

        atualiza_altura(y);
        atualiza_altura(x);

        return x;
    }

    /**
     * @brief              Método destrutor.
     *
     */
    virtual ~NoAVL() {

    }

    /**
     * @brief              Método "get" do atributo altura.
     *
     */
    int getAltura() {
        return altura;
    }

    /**
     * @brief              Método para calcular a altura de um nodo. Se
     *                     o nodo for um ponteiro nulo, a altura, por padrão,
     *                     é -1. Caso contrário, retronará a altura do nodo.
     *
     * @param      nodo    Nodo que terá sua altura calculada.
     */
    int calc_altura(NoAVL<T>* nodo) {
        if (nodo == nullptr) {
            return -1;
        } else {
            return nodo->getAltura();
        }
    }

    /**
     * @brief              Método para verificar se a árvore está desbalanceada.
     *                     O método calcula a diferença das alturas entre os dois
     *                     nodos filhos de um nodo raiz.
     *
     * @param      arv     Nodo que será verificado
     */
    int calc_bal(NoAVL<T>* arv) {
        if (arv == nullptr) {
            return 0;
        } else {
            int alt = calc_altura(arv->getEsquerda()) -
                  calc_altura(arv->getDireita());
            return alt;
        }
    }

    /**
     * @brief              Método "get" para o atributo elementos.
     *
     */
    std::vector<NoAVL<T>* > getElementos() {
        return elementos;
    }

    /**
     * @brief              Método "get" para o atributo esquerda.
     *
     */
    NoAVL<T>* getEsquerda() {
        return esquerda;
    }

    /**
     * @brief              Método "get" para o atributo direita.
     *
     */
    NoAVL<T>* getDireita() {
        return direita;
    }

    /**
     * @brief              Método para inserir um novo elemento na árvore.
     *                     Primeiro verificamos se queremos inserir na direita
     *                     ou na esquerda. Quando acharmos um ponteiro nulo,
     *                     significa que podemos inserir. Depois atualiazamos
     *                     as alturas e verificamos se a árvore percisa ser
     *                     balanceada.
     *
     * @param      data    Dado que será insirido
     * @param      arv     Árvore em que queremos inserir o dado
     */
    NoAVL<T>* inserir(const T& data, NoAVL<T>* arv) {
        if (arv == nullptr) {
            return new NoAVL<T>(data);
        }
        if (data < *arv->getDado()) {
            arv->esquerda = inserir(data, arv->getEsquerda());
        } else {
            arv->direita = inserir(data, arv->getDireita());
        }

        atualiza_altura(arv);

        int bal = calc_bal(arv);

        if (bal > 1 && data < *arv->getEsquerda()->getDado()) {
            return simp_roda_dir(arv);
        }
        if (bal < -1 && data > *arv->getDireita()->getDado()) {
            return simp_roda_esq(arv);
        }
        if (bal > 1 && data > *arv->getEsquerda()->getDado()) {
            arv->esquerda = simp_roda_esq(arv->getEsquerda());
            return simp_roda_dir(arv);
        }
        if (bal < -1 && data < *arv->getDireita()->getDado()) {
            arv->direita = simp_roda_dir(arv->getDireita());
            return simp_roda_esq(arv);
        }
        return arv;
    }

    /**
     * @brief              Método para remover um dado da árvore. Primeiro
     *                     verificamos se o dado está na esquerda ou na direita
     *                     Depois de encontrar o dado, ajustamos os ponteiros
     *                     para que nenhum endereço de memória seja perdido.
     *                     Em seguida, apagamos o dado e por último atualizamos
     *                     as alturas e verificamos se a árvore não
     *                     está desbalanceada.
     *
     * @param      data    Dado que queremos remover.
     * @param      arv     Árvore que iremos retirar o dado.
     */
    NoAVL<T>* remover(NoAVL<T>* arv, const T& data) {
        if (arv == nullptr) {
            return arv;
        }
        if (data <  *arv->getDado()) {
            arv->esquerda = remover(arv->getEsquerda(), data);
        } else if (data > *arv->getDado()) {
            arv->direita = remover(arv->getDireita(), data);
        } else {
            if (arv->getEsquerda() == nullptr || arv->getDireita() == nullptr) {
                NoAVL<T> *tmp;
                if (arv->getEsquerda() !=nullptr) {
                    tmp = arv->getEsquerda();
                } else {
                    tmp = arv->getDireita();
                }

                if (tmp == nullptr) {
                    tmp = arv;
                    arv = nullptr;
                } else {
                    *arv = *tmp;
                    delete tmp;
                }
            } else {
             NoAVL<T>* tmp = minimo(arv->getDireita());
             arv->dado = tmp->getDado();
             arv->direita = remover(arv->getDireita(), *tmp->getDado());
            }
        }

        if (arv == nullptr) {
            return arv;
        }

        atualiza_altura(arv);

        int bal = calc_bal(arv);

        if (bal > 1 && calc_bal(arv->getEsquerda()) >= 0) {
            return simp_roda_dir(arv);
        }
        if (bal > 1 && calc_bal(arv->getEsquerda()) < 0) {
            arv->esquerda = simp_roda_esq(arv->getEsquerda());
            return simp_roda_dir(arv);
        }
        if (bal < -1 && calc_bal(arv->getDireita()) > 0) {
            arv->direita = simp_roda_dir(arv->getDireita());
            return simp_roda_esq(arv);
        }
        if (bal < -1 && calc_bal(arv->getDireita()) <= 0) {
            return simp_roda_esq(arv);
        }

        return arv;
    }

    /**
     * @brief              Método para atualizar a altura de um nodo.
     *                     Pegamos a altura máxima entre os nodos filhos
     *                     , somamos com 1 e atribuímos à altura.
     *
     * @param      arv     Nodo que terá sua altura atualizada
     */
    void atualiza_altura(NoAVL<T> *arv) {
        arv->altura = max(calc_altura(arv->getEsquerda()),
                       calc_altura(arv->getDireita())) + 1;
    }

    /**
     * @brief              Método para encontrar o menor elemento de
     *                     uma árvore.
     *
     * @param      nodo    Árvore que será verificada.
     */
    NoAVL<T>* minimo(NoAVL<T>* nodo) {
        NoAVL<T>* aux;
        aux = nodo;
        while (aux->getEsquerda() != nullptr) {
            aux = aux->getEsquerda();
        }
        return aux;
    }

    /**
     * @brief              Método "get" para o atributo dado
     *
     */
    T* getDado() {
        return dado;
    }

    /**
     * @brief              Método para buscar se um dado existe na árvore.
     *
     * @param      arv     Árvore que será verificada
     * @param      data    Dado que será buscado
     */
    T* busca(const T& data, NoAVL<T>* arv) {
        while (arv != nullptr && *arv->getDado() != data) {
            if (*arv->getDado() < data) {
                arv = arv->getDireita();
            } else {
                arv = arv->getEsquerda();
            }
        }
        if (arv == nullptr) {
            throw std::runtime_error("Erro dado não existe.");
        } else {
            return arv->getDado();
        }
    }

    /**
     * @brief                 Método para ordenar os elementos na ordem meio
     *                        esquerda direita.
     *
     * @param      nodo       Arvore que será ordenada.
     *
     */
    void preOrdem(NoBinario<T>* nodo) {
        if (nodo != nullptr) {
            elementos.push_back(nodo);
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }

    /**
     * @brief                 Método para ordenar os elementos na ordem esquerda
     *                        meio direita.
     *
     * @param      nodo       Arvore que será ordenada.
     *
     */
    void emOrdem(NoBinario<T>* nodo) {
        if (nodo != nullptr) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }

    /**
     * @brief                 Método para ordenar os elementos na ordem esquerda
     *                        direita meio.
     *
     * @param      nodo       Arvore que será ordenada.
     *
     */
    void posOrdem(NoBinario<T>* nodo) {
        if (nodo != nullptr) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }

    /**
     * @brief              Método para encontrar o máximo entre dois dados.
     *
     * @param      dado1   Primeiro dado que será comparado
     * @param      dado2   Segundo dado que será comparado com o primeiro.
     */
    T max(T dado1, T dado2) {
        if (dado1 > dado2) {
            return dado1;
        } else {
            return dado2;
        }
    }
};

#endif /* NO_AVL_HPP */
