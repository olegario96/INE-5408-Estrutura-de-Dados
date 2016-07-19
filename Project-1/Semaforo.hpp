// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#ifndef SEMAFORO_HPP
#define SEMAFORO_HPP

#include <stdexcept>
#include "Pista.hpp"

class Semaforo {
 private:
    /*! \brief Pista de entrada no semáforo.
     *
     */
	Pista *pistaEnt;
    /*! \brief Primeira pista de saída.
     *
     */
	Pista *saida1;
    /*! \brief Segunda pista de saída.
     *
     */
	Pista *saida2;
    /*! \brief Terceira pista de saída.
     *
     */
	Pista *saida3;
    int s1;
    int s2;
    int s3;

 public:
	Semaforo(Pista *pEnt, Pista *sai1, Pista *sai2, Pista *sai3, int esq, int ret, int dir);
 	void transicao();
    Pista* calculaCurva();
    int getTempoResolucao();
    void setTempoResolucao();
};
#endif
