// Copyright [2016] <Gustavo Olegário>
#include <stdexcept>
#include "Elemento.hpp"
#include "ListaEnc.hpp"

template<typename T>

class PilhaEnc : private ListaEnc<T>{
 public:
    PilhaEnc() : ListaEnc<T>::ListaEnc() {}

    ~PilhaEnc() {
        limparPilha();
    }

    void empilha(const T& dado) {
        ListaEnc<T>::adicionaNoInicio(dado);
    }

    T desempilha() {
        if (PilhaVazia()) {
            throw std::runtime_error("Erro pilha vazia");
        } else {
           return ListaEnc<T>::retiraDoInicio();
        }
    }

    T topo() {
        if (PilhaVazia()) {
            throw std::runtime_error("Erro pilha vazia.");
        } else {
            return ListaEnc<T>::getHead()->getInfo();
        }
    }

    void limparPilha() {
        ListaEnc<T>::destroiLista();
    }

    bool PilhaVazia() {
        return ListaEnc<T>::listaVazia();
    }

    Elemento<T> *getHead() {
        return head;
    }
};
