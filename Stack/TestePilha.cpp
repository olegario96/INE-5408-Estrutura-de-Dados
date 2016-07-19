/* Copyright [2014] <Jean Martina>
 * TestePilha.cpp
 */

#include <stdio.h>
#include "gtest/gtest.h"
#include "Pilha.hpp"



int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    int a = RUN_ALL_TESTS();
    return a;
}

class Objeto{
};

class TestePilha: public ::testing::Test{
 protected:
    Pilha<int> p = Pilha<int>(10);
    Pilha<Objeto> pobj = Pilha<Objeto>(100);
};

TEST_F(TestePilha, PilhaVazia) {
    ASSERT_TRUE(p.PilhaVazia());
}

TEST_F(TestePilha, InsereElemento) {
	p.empilha(0);
	ASSERT_EQ(0, p.topo());
}

TEST_F(TestePilha, PilhaCheia) {
	p.empilha(0);
	p.empilha(1);
	p.empilha(2);
	p.empilha(3);
	p.empilha(4);
	p.empilha(5);
	p.empilha(6);
	p.empilha(7);
	p.empilha(8);
	p.empilha(9);
	ASSERT_TRUE(p.PilhaCheia());
}

TEST_F(TestePilha, Desempilha) {
	p.empilha(0);
	p.empilha(1);
	p.desempilha();
	ASSERT_EQ(0, p.topo());
}

TEST_F(TestePilha, Topo) {
	p.empilha(0);
	p.empilha(1);
	ASSERT_EQ(1, p.topo());
}

TEST_F(TestePilha, PosicaoTopo) {
	p.empilha(0);
	p.empilha(1);
	p.empilha(2);
	ASSERT_EQ(2, p.getPosTopo());
}

TEST_F(TestePilha, ExcecaoPilhaCheia) {
	p.empilha(0);
	p.empilha(1);
	p.empilha(2);
	p.empilha(3);
	p.empilha(4);
	p.empilha(5);
	p.empilha(6);
	p.empilha(7);
	p.empilha(8);
	p.empilha(9);
	EXPECT_ANY_THROW(p.empilha(10));
}
TEST_F(TestePilha, ExcecaoPilhaVazia) {
	EXPECT_ANY_THROW(p.desempilha());
}

TEST_F(TestePilha, LimpaPilha) {
	p.empilha(0);
	p.empilha(1);
	p.empilha(2);
	p.empilha(3);
	p.empilha(4);
	p.empilha(5);
	p.limparPilha();
	EXPECT_ANY_THROW(p.getPosTopo());
}
