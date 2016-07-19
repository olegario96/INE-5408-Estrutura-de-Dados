// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#ifndef CARRO_HPP
#define CARRO_HPP

class Carro {
 private:
    /*! \brief Tamanho do carro
     *
     */
    int tam;
    // Tempo para chegar até o final da pista
    int turn;

 public:
    Carro();
    Carro(int tam, int turn);
    ~Carro();
    int getTam();
    int getTurn();
    int setTurn(int turn);
};
#endif
