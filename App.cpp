#include <iostream>
#include <fstream>
#include "App.h"
#include "ItemNetflix.h"
#include "ItemIndiceDireto.h"
#include "ItemIndiceIndireto.h"
#include "GerenciadorDeArquivos.h"
#include "StringHelpers.h"

using namespace std;

// M�todos p�blicos da classe App:

App::App() { }

bool App::inicializarAplicacao()
{
    GerenciadorDeArquivos gerenciador;
    return gerenciador.gerarArquivosDeIndices();
}

void App::pesquisarItensPorTitulo()
{
    GerenciadorDeArquivos gerenciador;
    vector<ItemIndiceIndireto> conjuntoIndiceIndireto = gerenciador.obterSegundoConjuntoDeIndices();
    vector<ItemIndiceDireto> conjuntoIndiceDireto = gerenciador.obterPrimeiroConjuntoDeIndices();
    bool encontradoAlgumItem = false;
    ifstream arquivoCsv(gerenciador.getNomeDoArquivoCsv());
    string tituloPesquisa = "";

    cout << endl << "Digite o titulo do filme/serie que deseja encontrar: ";
    cin >> tituloPesquisa;
    cout << endl << "- Resultado da pesquisa:" << endl << endl;

    tituloPesquisa = toLowerCase(tituloPesquisa);

    for(int i = 0; i < (int)conjuntoIndiceIndireto.size(); i++)
    {
        string tituloDoItemNetflix = toLowerCase(conjuntoIndiceIndireto[i].tituloDoItemNetflix);

        if (tituloDoItemNetflix.find(tituloPesquisa) != string::npos)
        {
            ItemNetflix itemNetflix = conjuntoIndiceIndireto[i].obterItemNetflix(conjuntoIndiceDireto, arquivoCsv);
            itemNetflix.visualizarItem();
            cout << endl;
            encontradoAlgumItem = true;
        }
    }

    if (!encontradoAlgumItem)
    {
        cout << "Nenhum filme/serie encontrado com esse titulo." << endl;
    }
}

void App::exibirFilmesBrasileirosDe2019()
{
    GerenciadorDeArquivos gerenciador;
    vector<ItemIndiceDireto> conjuntoIndiceDireto = gerenciador.obterQuintoConjuntoDeIndices();
    ifstream arquivoCsv(gerenciador.getNomeDoArquivoCsv());

    cout << endl << "- Lista de filmes brasileiros do ano de 2019:" << endl << endl;

    for (int i = 0; i < (int)conjuntoIndiceDireto.size(); i++)
    {
        ItemNetflix itemNetflix = conjuntoIndiceDireto[i].obterItemNetflix(arquivoCsv);

        if ((itemNetflix.tipo == "Movie") && (itemNetflix.anoDeLancamento == "2019"))
        {
            itemNetflix.visualizarItem();
            cout << endl;
        }
    }
}

void App::removerItemPorId()
{
    string idDoItemNetflix;

    cout << endl << "Digite o ID do filme/serie que deseja remover: s";
    cin >> idDoItemNetflix;
    idDoItemNetflix = "s" + idDoItemNetflix;

    int posicaoDoItemNoArquivo = obterPosicaoDoItemNoArquivoPeloId(idDoItemNetflix);

    if (posicaoDoItemNoArquivo == -1)
    {
        cout << endl << "Nenhum filme/serie possui o ID indicado." << endl;
        return;
    }

    bool resultadoDaRemocaoDoArquivoCsv = removerItemNetflixDoArquivoCsv(posicaoDoItemNoArquivo, false);

    if (!resultadoDaRemocaoDoArquivoCsv)
    {
        cout << endl << "ERRO -> Nao foi possivel manipular o arquivo CSV. ";
        cout << "Logo, nao foi possivel realizar a remocao do filme/serie." << endl;
        return;
    }

    bool resultadoDaRemocaoDosArquivosDeIndice = removerItemNetflixDosArquivosDeIndices(idDoItemNetflix);

    if (!resultadoDaRemocaoDosArquivosDeIndice)
    {
        cout << endl << "ERRO -> Nao foi possivel manipular o arquivo os arquivos de indices. ";
        cout << "Portanto, nao foi possivel realizar a remocao do filme/serie. ";
        cout << "Sera necessario gerar novamente os arquivos de indice. ";
        cout << "As alteracoes no arquivo CSV serao revertidas." << endl;

        bool resultadoDaReversaoDaRemocao = removerItemNetflixDoArquivoCsv(posicaoDoItemNoArquivo, true);
        if (!resultadoDaReversaoDaRemocao)
        {
            cout << endl << "ERRO -> Nao foi possivel reverter da remocao do filme/serie do arquivo CSV. ";
            cout << "Os arquivos de indice estao inconsistentes com os dados." << endl;
        }

        return;
    }

    cout << endl << "O filme/serie foi removido com sucesso." << endl;
}

// M�todos privados da classe App:

int App::obterPosicaoDoItemNoArquivoPeloId(string t_idDoItemNetflix)
{
    GerenciadorDeArquivos gerenciador;
    vector<ItemIndiceDireto> conjuntoIndiceDireto = gerenciador.obterPrimeiroConjuntoDeIndices();

    for (int i = 0; i < (int)conjuntoIndiceDireto.size(); i++)
    {
        if (conjuntoIndiceDireto[i].idDoItemNetflix == t_idDoItemNetflix)
        {
            return conjuntoIndiceDireto[i].posicaoNoArquivo;
        }
    }

    return -1;
}

bool App::removerItemNetflixDoArquivoCsv(int t_posicaoDoItemNoArquivo, bool t_reverterRemocao)
{
    GerenciadorDeArquivos gerenciador;
    ofstream arquivoCsv(gerenciador.getNomeDoArquivoCsv(), ios::in | ios::out);

    if (arquivoCsv.fail())
    {
        return false;
    }

    arquivoCsv.seekp(t_posicaoDoItemNoArquivo);
    if (t_reverterRemocao)
    {
        arquivoCsv.write("s", 1);
    }
    else
    {
        arquivoCsv.write("*", 1);
    }
    arquivoCsv.close();

    return true;
}

bool App::removerItemNetflixDosArquivosDeIndices(string t_idDoItemNetflix)
{
    bool resultadoFinal = false;
    GerenciadorDeArquivos gerenciador;
    vector<string> nomeDosArquivosDeIndices = gerenciador.getNomeDosArquivosDeIndices();

    vector<vector<ItemIndiceDireto>> conjuntosDeIndicesDiretos;
    vector<vector<ItemIndiceDireto>> conjuntoDeIndices_3_4 = gerenciador.obterTerceiroQuartoConjuntoDeIndices();

    conjuntosDeIndicesDiretos.push_back(gerenciador.obterPrimeiroConjuntoDeIndices());
    conjuntosDeIndicesDiretos.push_back({});
    conjuntosDeIndicesDiretos.push_back(conjuntoDeIndices_3_4[0]);
    conjuntosDeIndicesDiretos.push_back(conjuntoDeIndices_3_4[1]);
    conjuntosDeIndicesDiretos.push_back(gerenciador.obterQuintoConjuntoDeIndices());

    for (int i = 0; i < (int)conjuntosDeIndicesDiretos.size(); i++)
    {
        vector<ItemIndiceDireto> conjuntoAtual = conjuntosDeIndicesDiretos[i];

        for (int j = 0; j < (int)conjuntoAtual.size(); j++)
        {
            if (conjuntoAtual[j].idDoItemNetflix == t_idDoItemNetflix)
            {
                conjuntoAtual.erase(conjuntoAtual.begin() + j);
                resultadoFinal = gerenciador.atualizarArquivoDeIndices(conjuntoAtual, nomeDosArquivosDeIndices[i]);
                break;
            }
        }
    }

    vector<ItemIndiceIndireto> conjuntoDeIndices_2 = gerenciador.obterSegundoConjuntoDeIndices();

    for (int i = 0; i < (int)conjuntoDeIndices_2.size(); i++)
    {
        if (conjuntoDeIndices_2[i].idDoItemNetflix == t_idDoItemNetflix)
        {
            conjuntoDeIndices_2.erase(conjuntoDeIndices_2.begin() + i);
            resultadoFinal = gerenciador.atualizarArquivoDeIndices(conjuntoDeIndices_2, nomeDosArquivosDeIndices[1]);
            break;
        }
    }

    return resultadoFinal;
}
