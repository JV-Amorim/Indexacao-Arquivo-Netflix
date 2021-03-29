#include <iostream>
#include <fstream>
#include "GerenciadorDeArquivos.h"

using namespace std;

// M�todos da classe GerenciadorDeArquivos:

GerenciadorDeArquivos::GerenciadorDeArquivos() { }

bool GerenciadorDeArquivos::gerarPrimeiroArquivoDeIndices()
{
    ifstream arquivoCsv(m_nomeDoArquivoCsv);
    ofstream arquivoDeIndices(m_nomesDosArquivosDeIndices[0]);
    string output;

    if (arquivoCsv.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomeDoArquivoCsv << "." << endl;

        arquivoCsv.close();
        arquivoDeIndices.close();
        return false;
    }

    if (arquivoDeIndices.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomesDosArquivosDeIndices[0] << "." << endl;

        arquivoCsv.close();
        arquivoDeIndices.close();
        return false;
    }

    getline(arquivoCsv, output);  // Header do arquivo.

    int posicaoAtual = 1;
    while (getline(arquivoCsv, output))
    {
        ItemNetflix itemNetflix = ItemNetflix::parseFromCsvLine(output);
        ItemIndiceDireto itemIndiceDireto(itemNetflix.id, posicaoAtual++);

        bool resultadoDaEscrita = itemIndiceDireto.escreverObjetoNoArquivo(arquivoDeIndices);

        if (!resultadoDaEscrita)
        {
            cout << "ERRO -> O arquivo de indices nao foi gerado ou ficou incompleto." << endl;
            arquivoCsv.close();
            arquivoDeIndices.close();
            return false;
        }
    }

    arquivoCsv.close();
    arquivoDeIndices.close();
    return true;
}

bool GerenciadorDeArquivos::gerarSegundoArquivoDeIndices()
{
    ifstream arquivoCsv(m_nomeDoArquivoCsv);
    ofstream arquivoDeIndices(m_nomesDosArquivosDeIndices[1]);
    string output;

    if (arquivoCsv.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomeDoArquivoCsv << "." << endl;

        arquivoCsv.close();
        arquivoDeIndices.close();
        return false;
    }

    if (arquivoDeIndices.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomesDosArquivosDeIndices[0] << "." << endl;

        arquivoCsv.close();
        arquivoDeIndices.close();
        return false;
    }

    getline(arquivoCsv, output);  // Header do arquivo.

    int posicaoAtual = 1;
    while (getline(arquivoCsv, output))
    {
        ItemNetflix itemNetflix = ItemNetflix::parseFromCsvLine(output);
        ItemIndiceIndireto itemIndiceIndireto(itemNetflix.id, itemNetflix.titulo, posicaoAtual++);

        bool resultadoDaEscrita = itemIndiceIndireto.escreverObjetoNoArquivo(arquivoDeIndices);

        if (!resultadoDaEscrita)
        {
            cout << "ERRO -> O arquivo de indices nao foi gerado ou ficou incompleto." << endl;
            arquivoCsv.close();
            arquivoDeIndices.close();
            return false;
        }
    }

    arquivoCsv.close();
    arquivoDeIndices.close();
    return true;
}

bool GerenciadorDeArquivos::gerarTerceiroQuartoArquivosDeIndices()
{
    // TODO - Implementar m�todo.

    return true;
}

bool GerenciadorDeArquivos::gerarQuintoArquivoDeIndices()
{
    // TODO - Implementar m�todo.

    return true;
}

vector<ItemIndiceDireto> obterPrimeiroConjuntoDeIndices()
{
    // TODO - Implementar m�todo.

    return {};
}

vector<ItemIndiceIndireto> obterSegundoConjuntoDeIndices()
{
    // TODO - Implementar m�todo.

    return {};
}

vector<vector<ItemIndiceDireto>> obterTerceiroQuartoConjuntoDeIndices()
{
    // TODO - Implementar m�todo.

    return {};
}

vector<ItemIndiceDireto> obterQuintoConjuntoDeIndices()
{
    // TODO - Implementar m�todo.

    return {};
}
