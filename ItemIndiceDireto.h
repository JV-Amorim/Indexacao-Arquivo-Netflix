#ifndef ITEM_INDICE_DIRETO_H
#define ITEM_INDICE_DIRETO_H

#include <string>
#include <fstream>
#include "ItemNetflix.h"

class ItemIndiceDireto
{
public:
    std::string idDoItemNetflix;
    int posicaoNoArquivo;

    /// Construtor.
    ItemIndiceDireto(std::string m_idDoItemNetflix, int m_posicaoNoArquivo);

    /// Escreve o objeto atual no arquivo aberto no ofstream passado como parâmetro.
    bool escreverItemIndiceNoArquivo(std::ofstream& t_arquivoAberto);

    /// Obtém, de forma direta, o ItemNetflix que possui o ID correspondente ao valor da propriedade
    /// idDoItemNetflix, utilizando a posição em bytes no arquivo (valor da propriedade posicaoNoArquivo).
    /// O parâmetro t_arquivoCSV trata-se do ifstream do arquivo netflix_titles.csv.
    ItemNetflix obterItemNetflix(std::ifstream& t_arquivoCSV);

    /// Transforma uma linha do arquivo de índices em um objeto ItemIndiceDireto.
    static ItemIndiceDireto parseFromFileLine(std::string t_conteudo);
};

#endif // ITEM_INDICE_DIRETO_H
