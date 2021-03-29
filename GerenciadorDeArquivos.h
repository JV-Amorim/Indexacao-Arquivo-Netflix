#ifndef GERENCIADOR_DE_ARQUIVOS_H
#define GERENCIADOR_DE_ARQUIVOS_H

#include <string>
#include <vector>
#include "ItemNetflix.h"
#include "ItemIndiceDireto.h"
#include "ItemIndiceIndireto.h"

class GerenciadorDeArquivos
{
private:
    const std::string m_nomeDoArquivoCsv{"netflix_titles.csv"};
    const std::vector<std::string> m_nomesDosArquivosDeIndices{"arq_index_1", "arq_index_2", "arq_index_3", "arq_index_4", "arq_index_5"};

public:
    /// Construtor padrão.
    GerenciadorDeArquivos();

    /// Gera os arquivos de índices.
    bool gerarArquivosDeIndices();

    /// Gera o arquivo de índices direto mapeando o ID de todos os filmes e séries (arq_index_1).
    /// Gera o arquivo de índices indireto para recuperar, através do título, o ID de um filme ou série (arq_index_2).
    /// Gera os dois arquivos de índices diretos mapeando os ID de todos os filmes e de todas as séries (arq_index_3 e arq_index_4).
    /// Gera um arquivo de índices mapeando o ID de todos os filmes e séries brasileiras (arq_index_5).

    /// Obtém o conjunto de índices do primeiro arquivo de índices (arq_index_1).
    std::vector<ItemIndiceDireto> obterPrimeiroConjuntoDeIndices();
    /// Obtém o conjunto de índices do segundo arquivo de índices (arq_index_2).
    std::vector<ItemIndiceIndireto> obterSegundoConjuntoDeIndices();
    /// Obtém um vector de tamanho 2 contendo o conjunto de índices do terceiro e quarto arquivo de índices (arq_index_3 e arq_index_4).
    std::vector<std::vector<ItemIndiceDireto>> obterTerceiroQuartoConjuntoDeIndices();
    /// Obtém o conjunto de índices do quinto arquivo de índices (arq_index_5).
    std::vector<ItemIndiceDireto> obterQuintoConjuntoDeIndices();
};

#endif // GERENCIADOR_ARQUIVO_H
