// Copyright 2016 <Otto Menegasso Pires>
//                <Gustav Figueira Olegário>
#include "Carro.hpp"
#include "Pista.hpp"
#include "Semaforo.hpp"
#include "Evento.hpp"
#include "Relogio.hpp"
#include <cstdlib>


/*! \brief As 14 pistas usadas na nossa simulação.
 *
 */
Pista *S1sul;
Pista *S1norte;
Pista *S2sul;
Pista *S2norte;
Pista *L1leste;
Pista *L1oeste;
Pista *N2sul;
Pista *N2norte;
Pista *N1sul;
Pista *N1norte;
Pista *O1leste;
Pista *O1oeste;
Pista *C1leste;
Pista *C1oeste;

/*! \brief Os 8 semáforos da nossa simulação.
 *
 */
Semaforo *S11;
Semaforo *S12;
Semaforo *S13;
Semaforo *S14;
Semaforo *S21;
Semaforo *S22;
Semaforo *S23;
Semaforo *S24;

int main(int argc, char **argv) {
    /*! \brief Inicializando o relógio
     *
     */
    Relogio temporizador(0);
    printf("Relogio Iniciado\n");

    /*! \brief Inicializando as pistas.
     *
     */
    S1sul = new Pista(60, 500, 0, 0, 500, 0, 0);
    S1norte = new Pista(60, 500, 7, 30, 500, 0, 0);
    S2sul = new Pista(40, 500, 0, 0, 500, 0, 0);
    S2norte = new Pista(40, 500, 15, 60, 500, 0, 0);
    L1leste = new Pista(30, 400, 0, 0, 400, 0, 0);
    L1oeste = new Pista(30, 400, 2, 10, 400, 0, 0);
    N2sul = new Pista(40, 500, 5, 20, 500, 0, 0);
    N2norte = new Pista(40, 500, 0, 0, 500, 0, 0);
    N1sul = new Pista(60, 500, 5, 20, 500, 0, 0);
    N1norte = new Pista(60, 500, 0, 0, 500, 0, 0);
    O1leste = new Pista(80, 2000, 2, 10, 2000, 0, 0);
    O1oeste = new Pista(80, 2000, 0, 0, 2000, 0, 0);
    C1leste = new Pista(60, 300, 0, 0, 300, 0, 0);
    C1oeste = new Pista(60, 300, 0, 0, 300, 0, 0);
    printf("Pistas Iniciadas\n");

    /*! \brief Inicializando os semáforos
     *
     */
    S11 = new Semaforo(N1sul, C1leste, S1sul, O1oeste, 80, 10, 10);
    S12 = new Semaforo(C1oeste, S1sul, O1oeste, N1norte, 30, 40, 30);
    S13 = new Semaforo(S1norte, O1oeste,N1norte, C1leste, 10, 10, 80);
    S14 = new Semaforo(O1leste, N1norte, C1leste, S1sul, 10, 80, 10);
    S21 = new Semaforo(N2sul, L1leste, S2sul, C1oeste, 40, 30, 30);
    S22 = new Semaforo(L1oeste, S2sul, C1leste, N2norte, 30, 30, 40);
    S23 = new Semaforo(S2norte, C1oeste, N2norte, L1leste, 30, 30, 40);
    S24 = new Semaforo(C1leste, N2norte, L1leste, S2sul, 30, 40, 30);
    printf("Semaforos Iniciados\n");

    /*! \brief Tempo de troca do semáforo.
     *
     */
    auto pEvSem = atoi(argv[3]);

    /*! \brief Inicializando os eventos
     *
     */
    Evento EvS1sul(S1sul, nullptr, 30, 1, 0);
    Evento EvS1norte(S1norte, nullptr,0, 2, 0);
    Evento EvS2sul(S2sul, nullptr, 30, 1, 0);
    Evento EvS2norte(S2norte, nullptr, 0, 2, 0);
    Evento EvL1leste(L1leste, nullptr, 30, 1, 0);
    Evento EvL1oeste(L1oeste, nullptr, 0, 2, 0);
    Evento EvN2sul(N2sul, nullptr, 0, 2, 0);
    Evento EvN2norte(N2norte, nullptr, 30, 1, 0);
    Evento EvN1sul(N1sul, nullptr, 0, 2, 0);
    Evento EvN1norte(N1norte, nullptr, 30, 1, 0);
    Evento EvO1leste(O1leste, nullptr, 0, 2, 0);
    Evento EvO1oeste(O1oeste, nullptr, 30, 1, 0);
    Evento EvS11(nullptr, S11, pEvSem, 3, pEvSem);
    Evento EvS12(nullptr, S12, 2*pEvSem, 3, pEvSem);
    Evento EvS13(nullptr, S13, 3*pEvSem, 3, pEvSem);
    Evento EvS14(nullptr, S14, 4*pEvSem, 3, pEvSem);
    Evento EvS21(nullptr, S21, pEvSem, 3, pEvSem);
    Evento EvS22(nullptr, S22, 2*pEvSem, 3, pEvSem);
    Evento EvS23(nullptr, S23, 3*pEvSem, 3, pEvSem);
    Evento EvS24(nullptr, S24, 4*pEvSem, 3, pEvSem);
    printf("Eventos Iniciados\n");

    /*! \brief Cria carros
     *
     */
    temporizador.adiciona(EvO1leste);
    temporizador.adiciona(EvN2sul);
    temporizador.adiciona(EvS1norte);
    temporizador.adiciona(EvS2norte);
    temporizador.adiciona(EvL1oeste);
    temporizador.adiciona(EvN1sul);

    /*! \brief Transições de semáforo
     *
     */
    temporizador.adiciona(EvS11);
    temporizador.adiciona(EvS12);
    temporizador.adiciona(EvS13);
    temporizador.adiciona(EvS14);
    temporizador.adiciona(EvS21);
    temporizador.adiciona(EvS22);
    temporizador.adiciona(EvS23);
    temporizador.adiciona(EvS24);

    /*! \brief Limpa as pistas
     *
     */
    temporizador.adiciona(EvS1sul);
    temporizador.adiciona(EvS2sul);
    temporizador.adiciona(EvL1leste);
    temporizador.adiciona(EvN2norte);
    temporizador.adiciona(EvN1norte);
    temporizador.adiciona(EvO1oeste);
    printf("Eventos Adicionados\n");

    /*! \brief Tempo total em segundos
     *
     */
    int turnos = std::atoi(argv[1]);

    /*! \brief Período para printar uma atualização
     *
     */
    int tempo = std::atoi(argv[2]);

    /*! \brief Relaório
     *
     */
   while (temporizador.getHead()->getInfo().getTempoResolucao() <= turnos) {
        if (temporizador.getHead()->getInfo().getTipoEvento() == 3) {
            printf("Tempo Global: %d - Transição\n", temporizador.getTempoGlobal());
        }
        temporizador.resolve();
        if (temporizador.getTempoGlobal() % tempo  == 0) {
            printf("Tempo Global: %d\n", temporizador.getTempoGlobal());
            printf(" Carros na Rua O1leste: %d\n Carros entraram na Rua O1leste: %d\n Carros sairam na Rua O1leste: %d\n",
                    O1leste->getSize(), O1leste->getCarrosEnt(), O1leste->getCarrosSai());

            printf("\n");
            printf(" Carros na Rua S1norte: %d\n Carros entraram na Rua S1norte: %d\n Carros sairam na Rua S1norte: %d\n",
                    S1norte->getSize(), S1norte->getCarrosEnt(), S1norte->getCarrosSai());

            printf("\n");
            printf(" Carros na Rua S2norte: %d\n Carros entraram na Rua S2norte: %d\n Carros sairam na Rua S2norte: %d\n",
                    S2norte->getSize(), S2norte->getCarrosEnt(), S2norte->getCarrosSai());

            printf("\n");
            printf(" Carros na Rua L1oeste: %d\n Carros entraram na Rua L1oeste: %d\n Carros sairam na Rua L1oeste: %d\n",
                    L1oeste->getSize(), L1oeste->getCarrosEnt(), L1oeste->getCarrosSai());

            printf("\n");
            printf(" Carros na Rua N2sul: %d\n Carros entraram na N2sul: %d\n Carros sairam na Rua N2sul: %d\n",
                    N2sul->getSize(), N2sul->getCarrosEnt(), N2sul->getCarrosSai());

            printf("\n");
            printf(" Carros na Rua N1sul: %d\n Carros entraram na Rua N1sul: %d\n Carros sairam na Rua N1sul: %d\n",
                    N1sul->getSize(), N1sul->getCarrosEnt(), N1sul->getCarrosSai());

            printf("\n");
            printf(" Carros na Rua C1oeste: %d\n Carros entraram na Rua C1oeste: %d\n Carros sairam na Rua C1oeste: %d\n",
                    C1oeste->getSize(), C1oeste->getCarrosEnt(), C1oeste->getCarrosSai());

            printf("\n");
            printf(" Carros na Rua C1leste: %d\n Carros entraram na Rua C1leste: %d\n Carros sairam na Rua C1leste: %d\n",
                    C1leste->getSize(), C1leste->getCarrosEnt(), C1leste->getCarrosSai());
            printf("\n");
            printf("-------------------------\n");
        }
   }

   /*! \brief Total de carros que entraram
     *
     */
    auto carrosEntrada = O1leste->getCarrosEnt() + N2sul->getCarrosEnt() + S1norte->getCarrosEnt() + S2norte->getCarrosEnt() + L1oeste->getCarrosEnt() + N1sul->getCarrosEnt();
    /*! \brief Total de carros que sairam
     *
     */
    auto carrosSaida = S1sul->getCarrosSai() + S2sul->getCarrosSai() + L1leste->getCarrosSai() + N2norte->getCarrosSai() + N1norte->getCarrosSai() + O1oeste->getCarrosSai();

    /*! \brief Relatório final
     *
     */
    printf("Número de carros que entraram no cruzamento: %d\n", carrosEntrada);
    printf("Número de carros que saíram do cruzamento: %d\n", carrosSaida);

    /*! \brief Desalocando a memória
     *
     */
    delete S1sul;
    delete S1norte;
    delete S2sul;
    delete S2norte;
    delete L1leste;
    delete L1oeste;
    delete N2sul;
    delete N2norte;
    delete N1sul;
    delete N1norte;
    delete O1leste;
    delete O1oeste;
    delete C1leste;
    delete C1oeste;

    delete S11;
    delete S12;
    delete S13;
    delete S14;
    delete S21;
    delete S22;
    delete S23;
    delete S24;

    return 0;
}
