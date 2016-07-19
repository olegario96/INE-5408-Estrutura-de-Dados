// "Copyright [2016] <Gustavo Olegário>"
// "Copyright [2016] <Otto Pires>"

#ifndef WORD_INDEX_H
#define WORD_INDEX_H

#include "ListaDupla.hpp"


/**
 * Struct utilizada para conter as palavras que estão contidas no arquivo
 */
struct Word_Index {
    char word[100];
    ListaDupla<int> positions;

    Word_Index() {
        word[0] = '\0';
    }

    Word_Index(char* word1, int arg) {
        strcpy(word, word1);
        positions.adicionaDuplo(arg);
    }

    bool operator==(const Word_Index& rhs) const {
        return strcmp(word, rhs.word) == 0;
    }

    bool operator<(const Word_Index& rhs) const {
        return strcmp(word, rhs.word) < 0;
    }

    bool operator>(const Word_Index& rhs) const {
        return strcmp(word, rhs.word) > 0;
    }
};

#endif /* WORD_INDEX_H */