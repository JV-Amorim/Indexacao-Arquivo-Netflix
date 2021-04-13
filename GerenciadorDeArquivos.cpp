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

    ofstream arquivoDeIndices1(m_nomesDosArquivosDeIndices[0]);
    ofstream arquivoDeIndices2(m_nomesDosArquivosDeIndices[1]);
    ofstream arquivoDeIndices3(m_nomesDosArquivosDeIndices[2]);
    ofstream arquivoDeIndices4(m_nomesDosArquivosDeIndices[3]);
    ofstream arquivoDeIndices5(m_nomesDosArquivosDeIndices[4]);

    bool algumArquivoFalhou =
        arquivoCsv.fail() || arquivoDeIndices1.fail() || arquivoDeIndices2.fail()
        || arquivoDeIndices3.fail() || arquivoDeIndices4.fail() || arquivoDeIndices5.fail();

    if (algumArquivoFalhou)
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomeDoArquivoCsv << "." << endl;

        arquivoCsv.close();
        arquivoDeIndices1.close();
        arquivoDeIndices2.close();
        arquivoDeIndices3.close();
        arquivoDeIndices4.close();
        arquivoDeIndices5.close();

        return false;
    }

    string output;
    int posicaoAtual = 0;

    getline(arquivoCsv, output);  // Header do arquivo.
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

        bool resultadoDaEscrita1 = itemIndiceDireto.escreverItemIndiceNoArquivo(arquivoDeIndices1); // arq_index_1
        bool resultadoDaEscrita2 = itemIndiceIndireto.escreverItemIndiceNoArquivo(arquivoDeIndices2); // arq_index_2

        bool resultadoDaEscrita3 = true, resultadoDaEscrita4 = true;
        if (itemNetflix.tipo == "Movie")
        {
            resultadoDaEscrita3 = itemIndiceDireto.escreverItemIndiceNoArquivo(arquivoDeIndices3); // arq_index_3
        }
        else if (itemNetflix.tipo == "TV Show")
        {
            resultadoDaEscrita4 = itemIndiceDireto.escreverItemIndiceNoArquivo(arquivoDeIndices4); // arq_index_4
        }

        bool resultadoDaEscrita5 = true;
        if (itemNetflix.pais.find("Brazil") != string::npos)
        {
            resultadoDaEscrita5 = itemIndiceDireto.escreverItemIndiceNoArquivo(arquivoDeIndices5); // arq_index_5
        }

        if (!resultadoDaEscrita1 || !resultadoDaEscrita2 || !resultadoDaEscrita3 || !resultadoDaEscrita4 || !resultadoDaEscrita5)
        {
            cout << "ERRO -> Os arquivo de indices nao foram gerados ou ficaram incompletos." << endl;

            arquivoCsv.close();
            arquivoDeIndices1.close();
            arquivoDeIndices2.close();
            arquivoDeIndices3.close();
            arquivoDeIndices4.close();
            arquivoDeIndices5.close();

            return false;
        }

        posicaoAtual += (int)output.size() + 2;
    }

    arquivoCsv.close();
    arquivoDeIndices1.close();
    arquivoDeIndices2.close();
    arquivoDeIndices3.close();
    arquivoDeIndices4.close();
    arquivoDeIndices5.close();

    return true;
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
