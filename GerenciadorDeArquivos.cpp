#include <iostream>
#include <fstream>
#include "GerenciadorDeArquivos.h"
#include "StringHelpers.h"

using namespace std;

// Métodos públicos da classe GerenciadorDeArquivos:

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
    unsigned int posicaoAtual = 0;

    // Header do arquivo.
    getline(arquivoCsv, output);
    posicaoAtual += (unsigned int)output.size() + 2;

    while (getline(arquivoCsv, output))
    {
        if (output[0] == '*')
        {
            posicaoAtual += (unsigned int)output.size() + 2;
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

        posicaoAtual += (unsigned int)output.size() + 2;
    }

    arquivoCsv.close();

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

vector<ItemIndiceDireto> GerenciadorDeArquivos::obterConjuntoDeIndicesDiretos(std::string t_nomeDoArquivoDeIndices)
{
    ifstream arquivoDeIndices(t_nomeDoArquivoDeIndices);

    if (arquivoDeIndices.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << t_nomeDoArquivoDeIndices << "." << endl;
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

vector<ItemIndiceIndireto> GerenciadorDeArquivos::obterConjuntoDeIndicesIndiretos(std::string t_nomeDoArquivoDeIndices)
{
    ifstream arquivoDeIndices(t_nomeDoArquivoDeIndices);

    if (arquivoDeIndices.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << t_nomeDoArquivoDeIndices << "." << endl;
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

vector<ItemNetflix> GerenciadorDeArquivos::buscarItemNetflixPorTitulo(string t_titulo)
{
    vector<ItemIndiceDireto> conjuntoIndiceDireto = obterConjuntoDeIndicesDiretos(m_nomesDosArquivosDeIndices[0]);
    vector<ItemIndiceIndireto> conjuntoIndiceIndireto = obterConjuntoDeIndicesIndiretos(m_nomesDosArquivosDeIndices[1]);
    ifstream arquivoCsv(m_nomeDoArquivoCsv);

    if (conjuntoIndiceDireto.size() == 0 || conjuntoIndiceIndireto.size() == 0)
    {
        return {};
    }
    if (arquivoCsv.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomeDoArquivoCsv << "." << endl;
        return {};
    }

    vector<ItemNetflix> itensEncontrados;
    t_titulo = toLowerCase(t_titulo);

    for(unsigned int i = 0; i < (unsigned int)conjuntoIndiceIndireto.size(); i++)
    {
        string tituloDoItemNetflix = toLowerCase(conjuntoIndiceIndireto[i].tituloDoItemNetflix);

        if (tituloDoItemNetflix.find(t_titulo) != string::npos)
        {
            ItemNetflix itemNetflix = conjuntoIndiceIndireto[i].obterItemNetflix(conjuntoIndiceDireto, arquivoCsv);
            itensEncontrados.push_back(itemNetflix);
        }
    }

    return itensEncontrados;
}

bool GerenciadorDeArquivos::atualizarArquivoDeIndices(vector<ItemIndiceDireto> t_novoConjuntoDeIndices, string t_nomeDoArquivoDeIndices)
{
    ofstream arquivoDeIndices(t_nomeDoArquivoDeIndices, ios::trunc);

    for (unsigned int i = 0; i < (unsigned int)t_novoConjuntoDeIndices.size(); i++)
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

    for (unsigned int i = 0; i < (unsigned int)t_novoConjuntoDeIndices.size(); i++)
    {
        if (!t_novoConjuntoDeIndices[i].escreverItemIndiceNoArquivo(arquivoDeIndices))
        {
            return false;
        }
    }

    return true;
}

void GerenciadorDeArquivos::removerItemNetflix(string t_idDoItemNetflix)
{
    unsigned int posicaoDoItemNoArquivo = obterPosicaoDoItemNoArquivoPeloId(t_idDoItemNetflix);

    if (posicaoDoItemNoArquivo == 0)
    {
        cout << endl << "Nenhum filme/serie possui o ID indicado." << endl;
        return;
    }

    bool resultadoDaRemocaoDoArquivoCsv = removerItemNetflixDoArquivoCsv(posicaoDoItemNoArquivo);

    if (!resultadoDaRemocaoDoArquivoCsv)
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomeDoArquivoCsv << "." << endl;
        cout << "Logo, nao foi possivel realizar a remocao do filme/serie." << endl;
        return;
    }

    bool resultadoDaRemocaoDosArquivosDeIndice = removerItemNetflixDosArquivosDeIndices(t_idDoItemNetflix);

    if (!resultadoDaRemocaoDosArquivosDeIndice)
    {
        cout << "ERRO -> Nao foi possivel remover o ItemNetflix dos arquivos de indices. ";
        cout << "Os arquivos de indice estao inconsistentes com o arquivo CSV. ";
        cout << "Sera necessario gera-los novamente, reinicializando a aplicacao." << endl;
        return;
    }

    cout << endl << "O filme/serie foi removido com sucesso." << endl;
}

string GerenciadorDeArquivos::obterIdDoProximoItemNetflix()
{
    vector<ItemIndiceDireto> conjuntoIndicesDireto = obterConjuntoDeIndicesDiretos(m_nomesDosArquivosDeIndices[0]);

    if (conjuntoIndicesDireto.size() == 0)
    {
        return "-";
    }

    ItemIndiceDireto ultimoItem = conjuntoIndicesDireto[conjuntoIndicesDireto.size() - 1];
    unsigned int idDoUltimoItem = std::stoi(ultimoItem.idDoItemNetflix.substr(1));
    idDoUltimoItem++;

    return "s" + to_string(idDoUltimoItem);
}

void GerenciadorDeArquivos::inserirItemNetflix(ItemNetflix t_itemNetflix)
{
    bool resultadoDaInsercaoEmEspacoDisponivel = tentarInsercaoDeItemNetflixEmEspacoDisponivel(t_itemNetflix);

    if (!resultadoDaInsercaoEmEspacoDisponivel)
    {
         ofstream arquivoCsv(m_nomeDoArquivoCsv, ios::app);

        if (arquivoCsv.fail())
        {
            cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomeDoArquivoCsv << "." << endl;
            return;
        }

        string itemNetflixString = t_itemNetflix.toCsvLine();
        arquivoCsv << itemNetflixString << endl;

        unsigned int posicaoDoItemNoArquivoCsv = ((unsigned int)arquivoCsv.tellp()) - itemNetflixString.size() - 2;
        bool resultadoDaAtualizacaoDosIndices = adicionarItemNetflixAosArquivosDeIndices(t_itemNetflix, posicaoDoItemNoArquivoCsv);

        if(!resultadoDaAtualizacaoDosIndices)
        {
            cout << "ERRO -> Os arquivos de indice estao inconsistentes com o arquivo CSV. ";
            cout << "Sera necessario gera-los novamente, reinicializando a aplicacao." << endl;
            arquivoCsv.close();
            return;
        }

        arquivoCsv.close();
    }

    cout << endl << "O novo filme/serie foi inserido com sucesso." << endl;
}

// Métodos privados da classe GerenciadorDeArquivos:

unsigned int GerenciadorDeArquivos::obterPosicaoDoItemNoArquivoPeloId(string t_idDoItemNetflix)
{
    ItemIndiceDireto indiceComIdProcurado(t_idDoItemNetflix, -1);
    vector<ItemIndiceDireto> conjuntoIndiceDireto = obterConjuntoDeIndicesDiretos(m_nomesDosArquivosDeIndices[0]);

    unsigned int inicio = 0;
    unsigned int fim = ((unsigned int)conjuntoIndiceDireto.size()) - 1;
    unsigned int meio;

    while (inicio <= fim)
    {
        meio = (inicio + fim) / 2;

        if (indiceComIdProcurado.idDoItemNetflix == conjuntoIndiceDireto[meio].idDoItemNetflix)
        {
            return conjuntoIndiceDireto[meio].posicaoNoArquivo;
        }
        else if (indiceComIdProcurado < conjuntoIndiceDireto[meio])
        {
            fim = meio - 1;
        }
        else
        {
            inicio = meio + 1;
        }
    }

    return 0;
}

bool GerenciadorDeArquivos::removerItemNetflixDoArquivoCsv(int t_posicaoDoItemNoArquivo)
{
    ofstream arquivoCsv(m_nomeDoArquivoCsv, ios::in | ios::out);

    if (arquivoCsv.fail())
    {
        return false;
    }

    arquivoCsv.seekp(t_posicaoDoItemNoArquivo);
    arquivoCsv.write("*", 1);

    arquivoCsv.close();

    return true;
}

bool GerenciadorDeArquivos::removerItemNetflixDosArquivosDeIndices(string t_idDoItemNetflix)
{
    bool resultadoFinal = false;

    vector<vector<ItemIndiceDireto>> conjuntosDeIndicesDiretos;
    conjuntosDeIndicesDiretos.push_back(obterConjuntoDeIndicesDiretos(m_nomesDosArquivosDeIndices[0]));
    conjuntosDeIndicesDiretos.push_back({});
    conjuntosDeIndicesDiretos.push_back(obterConjuntoDeIndicesDiretos(m_nomesDosArquivosDeIndices[2]));
    conjuntosDeIndicesDiretos.push_back(obterConjuntoDeIndicesDiretos(m_nomesDosArquivosDeIndices[3]));
    conjuntosDeIndicesDiretos.push_back(obterConjuntoDeIndicesDiretos(m_nomesDosArquivosDeIndices[4]));

    for (unsigned int i = 0; i < (unsigned int)conjuntosDeIndicesDiretos.size(); i++)
    {
        vector<ItemIndiceDireto> conjuntoAtual = conjuntosDeIndicesDiretos[i];

        for (unsigned int j = 0; j < (unsigned int)conjuntoAtual.size(); j++)
        {
            if (conjuntoAtual[j].idDoItemNetflix == t_idDoItemNetflix)
            {
                conjuntoAtual.erase(conjuntoAtual.begin() + j);
                resultadoFinal = atualizarArquivoDeIndices(conjuntoAtual, m_nomesDosArquivosDeIndices[i]);
                break;
            }
        }
    }

    vector<ItemIndiceIndireto> conjuntoDeIndicesIndiretos = obterConjuntoDeIndicesIndiretos(m_nomesDosArquivosDeIndices[1]);

    for (unsigned int i = 0; i < (unsigned int)conjuntoDeIndicesIndiretos.size(); i++)
    {
        if (conjuntoDeIndicesIndiretos[i].idDoItemNetflix == t_idDoItemNetflix)
        {
            conjuntoDeIndicesIndiretos.erase(conjuntoDeIndicesIndiretos.begin() + i);
            resultadoFinal = atualizarArquivoDeIndices(conjuntoDeIndicesIndiretos, m_nomesDosArquivosDeIndices[1]);
            break;
        }
    }

    return resultadoFinal;
}

bool GerenciadorDeArquivos::adicionarItemNetflixAosArquivosDeIndices(ItemNetflix t_itemNetflix, unsigned int t_posicaoDoItemNoArquivoCsv)
{
    ItemIndiceDireto itemIndiceDireto(t_itemNetflix.id, t_posicaoDoItemNoArquivoCsv);
    ItemIndiceIndireto itemIndiceIndireto(t_itemNetflix.id, t_itemNetflix.titulo);

    ofstream arqIndices1(m_nomesDosArquivosDeIndices[0], ios::app);
    ofstream arqIndices2(m_nomesDosArquivosDeIndices[1], ios::app);
    ofstream arqIndices3(m_nomesDosArquivosDeIndices[2], ios::app);
    ofstream arqIndices4(m_nomesDosArquivosDeIndices[3], ios::app);
    ofstream arqIndices5(m_nomesDosArquivosDeIndices[4], ios::app);

    if (arqIndices1.fail() || arqIndices2.fail() || arqIndices3.fail() || arqIndices4.fail() || arqIndices5.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular um ou mais arquivos de índices." << endl;
        return false;
    }

    itemIndiceDireto.escreverItemIndiceNoArquivo(arqIndices1);
    itemIndiceIndireto.escreverItemIndiceNoArquivo(arqIndices2);

    if (t_itemNetflix.tipo == "Movie")
    {
        itemIndiceDireto.escreverItemIndiceNoArquivo(arqIndices3);
    }
    else if (t_itemNetflix.tipo == "TV Show")
    {
        itemIndiceDireto.escreverItemIndiceNoArquivo(arqIndices4);
    }

    if (t_itemNetflix.pais.find("Brazil") != string::npos)
    {
        itemIndiceDireto.escreverItemIndiceNoArquivo(arqIndices5);
    }

    arqIndices1.close();
    arqIndices2.close();
    arqIndices3.close();
    arqIndices4.close();
    arqIndices5.close();

    return true;
}

bool GerenciadorDeArquivos::tentarInsercaoDeItemNetflixEmEspacoDisponivel(ItemNetflix t_itemNetflix)
{
    fstream arquivoCsv(m_nomeDoArquivoCsv);

    if (arquivoCsv.fail())
    {
        cout << "ERRO -> Nao foi possivel manipular o arquivo " << m_nomeDoArquivoCsv << "." << endl;
        return false;
    }

    string output;
    unsigned int posicaoVerificacao = 0;

    getline(arquivoCsv, output);
    posicaoVerificacao += (unsigned int)output.size() + 2;

    string itemNetflixString = t_itemNetflix.toCsvLine();
    unsigned int tamanhoItemNetflixString = (unsigned int)itemNetflixString.size();
    bool espacoDisponivel = false;

    while(getline(arquivoCsv, output))
    {
        unsigned int tamanhoOutput = (unsigned int)output.size();
        if ((output[0] == '*') && (tamanhoItemNetflixString <= tamanhoOutput))
        {
            espacoDisponivel = true;
            break;
        }
        posicaoVerificacao += (unsigned int)output.size() + 2;
    }

    if (!espacoDisponivel)
    {
        return false;
    }

    arquivoCsv.seekp(posicaoVerificacao, ios::beg);
    arquivoCsv << itemNetflixString;

    unsigned int espacoEmBranco = (unsigned int)output.size() - tamanhoItemNetflixString;
    for(unsigned int i = 0; i < espacoEmBranco; i++)
    {
        arquivoCsv.write(" ", 1);
    }
    cout << endl;

    unsigned int posicaoDoItemNoArquivoCsv = ((unsigned int)arquivoCsv.tellp()) - itemNetflixString.size() - espacoEmBranco;
    bool resultadoDaAtualizacaoDosIndices = adicionarItemNetflixAosArquivosDeIndices(t_itemNetflix, posicaoDoItemNoArquivoCsv);

    if(!resultadoDaAtualizacaoDosIndices)
    {
        cout << "ERRO -> Os arquivos de indice estao inconsistentes com o arquivo CSV. ";
        cout << "Sera necessario gera-los novamente, reinicializando a aplicacao." << endl;
        arquivoCsv.close();
        return false;
    }

    arquivoCsv.close();

    return true;
}
