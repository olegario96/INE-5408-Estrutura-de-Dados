// Copyright[2016] <Gustavo Olegário>
#include <stdexcept>

template <typename T>
// Implementação de uma classe Fila que enfileira dados do tipo T.
class Fila {
	// Variáveis privadas.
	private:
		// A fila proprimente dita do tipo T.
        T* m_dados;
        // Int que indica o indíce do último elemento.
        int fim;
        // Int que inicializa a fila com um tamanho padrão.
        int MAXFILA = 100;

 public:
         // Construtor que inicializa a fila com tamanho padrão e
         // retorna uma fila.
        Fila() {
			m_dados = new T[MAXFILA];
			fim = -1;
		}

		// Construtor que inicializa a fila com tamanho escolhido
		// pelo usuário e retorna uma fila do tipo T.
		Fila<T>(int tam) {
			MAXFILA = tam;
			m_dados = new T[MAXFILA];
			fim = -1;
		}

		// Método que adiciona um dado do tipo T na fila.
		void inclui(T dado) {
			if (filaCheia()) {
				throw std::runtime_error("Erro fila cheia");
			} else {
				++fim;
				m_dados[fim] = dado;
			}
		}

		// Método que retira o primeiro dado fila e o retorna
		// se a fila não estiver vazia, além de ajustar a fila.
		T retira() {
			if (filaVazia()) {
				throw std::runtime_error("Erro fila vazia");
			} else {
				T aux = m_dados[0];
				for (int i = 0; i < MAXFILA - 2; ++i) {
					m_dados[i] = m_dados[i + 1];
				}
				--fim;
				return aux;
			}
		}

		// Método que retorna o último elemento da fila, se ela
		// não estiver vazia.
		T ultimo() {
		    if (filaVazia()) {
		        throw std::runtime_error("Erro fila vazia");
		    } else {
			    return m_dados[fim];
			}
		}

		// Método que retorna o índice do último elemento,
		// se a fila não estiver vazia.
		int getUltimo() {
		    if (filaVazia()) {
		        throw std::runtime_error("Erro fila vazia");
		    } else {
			    return fim;
			}
		}

		// Método que diz se a fila está cheia.
		bool filaCheia() {
			return fim == MAXFILA - 1;
		}

		// Método que diz se a fila está vazia.
		bool filaVazia() {
			return fim == -1;
		}

		// Método que reinicializa a pilha.
		void inicializaFila() {
			fim = -1;
		}
};
