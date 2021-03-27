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

    void visualizarItem();
    std::string toCsvLine();

    static void visualizarLista(std::vector<ItemNetflix> t_itens);
    static void visualizarLista(std::vector<ItemNetflix> t_itens, int t_limite);
    static ItemNetflix parseFromCsvLine(std::string t_conteudo);
};

#endif // ITEM_NETFLIX_H
