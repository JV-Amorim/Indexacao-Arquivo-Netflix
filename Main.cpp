#include <iostream>
#include "ItemNetflix.h"
#include "GerenciadorDeArquivos.h"

using namespace std;

int main()
{
    GerenciadorDeArquivos gerenciador;

    vector<ItemNetflix> itens = gerenciador.obterTodosOsItensDoArquivoCsv();
    ItemNetflix::visualizarLista(itens, 100);

    return 0;
}
