#ifndef ITEM_NETFLIX_H
#define ITEM_NETFLIX_H

#include <string>
#include <vector>

class ItemNetflix
{
public:
    std::string id{""}, tipo{""}, titulo{""}, diretor{""}, pais{""}, dataDeAdicao{""}, anoDeLancamento{""}, classificacao{""}, duracao{""}, descricao{""};
    std::vector<std::string> elenco{}, generos{};

    ItemNetflix();
    
    /**
     * Exibe os dados do ItemNetflix.
     */
    void visualizarItem();

    /**
     * Cria um objeto ItemNetflix a partir de uma linha do arquivo CSV.
     * @param t_conteudo Conteúdo da linha do arquivo.
     * @returns O ItemNetflix criado.
     */
    static ItemNetflix parseFromCsvLine(std::string t_conteudo);
};

#endif // ITEM_NETFLIX_H
