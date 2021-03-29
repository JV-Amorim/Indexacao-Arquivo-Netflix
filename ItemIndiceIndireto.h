#ifndef ITEM_INDICE_INDIRETO_H
#define ITEM_INDICE_INDIRETO_H

#include <string>
#include <fstream>

class ItemIndiceIndireto
{
public:
    std::string idDoItemNetflix, tituloDoItemNetflix;
    int posicaoNoArquivo;

    /// Construtor.
    ItemIndiceIndireto(std::string m_idDoItemNetflix, std::string m_tituloDoItemNetflix, int m_posicaoNoArquivo);

    /// Escreve o objeto atual no arquivo aberto no ofstream passado como parâmetro.
    bool escreverObjetoNoArquivo(std::ofstream& t_arquivoAberto);

    /// Transforma uma linha do arquivo de índices em um objeto ItemIndiceIndireto.
    static ItemIndiceIndireto parseFromFileLine(std::string t_conteudo);
};

#endif // ITEM_INDICE_INDIRETO_H

