// Copyright 2015 Jean Martina

#include <vector>
#include <random>
#include <algorithm>
#include <cstdio>
#include "gtest/gtest.h"
#include "NoRB.hpp"

#define N_ITER       32

#define R_MIN    -2000000
#define R_MAX     2000000
#define R_SEED    42

#define RB_RUBRO     true
#define RB_NEGRO     false

#define size_int_array(x)   sizeof(x)/sizeof(int)

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class NoRBTest: public ::testing::Test {
 public:
    virtual void SetUp() {
        this->inteiro = new NoRB<int>(10);

        // Gerador de números aleatórios com seed R_SEED
        // e range entre R_MIN e R_MAX
        gen = std::mt19937(R_SEED);
        dis = std::uniform_int_distribution<>(R_MIN, R_MAX);
    }

    virtual void TearDown() {
        delete inteiro;
    }

 protected:
    NoRB<int> *inteiro;

    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
};

template <typename T>
void checkBinTree(NoRB<T>* arv) {
    NoRB<T>* esquerda = arv->getEsquerda();
    if (esquerda != nullptr) {
        ASSERT_LE(*esquerda->getDado(), *arv->getDado());
        checkBinTree(esquerda);
    }

    NoRB<T>* direita = arv->getDireita();
    if (direita != nullptr) {
        ASSERT_GE(*direita->getDado(), *arv->getDado());
        checkBinTree(direita);
    }
}

TEST_F(NoRBTest, inserir) {
    for (int h = 1; h < 10; h++) {
        inteiro = inteiro->inserir(h, inteiro);
    }

    checkBinTree(inteiro);
}

TEST_F(NoRBTest, busca) {
    int h;
    for (h = 1; h < 10; h++) {
        inteiro = inteiro->inserir(h, inteiro);
    }

    for (h = 1; h < 11; h++) {
        ASSERT_EQ(h, *(inteiro->busca(h, inteiro)));
    }

    for (h = 11; h < 20; h++) {
        ASSERT_ANY_THROW(inteiro->busca(h, inteiro));
    }
}

TEST_F(NoRBTest, minimo) {
    int minimo = 10;
    ASSERT_EQ(minimo, *(inteiro->minimo(inteiro)->getDado()));

    for (int h = 0; h < N_ITER; h++) {
        int to_insert = dis(gen);
        if (to_insert < minimo) minimo = to_insert;

        inteiro = inteiro->inserir(to_insert, inteiro);
        ASSERT_EQ(minimo, *(inteiro->minimo(inteiro)->getDado()));
    }
}

template <typename T>
void checkColor(NoRB<T> *node) {
    if (node == nullptr) return;
    switch (node->getCor(node)) {
        case RB_RUBRO: {
            NoRB<T> *dir = node->getDireita();
            EXPECT_EQ(node->getCor(dir), RB_NEGRO);

            NoRB<T> *esq = node->getEsquerda();
            EXPECT_EQ(node->getCor(esq), RB_NEGRO);
        }
        default:
            checkColor(node->getDireita());
            checkColor(node->getEsquerda());
    }
}

TEST_F(NoRBTest, cor) {
    for (int i = 0; i < N_ITER; i++) {
        inteiro = inteiro->inserir(dis(gen), inteiro);
        checkColor(inteiro);
    }
}

TEST_F(NoRBTest, insereCaso3d) {
    inteiro = inteiro->inserir(11, inteiro);
    inteiro = inteiro->inserir(12, inteiro);

    ASSERT_EQ(11, *(inteiro->getDado()));
    ASSERT_EQ(10, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(12, *(inteiro->getDireita()->getDado()));
    checkColor(inteiro);
}

TEST_F(NoRBTest, insereCaso3e) {
    inteiro = inteiro->inserir(9, inteiro);
    inteiro = inteiro->inserir(8, inteiro);

    ASSERT_EQ(9, *(inteiro->getDado()));
    ASSERT_EQ(8, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(10, *(inteiro->getDireita()->getDado()));
    checkColor(inteiro);
}

TEST_F(NoRBTest, insereCaso2de) {
    inteiro = inteiro->inserir(7, inteiro);
    inteiro = inteiro->inserir(8, inteiro);

    ASSERT_EQ(8, *(inteiro->getDado()));
    ASSERT_EQ(7, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(10, *(inteiro->getDireita()->getDado()));
    checkColor(inteiro);
}

TEST_F(NoRBTest, insereCaso2ed) {
    inteiro = inteiro->inserir(12, inteiro);
    inteiro = inteiro->inserir(11, inteiro);

    ASSERT_EQ(11, *(inteiro->getDado()));
    ASSERT_EQ(10, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(12, *(inteiro->getDireita()->getDado()));
    checkColor(inteiro);
}

TEST_F(NoRBTest, remover) {
    int h;
    for (h = 0; h < 10; h++) {
        inteiro = inteiro->inserir(h, inteiro);
    }

    for (h = 0; h < 10; h++) {
        ASSERT_EQ(h, *(inteiro->busca(h, inteiro)));
    }

    for (h = 0; h < 10; h++) {
        inteiro = inteiro->remover(inteiro, h);
    }

    for (h = 0; h < 10; h++) {
        ASSERT_ANY_THROW(inteiro->busca(h, inteiro));
    }
}

template <typename T>
NoRB<T>* insereArray(T* array, int tam, NoRB<T>* arv) {
    for (int i = 0; i < tam; i++) {
        arv = arv->inserir(array[i], arv);
    }
    return arv;
}

TEST_F(NoRBTest, removerCaso0R) {
    int to_insert[] = {8, 12, 9, 11};
    inteiro = insereArray(to_insert, size_int_array(to_insert), inteiro);

    inteiro = inteiro->remover(inteiro, 8);
    inteiro->emOrdem(inteiro);
    std::vector<NoRB<int>*> elementos = inteiro->getElementos();

    int verifica[] = {9, 10, 11, 12};
    for (uint i = 0; i < size_int_array(verifica); i++) {
        EXPECT_EQ(*(elementos[i]->getDado()), verifica[i]);
    }
    checkColor(inteiro);
}

TEST_F(NoRBTest, removerCaso0N) {
    int to_insert[] = {5, 15, 4, 16, 8, 14, 7};
    inteiro = insereArray(to_insert, size_int_array(to_insert), inteiro);

    inteiro = inteiro->remover(inteiro, 10);
    inteiro->emOrdem(inteiro);
    std::vector<NoRB<int>*> elementos = inteiro->getElementos();

    int verifica[] = {4, 5, 7, 8, 14, 15, 16}; // em-ordem (ambos)
    // int verifica[] = {8, 5, 4, 7, 15, 14, 16}; // pre-ordem (esquerda)
    // int verifica[] = {14, 5, 4, 8, 7, 15, 16}; // pre-ordem (direita)
    for (uint i = 0; i < size_int_array(verifica); i++) {
        EXPECT_EQ(*(elementos[i]->getDado()), verifica[i]);
    }
    checkColor(inteiro);
}

TEST_F(NoRBTest, removerRotacaoSimplesDireita) {
    int to_insert[] = {5, 15, 14, 16, 6, 17, 13, 18, 7, 8, 3, 19};
    inteiro = insereArray(to_insert, size_int_array(to_insert), inteiro);

    inteiro = inteiro->remover(inteiro, 15);
    inteiro->emOrdem(inteiro);
    std::vector<NoRB<int>*> elementos = inteiro->getElementos();

    int verifica[] = {3, 5, 6, 7, 8, 10, 13, 14, 16, 17, 18, 19};
    for (uint i = 0; i < size_int_array(verifica); i++) {
        EXPECT_EQ(*(elementos[i]->getDado()), verifica[i]);
    }
    checkColor(inteiro);
    /*
    ASSERT_EQ(3, *(inteiro->getEsquerda()->getEsquerda()
                        ->getEsquerda()->getDado()));
    ASSERT_EQ(5, *(inteiro->getEsquerda()->getEsquerda()->getDado()));
    ASSERT_EQ(6, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(7, *(inteiro->getEsquerda()
                        ->getDireita()->getDado()));
    ASSERT_EQ(8, *(inteiro->getEsquerda()->getDireita()
                        ->getDireita()->getDado()));
    ASSERT_EQ(10, *(inteiro->getDado()));
    ASSERT_EQ(13, *(inteiro->getDireita()->getEsquerda()
                        ->getEsquerda()->getDado()));
    ASSERT_EQ(14, *(inteiro->getDireita()->getEsquerda()->getDado()));
    ASSERT_EQ(16, *(inteiro->getDireita()->getDado()));
    ASSERT_EQ(17, *(inteiro->getDireita()->getDireita()
                        ->getEsquerda()->getDado()));
    ASSERT_EQ(18, *(inteiro->getDireita()->getDireita()->getDado()));
    ASSERT_EQ(19, *(inteiro->getDireita()->getDireita()
                        ->getDireita()->getDado()));
    */
}

TEST_F(NoRBTest, removerRotacaoSimplesEsquerda) {
    int to_insert[] = {5, 15, 14, 16, 6, 13};
    inteiro = insereArray(to_insert, size_int_array(to_insert), inteiro);

    inteiro = inteiro->remover(inteiro, 15);
    inteiro->emOrdem(inteiro);
    std::vector<NoRB<int>*> elementos = inteiro->getElementos();

    int verifica[] = {5, 6, 10, 13, 14, 16};
    for (uint i = 0; i < size_int_array(verifica); i++) {
        EXPECT_EQ(*(elementos[i]->getDado()), verifica[i]);
    }
    checkColor(inteiro);

    /*
    ASSERT_EQ(5, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(6, *(inteiro->getEsquerda()->getDireita()->getDado()));
    ASSERT_EQ(10, *(inteiro->getDado()));
    ASSERT_EQ(13, *(inteiro->getDireita()->getEsquerda()->getDado()));
    ASSERT_EQ(14, *(inteiro->getDireita()->getDado()));
    ASSERT_EQ(16, *(inteiro->getDireita()->getDireita()->getDado()));
    */
}

TEST_F(NoRBTest, removerRotacaoDuplaEsquerda) {
    int to_insert[] = {4, 15, 14, 17, 6, 20, 13, 25, 7, 8, 2, 26, 18};
    inteiro = insereArray(to_insert, size_int_array(to_insert), inteiro);


    inteiro = inteiro->remover(inteiro, 26);
    inteiro = inteiro->remover(inteiro, 25);
    inteiro->emOrdem(inteiro);
    std::vector<NoRB<int>*> elementos = inteiro->getElementos();

    int verifica[] = {2, 4, 6, 7, 8, 10, 13, 14, 15, 17, 18, 20};
    for (uint i = 0; i < size_int_array(verifica); i++) {
        EXPECT_EQ(*(elementos[i]->getDado()), verifica[i]);
    }
    checkColor(inteiro);

    /*
    ASSERT_EQ(2, *(inteiro->getEsquerda()->getEsquerda()
                                ->getEsquerda()->getDado()));

    ASSERT_EQ(4, *(inteiro->getEsquerda()->getEsquerda()->getDado()));
    ASSERT_EQ(6, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(7, *(inteiro->getEsquerda()->getDireita()->getDado()));
    ASSERT_EQ(8, *(inteiro->getEsquerda()->getDireita()
                                ->getDireita()->getDado()));

    ASSERT_EQ(10, *(inteiro->getDado()));
    ASSERT_EQ(13, *(inteiro->getDireita()->getEsquerda()
                                ->getEsquerda()->getDado()));

    ASSERT_EQ(14, *(inteiro->getDireita()->getEsquerda()->getDado()));
    ASSERT_EQ(15, *(inteiro->getDireita()->getDado()));
    ASSERT_EQ(17, *(inteiro->getDireita()->getDireita()
                                ->getEsquerda()->getDado()));

    ASSERT_EQ(18, *(inteiro->getDireita()->getDireita()->getDado()));
    ASSERT_EQ(20, *(inteiro->getDireita()->getDireita()
                                ->getDireita()->getDado()));
    */
}

TEST_F(NoRBTest, removerRotacaoDuplaDireita) {
    int to_insert[] = {4, 15, 14, 17, 6, 20, 13, 25, 7, 8, 2, 26, 16};
    inteiro = insereArray(to_insert, size_int_array(to_insert), inteiro);


    inteiro = inteiro->remover(inteiro, 14);
    inteiro = inteiro->remover(inteiro, 13);
    inteiro->emOrdem(inteiro);
    std::vector<NoRB<int>*> elementos = inteiro->getElementos();

    int verifica[] = {2, 4, 6, 7, 8, 10, 15, 16, 17, 20, 25, 26};
    for (uint i = 0; i < size_int_array(verifica); i++) {
        EXPECT_EQ(*(elementos[i]->getDado()), verifica[i]);
    }
    checkColor(inteiro);

    /*
    ASSERT_EQ(2, *(inteiro->getEsquerda()->getEsquerda()
                                    ->getEsquerda()->getDado()));

    ASSERT_EQ(4, *(inteiro->getEsquerda()->getEsquerda()->getDado()));
    ASSERT_EQ(6, *(inteiro->getEsquerda()->getDado()));
    ASSERT_EQ(7, *(inteiro->getEsquerda()->getDireita()->getDado()));
    ASSERT_EQ(8, *(inteiro->getEsquerda()->getDireita()
                                    ->getDireita()->getDado()));

    ASSERT_EQ(10, *(inteiro->getDado()));
    ASSERT_EQ(15, *(inteiro->getDireita()->getEsquerda()
                                    ->getEsquerda()->getDado()));

    ASSERT_EQ(16, *(inteiro->getDireita()->getEsquerda()->getDado()));
    ASSERT_EQ(17, *(inteiro->getDireita()->getEsquerda()
                                    ->getDireita()->getDado()));

    ASSERT_EQ(25, *(inteiro->getDireita()->getDireita()->getDado()));
    ASSERT_EQ(26, *(inteiro->getDireita()->getDireita()
                                    ->getDireita()->getDado()));
    */
}
