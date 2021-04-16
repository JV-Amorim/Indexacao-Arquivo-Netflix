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

    ItemIndiceIndireto(std::string idDoItemNetflix, std::string m_tituloDoItemNetflix);

    /**
     * Escreve o objeto atual no arquivo especificado.
     * @param t_arquivoAberto O arquivo onde o ItemIndiceIndireto deverá ser escrito.
     * @returns Se a escrita no arquivo ocorreu com sucesso.
     */
    bool escreverItemIndiceNoArquivo(std::ofstream& t_arquivoAberto);

    /**
     * Obtém, de forma indireta, o ItemNetflix correspondente ao ItemIndiceIndireto atual.
     * @param conjuntoDeIndicesDiretos O conjunto de índices diretos para ser utilizado como
     * intermediário para obter o ItemNetflix.
     * @param t_arquivoCSV O arquivo de onde o ItemNetflix será obtido.
     * @returns O ItemNetflix obtido.
     */
    ItemNetflix obterItemNetflix(std::vector<ItemIndiceDireto> conjuntoDeIndicesDiretos, std::ifstream& t_arquivoCSV);

    /**
     * Cria um objeto ItemNetflix a partir de uma linha do arquivo de índices.
     * @param t_conteudo Conteúdo da linha do arquivo.
     * @returns O ItemIndiceIndireto criado.
     */
    static ItemIndiceIndireto parseFromFileLine(std::string t_conteudo);

    /**
     * Ordena um vector de ItemIndiceIndireto em ordem crescente de acordo o valor da propriedade 
     * idDoItemNetflix.
     * @param conjuntoDeIndices O vector de ItemIndiceIndireto a ser ordenado.
     * @returns O vector de ItemIndiceIndireto ordenado.
     */
    static std::vector<ItemIndiceIndireto> ordenarConjuntoDeIndices(std::vector<ItemIndiceIndireto> conjuntoDeIndices);

    /**
     * Sobrecarga do operador '<' para comparar dois objetos do tipo ItemIndiceIndireto de acordo com
     * o idDoItemNetflix de cada um.
     */
    bool operator < (const ItemIndiceIndireto& item);
};

#endif // ITEM_INDICE_INDIRETO_H

