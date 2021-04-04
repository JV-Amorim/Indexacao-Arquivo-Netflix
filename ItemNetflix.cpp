#include <iostream>
#include <string.h>
#include "ItemNetflix.h"
#include "StringHelpers.h"

using namespace std;

// Métodos da classe ItemNetflix:

ItemNetflix::ItemNetflix() { }

void ItemNetflix::visualizarItem()
{
    cout << "ITEM DA NETFLIX" << endl;

    cout << "ID: " << id << endl;
    cout << "Tipo: " << tipo << endl;
    cout << "Titulo: " << titulo << endl;
    cout << "Diretor: " << diretor << endl;

    cout << "Elenco: ";
    for (int i = 0; i < (int)elenco.size(); i++)
    {
        cout << elenco[i];
        if (i + 1 != (int)elenco.size())
        {
            cout << ",";
        }
    }
    cout << endl;

    cout << "Pais: " << pais << endl;
    cout << "Data de adicao: " << dataDeAdicao << endl;
    cout << "Ano de lancamento: " << anoDeLancamento << endl;
    cout << "Classificacao: " << classificacao << endl;
    cout << "Duracao: " << duracao << endl;

    cout << "Generos: ";
    for (int i = 0; i < (int)generos.size(); i++)
    {
        cout << generos[i];
        if (i + 1 != (int)generos.size())
        {
            cout << ",";
        }
    }
    cout << endl;

    cout << "Descricao: " << descricao << endl;
}

ItemNetflix ItemNetflix::parseFromCsvLine(string t_conteudo)
{
    ItemNetflix item;
    char* copiaDoConteudo = _strdup(t_conteudo.c_str());

    item.id = strsep(&copiaDoConteudo, ";");
    item.tipo = strsep(&copiaDoConteudo, ";");
    item.titulo = strsep(&copiaDoConteudo, ";");
    item.diretor = strsep(&copiaDoConteudo, ";");
    char* elenco = strsep(&copiaDoConteudo, ";");
    item.pais = strsep(&copiaDoConteudo, ";");
    item.dataDeAdicao = strsep(&copiaDoConteudo, ";");
    item.anoDeLancamento = strsep(&copiaDoConteudo, ";");
    item.classificacao = strsep(&copiaDoConteudo, ";");
    item.duracao = strsep(&copiaDoConteudo, ";");
    char* generos = strsep(&copiaDoConteudo, ";");
    item.descricao = strsep(&copiaDoConteudo, ";");

    char* e;
    while((e = strsep(&elenco, ",")) != NULL)
    {
       item.elenco.push_back(e);
    }

    char* g;
    while((g = strsep(&generos, ",")) != NULL)
    {
       item.generos.push_back(g);
    }

    return item;
}
