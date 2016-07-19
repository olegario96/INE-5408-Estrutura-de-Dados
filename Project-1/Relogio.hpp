// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#ifndef RELOGIO_HPP
#define RELOGIO_HPP

#include "Evento.hpp"
#include "ListaEnc.hpp"

class Relogio : private ListaEnc<Evento> {
 private:
 	/*! \brief Tempo global
     *
     */
    int tempoGlobal;

 public:
    Relogio(int tempG);
    ~Relogio();
    void adiciona(Evento ev);
    void resolve();
    int getTempoGlobal();
    Elemento<Evento>* getHead();
};
#endif
