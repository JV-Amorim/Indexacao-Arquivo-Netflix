#include <iostream>
#include <string.h>
#include <algorithm>
#include "ItemIndiceIndireto.h"
#include "StringHelpers.h"

using namespace std;

// Métodos da classe ItemIndiceIndireto:

ItemIndiceIndireto::ItemIndiceIndireto(string m_idDoItemNetflix, std::string m_tituloDoItemNetflix)
{
    idDoItemNetflix = m_idDoItemNetflix;
    tituloDoItemNetflix = m_tituloDoItemNetflix;
}

bool ItemIndiceIndireto::escreverItemIndiceNoArquivo(ofstream& t_arquivoAberto)
{
    t_arquivoAberto << idDoItemNetflix << ";" << tituloDoItemNetflix << endl;

    if (t_arquivoAberto.fail())
    {
        return false;
    }

    return true;
}

ItemNetflix ItemIndiceIndireto::obterItemNetflix(vector<ItemIndiceDireto> conjuntoDeIndicesDiretos, ifstream& t_arquivoCSV)
{
    unsigned int posicaoNoArquivo;

    if (t_arquivoCSV.fail())
    {
        cout << "Ocorreu um erro ao obter a posicao do ItemNetflix que possui ID = " << idDoItemNetflix << "." << endl;
        return {};
    }

    for (unsigned int i = 0; i < (unsigned int)conjuntoDeIndicesDiretos.size(); i++)
    {
        string idDoItemAtual = "s" + to_string(conjuntoDeIndicesDiretos[i].idDoItemNetflix);

        if (idDoItemAtual == idDoItemNetflix)
        {
            posicaoNoArquivo = conjuntoDeIndicesDiretos[i].posicaoNoArquivo;
            break;
        }
    }

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

ItemIndiceIndireto ItemIndiceIndireto::parseFromFileLine(string t_conteudo)
{
    char* copiaDoConteudo = _strdup(t_conteudo.c_str());

    string idDoItemNetflix = strsep(&copiaDoConteudo, ";");
    string tituloDoItemNetflix = strsep(&copiaDoConteudo, ";");

    ItemIndiceIndireto item(idDoItemNetflix, tituloDoItemNetflix);
    return item;
}

vector<ItemIndiceIndireto> ItemIndiceIndireto::ordenarConjuntoDeIndices(vector<ItemIndiceIndireto> conjuntoDeIndices)
{
    std::sort(conjuntoDeIndices.begin(), conjuntoDeIndices.end());
    return conjuntoDeIndices;
}

bool ItemIndiceIndireto::operator < (const ItemIndiceIndireto& item)
{
    unsigned int idDoItemBase = std::stoi(idDoItemNetflix.substr(1));
    unsigned int idDoOutroItem = std::stoi(item.idDoItemNetflix.substr(1));
    return (idDoItemBase < idDoOutroItem);
}
