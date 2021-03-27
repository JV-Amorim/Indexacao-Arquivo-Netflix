#include <iostream>
#include <fstream>
#include "GerenciadorDeArquivos.h"

using namespace std;

// Métodos da classe GerenciadorDeArquivos:

GerenciadorDeArquivos::GerenciadorDeArquivos() { }

vector<ItemNetflix> GerenciadorDeArquivos::obterTodosOsItensDoArquivoCsv()
{
    ifstream arquivoCsv(m_nomeDoArquivoCsv);

    if (arquivoCsv.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo CSV." << endl;
        return {};
    }

    vector<ItemNetflix> itens;
    string output;

    getline(arquivoCsv, output);  // Header do arquivo.

    while (getline(arquivoCsv, output))
    {
        ItemNetflix item = ItemNetflix::parseFromCsvLine(output);
        itens.push_back(item);
    }

    arquivoCsv.close();

    return itens;
}
