#include <iostream>
#include "Main.h"

using namespace std;

// Alunos: João Vitor Amorim e Thiago Riquelmo.

int main()
{
    App app;
    bool inicializouComSucesso = app.inicializarAplicacao();

    if (!inicializouComSucesso)
    {
        cout << "ERRO -> Nao foi possivel inicializar a aplicacao." << endl;
        return -1;
    }

    unsigned int opcaoEscolhida;
    bool repetir = true;

    do
    {
        cout << "MENU DE OPCOES" << endl;
        cout << "1. Inserir um novo filme/serie;" << endl;
        cout << "2. Remover um filme/serie pelo ID;" << endl;
        cout << "3. Pesquisar filme/serie pelo titulo;" << endl;
        cout << "4. Consultas diversas;" << endl;
        cout << "0. Sair;" << endl;

        cout << "Digite o numero da opcao desejada: ";
        cin >> opcaoEscolhida;

        switch (opcaoEscolhida)
        {
            case 1:
                app.inserirNovoItemNetflix();
                cout << endl << endl;
                break;

            case 2:
                app.removerItemPorId();
                cout << endl << endl;
                break;

            case 3:
                app.pesquisarItensPorTitulo();
                cout << endl << endl;
                break;

            case 4:
                exibirMenuDeConsultasDiversas(app);
                cout << endl << endl;
                break;

            case 0:
                repetir = false;
                break;

            default:
                cout << endl << "Digite uma opcao valida!" << endl;
                cout << endl << endl;
                break;
        }
    }
    while (repetir);

    return 0;
}

void exibirMenuDeConsultasDiversas(App app)
{
    unsigned int opcaoEscolhida;
    bool repetir = true;

    cout << endl;

    do
    {
        cout << "CONSULTAS DIVERSAS" << endl;
        cout << "1. Exibir filmes brasileiros de 2019;" << endl;
        cout << "2. Exibir filmes/series destinados para toda a familia;" << endl;
        cout << "3. Exibir filmes/series com tematica de artes marciais;" << endl;
        cout << "4. Exibir filmes com a participacao do ator Leonardo DiCaprio;" << endl;
        cout << "5. Exibir filmes dirigidos por Steven Spielberg;" << endl;
        cout << "6. Exibir filmes documentais com duracao superior a duas horas;" << endl;
        cout << "0. Retornar;" << endl;

        cout << "Digite o numero da opcao desejada: ";
        cin >> opcaoEscolhida;

        switch (opcaoEscolhida)
        {
            case 1:
                app.exibirFilmesBrasileirosDe2019();
                cout << endl << endl;
                break;
            case 2:
                app.exibirFilmesSeriesParaFamilia();
                cout << endl << endl;
                break;

            case 3:
                app.exibirFilmesSeriesComTematicaDeArtesMarciais();
                cout << endl << endl;
                break;

            case 4:
                app.exibirFilmesComAtorLeonardoDiCaprio();
                cout << endl << endl;
                break;

            case 5:
                app.exibirFilmesDirigidosPorStevenSpielberg();
                cout << endl << endl;
                break;

            case 6:
                app.exibirFilmesDocumentaisComMaisDeDuasHoras();
                cout << endl << endl;
                break;

            case 0:
                repetir = false;
                break;

            default:
                cout << endl << "Digite uma opcao valida!" << endl;
                cout << endl << endl;
                break;
        }
    }
    while (repetir);
}
