#ifndef CLASSIMOBI_H
#define CLASSIMOBI_H
#include <string>
#include <vector>


class Corretor
{
private:
    static int nextId_cr;
public:
    int id;
    std::string nome; //contém espaço
    std::string telefone;
    bool avaliador;
    double lat; //latitude
    double lng; //longitude
    std::vector <int> imoveis_associados;
    
    //[telefone] [avaliador] [latitude] [longitude] [nome]
    Corretor(std::string novoTelefone, bool eh_avaliador, double novaLat, double novaLng, std::string novoNome);

        
};

class Cliente
{
private:
    static int nextId_cl;
public:
    int id;
    std::string nome; //contém espaço
    std::string telefone;

    //[telefone] [nome]
    Cliente(std::string novoTelefone, std::string novoNome);

       
};

class Imovel
{
private:
    static int nextId_im;
public:
    int id;
    int nextProprietarioId; //id do proprietario
    double lat; //latitude
    double lng; //longitude
    std::string endereco; //contém espaço
    double preco;
    
    enum tipo{
        Casa,
        Apartamento,
        Terreno

    };

    tipo tipo_imovel;    
       
    Imovel(int novoImovel, int NOVO_nextProprietarioId, double novaLat, double novaLng, double novoPreco, std::string novoEndereco);
    
};

#endif