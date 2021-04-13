#ifndef APP_H
#define APP_H

class App
{
private:
    // TODO - Adicionar comentários:
    int obterPosicaoDoItemNoArquivoPeloId(std::string t_idDoItemNetflix);
    bool removerItemNetflixDoArquivoCsv(int t_posicaoDoItemNoArquivo, bool t_reverterRemocao);
    bool removerItemNetflixDosArquivosDeIndices(std::string t_idDoItemNetflix);

public:
    /// Construtor padrão.
    App();

    /// Inicializa a aplicação, gerando os arquivos de índices.
    bool inicializarAplicacao();
    /// Permite ao usuário encontrar todos os ItemNetflix cujo título corresponde ao termo digitado.
    void pesquisarItensPorTitulo();
    /// Exibe todos os filmes produzidos no Brasil cujo ano de lançamento seja 2019.
    void exibirFilmesBrasileirosDe2019();
    /// Permite ao usuário excluir um ItemNetflix cujo ID corresponda ao digitado.
    void removerItemPorId();
};

#endif // APP_H
