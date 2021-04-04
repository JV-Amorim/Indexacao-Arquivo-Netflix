#include <iostream>
#include <fstream>
#include "Main.h"
#include "ItemNetflix.h"
#include "ItemIndiceDireto.h"
#include "ItemIndiceIndireto.h"
#include "GerenciadorDeArquivos.h"

using namespace std;

/// Alunos: João Vitor Amorim e Thiago Riquelmo.

int main()
{
    GerenciadorDeArquivos gerenciador;
    gerenciador.gerarArquivosDeIndices();

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
                buscarPorTitulo();
                cout << endl << endl;
                break;

            case 2:
                imprimirObrasBrasileiras();
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

void buscarPorTitulo()
{
    GerenciadorDeArquivos gerenciador;
    vector<ItemIndiceIndireto> conjuntoIndiceIndireto = gerenciador.obterSegundoConjuntoDeIndices();
    vector<ItemIndiceDireto> conjuntoIndiceDireto = gerenciador.obterPrimeiroConjuntoDeIndices();
    bool encontradoAlgumItem = false;
    ifstream arquivoCsv(gerenciador.getNomeDoArquivoCsv());
    string tituloPesquisa = "";

    cout << endl << "Digite o titulo da obra desejada: ";
    cin >> tituloPesquisa;
    cout << endl << "- Resultado da pesquisa:" << endl << endl;

    for(int i = 0; i < (int)conjuntoIndiceIndireto.size(); i++)
    {
        if (conjuntoIndiceIndireto[i].tituloDoItemNetflix.find(tituloPesquisa) != string::npos)
        {
            ItemNetflix itemNetflix = conjuntoIndiceIndireto[i].obterItemNetflix(conjuntoIndiceDireto, arquivoCsv);
            itemNetflix.visualizarItem();
            cout << endl;
            encontradoAlgumItem = true;
        }
    }

    if (!encontradoAlgumItem)
    {
        cout << "Nenhum filme/serie encontrado com esse titulo." << endl;
    }
}

void imprimirObrasBrasileiras()
{
    GerenciadorDeArquivos gerenciador;
    vector<ItemIndiceDireto> conjuntoIndiceDireto = gerenciador.obterQuintoConjuntoDeIndices();
    ifstream arquivoCsv(gerenciador.getNomeDoArquivoCsv());

    cout << endl << "- Lista de filmes brasileiros do ano de 2019:" << endl << endl;

    for (int i = 0; i < (int)conjuntoIndiceDireto.size(); i++)
    {
        ItemNetflix itemNetflix = conjuntoIndiceDireto[i].obterItemNetflix(arquivoCsv);

        if ((itemNetflix.tipo == "Movie") && (itemNetflix.anoDeLancamento == "2019"))
        {
            itemNetflix.visualizarItem();
            cout << endl;
        }
    }
}
