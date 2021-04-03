#ifndef ITEM_INDICE_INDIRETO_H
#define ITEM_INDICE_INDIRETO_H

#include <string>
#include <fstream>
#include <vector>
#include "ItemIndiceDireto.h"
#include "ItemNetflix.h"

class ItemIndiceIndireto
{
public:
    std::string idDoItemNetflix, tituloDoItemNetflix;

    /// Construtor.
    ItemIndiceIndireto(std::string idDoItemNetflix, std::string m_tituloDoItemNetflix);

    /// Escreve o objeto atual no arquivo aberto no ofstream passado como parâmetro.
    bool escreverItemIndiceNoArquivo(std::ofstream& t_arquivoAberto);

    /// Obtém, de forma indireta, o ItemNetflix que possui o ID correspondente ao valor da propriedade
    /// idDoItemNetflix, utilizando a posição em bytes no arquivo (valor da propriedade posicaoNoArquivo).
    /// O parâmetro conjuntoDeIndicesDiretos trata-se do conjunto de índices direto.
    /// O parâmetro t_arquivoCSV trata-se do ifstream do arquivo netflix_titles.csv.
    ItemNetflix obterItemNetflix(std::vector<ItemIndiceDireto> conjuntoDeIndicesDiretos, std::ifstream& t_arquivoCSV);

    /// Transforma uma linha do arquivo de índices em um objeto ItemIndiceIndireto.
    static ItemIndiceIndireto parseFromFileLine(std::string t_conteudo);
};

#endif // ITEM_INDICE_INDIRETO_H

