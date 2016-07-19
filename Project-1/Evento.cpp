// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#include "Evento.hpp"

    /*! \brief Método construtor
     *
     */
    Evento::Evento(Pista *pist, Semaforo *semaf, int tempoReso, int tipoEve, int pEvSem) {
        pista = pist;
        sem = semaf;
        tempoResolucao = tempoReso;
    	tipoEvento = tipoEve;
        periodoEvSem = pEvSem;
    }

    /*! \brief Método construtor (padrão).
     *
     */
    Evento::Evento() = default;

    /*! \brief Método destrutor (padrão)
     *
     */
    Evento::~Evento() = default;

    /*! \brief Método para resolver cada um dos tipos dos três eventos.
     *         Se for um evento do tipo limpa a pista, toda os carros da
     *         pista serão eliminados. Se for um evento do tipo adicionar
     *         carro, um novo carro será colocado no fim da fila. E por último
     *         se for transição, a transição será feita.
     *
     */
    void Evento::resolucao() {
        switch(tipoEvento) {
            case limpaPista: pista->limpaPista(); break;
            case adicionaCarro: { int tam = (rand() % 7) + 1;
                                 Carro *novo = new Carro(tam, 0);
                                 novo->setTurn(0);
                                 pista->adicionaNoFim(*novo);
                                 break;
            }
            case transicaoSem: sem->transicao(); break;
            default: throw std::runtime_error("Tipo de Evento não compatível"); break;
        }
    }

    /*! \brief Método que retorna o período de cada tipo de evento.
     *
     */
    int Evento::periodo() {
        switch (tipoEvento) {
            case limpaPista: return 30; break;
            case adicionaCarro: return pista->calculaFreq(); break;
            case transicaoSem: return 5*periodoEvSem; break;
            default: throw std::runtime_error("tipo de Evento não especificado"); break;
        }
    }

    /*! \brief Método 'get' do atributo tempoResolucao.
     *
     */
    int Evento::getTempoResolucao() {
    	return tempoResolucao;
    }

    /*! \brief Método 'set' do atributo tempoResolucao.
     *
     */
    void Evento::setTempoResolucao(int novoTempo) {
        tempoResolucao = novoTempo;
    }

    /*! \brief Método 'get' do atributo PeriodoEvSem.
     *
     */
    int Evento::getPeriodoEvSem() {
        return periodoEvSem;
    }

    int Evento::getTipoEvento() {
        return tipoEvento;
    }
