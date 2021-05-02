#ifndef APP_H
#define APP_H

#include "ItemNetflix.h"

class App
{
private:

    /**
     * Exibe um campo de formulário que recebe uma resposta (entrada de texto) do usuário.
     * @param labelDoCampo Label do campo de formulário.
     * @param outputDoCampo Output do campo de formulário, que representa o texto que o usuário
     * digitou como resposta.
     * @returns Se a entrada de texto passou na validação do campo de formulário.
     */
    bool exibirCampoDeFormulario(std::string labelDoCampo, std::string& outputDoCampo);

    /**
     * Verifica se a resposta inserida por um usuário em um campo de formulário é válida.
     * @param resposta A resposta a ser validada.
     * @returns Se a resposta obtida no campo de formulário é válida.
     */
    bool validarRespostaDoCampoDeFormulario(std::string resposta);

public:
    App();

    /**
     * Inicializa a aplicação, gerando os arquivos de índices.
     * @returns Se a aplicação foi inicializada com sucesso.
     */
    bool inicializarAplicacao();

    /**
     * Insere um novo ItemNetflix ao arquivo de dados CSV.
     */
    void inserirNovoItemNetflix();

    /**
     * Exclui um ItemNetflix cujo ID corresponda ao digitado.
     */
    void removerItemPorId();

    /**
     * Encontra todos os ItemNetflix cujo título corresponde ao termo digitado.
     */
    void pesquisarItensPorTitulo();

    /**
     * Exibe todos os filmes produzidos no Brasil cujo ano de lançamento seja 2019.
     */
    void exibirFilmesBrasileirosDe2019();

    /**
     * Exibe todos os filmes e séries destinados à toda a família.
     */
    void exibirFilmesSeriesParaFamilia();

    /**
     * Exibe todos os filmes e séries com a temática de artes marciais.
     */
    void exibirFilmesSeriesComTematicaDeArtesMarciais();

    /**
     * Exibe todos os filmes que possuam o ator Leonardo DiCaprio no elenco.
     */
    void exibirFilmesComAtorLeonardoDiCaprio();

    /**
     * Exibe todos os filmes que possuam Steven Spielberg como diretor.
     */
    void exibirFilmesDirigidosPorStevenSpielberg();

    /**
     * Exibe todos os filmes documentais com duração superior a duas horas.
     */
    void exibirFilmesDocumentaisComMaisDeDuasHoras();
};

#endif // APP_H
