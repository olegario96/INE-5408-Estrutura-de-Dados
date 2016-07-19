// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#include "Pista.hpp"
#include <iostream>

    /*! \brief Método construtor
     *
     */
    Pista::Pista(int velo, int tam, int freqaux, int freq, int tamRes, int carEnt, int carSai) {
 		velocidade = velo;
 		tamanho = tam;
        frequenciaAux = freqaux;
 		frequenciaBase = freq;
 		tamRestante = tamRes;
        carrosEnt = carEnt;
        carrosSai = carSai;
 	}

 	/*! \brief Método destrutor (padrão).
 	 *
 	 */
    Pista::~Pista() = default;

 	/*! \brief Método para retirar um carro da fila.
 	 *         Verifica se está vazia e realiza a operação.
 	 *
 	 */
 	Carro Pista::retiraDoInicio() {
 		if (pistaVazia()) {
 			printf("Erro pista vazia.\n");
 		} else {
 			Carro aux = FilaEnc<Carro>::retira();
 			tamRestante = tamRestante + aux.getTam() + 3;
            //printf("Carro retirado!\n");
            carrosSai += 1;
 			return aux;
 		}
 	}

 	/*! \brief Método para adicionar um carro no fim da fsila.
 	 *         Verifica se a pista cheia e realiza a operação.
 	 *
 	 */
 	void Pista::adicionaNoFim(Carro carro) {
 		if (!pistaCheia() && tamRestante > (carro.getTam() + 3)) {
 				tamRestante = tamRestante - (carro.getTam() + 3);
 				FilaEnc<Carro>::inclui(carro);
                carrosEnt += 1;
                //printf("Carro adicionado!\n");
 			} else {
 				printf("Engarrafamento\n");
 			}
 	}

    /*! \brief Calcula a frequência para gerar os carros.
     *
     */
    int Pista::calculaFreq() {
        int aux = rand() % (frequenciaAux+1);
        return frequenciaBase - aux;
    }


 	/*! \brief Calcula o tempo que o carro leva para atravessar a pista.
 	 *
 	 */
 	int Pista::calculaTurno() {
 		return (tamanho / (velocidade/3.6));
 	}

    /*! \brief Método 'get' para ver o primeiro carro da fila.
     *
     */
    Elemento<Carro>* Pista::getHead() {
        return FilaEnc<Carro>::getHead();
    }

    /*! \brief Método para 'setar' o turno dos carros para zero, para que
     *         quando o semáforo estiver verde todos os carros poderem fazer
     *         a transição de pista.
     *
     */
    void Pista::decrementa() {
        Elemento<Carro>* aux = FilaEnc<Carro>::getHead();
        for (int i = 0; i < FilaEnc<Carro>::getSize(); ++i) {
            aux->getInfo().setTurn(0);
            aux = aux->getProximo();
        }
    }

 	/*! \brief Método para verificar se a pista está vazia.
 	 *
 	 */
 	bool Pista::pistaVazia() {
 		return tamRestante == tamanho;
 	}

 	/*! \brief Método para verificar se a pista está cheia.
 	 *
 	 */
 	bool Pista::pistaCheia() {
 		return tamRestante == 0;
 	}

 	/*! \brief Método 'get' do tamanhoRestante.
 	 *
 	 */
 	int Pista::getTamRestante() {
 		return tamRestante;
 	}

 	/*! \brief Método 'get' do tamanho.
 	 *
 	 */
 	int Pista::getTamanho() {
 		return tamanho;
 	}

    /*! \brief Método 'get' do atributo carrosEnt
     *
     */
    int Pista::getCarrosEnt() {
        return carrosEnt;
    }

    /*! \brief Método 'get' do atributo carrosSai
     *
     */
    int Pista::getCarrosSai() {
        return carrosSai;
    }

    /*! \brief Método 'get' para o tamanho da fila de carros.
     *
     */
    int Pista::getSize() {
        return FilaEnc<Carro>::getSize();
    }

 	/*! \brief Método para resolver os carros que precisam ser retirados.
 	 *
 	 */
 	void Pista::limpaPista() {
 		while (tamRestante < tamanho) {
 			retiraDoInicio();
        }
 	}
