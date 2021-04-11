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
        cout << "3. Sair;" << endl;

        cout << "Digite o numero da opcao desejada: ";
        cin >> opcaoEscolhida;

        switch (opcaoEscolhida)
        {
            case 1:
                app.pesquisarItensPorTitulo();
                cout << endl << endl;
                break;

            case 2:
                app.exibirItensBrasileirosDe2019();
                cout << endl << endl;
                break;

            case 3:
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
