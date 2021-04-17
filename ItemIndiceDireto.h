#ifndef ITEM_INDICE_DIRETO_H
#define ITEM_INDICE_DIRETO_H

#include <string>
#include <vector>
#include <fstream>
#include "ItemNetflix.h"

class ItemIndiceDireto
{
public:
    std::string idDoItemNetflix;
    unsigned int posicaoNoArquivo;

    ItemIndiceDireto(std::string m_idDoItemNetflix, int m_posicaoNoArquivo);

    /**
     * Escreve o objeto atual no arquivo especificado.
     * @param t_arquivoAberto O arquivo onde o ItemIndiceDireto deverá ser escrito.
     * @returns Se a escrita no arquivo ocorreu com sucesso.
     */
    bool escreverItemIndiceNoArquivo(std::ofstream& t_arquivoAberto);

    /**
     * Obtém, de forma direta, o ItemNetflix correspondente ao ItemIndiceDireto atual.
     * @param t_arquivoCSV O arquivo de onde o ItemNetflix será obtido.
     * @returns O ItemNetflix obtido.
     */
    ItemNetflix obterItemNetflix(std::ifstream& t_arquivoCSV);

    /**
     * Cria um objeto ItemNetflix a partir de uma linha do arquivo de índices.
     * @param t_conteudo Conteúdo da linha do arquivo.
     * @returns O ItemIndiceDireto criado.
     */
    static ItemIndiceDireto parseFromFileLine(std::string t_conteudo);

    /**
     * Ordena um vector de ItemIndiceDireto em ordem crescente de acordo o valor da propriedade
     * idDoItemNetflix.
     * @param conjuntoDeIndices O vector de ItemIndiceDireto a ser ordenado.
     * @returns O vector de ItemIndiceDireto ordenado.
     */
    static std::vector<ItemIndiceDireto> ordenarConjuntoDeIndices(std::vector<ItemIndiceDireto> conjuntoDeIndices);

    /**
     * Sobrecarga do operador '<' para comparar dois objetos do tipo ItemIndiceDireto de acordo com
     * o idDoItemNetflix de cada um.
     */
    bool operator < (const ItemIndiceDireto& item);
};

#endif // ITEM_INDICE_DIRETO_H
