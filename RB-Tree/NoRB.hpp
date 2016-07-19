//  "Copyright [2016] <Gustavo Olegário>"
#ifndef NO_RB_HPP
#define NO_RB_HPP

#include <vector>
#include <algorithm>
#include <exception>

#define RB_RUBRO true
#define RB_NEGRO false

template <typename T>
/**
 * @brief      Implementação Árvore RB
 *
 * @param      dado       Ponteiro do dado genérico do vértice
 * @param      esquerda   Ponteiro para o vértice a esquerda
 * @param      direita    Ponteiro para o vértice a direita
 * @param      elementos  Vetor de elementos percorridos nas recursões
 * @param      cor        Variável para verificar se o nodo é rubro ou negro
 */
class NoRB {
 private:
    T* dado;  //!< Atributo onde é guardado o valor representado pelo nó
    NoRB<T>* esquerda;  //!< Atributo que aponta para menor nó descendente
    NoRB<T>* direita;  //!< Atributo que aponta para maior nó descendente
    NoRB<T>* pai;  //!< Atributo que aponta para nó ascendente
    bool cor;  //!< Atributo que indica a getCor() do nó
    std::vector<NoRB<T>* > elementos;

 public:
    /**
     * @brief      Método construtor, para construir um novo nodo obviamente
     *             Por padrão, esquerda, direita e pai são nulos e a cor é
     *             negra.
     *
     * @param      data       Dado que o nodo apontará
     */
    explicit NoRB(const T& data) {
        dado = new T (data);
        esquerda = nullptr;
        direita = nullptr;
        pai = nullptr;
        cor = RB_NEGRO;
    }

    /**
     * @brief      Método destrutor. Apenas desalocamos o dado.
     *
     */
    virtual ~NoRB() {
        delete dado;
    }

    /**
     * @brief      Método que nos retorna um ponteiro para o nodo pai
     *
     */
    NoRB<T>* getPai() {
        return pai;
    }

    /**
     * @brief      Método para verificar a cor de um nodo. Por padrão,
     *             todo nullptr é um nodo de cor negra.
     *
     * @param      node       Ponteiro para o nó que será verificado
     */
    bool getCor(NoRB<T> *node) {
        if (node != nullptr) {
            return node->cor;
        } else {
            return RB_NEGRO;
        }
    }

    /**
     * @brief      Método qe retorna o atributo elementos, que é uma
     *             lista de ponteiros para nodos.
     *
     */
    std::vector<NoRB<T>* > getElementos() {
        return elementos;
    }

    /**
     * @brief      Método que retorna um ponteiro para o filho da esquerda.
     *
     */
    NoRB<T>* getEsquerda() {
        return esquerda;
    }

    /**
     * @brief      Método que retorna um ponteiro para o filho da direita.
     *
     */
    NoRB<T>* getDireita() {
        return direita;
    }


    /**
     * @brief      Método para rebalencear os nodos filhos e pai de uma árvore
     *             RB. A rotação será realizada do lado esquerdo da árvore.
     *             Após feita a rotação, os filhos poderão ser recoloridos
     *             para manter as propriedades originais da árvore.
     *
     * @param      arv       Raiz da árvore que será rotacionada
     */
    NoRB<T>* roda_esq(NoRB<T> *arv) {
        NoRB<T> *nodo, *tmp;

        nodo = arv->getEsquerda();
        arv->esquerda = nodo->getDireita();
        nodo->direita = arv;

        nodo->pai = arv->getPai();
        arv->pai = nodo;

        if (arv->getEsquerda() != nullptr) {
            arv->getEsquerda()->pai = arv;
        }

        tmp = nodo->getDireita();

        if (getCor(tmp->getDireita()) == RB_RUBRO) {
            if (nodo->getPai() != nullptr) {
                nodo->cor = RB_RUBRO;
            } else {
                nodo->cor = RB_NEGRO;
            }
            nodo->getEsquerda()->cor = RB_NEGRO;
            nodo->getDireita()->cor = RB_NEGRO;
        } else {
            nodo->cor = RB_NEGRO;
            tmp->cor = RB_RUBRO;
        }
        return nodo;
    }

    /**
     * @brief      Método para rebalencear os nodos filhos e pai de uma árvore
     *             RB. A rotação será realizada do lado direito da árvore.
     *             Após feita a rotação, os filhos poderão ser recoloridos
     *             para manter as propriedades originais da árvore.
     *
     * @param      arv       Raiz da árvore que será rotacionada
     */
    NoRB<T>* roda_dir(NoRB<T> *arv) {
        NoRB<T> *nodo, *tmp;

        nodo = arv->getDireita();
        arv->direita = nodo->getEsquerda();
        nodo->esquerda = arv;

        nodo->pai = arv->getPai();
        arv->pai = nodo;

        if (arv->getDireita() != nullptr) {
            arv->getDireita()->pai = arv;
        }

        tmp = nodo->getEsquerda();

        if (getCor(tmp->getEsquerda()) == RB_RUBRO) {
            if (nodo->getPai() != nullptr) {
                nodo->cor = RB_RUBRO;
            } else {
                nodo->cor = RB_NEGRO;
            }
            nodo->getEsquerda()->cor = RB_NEGRO;
            nodo->getDireita()->cor = RB_NEGRO;
        } else {
            nodo->cor = RB_NEGRO;
            tmp->cor = RB_RUBRO;
        }
        return nodo;
    }

    /**
     * @brief      Método para rebalencear os nodos filhos e pai de uma árvore
     *             RB. A rotação dupla consiste em duas rotações simples uma para
     *             cada lado.A rotação será feita para balancear o lado direito
     *             da árvore. Após feita a rotação, os filhos poderão ser recoloridos
     *             para manter as propriedades originais da árvore.
     *
     * @param      arv       Raiz da árvore que será rotacionada
     */
    NoRB<T>* roda_dup_dir(NoRB<T>* arv) {
        arv->direita = roda_esq(arv->getDireita());
        return roda_dir(arv);
    }

    /**
     * @brief      Método para rebalencear os nodos filhos e pai de uma árvore
     *             RB. A rotação dupla consiste em duas rotações simples uma para
     *             cada lado.A rotação será feita para balancear o lado esquerdo
     *             da árvore. Após feita a rotação, os filhos poderão ser recoloridos
     *             para manter as propriedades originais da árvore.
     *
     * @param      arv       Raiz da árvore que será rotacionada
     */
    NoRB<T>* roda_dup_esq(NoRB<T>* arv) {
        arv->esquerda = roda_dir(arv->getEsquerda());
        return roda_esq(arv);
    }

    /**
     * @brief      Método para fazer uma inserção simples em uma árvore
     *             binária. Verificamos se o dado é maior ou menor e
     *             vamos caminhando pela árvore até achar um nodo condi-
     *             zente e com o devido ponteiro vazio. Depois da inser-
     *             ção feita, colorimos o novo nodo filho e ajustamos os
     *             ponteiros.
     *
     * @param      data      Dado que iremos inserir.
     * @param      arv       Raiz da árvore que vamos fazer a inserção
     */
    NoRB<T>* inserirBin(const T& data, NoRB<T>* arv) {
        if (data < *arv->getDado()) {
        if (arv->esquerda == nullptr) {
            arv->esquerda = new NoRB<T>(data);
            arv->getEsquerda()->pai = arv;
            arv->getEsquerda()->cor = RB_RUBRO;
        } else {
            arv->esquerda = inserir(data, arv->esquerda);
        }
    } else {
        if (arv->direita == nullptr) {
            arv->direita = new NoRB<T>(data);
            arv->getDireita()->pai = arv;
            arv->getDireita()->cor = RB_RUBRO;
        } else {
            arv->direita = inserir(data, arv->direita);
        }
    }
    return arv;
    }

    /**
     * @brief      Método para inserir um novo nodo na nossa árvore RB.
     *             Fazemos uma inserção simples de árvore binária e depois
     *             fazemos uma verificação de violações para corrigir possíveis
     *             problemas de balanceamento e coloração.
     *
     * @param      data      Dado que iremos inserir.
     * @param      arv       Raiz da árvore que vamos fazer a inserção.
     */
    NoRB<T>* inserir(const T& data, NoRB<T>* arv) {
        arv = inserirBin(data, arv);
        return fixViolation(arv);
    }

    /**
     * @brief      Método para verificar se após a inserção, a árvore
     *             não está desbalanceada e se segue as propriedades
     *             originais. Será verificado os filhos e os netos da
     *             árvore e de acordo com a coloração de cada um faremos
     *             uma determinada rotação.
     *
     * @param      nodo      Árvore que será verificada
     */
    NoRB<T>* fixViolation(NoRB<T>* nodo) {
        if (getCor(nodo->getDireita()) == RB_RUBRO) {
            if (getCor(nodo->getDireita()->getDireita()) == RB_RUBRO) {
                return roda_dir(nodo);
            }
            if (getCor(nodo->getDireita()->getEsquerda()) == RB_RUBRO) {
                return roda_dup_dir(nodo);
            }
        }

        if (getCor(nodo->getEsquerda()) == RB_RUBRO) {
            if (getCor(nodo->getEsquerda()->getEsquerda()) == RB_RUBRO) {
                return roda_esq(nodo);
            }
            if (getCor(nodo->getEsquerda()->getDireita()) == RB_RUBRO) {
                return roda_dup_esq(nodo);
            }
       }
        return nodo;
    }

    /**
     * @brief      Procuramos o dado a ser deletado na árvore. Quando acharmos,
     *             o dado, verificamos se ele possui filhos ou não.Se ele tiver
     *             filhos, fazemos o ajuste de ponteiros, deletemos o dado e
     *             faremos uma verificação para ver se as propriedades da
     *             árvore como coloração e balanceamento foram mantidos.
     *
     * @param      arv      Raiz da árvore que será verificada
     * @param      data     Dado que será deletado
     */
    NoRB<T>* remover(NoRB<T>* arv, const T& data) {
         if (arv == nullptr) {
            throw std::runtime_error("Dado não está na árvore");
         } else {
            if (data < *arv->getDado()) {
                arv->esquerda = remover(arv->getEsquerda(), data);
            } else if (data > *arv->getDado()) {
                arv->direita = remover(arv->getDireita(), data);
            } else if (arv->getEsquerda() != nullptr &&
                       arv->getDireita() != nullptr) {
                *arv->dado = *minimo(arv->getDireita())->getDado();
                arv->direita = remover(arv->getDireita(), *arv->getDado());
            } else if (arv->getEsquerda() == nullptr &&
                       arv->getDireita() == nullptr) {
                delete arv;
                return nullptr;
            } else {
                NoRB<T> *tmp = arv;
                if (arv->getEsquerda() != nullptr) {
                    arv = arv->getEsquerda();
                } else {
                    arv = arv->getDireita();
                }
                arv->pai = tmp->getPai();
                tmp->esquerda = nullptr;
                tmp->direita = nullptr;
                delete tmp;
                return arv;
            }
            return fixViolation(arv);
         }
    }

    /**
     * @brief      Método para encontrar o nodo com menor valor
     *             de dado na árvore.
     *
     * @param      nodo      Árvore que será verificada.
     */
    NoRB<T>* minimo(NoRB<T>* nodo) {
        if (nodo->getEsquerda() == nullptr) {
            return nodo;
        } else {
            return minimo(nodo->getEsquerda());
        }
    }

    /**
     * @brief      Método que retorna o dado guardado por um nodo.
     */
    T* getDado() {
        return dado;
    }

    /**
     * @brief      Método para encontrar se um certo dado existe
     *             na árvore ou não. A árvore será iterada até achar
     *             o dado. Se achar um nullptr, verificamos
     *             exibimos uma mensagem de erro.
     *
     * @param      data      Dado que será buscado
     * @param      arv       Raiz da árvore que será verificada
     */
    T* busca(const T& data, NoRB<T>* arv) {
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
     * @brief      Método para colocar os nodos da árvore
     *             na lista "elementos" em preOrdem
     *
     * @param      nodo      Árvore que será ordenada
     */
    void preOrdem(NoRB<T>* nodo) {
        if (nodo !=nullptr) {
            elementos.push_back(nodo);
            preOrdem(nodo->getEsquerda());
            preOrdem(nodo->getDireita());
        }
    }

    /**
     * @brief      Método para colocar os nodos da árvore
     *             na lista "elementos" em emOrdem
     *
     * @param      nodo      Árvore que será ordenada
     */
    void emOrdem(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            emOrdem(nodo->getEsquerda());
            elementos.push_back(nodo);
            emOrdem(nodo->getDireita());
        }
    }

    /**
     * @brief      Método para colocar os nodos da árvore
     *             na lista "elementos" em posOrdem
     *
     * @param      nodo      Árvore que será ordenada
     */
    void posOrdem(NoRB<T>* nodo) {
        if (nodo != nullptr) {
            posOrdem(nodo->getEsquerda());
            posOrdem(nodo->getDireita());
            elementos.push_back(nodo);
        }
    }
};

#endif /* NO_RB_HPP */
