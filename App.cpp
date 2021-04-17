#include <iostream>
#include <fstream>
#include "string.h"
#include "App.h"
#include "ItemNetflix.h"
#include "ItemIndiceDireto.h"
#include "ItemIndiceIndireto.h"
#include "GerenciadorDeArquivos.h"
#include "StringHelpers.h"

using namespace std;

// Métodos públicos da classe App:

App::App() { }

bool App::inicializarAplicacao()
{
    GerenciadorDeArquivos gerenciador;
    return gerenciador.gerarArquivosDeIndices();
}

void App::pesquisarItensPorTitulo()
{
    string titulo = "";
    cout << endl << "Digite o titulo do filme/serie que deseja encontrar: ";
    cin >> titulo;

    GerenciadorDeArquivos gerenciador;
    vector<ItemNetflix> itensEncontrados = gerenciador.buscarItemNetflixPorTitulo(titulo);

    cout << endl << "- Resultado da pesquisa:" << endl << endl;

    if (itensEncontrados.size() == 0)
    {
        cout << "Nenhum filme/serie encontrado com esse titulo." << endl;
        return;
    }

    for (unsigned int i = 0; i < (unsigned int)itensEncontrados.size(); i++)
    {
        itensEncontrados[i].visualizarItem();
        cout << endl;
    }
}

void App::exibirFilmesBrasileirosDe2019()
{
    GerenciadorDeArquivos gerenciador;
    string nomeDoArquivoDeIndices = gerenciador.getNomeDosArquivosDeIndices()[4];
    vector<ItemIndiceDireto> conjuntoIndiceDireto = gerenciador.obterConjuntoDeIndicesDiretos(nomeDoArquivoDeIndices);
    ifstream arquivoCsv(gerenciador.getNomeDoArquivoCsv());

    cout << endl << "- Lista de filmes brasileiros do ano de 2019:" << endl << endl;

    for (unsigned int i = 0; i < (unsigned int)conjuntoIndiceDireto.size(); i++)
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

    GerenciadorDeArquivos gerenciador;
    gerenciador.removerItemNetflix(idDoItemNetflix);
}

void App::inserirNovoItemNetflix()
{
    GerenciadorDeArquivos gerenciador;
    ItemNetflix itemNetflix;
    bool resultado;

    cout << endl << "> FORMULARIO DE INSERCAO" << endl;

    itemNetflix.id = gerenciador.obterIdDoProximoItemNetflix();

    if (itemNetflix.id == "-")
    {
        cout << "ERRO -> Nao foi possivel gerar o ID. Tente novamente." << endl;
        return;
    }

    cout << "- ID (gerado automaticamente): " << itemNetflix.id << endl;

    resultado = exibirCampoDeFormulario("- Tipo (informe F para filme e S para serie)", itemNetflix.tipo);
    if (!resultado) return;

    if (itemNetflix.tipo == "F" || itemNetflix.tipo == "f")
    {
        itemNetflix.tipo = "Movie";
    }
    else if (itemNetflix.tipo == "S" || itemNetflix.tipo == "s")
    {
        itemNetflix.tipo = "TV Show";
    }
    else
    {
        cout << "ERRO -> Nao foi digitada uma opcao valida. Tente novamente." << endl;
        return;
    }

    resultado = exibirCampoDeFormulario("- Titulo", itemNetflix.titulo);
    if (!resultado) return;

    resultado = exibirCampoDeFormulario("- Diretor", itemNetflix.diretor);
    if (!resultado) return;

    string elenco;
    resultado = exibirCampoDeFormulario("- Elenco (separe cada integrante com uma virgula)", elenco);
    if (!resultado) return;

    char *e, *elencoCopia = _strdup(elenco.c_str());
    while((e = strsep(&elencoCopia, ",")) != NULL)
    {
       itemNetflix.elenco.push_back(e);
    }

    resultado = exibirCampoDeFormulario("- Pais (separe cada pais com uma virgula)", itemNetflix.pais);
    if (!resultado) return;

    resultado = exibirCampoDeFormulario("- Data de adicao (DD/MM/AAAA)", itemNetflix.dataDeAdicao);
    if (!resultado) return;

    resultado = exibirCampoDeFormulario("- Ano de lancamento (AAAA)", itemNetflix.anoDeLancamento);
    if (!resultado) return;

    resultado = exibirCampoDeFormulario("- Classificacao", itemNetflix.classificacao);
    if (!resultado) return;

    resultado = exibirCampoDeFormulario("- Duracao", itemNetflix.duracao);
    if (!resultado) return;

    string generos;
    resultado = exibirCampoDeFormulario("- Generos", generos);
    if (!resultado) return;

    char *g, *generosCopia = _strdup(generos.c_str());
    while((g = strsep(&generosCopia, ",")) != NULL)
    {
       itemNetflix.generos.push_back(g);
    }

    resultado = exibirCampoDeFormulario("- Descricao", itemNetflix.descricao);
    if (!resultado) return;

    gerenciador.inserirItemNetflix(itemNetflix);
}

// Métodos privados da classe App:

bool App::exibirCampoDeFormulario(string labelDoCampo, string& outputDoCampo)
{
    string resposta;

    cout << labelDoCampo << ": ";
    cin.clear();
    getline(cin >> ws, resposta);

    if (!validarRespostaDoCampoDeFormulario(resposta))
    {
        return false;
    }

    outputDoCampo = resposta;

    return true;
}

bool App::validarRespostaDoCampoDeFormulario(string resposta)
{
    if (resposta.find(";") != string::npos)
    {
        cout << "ERRO -> O caractere ';' nao pode ser inserido (nao permitido). Tente novamente." << endl;
        return false;
    }
    if (resposta.find("\n") != string::npos)
    {
        cout << "ERRO -> O caractere '\n' nao pode ser inserido (nao permitido). Tente novamente." << endl;
        return false;
    }
    return true;
}


