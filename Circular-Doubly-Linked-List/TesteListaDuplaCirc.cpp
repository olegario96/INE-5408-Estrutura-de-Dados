/*
Copyright [2014] <Jean Martina>
*/
#include <cstdlib>

#include "gtest/gtest.h"
#include "ListaDuplaCirc.hpp"
#define tam 10
#define offset 1000

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

class Objeto{
};

class TesteLista: public ::testing::Test{
 protected:
	ListaDuplaCirc<int> l = ListaDuplaCirc<int>();
	ListaDuplaCirc<Objeto*> lobj = ListaDuplaCirc<Objeto*>();
};

TEST_F(TesteLista, ListaVazia) {
	ASSERT_TRUE(l.listaVazia());
	ASSERT_TRUE(lobj.listaVazia());

	l.adicionaDuplo(1);
	lobj.adicionaDuplo(new Objeto);

	ASSERT_FALSE(l.listaVazia());
	ASSERT_FALSE(lobj.listaVazia());
}

TEST_F(TesteLista, ListaContem) {
	Objeto* o = new Objeto();

	ASSERT_FALSE(l.contemDuplo(1));
	l.adicionaDuplo(1);
	ASSERT_TRUE(l.contemDuplo(1));

	ASSERT_FALSE(lobj.contemDuplo(o));
	lobj.adicionaDuplo(o);
	ASSERT_TRUE(lobj.contemDuplo(o));
}

TEST_F(TesteLista, ListaDestroi) {
	Objeto* o = new Objeto();

	l.adicionaDuplo(1);
	lobj.adicionaDuplo(o);

	l.destroiListaDuplo();
	lobj.destroiListaDuplo();

	ASSERT_TRUE(l.listaVazia());
	ASSERT_FALSE(l.contemDuplo(1));

	ASSERT_TRUE(lobj.listaVazia());
	ASSERT_FALSE(lobj.contemDuplo(o));
}

TEST_F(TesteLista, ListaPosicao) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	for (i = 0; i < tam; i++) {
		ASSERT_EQ(l.posicaoDuplo(i), i);
	}
}

TEST_F(TesteLista, ListaMostra) {
	int i;
	for (i = tam-1; i >= 0; i--) {
		l.adicionaDuplo(i);
	}
	ASSERT_EQ(l.mostra(0), tam-1);
}

TEST_F(TesteLista, ListaMostraExcep) {
	int i;
	for (i = tam-1; i >= 0; i--) {
		l.adicionaDuplo(i);
	}
	ASSERT_ANY_THROW(l.mostra(tam+2));
}

TEST_F(TesteLista, ListaPosicaoExcep) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	ASSERT_ANY_THROW(l.posicaoDuplo(tam+2));
}

TEST_F(TesteLista, ListaAdiciona) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	for (i = 0; i < tam; i++) {
		ASSERT_EQ(l.mostra(i), i);
	}
}

TEST_F(TesteLista, ListaVerUltimo) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	ASSERT_EQ(l.verUltimo(), i-1);
}

TEST_F(TesteLista, ListaAdicionaInicio) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaNoInicioDuplo(i);
	}
	for (i = 0; i < tam; i++) {
		ASSERT_EQ(l.posicaoDuplo(tam-i-1), i);
	}
}

TEST_F(TesteLista, ListaAdicionaPosicao) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaNaPosicaoDuplo(i, i);
	}
	for (i = 0; i < tam; i++) {
		ASSERT_EQ(l.posicaoDuplo(i), i);
	}
}

TEST_F(TesteLista, ListaAdicionaPosicao2) {
	l.adicionaNaPosicaoDuplo(5, 0);
	l.adicionaNaPosicaoDuplo(2, 1);
	l.adicionaNaPosicaoDuplo(3, 1);
	l.adicionaNaPosicaoDuplo(6, 1);
	ASSERT_EQ(l.posicaoDuplo(5), 0);
	ASSERT_EQ(l.posicaoDuplo(2), 3);
	ASSERT_EQ(l.posicaoDuplo(3), 2);
	ASSERT_EQ(l.posicaoDuplo(6), 1);
}

TEST_F(TesteLista, ListaAdicionaPosicaoExcep1) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaNaPosicaoDuplo(i, i);
	}
	ASSERT_ANY_THROW(l.adicionaNaPosicaoDuplo(i+1, i+1));
	ASSERT_ANY_THROW(l.adicionaNaPosicaoDuplo(i+1, i+2));
}

TEST_F(TesteLista, ListaAdicionaOrdem) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaEmOrdem(tam-i);
	}
	for (i= 1; i < tam; i++) {
		ASSERT_EQ(l.posicaoDuplo(i), i-1);
	}
}

TEST_F(TesteLista, ListaRemove) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	for (i = tam-1; i >= 0; i--) {
		ASSERT_EQ(l.retiraDuplo(), i);
	}
}

TEST_F(TesteLista, ListaRemoveExcep) {
	ASSERT_ANY_THROW(l.retiraDuplo());
}

TEST_F(TesteLista, ListaRemoveInicio) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	for (i = 0; i < tam; i++) {
		ASSERT_EQ(l.retiraDoInicioDuplo(), i);
	}
}

TEST_F(TesteLista, ListaRemoveInicioExcep) {
	ASSERT_ANY_THROW(l.retiraDoInicioDuplo());
}

TEST_F(TesteLista, ListaEliminaInicio) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	l.eliminaDoInicioDuplo();
	for (i = 1; i < tam; i++) {
		ASSERT_EQ(l.retiraDoInicioDuplo(), i);
	}
}

TEST_F(TesteLista, ListaRemovePosicao) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	ASSERT_EQ(l.retiraDaPosicaoDuplo(1), 1);
}

TEST_F(TesteLista, ListaRemovePosicaoExcep1) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	ASSERT_ANY_THROW(l.retiraDaPosicaoDuplo(tam+2));
}

TEST_F(TesteLista, ListaRemovePosicaoExcep2) {
	ASSERT_ANY_THROW(l.retiraDaPosicaoDuplo(1));
}

TEST_F(TesteLista, ListaRemoveEspecifico) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	for (i = 0; i < tam; i++) {
		ASSERT_EQ(l.retiraEspecificoDuplo(i), i);
	}
}

TEST_F(TesteLista, ListaRemoveEspecificoExcep1) {
	int i;
	for (i = 0; i < tam; i++) {
		l.adicionaDuplo(i);
	}
	l.retiraEspecificoDuplo(3);
	ASSERT_ANY_THROW(l.retiraEspecificoDuplo(3));
}

TEST_F(TesteLista, ListaRemoveEspecificoExcep2) {
	ASSERT_ANY_THROW(l.retiraEspecificoDuplo(3));
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
