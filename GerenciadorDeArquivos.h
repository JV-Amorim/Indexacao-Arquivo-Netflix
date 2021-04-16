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
    GerenciadorDeArquivos();

    /**
     * Getter da propriedade privada m_nomeDoArquivoCsv.
     * @returns String contendo o nome arquivo CSV.
     */
    std::string getNomeDoArquivoCsv();
    
    /**
     * Getter da propriedade privada m_nomesDosArquivosDeIndices.
     * @returns Um vector de strings contendo os nomes dos arquivos de índices.
     */
    std::vector<std::string> getNomeDosArquivosDeIndices();

    /**
     * Gera os arquivos de índices.
     * @returns Se os arquivos de índices foram gerados com sucesso.
     */
    bool gerarArquivosDeIndices();

    /**
     * Obtém o conjunto de índices do primeiro arquivo de índices (arq_index_1).
     * @returns Um vector de ItemIndiceDireto contendo o conjunto de índices.
     */
    std::vector<ItemIndiceDireto> obterPrimeiroConjuntoDeIndices();

    /**
     * Obtém o conjunto de índices do segundo arquivo de índices (arq_index_2).
     * @returns Um vector de ItemIndiceIndireto contendo o conjunto de índices.
     */
    std::vector<ItemIndiceIndireto> obterSegundoConjuntoDeIndices();

    /**
     * Obtém os conjuntos de índices do terceiro e quarto arquivo de índices (arq_index_3 e arq_index_4).
     * @returns Um vector de vector de ItemIndiceDireto contendo os dois conjuntos de índices.
     */
    std::vector<std::vector<ItemIndiceDireto>> obterTerceiroQuartoConjuntoDeIndices();
    
    /**
     * Obtém o conjunto de índices do quinto arquivo de índices (arq_index_5).
     * @returns Um vector de ItemIndiceDireto contendo o conjunto de índices.
     */
    std::vector<ItemIndiceDireto> obterQuintoConjuntoDeIndices();

    /**
     * Atualiza o arquivo de índices especificado com um novo conjunto de índices diretos.
     * @param t_novoConjuntoDeIndices Novo conjunto de índices.
     * @param t_nomeDoArquivoDeIndices Nome do arquivo de índices a ser atualizado.
     * @returns Se a atualização ocorreu com sucesso.
     */
    bool atualizarArquivoDeIndices(std::vector<ItemIndiceDireto> t_novoConjuntoDeIndices, std::string t_nomeDoArquivoDeIndices);

    /**
     * Atualiza o arquivo de índices especificado com um novo conjunto de índices indiretos.
     * @param t_novoConjuntoDeIndices Novo conjunto de índices.
     * @param t_nomeDoArquivoDeIndices Nome do arquivo de índices a ser atualizado.
     * @returns Se a atualização ocorreu com sucesso.
     */
    bool atualizarArquivoDeIndices(std::vector<ItemIndiceIndireto> t_novoConjuntoDeIndices, std::string t_nomeDoArquivoDeIndices);
};

#endif // GERENCIADOR_ARQUIVO_H
