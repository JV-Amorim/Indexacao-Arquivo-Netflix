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

    /// Getter da propriedade m_nomeDoArquivoCsv.
    std::string getNomeDoArquivoCsv();
    /// Getter da propriedade m_nomesDosArquivosDeIndices.
    std::vector<std::string> getNomeDosArquivosDeIndices();

    /// Gera os arquivos de índices.
    bool gerarArquivosDeIndices();

    /// Obtém o conjunto de índices do primeiro arquivo de índices (arq_index_1).
    std::vector<ItemIndiceDireto> obterPrimeiroConjuntoDeIndices();
    /// Obtém o conjunto de índices do segundo arquivo de índices (arq_index_2).
    std::vector<ItemIndiceIndireto> obterSegundoConjuntoDeIndices();
    /// Obtém um vector de tamanho 2 contendo o conjunto de índices do terceiro e quarto arquivo de índices (arq_index_3 e arq_index_4).
    std::vector<std::vector<ItemIndiceDireto>> obterTerceiroQuartoConjuntoDeIndices();
    /// Obtém o conjunto de índices do quinto arquivo de índices (arq_index_5).
    std::vector<ItemIndiceDireto> obterQuintoConjuntoDeIndices();

    // TODO - Adicionar comentários:
    bool atualizarArquivoDeIndices(std::vector<ItemIndiceDireto> t_novoConjuntoDeIndices, std::string t_nomeDoArquivoDeIndices);
    bool atualizarArquivoDeIndices(std::vector<ItemIndiceIndireto> t_novoConjuntoDeIndices, std::string t_nomeDoArquivoDeIndices);
};

#endif // GERENCIADOR_ARQUIVO_H
