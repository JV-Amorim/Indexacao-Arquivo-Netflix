#ifndef APP_H
#define APP_H

class App
{
private:
    // TODO - Adicionar coment�rios:
    int obterPosicaoDoItemNoArquivoPeloId(std::string t_idDoItemNetflix);
    bool removerItemNetflixDoArquivoCsv(int t_posicaoDoItemNoArquivo, bool t_reverterRemocao);
    bool removerItemNetflixDosArquivosDeIndices(std::string t_idDoItemNetflix);

public:
    /// Construtor padr�o.
    App();

    /// Inicializa a aplica��o, gerando os arquivos de �ndices.
    bool inicializarAplicacao();
    /// Permite ao usu�rio encontrar todos os ItemNetflix cujo t�tulo corresponde ao termo digitado.
    void pesquisarItensPorTitulo();
    /// Exibe todos os filmes produzidos no Brasil cujo ano de lan�amento seja 2019.
    void exibirFilmesBrasileirosDe2019();
    /// Permite ao usu�rio excluir um ItemNetflix cujo ID corresponda ao digitado.
    void removerItemPorId();
};

#endif // APP_H
