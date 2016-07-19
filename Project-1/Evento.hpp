// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <stdexcept>
#include "Semaforo.hpp"
#include "Pista.hpp"

/*! \brief Enum dos 3 eventos possíveis do simulador
 *
 */
enum tipos { limpaPista      = 1,
             adicionaCarro   = 2,
             transicaoSem    = 3
           };

class Evento {
 private:
    /*! \brief Pista onde ocorrerá o evento
     *
     */
    Pista *pista;
    /*! \brief Semáforo para controlar os eventos
     *
     */
    Semaforo *sem;
    /*! \brief Tempo para resolver os eventos
     *
     */
    int tempoResolucao;
    /*! \brief Tipo de cada evento (ver comentário de enum).
     *
     */
    int tipoEvento;

    /*! \brief Periodo para a transição de cada semaforo
     *
     */
    int periodoEvSem;

 public:
    Evento();
    Evento(Pista *pista, Semaforo *sem, int tRes, int tEv, int pEvSem);
    ~Evento();

    void resolucao();
    int periodo();
    int getTempoResolucao();
    void setTempoResolucao(int novoTempo);
    int getPeriodoEvSem();
    int getTipoEvento();
};
#endif
