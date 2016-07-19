// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#include "Semaforo.hpp"

    /*! \brief Método construtor
     *
     */
    Semaforo::Semaforo(Pista *pEnt, Pista *sai1, Pista *sai2, Pista *sai3, int esq, int ret, int dir) {
 		pistaEnt = pEnt;
 		saida1 = sai1;
 		saida2 = sai2;
 		saida3 = sai3;
 		s1 = esq;
 		s2 = ret;
 		s3 = dir;
 	}

  /*! \brief Método para fazer a transição de um carro de uma pista para outra.
   *         Se a pista de entrada estiver vazia ou a pista de saída estiver cheia
   *         haverá um erro. Caso contrário, a transição será executada para todos
   *         os carros que já estão no tempo de fazer a troca de pista.
   *
   */

  void Semaforo::transicao() {
      //printf("Transição\n");
      Pista *aux = calculaCurva();
      if (pistaEnt->getHead() == nullptr || pistaEnt->pistaVazia()) {
          printf("Não há carro para retirar\n\n");
      } else if (aux->pistaCheia() || aux->getTamRestante() < (pistaEnt->getHead()->getInfo().getTam() + 3)) {
          printf("Engarrafamento\n\n");
      } else {
          while (pistaEnt->getHead() != nullptr && pistaEnt->getHead()->getInfo().getTurn() == 0) {
              Carro saiCarro = pistaEnt->retiraDoInicio();
              saiCarro.setTurn(aux->calculaTurno());
              aux->adicionaNoFim(saiCarro);
          }
      }
      pistaEnt->decrementa();
  }

    /*! \brief Método para calcular a probabilidade um carro fazer a curva.
     *
     */
   	Pista* Semaforo::calculaCurva() {
   	    int aux = rand() % 100;
 		    if(aux < s1) {
 			      return saida1;
 		    } else if (aux < s1 + s2) {
 			      return saida2;
 		    } else if (aux < s1 + s2 + s3) {
 			      return saida3;
 		    }
    }
