#include "classimobi.h"
#include <iostream>
using namespace std;


Corretor::Corretor(string novoTelefone, bool eh_avaliador, double novaLat, double novaLng, string novoNome){
        nome = novoNome;
        telefone = novoTelefone;
        avaliador = eh_avaliador;
        lat = novaLat;
        lng = novaLng;
        id = nextId_cr++;
    }

Cliente::Cliente(string novoTelefone, string novoNome){
        nome = novoNome;
        telefone = novoTelefone;
        id = nextId_cl++;
        
    }

Imovel::Imovel(int novoImovel, int NOVO_nextProprietarioId, double novaLat, double novaLng, double novoPreco, string novoEndereco){        
        tipo_imovel = static_cast<tipo>(novoImovel); //faz a conversão de int para enum
        nextProprietarioId = NOVO_nextProprietarioId;
        lat = novaLat;
        lng = novaLng;
        preco = novoPreco;
        endereco = novoEndereco;
        id = nextId_im++;


    }

int Corretor::nextId_cr = 1;
int Cliente::nextId_cl = 1;
int Imovel::nextId_im = 1;

