// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#ifndef PISTA_HPP
#define PISTA_HPP

#include <stdexcept>
#include "FilaEnc.hpp"
#include "Carro.hpp"

/*! \brief Classe pista. Uma extensão da clase Fila Encadeada do tipo "Carro"
 *
 */
class Pista : private FilaEnc<Carro> {
 private:
 	/*! \brief Velocidade permitida na pista.
     *
     */
 	int velocidade;
 	/*! \brief Tamanho da pista.
     *
     */
 	int tamanho;
 	/*! \brief Frequência auxiliar para ajudar no cálculo
 	 *         da frequência final de geração de carros.
     *
     */
    int frequenciaAux;
    /*! \brief Frequência padrão para gerar carros na pista
     *
     */
 	int frequenciaBase;
 	/*! \brief Espaço disponível na pista.
     *
     */
 	int tamRestante;

    /*! \brief Número de carros que entraram.
     *
     */
    int carrosEnt;
    /*! \brief Número de carros que sairam
     *
     */
    int carrosSai;

 public:
 	Pista(int vel, int tam, int faux, int fbase, int tamrest, int carEnt, int carSai);
 	~Pista();
 	Carro retiraDoInicio();
 	void adicionaNoFim(Carro carro);
    int calculaFreq();
 	int calculaTurno();
    Elemento<Carro>* getHead();
 	void decrementa();
    bool pistaVazia();
 	bool pistaCheia();
 	int getTamRestante();
 	int getTamanho();
    int getCarrosEnt();
    int getCarrosSai();
    int getSize();
 	void limpaPista();
};
#endif
