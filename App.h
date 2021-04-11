#ifndef APP_H
#define APP_H

class App
{
public:
    /// Construtor padrão.
    App();

    /// Inicializa a aplicação, gerando os arquivos de índices.
    bool inicializarAplicacao();
    /// Permite o usuário encontrar todos os ItemNetflix cujo título corresponde ao termo digitado.
    void pesquisarItensPorTitulo();
    /// Exibe todos os ItemNetflix produzidos no Brasil cujo ano de lançamento seja 2019.
    void exibirItensBrasileirosDe2019();
};

#endif // APP_H
