#include <iostream>
#include <fstream>
#include "GerenciadorDeArquivos.h"

using namespace std;

// Métodos da classe GerenciadorDeArquivos:

GerenciadorDeArquivos::GerenciadorDeArquivos() { }

bool GerenciadorDeArquivos::gerarArquivosDeIndices()
{
    ifstream arquivoCsv(m_nomeDoArquivoCsv);
    string output;

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

    getline(arquivoCsv, output);  // Header do arquivo.

    int posicaoAtual = 1;
    while (getline(arquivoCsv, output))
    {
        ItemNetflix itemNetflix = ItemNetflix::parseFromCsvLine(output);

        ItemIndiceDireto itemIndiceDireto(itemNetflix.id, posicaoAtual);
        ItemIndiceIndireto itemIndiceIndireto(itemNetflix.id, itemNetflix.titulo, posicaoAtual);

        bool resultadoDaEscrita1 = itemIndiceDireto.escreverObjetoNoArquivo(arquivoDeIndices1); // arq_index_1
        bool resultadoDaEscrita2 = itemIndiceIndireto.escreverObjetoNoArquivo(arquivoDeIndices2); // arq_index_2

        bool resultadoDaEscrita3 = true, resultadoDaEscrita4 = true;
        if (itemNetflix.tipo == "Movie")
        {
            resultadoDaEscrita3= itemIndiceDireto.escreverObjetoNoArquivo(arquivoDeIndices3); // arq_index_3
        }
        else if (itemNetflix.tipo == "TV Show")
        {
            resultadoDaEscrita4 = itemIndiceDireto.escreverObjetoNoArquivo(arquivoDeIndices4); // arq_index_4
        }

        bool resultadoDaEscrita5 = true;
        if (itemNetflix.pais.find("Brazil") != string::npos)
        {
            resultadoDaEscrita5 = itemIndiceDireto.escreverObjetoNoArquivo(arquivoDeIndices5); // arq_index_5
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

        posicaoAtual++;
    }

    arquivoCsv.close();
    arquivoDeIndices1.close();
    arquivoDeIndices2.close();
    arquivoDeIndices3.close();
    arquivoDeIndices4.close();
    arquivoDeIndices5.close();

    return true;
}

vector<ItemIndiceDireto> obterPrimeiroConjuntoDeIndices()
{
    // TODO - Implementar método.

    return {};
}

vector<ItemIndiceIndireto> obterSegundoConjuntoDeIndices()
{
    // TODO - Implementar método.

    return {};
}

vector<vector<ItemIndiceDireto>> obterTerceiroQuartoConjuntoDeIndices()
{
    // TODO - Implementar método.

    return {};
}

vector<ItemIndiceDireto> obterQuintoConjuntoDeIndices()
{
    // TODO - Implementar método.

    return {};
}
