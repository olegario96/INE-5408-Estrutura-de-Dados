// Copyright

#include <gtest/gtest.h>
#include <vector>
#include <cstdio>
#include "NoBinario.hpp"

#define TAM1 10
#define TAM2 20

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class Objeto {};

class NoBinarioTest : public ::testing::Test {
 protected:
    NoBinario<Objeto*>* objeto;
    NoBinario<int>* inteiro;
 public:
    virtual void SetUp() {
        this->inteiro = new NoBinario<int>(10);
        this->objeto = new NoBinario<Objeto*>(new Objeto());
    }
};

TEST_F(NoBinarioTest, getDado) {
    Objeto* o = new Objeto();

    ASSERT_EQ(10, *(inteiro->getDado()));
    inteiro = new NoBinario<int>(5);
    ASSERT_EQ(5, *(inteiro->getDado()));
    inteiro = new NoBinario<int>(15);
    ASSERT_EQ(15, *(inteiro->getDado()));
    objeto = new NoBinario<Objeto*>(o);
    ASSERT_EQ(o, *(objeto->getDado()));
}

TEST_F(NoBinarioTest, busca) {
    ASSERT_EQ(10, *(inteiro->busca(10, inteiro)));

    ASSERT_NO_THROW(inteiro->inserir(5, inteiro));
    ASSERT_EQ(5, *(inteiro->busca(5, inteiro)));

    ASSERT_NO_THROW(inteiro->inserir(20, inteiro));
    ASSERT_EQ(20, *(inteiro->busca(20, inteiro)));

    ASSERT_NO_THROW(inteiro->inserir(3, inteiro));
    ASSERT_EQ(3, *(inteiro->busca(3, inteiro)));

    ASSERT_NO_THROW(inteiro->inserir(16, inteiro));
    ASSERT_EQ(16, *(inteiro->busca(16, inteiro)));

    ASSERT_ANY_THROW(inteiro->busca(14, inteiro));
}

TEST_F(NoBinarioTest, inserir) {
    int i;
    for (i = 0; i < TAM1; i++) {
        ASSERT_NO_THROW(inteiro->inserir(i, inteiro));
    }
    for (i = TAM1 + 1; i < TAM2; i++) {
        ASSERT_NO_THROW(inteiro->inserir(i, inteiro));
    }
    for (i = 0; i < TAM1; i++) {
        ASSERT_EQ(i, *(inteiro->busca(i, inteiro)));
    }
    for (i = TAM1+1; i < TAM2; i++) {
        ASSERT_EQ(i, *(inteiro->busca(i, inteiro)));
    }
}

TEST_F(NoBinarioTest, remover) {
    int i;
    for (i = 0; i < TAM1; i++) {
        ASSERT_NO_THROW(inteiro->inserir(i, inteiro));
    }
    for (i = TAM1+1; i < TAM2; i++) {
        ASSERT_NO_THROW(inteiro->inserir(i, inteiro));
    }
    for (i = 0; i < TAM1; i++) {
        ASSERT_EQ(i, *(inteiro->busca(i, inteiro)));
    }
    for (i = TAM1+1; i < TAM2; i++) {
        ASSERT_EQ(i, *(inteiro->busca(i, inteiro)));
    }
    for (i = 0; i < TAM1; i++) {
        ASSERT_NO_THROW(inteiro->remover(inteiro, i));
    }
    for (i = TAM1+1; i < TAM2; i++) {
        ASSERT_NO_THROW(inteiro->remover(inteiro, i));
    }
    for (i = 0; i < TAM1; i++) {
        ASSERT_ANY_THROW(inteiro->busca(i, inteiro));
    }
    for (i = TAM1+1; i < TAM2; i++) {
        ASSERT_ANY_THROW(inteiro->busca(i, inteiro));
    }
}

TEST_F(NoBinarioTest, removerArvEsq) {
    inteiro->inserir(7, inteiro);
    inteiro->inserir(5, inteiro);
    inteiro->inserir(4, inteiro);
    inteiro->inserir(6, inteiro);
    inteiro->remover(inteiro, 7);
    NoBinario<int>* esq = inteiro->getEsquerda();
    ASSERT_EQ(*(esq->getDado()), 5);
    ASSERT_EQ(*(esq->getDireita()->getDado()), 6);
    ASSERT_EQ(*(esq->getEsquerda()->getDado()), 4);
}

TEST_F(NoBinarioTest, removerArvDir) {
    inteiro->inserir(2, inteiro);
    inteiro->inserir(5, inteiro);
    inteiro->inserir(4, inteiro);
    inteiro->inserir(6, inteiro);
    inteiro->remover(inteiro, 2);
    NoBinario<int>* esq = inteiro->getEsquerda();
    ASSERT_EQ(*(esq->getDado()), 5);
    ASSERT_EQ(*(esq->getDireita()->getDado()), 6);
    ASSERT_EQ(*(esq->getEsquerda()->getDado()), 4);
}

TEST_F(NoBinarioTest, remover2Sub) {
    inteiro->inserir(20, inteiro);
    inteiro->inserir(25, inteiro);
    inteiro->inserir(26, inteiro);
    inteiro->inserir(15, inteiro);
    inteiro->inserir(14, inteiro);
    inteiro->inserir(16, inteiro);

    inteiro->remover(inteiro, 20);

    NoBinario<int>* d = inteiro->getDireita();
    ASSERT_TRUE(*(d->getDado()) == 25 || *(d->getDado()) == 16);

    NoBinario<int>* dd = d->getDireita();
    NoBinario<int>* de = d->getEsquerda();

    if (*(d->getDado()) == 25) {
        ASSERT_EQ(*(dd->getDado()), 26);
        ASSERT_EQ(*(de->getDado()), 15);

        ASSERT_EQ(dd->getEsquerda(), nullptr);
        ASSERT_EQ(dd->getDireita(), nullptr);

        NoBinario<int>* ded = de->getDireita();
        NoBinario<int>* dee = de->getEsquerda();

        ASSERT_EQ(*(ded->getDado()), 16);
        ASSERT_EQ(*(dee->getDado()), 14);

        ASSERT_EQ(ded->getEsquerda(), nullptr);
        ASSERT_EQ(ded->getDireita(), nullptr);

        ASSERT_EQ(dee->getEsquerda(), nullptr);
        ASSERT_EQ(dee->getDireita(), nullptr);
    } else {
        ASSERT_EQ(*(dd->getDado()), 25);
        ASSERT_EQ(*(de->getDado()), 15);

        NoBinario<int>* ddd = dd->getDireita();
        NoBinario<int>* dde = dd->getEsquerda();

        ASSERT_EQ(*(ddd->getDado()), 26);
        ASSERT_EQ(*(dde->getDado()), 14);

        ASSERT_EQ(ddd->getEsquerda(), nullptr);
        ASSERT_EQ(ddd->getDireita(), nullptr);

        ASSERT_EQ(dde->getEsquerda(), nullptr);
        ASSERT_EQ(dde->getDireita(), nullptr);
    }
}

TEST_F(NoBinarioTest, minimo) {
    int i;
    ASSERT_EQ(10, *(inteiro->minimo(inteiro)->getDado()));
    for (i = 9;  i >= 0; i--) {
        ASSERT_NO_THROW(inteiro->inserir(i, inteiro));
        ASSERT_EQ(i, *(inteiro->minimo(inteiro)->getDado()));
    }
}

TEST_F(NoBinarioTest, preOrdem) {
    ASSERT_NO_THROW(inteiro->inserir(8, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(9, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(11, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(12, inteiro));
    ASSERT_NO_THROW(inteiro->preOrdem(inteiro));
    std::vector<NoBinario<int>* > elementos = inteiro->getElementos();
    ASSERT_EQ(10, *(elementos[0]->getDado()));
    ASSERT_EQ(8, *(elementos[1]->getDado()));
    ASSERT_EQ(9, *(elementos[2]->getDado()));
    ASSERT_EQ(11, *(elementos[3]->getDado()));
    ASSERT_EQ(12, *(elementos[4]->getDado()));
}

TEST_F(NoBinarioTest, emOrdem) {
    ASSERT_NO_THROW(inteiro->inserir(8, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(9, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(11, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(12, inteiro));
    ASSERT_NO_THROW(inteiro->emOrdem(inteiro));
    std::vector<NoBinario<int>* > elementos = inteiro->getElementos();
    ASSERT_EQ(8, *(elementos[0]->getDado()));
    ASSERT_EQ(9, *(elementos[1]->getDado()));
    ASSERT_EQ(10, *(elementos[2]->getDado()));
    ASSERT_EQ(11, *(elementos[3]->getDado()));
    ASSERT_EQ(12, *(elementos[4]->getDado()));
}

TEST_F(NoBinarioTest, posOrdem) {
    ASSERT_NO_THROW(inteiro->inserir(8, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(9, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(11, inteiro));
    ASSERT_NO_THROW(inteiro->inserir(12, inteiro));
    ASSERT_NO_THROW(inteiro->posOrdem(inteiro));
    std::vector<NoBinario<int>* > elementos = inteiro->getElementos();
    ASSERT_EQ(9, *(elementos[0]->getDado()));
    ASSERT_EQ(8, *(elementos[1]->getDado()));
    ASSERT_EQ(12, *(elementos[2]->getDado()));
    ASSERT_EQ(11, *(elementos[3]->getDado()));
    ASSERT_EQ(10, *(elementos[4]->getDado()));
}
