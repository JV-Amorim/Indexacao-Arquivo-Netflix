#include <iostream>
#include "ItemNetflix.h"
#include "GerenciadorDeArquivos.h"

using namespace std;

int main()
{
    GerenciadorDeArquivos gerenciador;
    gerenciador.gerarArquivosDeIndices();
    return 0;
}
