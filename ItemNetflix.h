#ifndef ITEM_NETFLIX_H
#define ITEM_NETFLIX_H

#include <string>
#include <vector>

class ItemNetflix
{
public:
    std::string id{""}, tipo{""}, titulo{""}, diretor{""}, pais{""}, dataDeAdicao{""}, anoDeLancamento{""}, classificacao{""}, duracao{""}, descricao{""};
    std::vector<std::string> elenco{}, generos{};

    /// Construtor padrão.
    ItemNetflix();
    /// Exibe todos os dados do ItemNetflix na tela.
    void visualizarItem();
    /// Transforma uma linha do arquivo netflix_titles.csv em um objeto ItemNetflix.
    static ItemNetflix parseFromCsvLine(std::string t_conteudo);
};

#endif // ITEM_NETFLIX_H
