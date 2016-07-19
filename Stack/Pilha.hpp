// Copyright[2016] <Gustavo Olegário>
#include <stdexcept>

template<typename T>
// Implementa a classe a pilha de um elemento T.
class Pilha {
 // Variáveis privadas.
 private:
 		  // Define o tamanho padrão da pilha.
          int MAXPILHA = 100;
          // Variável que retorna o índice do último elemento.
          int pinaculo;
          // A pilha propriamente dita.
		  T* m_dados;

 public:
 		// Método construtor que inicializa a pilha 
 		// com tamanho padrão e retorna uma pilha.
        Pilha() {
    	    m_dados = new T[MAXPILHA];
    	    pinaculo = -1;
        }

        // Método construtor que inicializa a pilha
        // com tamanho escolhido pelo usuário e retorna uma pilha.
        Pilha<T>(int t) {
        	MAXPILHA = t;
        	m_dados = new T[MAXPILHA];
        	pinaculo = -1;
        }

        // Se a pilha não estiver cheia,
        // empilha um dado do tipo T.
	    void empilha(T dado) {
	    	if (PilhaCheia()) {
	    		 throw std::runtime_error("Erro pilha cheia.");
	    	} else {
	    		pinaculo = pinaculo + 1;
	    		m_dados[pinaculo] = dado;
	    	}
	    }

	    // Se a pilha não estiver vazia,
	    // retira o último elemento e
	    // retorna o novo último elemento
	    T desempilha() {
	    	if (PilhaVazia()) {
		    	throw std::runtime_error("Erro pilha vazia.");
		    } else {
			    pinaculo = pinaculo - 1;
			    return (m_dados[pinaculo + 1]);
		    }
		}

		// Se a pilha não estiver vazia, 
		// retorna o último elemento
	    T topo() {
	    	if (PilhaVazia()) {
		        throw std::runtime_error("Erro pilha vazia.");
		    } else {
		    	return (m_dados[pinaculo]);
		    }
    	}

    	// Se a pilha não estiver vazia
    	// retorna o índice do último elemento.
	    int getPosTopo() {
	    	if (PilhaVazia()) {
	    		throw std::runtime_error("Erro pilha vazia.");
	    	} else {
	    		return pinaculo;
	    	}
    	}

    	// Reinicializa a pilha.
	    void limparPilha() {
		    pinaculo = -1;
		    m_dados = new T[MAXPILHA];
	    }

	    // Retorna se a pilha está vazia.
	    bool PilhaVazia() {
		    return pinaculo == -1;
	    }

	    // Retorna se a pilha estiver cheia.
	    bool PilhaCheia() {
		    return pinaculo == MAXPILHA - 1;
	    }
};
