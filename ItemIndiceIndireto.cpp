#include "ItemIndiceIndireto.h"
#include "StringHelpers.h"

using namespace std;

// Métodos da classe ItemIndiceIndireto:

ItemIndiceIndireto::ItemIndiceIndireto(string m_idDoItemNetflix, std::string m_tituloDoItemNetflix, int m_posicaoNoArquivo)
{
    idDoItemNetflix = m_idDoItemNetflix;
    posicaoNoArquivo = m_posicaoNoArquivo;
    tituloDoItemNetflix = m_tituloDoItemNetflix;
}

ItemIndiceIndireto ItemIndiceIndireto::parseFromFileLine(string t_conteudo)
{
    // TODO - Implementar método.

    ItemIndiceIndireto item("-1", "", -1);
    return item;
}

bool ItemIndiceIndireto::escreverObjetoNoArquivo(ofstream& t_arquivoAberto)
{
    t_arquivoAberto << idDoItemNetflix << ";" << tituloDoItemNetflix << ";" << posicaoNoArquivo << endl;

    if (t_arquivoAberto.fail())
    {
        return false;
    }

    return true;
}
