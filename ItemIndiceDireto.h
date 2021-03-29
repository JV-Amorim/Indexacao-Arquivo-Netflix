#ifndef ITEM_INDICE_DIRETO_H
#define ITEM_INDICE_DIRETO_H

#include <string>
#include <fstream>

class ItemIndiceDireto
{
public:
    std::string idDoItemNetflix;
    int posicaoNoArquivo;

    /// Construtor.
    ItemIndiceDireto(std::string m_idDoItemNetflix, int m_posicaoNoArquivo);

    /// Escreve o objeto atual no arquivo aberto no ofstream passado como par�metro.
    bool escreverObjetoNoArquivo(std::ofstream& t_arquivoAberto);

    /// Transforma uma linha do arquivo de �ndices em um objeto ItemIndiceDireto.
    static ItemIndiceDireto parseFromFileLine(std::string t_conteudo);
};

#endif // ITEM_INDICE_DIRETO_H
