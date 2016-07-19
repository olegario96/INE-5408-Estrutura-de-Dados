/* Copyright [2014] <Jean Martina>
 * TesteFila.cpp
 */

#include <stdio.h>
#include "gtest/gtest.h"
#include "Fila.hpp"


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    int a = RUN_ALL_TESTS();
    return a;
}

class Objeto{
};

class TesteFila: public ::testing::Test{
 protected:
    Fila<int> p = Fila<int>(10);
    Fila<Objeto> pobj = Fila<Objeto>(100);
};

TEST_F(TesteFila, FilaVazia) {
    ASSERT_TRUE(p.filaVazia());
}


TEST_F(TesteFila, InsereElemento) {
	p.inclui(0);
	ASSERT_EQ(0, p.getUltimo());
}

TEST_F(TesteFila, FilaCheia) {
	p.inclui(0);
	p.inclui(1);
	p.inclui(2);
	p.inclui(3);
	p.inclui(4);
	p.inclui(5);
	p.inclui(6);
	p.inclui(7);
	p.inclui(8);
	p.inclui(9);
	ASSERT_TRUE(p.filaCheia());
}

TEST_F(TesteFila, Retira) {
	p.inclui(0);
	p.inclui(1);
	p.inclui(2);
	ASSERT_EQ(0, p.retira());
	ASSERT_EQ(1, p.getUltimo());
}

TEST_F(TesteFila, Ultimo) {
	p.inclui(0);
	p.inclui(1);
	ASSERT_EQ(1, p.getUltimo());
	ASSERT_EQ(1, p.ultimo());
}

TEST_F(TesteFila, PosicaoUltimo) {
	p.inclui(0);
	p.inclui(1);
	p.inclui(2);
	ASSERT_EQ(2, p.getUltimo());
}

TEST_F(TesteFila, ExcecaoFilaCheia) {
	p.inclui(0);
	p.inclui(1);
	p.inclui(2);
	p.inclui(3);
	p.inclui(4);
	p.inclui(5);
	p.inclui(6);
	p.inclui(7);
	p.inclui(8);
	p.inclui(9);
	EXPECT_ANY_THROW(p.inclui(10));
}
TEST_F(TesteFila, ExcecaoFilaVazia) {
	EXPECT_ANY_THROW(p.retira());
}

TEST_F(TesteFila, LimpaFila) {
	p.inclui(0);
	p.inclui(1);
	p.inclui(2);
	p.inclui(3);
	p.inclui(4);
	p.inclui(5);
	p.inicializaFila();
	EXPECT_ANY_THROW(p.ultimo());
}
