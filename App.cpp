#include <iostream>
#include <fstream>
#include "App.h"
#include "ItemNetflix.h"
#include "ItemIndiceDireto.h"
#include "ItemIndiceIndireto.h"
#include "GerenciadorDeArquivos.h"

using namespace std;

// Métodos da classe App:

App::App() { }

bool App::inicializarAplicacao()
{
    GerenciadorDeArquivos gerenciador;
    return gerenciador.gerarArquivosDeIndices();
}

void App::pesquisarItensPorTitulo()
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

void App::exibirItensBrasileirosDe2019()
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
