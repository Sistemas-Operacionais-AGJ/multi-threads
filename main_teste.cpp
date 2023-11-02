#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include "Cozinha.h" // Certifique-se de que "Cozinha.h" está incluído corretamente
                    // Teste do chat gpt                        
using namespace std;

int main() {
    // Criar uma instância da classe Cozinha
    Cozinha cozinha;

    // Testar os getters
    int salad = cozinha.getSalad();
    int dessert = cozinha.getDessert();
    int rice = cozinha.getRice();
    int bean = cozinha.getBean();
    int complement = cozinha.getComplement();
    int meat = cozinha.getMeat();

    cout << "Valores iniciais dos itens prontos para entrega:" << endl;
    cout << "Salada: " << salad << endl;
    cout << "Sobremesa: " << dessert << endl;
    cout << "Arroz: " << rice << endl;
    cout << "Feijão: " << bean << endl;
    cout << "Complemento: " << complement << endl;
    cout << "Carne: " << meat << endl;

    // Testar os setters
    cozinha.setSalad(1);
    cozinha.setDessert(2);
    cozinha.setRice(3);
    cozinha.setBean(4);
    cozinha.setComplement(5);
    cozinha.setMeat(6);

    cout << "Valores definidos para os itens prontos para entrega:" << endl;
    cout << "Salada: " << cozinha.getSalad() << endl;
    cout << "Sobremesa: " << cozinha.getDessert() << endl;
    cout << "Arroz: " << cozinha.getRice() << endl;
    cout << "Feijão: " << cozinha.getBean() << endl;
    cout << "Complemento: " << cozinha.getComplement() << endl;
    cout << "Carne: " << cozinha.getMeat() << endl;

    // Testar a função cookingItems
    int foodToCook = 0; // Você pode definir o tipo de comida a ser cozida (0 para Salada, 1 para Sobremesa, etc.)
    cout << "Cozinhando o item " << foodToCook << "..." << endl;
    cozinha.cookingItems(foodToCook);
    cout << "Item " << foodToCook << " pronto!" << endl;

    // Testar a função deliveryItems
    int foodToDeliver = 2; // Você pode definir o tipo de comida a ser entregue (0 para Salada, 1 para Sobremesa, etc.)
    int result = cozinha.deliveryItems(foodToDeliver);
    if (result == 0) {
        cout << "Não há item " << foodToDeliver << " pronto para entrega." << endl;
    } else {
        cout << "Entregando o item " << foodToDeliver << "..." << endl;
        cout << "Item " << foodToDeliver << " entregue com sucesso!" << endl;
    }

    return 0;
}
