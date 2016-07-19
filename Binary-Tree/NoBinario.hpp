// "Copyright [2016] <Gustavo Figueira Olegário>"
#ifndef NO_BINARIO_HPP
#define NO_BINARIO_HPP

#include <cstdlib>
#include <vector>
#include <stdexcept>

template <typename T>
/**
 * @brief      Implementação Árvore binária
 *
 * @param      dado       Ponteiro do dado genérico do vértice
 * @param      esquerda   Ponteiro para o vértice a esquerda
 * @param      direita    Ponteiro para o vértice a direita
 * @param      elementos  Vetor de elementos percorridos nas recursões
 */
class NoBinario {  // Documentacao
 private:
    T* dado;
    NoBinario<T>* esquerda;
    NoBinario<T>* direita;
    std::vector<NoBinario<T>* > elementos;  //!< Elementos acessados durante
                                            // o percurso realizado

 public:
    /**
     * @brief                 Método construtor
     *
     * @param      data       Dado que o vértice guardará
     */
    NoBinario<T>(const T& data) {
        dado = new T(data);
        esquerda = nullptr;
        direita = nullptr;
    }

    /**
     * @brief                 Método destrutor
     *
     */
    virtual ~NoBinario() {
        delete dado;
    }

    /**
     * @brief                 Método 'get' do atribudo dado
     *
     */
    T* getDado() {
        return dado;
    }

    /**
     * @brief                 Método 'get' do atributo elementos
     *
     */
    std::vector< NoBinario<T>* > getElementos() {
        return elementos;
    }

    /**
     * @brief                 Método 'get' do atributo esquerda
     *
     */
    NoBinario<T>* getEsquerda() {
        return esquerda;
    }

    /**
     * @brief                 Método 'get' do atributo direita
     *
     */
    NoBinario<T>* getDireita() {
        return direita;
    }

    /**
     * @brief                 Método 'set' do atributo esquerda
     *
     * @param      *nodo       Novo vértice que o vértice atual irá apontar no
     *                        lado esquerdo
     */
    void setEsquerda(NoBinario<T>* nodo) {
        esquerda = nodo;
    }

    /**
     * @brief                 Método 'set' do atributo direita
     *
     * @param      *nodo       Novo vértice que o vértice atual irá apontar no
     *                        lado direito
     */
    void setDireita(NoBinario<T>* nodo) {
        direita = nodo;
    }

    /**
     * @brief                 Método 'set' do atributo dado
     *
     * @param      data       Dado que o vértice apontará
     */
    void setDado(T *data) {
        dado = data;
    }

    /**
     * @brief                 Método para verificar se um dado existe na árvore
     *                        ou não.
     *
     * @param      data       Dado que será verificado se pertence ou não a ár-
     *                        vore.
     * @param      *arv       Árvore onde será verificado se o dado existe.
     */
    T* busca(const T& data, NoBinario<T>* arv) {
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
     * @brief                 Método para inserir um novo vértice na árvore.
     *
     * @param      data       Dado que será inserido.
     *
     * @param      arv        Árvore onde o vértice será inserido.
     */
    NoBinario<T>* inserir(const T& data, NoBinario<T>* arv) {
        NoBinario *novoNodo;
        if (data < *arv->getDado()) {
            // Inserção à esquerda.
            if (arv->getEsquerda() == nullptr) {
                novoNodo = new NoBinario(data);
                arv->setEsquerda(novoNodo);
            } else {
                arv = inserir(data, arv->getEsquerda());
            }
        } else {
            // Inserção à direita.
            if (arv->getDireita() == nullptr) {
                novoNodo = new NoBinario(data);
                arv->setDireita(novoNodo);
            } else {
                arv = inserir(data, arv->getDireita());
            }
        }
        return arv;
    }

   /**
     * @brief                 Método para remover um novo vértice na árvore.
     *
     * @param      data       Dado que será removido.
     *
     * @param      arv        Árvore onde o vértice será removido.
     */
    NoBinario<T>* remover(NoBinario<T>* arv, const T& data) {
        NoBinario<T> *tmp, *filho;
        if (arv == nullptr) {
            return arv;
        } else {
            if (data < *arv->getDado()) {  // Vá à esquerda.
                arv->setEsquerda(remover(arv->getEsquerda(), data));
                return arv;
            } else {
                if (data > *arv->getDado()) {  // Vá à direita.
                    arv->setDireita(remover(arv->getDireita(), data));
                    return arv;
                } else {  // Encontrei elemento que quero deletar
                    if (arv->getDireita() != nullptr &&
                        arv->getEsquerda() != nullptr) {  // 2 filhos
                        tmp = minimo(arv->getDireita());
                        arv->setDado(tmp->getDado());
                        arv->setDireita(remover(arv->getDireita(),
                                         *arv->getDado()));
                        return arv;
                    } else {  // 1 filho
                        tmp = arv;
                        if (arv->getDireita() != nullptr) {  // Filho à direita
                            filho = arv->getDireita();
                            return filho;
                        } else {
                            if (arv->getEsquerda() != nullptr) {  // Filho à esq
                                filho = arv->getEsquerda();
                                return filho;
                            } else {  // Folha
                                delete arv;
                                return nullptr;
                            }
                        }
                    }
                }
            }
        }
    }

    /**
     * @brief                 Método para verificar quem é o menor nodo
     *
     * @param      nodo       Árvore que será verificada.
     *
     */
    NoBinario<T>* minimo(NoBinario<T>* nodo) {
        if (nodo->getEsquerda() == nullptr) {
            return nodo;
        } else {
            return nodo = minimo(nodo->getEsquerda());
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
};

#endif /* NO_BINARIO_HPP */
