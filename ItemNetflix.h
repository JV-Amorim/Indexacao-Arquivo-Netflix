#include <string>
#include <vector>

class ItemNetflix
{
public:
    std::string showId{""}, tipo{""}, titulo{""}, diretor{""}, pais{""}, dataDeAdicao{""}, anoDeLancamento{""}, classificacao{""}, duracao{""}, descricao{""};
    std::vector<std::string> elenco{}, generos{};

    ItemNetflix();
    std::string toString();
    static ItemNetflix parse(std::string t_conteudo);
};
