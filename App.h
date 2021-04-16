#ifndef APP_H
#define APP_H

class App
{
private:
    /**
     * Através de busca binária, obtém a posição de um ItemNetflix no arquivo CSV.
     * @param t_idDoItemNetflix O ID do ItemNetflix que se deseja obter a posição.
     * @returns Um inteiro que corresponde à posição do ItemNetflix no arquivo CSV.
     */
    int obterPosicaoDoItemNoArquivoPeloId(std::string t_idDoItemNetflix);
    
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

public:
    App();

    /**
     * Inicializa a aplicação, gerando os arquivos de índices.
     * @returns Se a aplicação foi inicializada com sucesso.
     */
    bool inicializarAplicacao();

    /**
     * Encontra todos os ItemNetflix cujo título corresponde ao termo digitado.
     */
    void pesquisarItensPorTitulo();

    /**
     * Exibe todos os filmes produzidos no Brasil cujo ano de lançamento seja 2019.
     */
    void exibirFilmesBrasileirosDe2019();

    /**
     * Permite ao usuário excluir um ItemNetflix cujo ID corresponda ao digitado.
     */
    void removerItemPorId();
};

#endif // APP_H
