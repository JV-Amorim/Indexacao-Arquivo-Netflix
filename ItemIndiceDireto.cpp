#include <iostream>
#include <string.h>
#include <algorithm>
#include "ItemIndiceDireto.h"
#include "StringHelpers.h"

using namespace std;

// Métodos públicos da classe ItemIndiceDireto:

ItemIndiceDireto::ItemIndiceDireto(string m_idDoItemNetflix, int m_posicaoNoArquivo)
{
    idDoItemNetflix = m_idDoItemNetflix;
    posicaoNoArquivo = m_posicaoNoArquivo;
}

bool ItemIndiceDireto::escreverItemIndiceNoArquivo(ofstream& t_arquivoAberto)
{
    t_arquivoAberto << idDoItemNetflix << ";" << posicaoNoArquivo << endl;

    if (t_arquivoAberto.fail())
    {
        return false;
    }

    return true;
}

ItemNetflix ItemIndiceDireto::obterItemNetflix(ifstream& t_arquivoCSV)
{
    t_arquivoCSV.clear();
    t_arquivoCSV.seekg(posicaoNoArquivo, ios::beg);

    string output;
    getline(t_arquivoCSV, output);

    if (t_arquivoCSV.fail())
    {
        cout << "Ocorreu um erro ao obter o ItemNetflix que possui ID = " << idDoItemNetflix << "." << endl;
        return {};
    }

    return ItemNetflix::parseFromCsvLine(output);
}

ItemIndiceDireto ItemIndiceDireto::parseFromFileLine(string t_conteudo)
{
    char* copiaDoConteudo = _strdup(t_conteudo.c_str());

    string idDoItemNetflix = strsep(&copiaDoConteudo, ";");
    unsigned int posicaoNoArquivo = stoi(strsep(&copiaDoConteudo, ";"));

    ItemIndiceDireto item(idDoItemNetflix, posicaoNoArquivo);
    return item;
}

vector<ItemIndiceDireto> ItemIndiceDireto::ordenarConjuntoDeIndices(vector<ItemIndiceDireto> conjuntoDeIndices)
{
    std::sort(conjuntoDeIndices.begin(), conjuntoDeIndices.end());
    return conjuntoDeIndices;
}

bool ItemIndiceDireto::operator < (const ItemIndiceDireto& item)
{
    unsigned int idDoItemBase = std::stoi(idDoItemNetflix.substr(1));
    unsigned int idDoOutroItem = std::stoi(item.idDoItemNetflix.substr(1));
    return (idDoItemBase < idDoOutroItem);
}
