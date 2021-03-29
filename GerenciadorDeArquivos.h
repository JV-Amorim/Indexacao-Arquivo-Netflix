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
    /// Construtor padr�o.
    GerenciadorDeArquivos();

    /// Gera os arquivos de �ndices.
    bool gerarArquivosDeIndices();

    /// Gera o arquivo de �ndices direto mapeando o ID de todos os filmes e s�ries (arq_index_1).
    /// Gera o arquivo de �ndices indireto para recuperar, atrav�s do t�tulo, o ID de um filme ou s�rie (arq_index_2).
    /// Gera os dois arquivos de �ndices diretos mapeando os ID de todos os filmes e de todas as s�ries (arq_index_3 e arq_index_4).
    /// Gera um arquivo de �ndices mapeando o ID de todos os filmes e s�ries brasileiras (arq_index_5).

    /// Obt�m o conjunto de �ndices do primeiro arquivo de �ndices (arq_index_1).
    std::vector<ItemIndiceDireto> obterPrimeiroConjuntoDeIndices();
    /// Obt�m o conjunto de �ndices do segundo arquivo de �ndices (arq_index_2).
    std::vector<ItemIndiceIndireto> obterSegundoConjuntoDeIndices();
    /// Obt�m um vector de tamanho 2 contendo o conjunto de �ndices do terceiro e quarto arquivo de �ndices (arq_index_3 e arq_index_4).
    std::vector<std::vector<ItemIndiceDireto>> obterTerceiroQuartoConjuntoDeIndices();
    /// Obt�m o conjunto de �ndices do quinto arquivo de �ndices (arq_index_5).
    std::vector<ItemIndiceDireto> obterQuintoConjuntoDeIndices();
};

#endif // GERENCIADOR_ARQUIVO_H
