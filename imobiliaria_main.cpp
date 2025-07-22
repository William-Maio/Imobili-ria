#include "classimobi.h"
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>
using namespace std;

#include <cmath>
constexpr double EARTH_R = 6371.0; // Raio da Terra em km

double haversine(double lat1, double lon1, double lat2, double lon2) {
    auto deg2rad = [](double d){ return d * M_PI / 180.0; };
    double dlat = deg2rad(lat2 - lat1);
    double dlon = deg2rad(lon2 - lon1);
    double a = std::pow(std::sin(dlat/2), 2) +
               std::cos(deg2rad(lat1)) * std::cos(deg2rad(lat2)) *
               std::pow(std::sin(dlon/2), 2);
    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));
    return EARTH_R * c;
}


bool vetorTodosSaoMenos1(const std::vector<int>& vector){
    for(int i = 0; i < vector.size(); i++){
            if(vector[i] != -1){
                return false;
            }

    }
    return true;
}


int main(){

//Criar os Corretores, Clientes e Imóveis
int quant_corretor;
int quant_cliente;
int quant_imovel;

string novoTelefone;
bool eh_avaliador;
double novaLat;
double novaLng;
string novoNome;
string novoImovel_string; //varivel para converter a string em int (novoImovel) para o num
int novoImovel;
int NOVO_nextProprietarioId;
double novoPreco;
string novoEndereco;

vector<Corretor> corretores;
vector<Cliente> clientes;
vector<Imovel> imoveis;


cin>>quant_corretor;
cin.ignore();

for (int i = 0; i < quant_corretor; i++){
    cin>>novoTelefone>>eh_avaliador>>novaLat>>novaLng;   //[telefone] [avaliador] [latitude] [longitude] [nome]
    cin.ignore();
    getline(cin, novoNome);
    corretores.emplace_back(novoTelefone, eh_avaliador, novaLat, novaLng, novoNome);    
    
}

cin>>quant_cliente;
cin.ignore();

for (int i = 0; i < quant_cliente; i++){
    cin>>novoTelefone;   //[telefone] [nome]
    cin.ignore();
    getline(cin, novoNome);
    clientes.emplace_back(novoTelefone, novoNome);    
    
}
//[tipo] [proprietarioId] [latitude] [longitude] [preco] [endereco]

cin>>quant_imovel;
cin.ignore();

for (int i = 0; i < quant_imovel; i++){
    cin>>novoImovel_string>>NOVO_nextProprietarioId>>novaLat>>novaLng>>novoPreco;   //[tipo] [proprietarioId] [latitude] [longitude] [preco] [endereco]
    cin.ignore();
    getline(cin, novoEndereco);
    
    if (novoImovel_string == "Casa")
    {
        novoImovel = 0;
    }else if (novoImovel_string == "Apartamento")
    {
        novoImovel = 1;
    }else if (novoImovel_string == "Terreno")
    {
        novoImovel = 2;
    }
    
        

    imoveis.emplace_back(novoImovel, NOVO_nextProprietarioId, novaLat, novaLng, novoPreco, novoEndereco);
    
}


int hora = 9;
int minuto = 0;
vector <int> quais_os_corretores; //quais são os corretores avaliadores


for(int i = 0; i < corretores.size(); i++){
    if(corretores[i].avaliador == 1){
        quais_os_corretores.push_back(i);
    }
    
}

//--------------------------IMOVEIS ASSOCIADOS AOS CORRETORES AVALIADORES-------------------
    int corretorIndex = 0;
    int avaliadorIndex = 0;
    int j = 0;
    for (int i = 0; i < imoveis.size(); i++){
        j = quais_os_corretores[avaliadorIndex];
        if(avaliadorIndex < corretores.size()){
            corretores[j].imoveis_associados.push_back(imoveis[i].id - 1);

            avaliadorIndex = (avaliadorIndex + 1) % quais_os_corretores.size();
            
        }
    }
    
    //--------------------------------- ORGANIZAR AGENDA AVALIADORES-----------------------------
    
    corretorIndex = 0;
    avaliadorIndex = 0;
    double distancia = 0;          
    double menor_distancia = 0;
    int imovel_proximo = 0; //selecionar qual o proximo imovel a ser mostrado
    int contador_impressoes = 0; //conta quantas impresssões foram feitas    
    
    for (int i = 0; i < corretores.size(); i++){
        //Comecar com o corretor em sua posição inicial (horário 09:00)
        hora = 9;
        minuto = 0;
        contador_impressoes = 0;
        if(corretores[i].avaliador == 1){            
            while (!vetorTodosSaoMenos1(corretores[i].imoveis_associados)){  //Repitir esse processo até todos os imóveis terem sido visitados    
                
                for(int j = 0; j < corretores[i].imoveis_associados.size(); j++){ //percorrer todos os imoveis para Calcular a distância de todos os imóveis não visitados a partir da posição atual do corretor.
                    
                    if (corretores[i].imoveis_associados[j] != -1){
                        distancia = haversine(corretores[i].lat, corretores[i].lng, imoveis[corretores[i].imoveis_associados[j]].lat, imoveis[corretores[i].imoveis_associados[j]].lng);
                                              
                        if(distancia < menor_distancia || menor_distancia == 0){//Selecione o imóvel mais próximo.
                            menor_distancia = distancia;
                                                        
                            imovel_proximo = j;
                            
                        }
                    
                    }
                }

                if(contador_impressoes == 0){
                    //Calcular o novo horário baseado na distância
                    minuto = menor_distancia * 2;
                    contador_impressoes++;

                    std::cout << "\nCorretor " << corretores[i].id << endl;
                    std::cout << setfill('0') << setw(2) << hora << ":" << setw(2) << minuto << " Imovel " << imoveis[corretores[i].imoveis_associados[imovel_proximo]].id << endl;

                }else{
                    //Calcular o novo horário baseado na distância após a primeira visita feita
                    hora++;
                    minuto = minuto + menor_distancia * 2;
                    contador_impressoes++;
                    std::cout << setfill('0') << setw(2) << hora << ":" << setw(2) << minuto << " Imovel " << imoveis[corretores[i].imoveis_associados[imovel_proximo]].id << endl;

                }                

                //Atualizar a posição do corretor para o imóvel selecionado.
                corretores[i].lat = imoveis[corretores[i].imoveis_associados[imovel_proximo]].lat;
                corretores[i].lng = imoveis[corretores[i].imoveis_associados[imovel_proximo]].lng;

                //atualizar menor distancia para 0
                menor_distancia = 0;

                //imovel foi selecionado e vamos remover da lista de imoveis
                corretores[i].imoveis_associados[imovel_proximo] = -1;
                
            }
            
        


        }
    }
    //-------------------------------------------------------------------------------------------

}

