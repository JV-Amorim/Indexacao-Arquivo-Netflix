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

    /**
     * Através de busca binária, obtém a posição de um ItemNetflix no arquivo CSV.
     * @param t_idDoItemNetflix O ID do ItemNetflix que se deseja obter a posição.
     * @returns Um inteiro que corresponde à posição do ItemNetflix no arquivo CSV.
     */
    unsigned int obterPosicaoDoItemNoArquivoPeloId(std::string t_idDoItemNetflix);

    /**
     * Remove um ItemNetflix do arquivo CSV.
     * @param t_posicaoDoItemNoArquivo A posição do ItemNetflix no arquivo CSV.
     * @returns Se a remoção foi realizada com sucesso.
     */
    bool removerItemNetflixDoArquivoCsv(int t_posicaoDoItemNoArquivo);

    /**
     * Remove um ItemNetflix dos arquivos de índices.
     * @param t_idDoItemNetflix O ID do ItemNetflix que se deseja remover dos arquivos de índices.
     * @returns Se a remoção foi realizada com sucesso.
     */
    bool removerItemNetflixDosArquivosDeIndices(std::string t_idDoItemNetflix);

    /**
     * Insere um ItemNetflix nos arquivos de índices, verificando os arquivos onde o item deve ser
     * inserido.
     * @param t_itemNetflix O ItemNetflix a ser inserido.
     * @param t_posicaoDoItemNoArquivoCsv A posição do ItemNetflix no arquivo CSV.
     * @returns Se a inserção foi realizada com sucesso.
     */
    bool adicionarItemNetflixAosArquivosDeIndices(ItemNetflix t_itemNetflix, unsigned int t_posicaoDoItemNoArquivoCsv);

    /**
     * Procura um espaço disponível no arquivo CSV (onde itens anteriores foram excluídos) e insere
     * o ItemNetflix nesse espaço, se o ItemNetflix couber no espaço.
     * @param t_itemNetflix O ItemNetflix a ser inserido.
     * @returns Se o ItemNetflix foi inserido em algum espaço disponível no meio do arquivo.
     */
    bool tentarInsercaoDeItemNetflixEmEspacoDisponivel(ItemNetflix t_itemNetflix);

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
     * Obtém o conjunto de índices diretos do arquivo especificado.
     * @param t_nomeDoArquivoDeIndices Nome do arquivo de índices.
     * @returns Um vector de ItemIndiceDireto contendo o conjunto de índices.
     */
    std::vector<ItemIndiceDireto> obterConjuntoDeIndicesDiretos(std::string t_nomeDoArquivoDeIndices);
    /**
     * Obtém o conjunto de índices indiretos do arquivo especificado.
     * @param t_nomeDoArquivoDeIndices Nome do arquivo de índices.
     * @returns Um vector de ItemIndiceIndireto contendo o conjunto de índices.
     */
    std::vector<ItemIndiceIndireto> obterConjuntoDeIndicesIndiretos(std::string t_nomeDoArquivoDeIndices);

    /**
     * Encontra todos os ItemNetflix cujo título corresponda, completamente ou parcialmente, ao termo digitado.
     */
    std::vector<ItemNetflix> buscarItemNetflixPorTitulo(std::string t_titulo);

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

    /**
     * Remove um ItemNetflix do arquivo CSV e atualiza os arquivos de índices.
     * @param t_idDoItemNetflix O ID do ItemNetflix que se deseja remover.
     */
    void removerItemNetflix(std::string t_idDoItemNetflix);

    /**
     * Obtém o ID do próximo ItemNetflix a ser inserido (incrementando o ID do último item no arquivo).
     * @return O ID obtido para o próximo item.
     */
    std::string obterIdDoProximoItemNetflix();

    /**
     * Insere um novo ItemNetflix no arquivo CSV e atualiza os arquivos de índices.
     * @param itemNetflix O objeto contendo os dados a serem inseridos no arquivo.
     */
    void inserirItemNetflix(ItemNetflix t_itemNetflix);
};

#endif // GERENCIADOR_ARQUIVO_H
