#ifndef APP_H
#define APP_H

class App
{
public:
    /// Construtor padr�o.
    App();

    /// Inicializa a aplica��o, gerando os arquivos de �ndices.
    bool inicializarAplicacao();
    /// Permite o usu�rio encontrar todos os ItemNetflix cujo t�tulo corresponde ao termo digitado.
    void pesquisarItensPorTitulo();
    /// Exibe todos os ItemNetflix produzidos no Brasil cujo ano de lan�amento seja 2019.
    void exibirItensBrasileirosDe2019();
};

#endif // APP_H
