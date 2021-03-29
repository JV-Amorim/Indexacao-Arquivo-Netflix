#include <iostream>
#include "ItemIndiceDireto.h"
#include "StringHelpers.h"

using namespace std;

// Métodos da classe ItemIndiceDireto:

ItemIndiceDireto::ItemIndiceDireto(string m_idDoItemNetflix, int m_posicaoNoArquivo)
{
    idDoItemNetflix = m_idDoItemNetflix;
    posicaoNoArquivo = m_posicaoNoArquivo;
}

ItemIndiceDireto ItemIndiceDireto::parseFromFileLine(string t_conteudo)
{
    // TODO - Implementar método.

    ItemIndiceDireto item("-1", -1);
    return item;
}

bool ItemIndiceDireto::escreverObjetoNoArquivo(ofstream& t_arquivoAberto)
{
    t_arquivoAberto << idDoItemNetflix << ";" << posicaoNoArquivo << endl;

    if (t_arquivoAberto.fail())
    {
        cout << "ERRO -> Ocorreu um erro na gravacao de um item de indice." << endl;
        return false;
    }

    return true;
}
