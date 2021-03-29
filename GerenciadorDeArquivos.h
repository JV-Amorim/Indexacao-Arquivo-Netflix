#ifndef GERENCIADOR_DE_ARQUIVOS_H
#define GERENCIADOR_DE_ARQUIVOS_H

#include <string>
#include <vector>
#include "ItemNetflix.h"

class GerenciadorDeArquivos
{
private:
    const std::string m_nomeDoArquivoCsv{"netflix_titles.csv"};
public:
    GerenciadorDeArquivos();
};

#endif // GERENCIADOR_ARQUIVO_H
