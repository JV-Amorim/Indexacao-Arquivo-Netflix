# Indexação de Arquivo de Dados - Netflix

Projeto para estudo de indexação de arquivos em C++, utilizando como base um arquivo de dados das séries e filmes da Netflix. Exercício da disciplina de Organização e Sistemas de Arquivos (Ciência da Computação - IFNMG).

## Parte 1

Descrição detalhada da parte 1: [visualizar](./Trabalho-Parte-1.pdf).

## Parte 2

**A) Implementação da remoção de registros:**

A remoção deverá ser realizada através da marcação do registro com um asterisco (*) no lugar do primeiro byte do registro no arquivo de dados Netflix. Os arquivos de índices deverão manter-se atualizados.

**B) Implementação da inserção de novos registros:**

Os novos registros deverão ser inseridos no final do arquivo de dados Netflix. Os arquivos de índices deverão manter-se atualizados.

**C) Implementação de um método de pesquisa binária:**

O método deverá permitir a realização de uma pesquisa binária nos índices ao ser informado um ID de registro. Para isso, os índices deverão sempre estarem ordenados em ordem crescente.

**D) Aprimoramento da inserção de novos registros:**

Ao inserir um novo registro, deverá ser consultado se existe algum espaço disponível no meio do arquivo, onde outros registros foram marcados como removidos, que comporte o novo registro. Caso esse espaço disponível exista, o novo registro deverá ser inserido nele, ao invés de ser inserido no final do arquivo. Os arquivos de índices deverão manter-se atualizados.

## Licença

Esse projeto é licenciado pela MIT License. Veja a [página da licença](https://opensource.org/licenses/MIT) para mais detalhes.