// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#include "Carro.hpp"

    /*! \brief Método construtor
     *
     */
    Carro::Carro(int tamanho, int turno) {
    	tam = tamanho;
    	turn = turno;
    }

    /*! \brief Método construtor (padrão).
     *
     */
    Carro::Carro() = default;

    /*! \brief Método destrutor (padrão).
     *
     */
    Carro::~Carro() = default;

    /*! \brief Método 'get' do atributo tamanho.
     *
     */
    int Carro::getTam() {
    	return tam;
    }

    /*! \brief Método 'get' do atributo turno.
     *
     */
    int Carro::getTurn() {
    	return turn;
    }

    /*! \brief Método 'set' do atributo turno.
     *
     */
    int Carro::setTurn(int turno) {
    	turn = turno;
    	return turn;
    }

