#include <iostream>
#include "Main.h"
#include "App.h"

using namespace std;

/// Alunos: João Vitor Amorim e Thiago Riquelmo.

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
        cout << "1. Pesquisar filme/serie pelo titulo;" << endl;
        cout << "2. Exibir filmes brasileiros de 2019;" << endl;
        cout << "3. Remover um filme/serie pelo ID;" << endl;
        cout << "4. Inserir um novo filme/serie;" << endl;
        cout << "0. Sair;" << endl;

        cout << "Digite o numero da opcao desejada: ";
        cin >> opcaoEscolhida;

        switch (opcaoEscolhida)
        {
            case 1:
                app.pesquisarItensPorTitulo();
                cout << endl << endl;
                break;

            case 2:
                app.exibirFilmesBrasileirosDe2019();
                cout << endl << endl;
                break;

            case 3:
                app.removerItemPorId();
                cout << endl << endl;
                break;

            case 4:
                app.inserirNovoItemNetflix();
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
