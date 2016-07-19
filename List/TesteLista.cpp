/* Copyright [2014] <Jean Martina>
 * TesteLista.cpp
 */
#include <cstdlib>
#include <ctime>
#include "gtest/gtest.h"
#include "Lista.hpp"
#define tam 10
#define offset 1000

int main(int argc, char* argv[]) {
	std::srand(std::time(NULL));
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

class Objeto{
};


class TesteLista: public ::testing::Test{
 protected:
	Lista<int> l = Lista<int>(tam);
	Lista<Objeto*> lobj = Lista<Objeto*>(tam*offset);
};

TEST_F(TesteLista, ListaVazia) {
	ASSERT_TRUE(l.listaVazia());
	ASSERT_TRUE(lobj.listaVazia());
}

TEST_F(TesteLista, ListaVaziaNeg) {
	ASSERT_TRUE(l.listaVazia());
	l.adiciona(1);
	ASSERT_FALSE(l.listaVazia());

	ASSERT_TRUE(lobj.listaVazia());
	lobj.adiciona(new Objeto);
	ASSERT_FALSE(lobj.listaVazia());
}

TEST_F(TesteLista, ListaCheia) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_TRUE(l.listaCheia());
	for (i= 0; i < tam*offset ; i++) {
		lobj.adiciona(new Objeto);
	}
	ASSERT_TRUE(lobj.listaCheia());
}

TEST_F(TesteLista, ListaCheiaNeg) {
	int i;
	for (i= 0; i < tam -1 ; i++) {
		l.adiciona(i);
	}
	ASSERT_FALSE(l.listaCheia());
	l.adiciona(tam);
	ASSERT_TRUE(l.listaCheia());

	for (i= 0; i < tam*offset-1 ; i++) {
		lobj.adiciona(new Objeto);
	}
	ASSERT_FALSE(lobj.listaCheia());
	lobj.adiciona(new Objeto);
	ASSERT_TRUE(lobj.listaCheia());
}

TEST_F(TesteLista, ListaContem) {
	Objeto* o = new Objeto();
	l.adiciona(1);
	ASSERT_TRUE(l.contem(1));
	lobj.adiciona(o);
	ASSERT_TRUE(lobj.contem(o));
}

TEST_F(TesteLista, ListaContemNeg) {
	Objeto* o = new Objeto();
	Objeto* o2 = new Objeto();
	l.adiciona(1);
	ASSERT_TRUE(l.contem(1));
	ASSERT_FALSE(l.contem(2));


	lobj.adiciona(o);
	ASSERT_TRUE(lobj.contem(o));
	ASSERT_FALSE(lobj.contem(o2));
}

TEST_F(TesteLista, ListaDestroi) {
	l.adiciona(1);
	l.destroiLista();
	ASSERT_TRUE(l.listaVazia());
	ASSERT_FALSE(l.contem(1));

	Objeto* o = new Objeto();
	lobj.adiciona(o);
	lobj.destroiLista();
	ASSERT_TRUE(lobj.listaVazia());
	ASSERT_FALSE(lobj.contem(o));
}

TEST_F(TesteLista, ListaPosicao) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_EQ(l.posicao(5), 5);
	ASSERT_EQ(l.posicao(3), 3);
}

TEST_F(TesteLista, ListaPosicaoExcep) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_ANY_THROW(l.posicao(tam+2));
}

TEST_F(TesteLista, ListaAdiciona) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_ANY_THROW(l.adiciona(i+1));
}

TEST_F(TesteLista, ListaAdicionaInicio) {
	int i;
	for (i= 0; i < tam-1 ; i++) {
		l.adicionaNoInicio(i);
	}
	l.adicionaNoInicio(i+1);
	ASSERT_EQ(l.posicao(i+1), 0);
	ASSERT_EQ(l.posicao(i-1), 1);
}

TEST_F(TesteLista, ListaAdicionaExcep) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adicionaNoInicio(i);
	}
	ASSERT_ANY_THROW(l.adicionaNoInicio(i+1));
}

TEST_F(TesteLista, ListaAdicionaPosicao) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adicionaNaPosicao(i, i);
	}
	ASSERT_EQ(l.posicao(i-1), i-1);
}

TEST_F(TesteLista, ListaAdicionaPosicao2) {
	l.adicionaNaPosicao(5, 0);
	l.adicionaNaPosicao(2, 1);
	l.adicionaNaPosicao(3, 1);
	l.adicionaNaPosicao(6, 1);
	ASSERT_EQ(l.posicao(5), 0);
	ASSERT_EQ(l.posicao(2), 3);
	ASSERT_EQ(l.posicao(3), 2);
	ASSERT_EQ(l.posicao(6), 1);
}

TEST_F(TesteLista, ListaAdicionaPosicaoExcep1) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adicionaNaPosicao(i, i);
	}
	ASSERT_ANY_THROW(l.adicionaNaPosicao(i+1, i+1));
}

TEST_F(TesteLista, ListaAdicionaPosicaoExcep2) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adicionaNaPosicao(i, i);
	}
	ASSERT_ANY_THROW(l.adicionaNaPosicao(i+1, i+2));
}

TEST_F(TesteLista, ListaAdicionaPosicaoExcep3) {
	ASSERT_ANY_THROW(l.adicionaNaPosicao(1, 1));
}

TEST_F(TesteLista, ListaAdicionaOrdem) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adicionaEmOrdem(tam-i);
	}
	ASSERT_TRUE((l.posicao(1)< l.posicao(2)));

	for (i= 1; i < tam ; i++) {
		ASSERT_EQ(l.posicao(i), i-1);
	}
}


TEST_F(TesteLista, ListaAdicionaOrdemExcep) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adicionaEmOrdem(tam-i);
	}
	ASSERT_ANY_THROW(l.adicionaEmOrdem(tam+2));
}

TEST_F(TesteLista, ListaRemove) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_EQ(l.retira(), i-1);
	ASSERT_FALSE(l.contem(i-1));
}

TEST_F(TesteLista, ListaRemoveExcep) {
	ASSERT_ANY_THROW(l.retira());
}

TEST_F(TesteLista, ListaRemoveInicio) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_EQ(l.retiraDoInicio(), 0);
	ASSERT_FALSE(l.contem(0));
}

TEST_F(TesteLista, ListaRemoveInicioExcep) {
	ASSERT_ANY_THROW(l.retiraDoInicio());
}

TEST_F(TesteLista, ListaRemoveInicioExcep2) {
	l.adiciona(1);
	l.retira();
	ASSERT_ANY_THROW(l.retiraDoInicio());
}

TEST_F(TesteLista, ListaRemovePosicao) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_EQ(l.retiraDaPosicao(1), 1);
}

TEST_F(TesteLista, ListaRemovePosicaoExcep1) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_ANY_THROW(l.retiraDaPosicao(tam+2));
}

TEST_F(TesteLista, ListaRemovePosicaoExcep2) {
	ASSERT_ANY_THROW(l.retiraDaPosicao(1));
}

TEST_F(TesteLista, ListaRemoveEspecifico) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	ASSERT_EQ(l.retiraEspecifico(3), 3);
}

TEST_F(TesteLista, ListaRemoveEspecificoExcep1) {
	int i;
	for (i= 0; i < tam ; i++) {
		l.adiciona(i);
	}
	l.retiraEspecifico(3);
	ASSERT_ANY_THROW(l.retiraEspecifico(3));
}

TEST_F(TesteLista, ListaRemoveEspecificoExcep2) {
	ASSERT_ANY_THROW(l.retiraEspecifico(3));
}

TEST_F(TesteLista, Maior) {
	ASSERT_TRUE(l.maior(2, 1));
	ASSERT_FALSE(l.maior(1, 2));
	ASSERT_FALSE(l.maior(2, 2));
}

TEST_F(TesteLista, Menor) {
	ASSERT_TRUE(l.menor(1, 2));
	ASSERT_FALSE(l.menor(2, 1));
	ASSERT_FALSE(l.menor(2, 2));
}

TEST_F(TesteLista, Igual) {
	ASSERT_TRUE(l.igual(1, 1));
	ASSERT_FALSE(l.igual(2, 1));
	ASSERT_FALSE(l.igual(1, 2));
}
