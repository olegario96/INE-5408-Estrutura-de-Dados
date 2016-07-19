// Copyright[2016] <Gustavo Olegário>
#include <stdexcept>

template <typename T>
// Implementa a classe Lista de um elemento T.
class Lista {
// Atributos privados.
 private:
    // A lista propriamente dita.
    T* dados;
    // O tamanho padrão da lista.
    int MAXLISTA = 100;
    // Índice do último elemento da lista.
    int ultimo;

// Métodos públicos
 public:
    // Método construtor
	Lista() {
		dados = new T[MAXLISTA];
		ultimo = -1;
	}
    // Método construtor com um tamanho da lista escolhido pelo usuário.
	explicit Lista(int tam) {
		MAXLISTA = tam;
		dados = new T[MAXLISTA];
		ultimo = -1;
	}

    // Método que adiciona um dado T no fim da lista, caso ela não esteja cheia.
	void adiciona(T dado) {
		if (listaCheia()) {
			throw std::runtime_error("Erro lista cheia.");
		} else {
			++ultimo;
			dados[ultimo] = dado;
		}
	}

    // Método que adiciona um dado T no início da lista, caso ela não esteja
    // cheia.
	void adicionaNoInicio(T dado) {
		if (listaCheia()) {
			throw std::runtime_error("Erro lista cheia.");
		} else {
			ultimo = ultimo + 1;
			for (int i = ultimo; i > 0; --i) {
				dados[i] = dados[i - 1];
			}
			dados[0] = dado;
		}
	}

    // Adiciona um dado T na lista em uma posição específica (e válida)
    // da lista, caso ela não esteja cheia.
	void adicionaNaPosicao(T dado, int posicao) {
		if (listaCheia()) {
			throw std::runtime_error("Erro lista cheia.");
		} else if (posicao > ultimo + 1 || posicao < 0) {
			throw std::runtime_error("Erro de posição.");
		} else {
			ultimo = ultimo + 1;
			for (int i = ultimo; i > posicao; --i) {
				dados[i] = dados[i - 1];
			}
			dados[posicao] = dado;
		}
	}

    // Adiciona um dado T na lista em uma ordem pré-definida,
    // caso ela não esteja cheia.
	void adicionaEmOrdem(T dado) {
		int i;
		if (listaCheia()) {
			throw std::runtime_error("Erro lista cheia");
		} else {
			for (i = 0; i <= ultimo && dado > dados[i]; ++i) {
			}
			return (adicionaNaPosicao(dado, i));
		}
	}

    // Retira o último elemento da lista, se ela não estiver vazia.
	T retira() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			--ultimo;
			return (dados[ultimo + 1]);
		}
	}

    // Retira o primeiro elemento da lista, se ela não estiver vazia.
	T retiraDoInicio() {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else {
			ultimo = ultimo - 1;
			T aux = dados[0];
			for (int i = 0; i <= ultimo; ++i) {
				dados[i] = dados[i + 1];
			}
			return aux;
		}
	}

    // Retira um elemento de uma posição específica (e válida),caso
    // ela não esteja vazia.
	T retiraDaPosicao(int posicao) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else if (posicao < 0 || posicao > ultimo) {
			throw std::runtime_error("Erro de posição.");
		} else {
			T aux = dados[posicao];
			ultimo = ultimo - 1;
			for (int i = posicao; i <= ultimo; ++i) {
				dados[i] = dados[i + 1];
			}
			return aux;
		}
	}

    // Retira um elemento específico da lista, caso ela não esteja vazia.
	T retiraEspecifico(T dado) {
		if (listaVazia()) {
			throw std::runtime_error("Erro lista vazia.");
		} else if (contem(dado) == false) {
			throw std::runtime_error("Dado inexistente na lista");
		} else {
			ultimo = ultimo - 1;
			int indice = posicao(dado);
			T aux = dados[indice];
			for (int i = indice; i <= ultimo; ++i) {
				dados[i] = dados[i + 1];
			}
			return aux;
		}
	}

    // Retorna o índice de onde se encontra um elemento específico.
	int posicao(T dado) {
		for (int i = 0; i <= ultimo; ++i) {
			if (dados[i] == dado) {
				return i;
			}
		}
		throw std::runtime_error("Não encontrado");
	}

    // Verifica se um elemento T existe na lista.
	bool contem(T dado) {
		try {
			posicao(dado);
			return true;
		} catch (std::runtime_error) {
			return false;
		}
	}

    // Verifica se dois dados são iguais.
	bool igual(T dado1, T dado2) {
		return dado1 == dado2;
	}

    // Verifica se o dado1 é maior que o dado2.
	bool maior(T dado1, T dado2) {
		return dado1 > dado2;
	}

	// Verifica se o dado1 é menor que o dado2.
	bool menor(T dado1, T dado2) {
		return dado1 < dado2;
	}

    // Verifica se a lista está cheia.
	bool listaCheia() {
		return ultimo == MAXLISTA - 1;
	}

    // Verifica se a lista está vazia.
	bool listaVazia() {
		return ultimo == -1;
	}

	// Reinicializa a lista.
	void destroiLista() {
		ultimo = -1;
	}
};

