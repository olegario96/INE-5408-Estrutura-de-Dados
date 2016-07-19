// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#include "Relogio.hpp"

    /*! \brief Método construtor
     *
     */
    Relogio::Relogio(int global) {
        tempoGlobal = global;
    }

    /*! \brief Método destrutor (padrão)
     *
     */
    Relogio::~Relogio() = default;

    /*! \brief Método para adicionar um novo evento na lista de eventos a serem resolvidos.
     *         O método verificará onde o evento se encaixa na lista comparando pelo tempo.
     *         Depois de fazer a verificação, faz a inserção.
     *
     */
    void Relogio::adiciona(Evento ev) {
        int pos = 0;
        Elemento<Evento>* aux = ListaEnc<Evento>::getHead();

        if (ListaEnc<Evento>::listaVazia()) {
            ListaEnc<Evento>::adicionaNoInicio(ev);
        } else {
            while (aux->getProximo() != nullptr &&
                   ev.getTempoResolucao() >= aux->getInfo().getTempoResolucao()) {

                     aux = aux->getProximo();
                     pos += 1;
            }
            if (ev.getTempoResolucao() >= aux->getInfo().getTempoResolucao()) {
                ListaEnc<Evento>::adiciona(ev);
            } else {
                ListaEnc<Evento>::adicionaNaPosicao(ev, pos);
            }

        }
    }

    /*! \brief Método para resolver os eventos da lista. Se o tempo de resolução do evento
     *         for menor ou igual ao tempo global ele deverá ser resolvido. Primeiro, o
     *         evento é removido da lista. Depois ele será resolvido. Por padrão, em nosso
     *         projeto, sempre que um evento é resolvido, um evento do mesmo tipo é gerado
     *         para ser resolvido daqui a tempoGlobal + periodo.;
     *
     */
    void Relogio::resolve() {
        Elemento<Evento> *cabeca = ListaEnc<Evento>::getHead();

        if (ListaEnc<Evento>::listaVazia()) {
            throw std::runtime_error("Todos os Eventos estão completos");
        } else if (cabeca->getInfo().getTempoResolucao() <= tempoGlobal) {
            Evento aux = ListaEnc<Evento>::retiraDoInicio();
            aux.resolucao();
            int tempoNovo = aux.periodo() + tempoGlobal;
            Evento novo = aux;
            novo.setTempoResolucao(tempoNovo);
            adiciona(novo);
        } else {
            tempoGlobal = cabeca->getInfo().getTempoResolucao();
        }
    }

    /*! \brief Método 'get' do atributo tempoGlobal.
     *
     */
    int Relogio::getTempoGlobal() {
        return tempoGlobal;
    }

    /*! \brief Método 'get' para a cabeça de lista dos eventos
     *
     */
    Elemento<Evento>* Relogio::getHead() {
        return ListaEnc<Evento>::getHead();
    }
