#include <iostream>
#include <fstream>
#include "GerenciadorDeArquivos.h"

using namespace std;

// Métodos da classe GerenciadorDeArquivos:

GerenciadorDeArquivos::GerenciadorDeArquivos() { }

string GerenciadorDeArquivos::getNomeDoArquivoCsv()
{
    return m_nomeDoArquivoCsv;
}

vector<string> GerenciadorDeArquivos::getNomeDosArquivosDeIndices()
{
    return m_nomesDosArquivosDeIndices;
}

bool GerenciadorDeArquivos::gerarArquivosDeIndices()
{
    ifstream arquivoCsv(m_nomeDoArquivoCsv);

    if (arquivoCsv.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomeDoArquivoCsv << "." << endl;
        arquivoCsv.close();
        return false;
    }

    vector<ItemIndiceDireto> conjuntoDeIndices1, conjuntoDeIndices3, conjuntoDeIndices4, conjuntoDeIndices5;
    vector<ItemIndiceIndireto> conjuntoDeIndices2;

    string output;
    int posicaoAtual = 0;

    // Header do arquivo.
    getline(arquivoCsv, output);
    posicaoAtual += (int)output.size() + 2;

    while (getline(arquivoCsv, output))
    {
        if (output[0] == '*')
        {
            posicaoAtual += (int)output.size() + 2;
            continue;
        }

        ItemNetflix itemNetflix = ItemNetflix::parseFromCsvLine(output);
        ItemIndiceDireto itemIndiceDireto(itemNetflix.id, posicaoAtual);
        ItemIndiceIndireto itemIndiceIndireto(itemNetflix.id, itemNetflix.titulo);

        conjuntoDeIndices1.push_back(itemIndiceDireto);
        conjuntoDeIndices2.push_back(itemIndiceIndireto);

        if (itemNetflix.tipo == "Movie")
        {
            conjuntoDeIndices3.push_back(itemIndiceDireto);
        }
        else if (itemNetflix.tipo == "TV Show")
        {
            conjuntoDeIndices4.push_back(itemIndiceDireto);
        }

        if (itemNetflix.pais.find("Brazil") != string::npos)
        {
            conjuntoDeIndices5.push_back(itemIndiceDireto);
        }

        posicaoAtual += (int)output.size() + 2;
    }

    arquivoCsv.close();

    // Ordenação dos índices antes de gravá-los nos arquivos:
    conjuntoDeIndices1 = ItemIndiceDireto::ordenarConjuntoDeIndices(conjuntoDeIndices1);
    conjuntoDeIndices2 = ItemIndiceIndireto::ordenarConjuntoDeIndices(conjuntoDeIndices2);
    conjuntoDeIndices3 = ItemIndiceDireto::ordenarConjuntoDeIndices(conjuntoDeIndices3);
    conjuntoDeIndices4 = ItemIndiceDireto::ordenarConjuntoDeIndices(conjuntoDeIndices4);
    conjuntoDeIndices5 = ItemIndiceDireto::ordenarConjuntoDeIndices(conjuntoDeIndices5);

    bool resultadoFinal =
        atualizarArquivoDeIndices(conjuntoDeIndices1, m_nomesDosArquivosDeIndices[0])
        && atualizarArquivoDeIndices(conjuntoDeIndices2, m_nomesDosArquivosDeIndices[1])
        && atualizarArquivoDeIndices(conjuntoDeIndices3, m_nomesDosArquivosDeIndices[2])
        && atualizarArquivoDeIndices(conjuntoDeIndices4, m_nomesDosArquivosDeIndices[3])
        && atualizarArquivoDeIndices(conjuntoDeIndices5, m_nomesDosArquivosDeIndices[4]);

    return resultadoFinal;
}

vector<ItemIndiceDireto> GerenciadorDeArquivos::obterPrimeiroConjuntoDeIndices()
{
    ifstream arquivoDeIndices(m_nomesDosArquivosDeIndices[0]);

    if (arquivoDeIndices.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomesDosArquivosDeIndices[0] << "." << endl;
        arquivoDeIndices.close();
        return {};
    }

    string output;
    vector<ItemIndiceDireto> conjuntoDeIndices;

    while (getline(arquivoDeIndices, output))
    {
        ItemIndiceDireto item = ItemIndiceDireto::parseFromFileLine(output);
        conjuntoDeIndices.push_back(item);
    }

    arquivoDeIndices.close();

    return conjuntoDeIndices;
}

vector<ItemIndiceIndireto> GerenciadorDeArquivos::obterSegundoConjuntoDeIndices()
{
    ifstream arquivoDeIndices(m_nomesDosArquivosDeIndices[1]);

    if (arquivoDeIndices.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomesDosArquivosDeIndices[1] << "." << endl;
        arquivoDeIndices.close();
        return {};
    }

    string output;
    vector<ItemIndiceIndireto> conjuntoDeIndices;

    while (getline(arquivoDeIndices, output))
    {
        ItemIndiceIndireto item = ItemIndiceIndireto::parseFromFileLine(output);
        conjuntoDeIndices.push_back(item);
    }

    arquivoDeIndices.close();

    return conjuntoDeIndices;
}

vector<vector<ItemIndiceDireto>> GerenciadorDeArquivos::obterTerceiroQuartoConjuntoDeIndices()
{
    // Filmes:

    ifstream arquivoDeIndicesFilmes(m_nomesDosArquivosDeIndices[2]);

    if (arquivoDeIndicesFilmes.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomesDosArquivosDeIndices[2] << "." << endl;
        arquivoDeIndicesFilmes.close();
        return {};
    }

    string outputFilmes;
    vector<ItemIndiceDireto> conjuntoDeIndicesFilmes;

    while (getline(arquivoDeIndicesFilmes, outputFilmes))
    {
        ItemIndiceDireto item = ItemIndiceDireto::parseFromFileLine(outputFilmes);
        conjuntoDeIndicesFilmes.push_back(item);
    }
    arquivoDeIndicesFilmes.close();

    // Séries:

    ifstream arquivoDeIndicesSeries(m_nomesDosArquivosDeIndices[3]);

    if (arquivoDeIndicesSeries.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomesDosArquivosDeIndices[3] << "." << endl;
        arquivoDeIndicesSeries.close();
        return {};
    }

    string outputSeries;
    vector<ItemIndiceDireto> conjuntoDeIndicesSeries;

    while (getline(arquivoDeIndicesSeries, outputSeries))
    {
        ItemIndiceDireto item = ItemIndiceDireto::parseFromFileLine(outputSeries);
        conjuntoDeIndicesSeries.push_back(item);
    }
    arquivoDeIndicesSeries.close();

    // Conjunto final:

    vector<vector<ItemIndiceDireto>> conjuntosDeIndices;
    conjuntosDeIndices.push_back(conjuntoDeIndicesFilmes);
    conjuntosDeIndices.push_back(conjuntoDeIndicesSeries);

    return conjuntosDeIndices;
}

vector<ItemIndiceDireto> GerenciadorDeArquivos::obterQuintoConjuntoDeIndices()
{
    ifstream arquivoDeIndices(m_nomesDosArquivosDeIndices[4]);

    if (arquivoDeIndices.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomesDosArquivosDeIndices[4] << "." << endl;
        arquivoDeIndices.close();
        return {};
    }

    string output;
    vector<ItemIndiceDireto> conjuntoDeIndices;

    while (getline(arquivoDeIndices, output))
    {
        ItemIndiceDireto item = ItemIndiceDireto::parseFromFileLine(output);
        conjuntoDeIndices.push_back(item);
    }

    arquivoDeIndices.close();

    return conjuntoDeIndices;
}

bool GerenciadorDeArquivos::atualizarArquivoDeIndices(vector<ItemIndiceDireto> t_novoConjuntoDeIndices, string t_nomeDoArquivoDeIndices)
{
    ofstream arquivoDeIndices(t_nomeDoArquivoDeIndices, ios::trunc);

    for (int i = 0; i < (int)t_novoConjuntoDeIndices.size(); i++)
    {
        if (!t_novoConjuntoDeIndices[i].escreverItemIndiceNoArquivo(arquivoDeIndices))
        {
            return false;
        }
    }

    return true;
}

bool GerenciadorDeArquivos::atualizarArquivoDeIndices(vector<ItemIndiceIndireto> t_novoConjuntoDeIndices, string t_nomeDoArquivoDeIndices)
{
    ofstream arquivoDeIndices(t_nomeDoArquivoDeIndices, ios::trunc);

    for (int i = 0; i < (int)t_novoConjuntoDeIndices.size(); i++)
    {
        if (!t_novoConjuntoDeIndices[i].escreverItemIndiceNoArquivo(arquivoDeIndices))
        {
            return false;
        }
    }

    return true;
}
