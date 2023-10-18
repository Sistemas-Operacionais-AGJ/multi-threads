#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

class Cozinha{
    public:
        Cozinha();
        ~Cozinha();

        //get 6 alimentos
        int getSalad();
        int getDessert();
        int getRice();
        int getBean();
        int getComplement();
        int getMeat();

        //set 6 alimentos

        int setSalad();
        int setDessert();
        int setRice();
        int setBean();
        int setComplement();
        int setMeat();


    private:
        // 6 alimentos: Salada, Sobremesa, Arroz, Feijão, Complemento, Carne
        const int productionTime[6] = {10, 5, 20, 20, 35, 50};
        const int productionTimeVariance[6] = {2, 1, 3, 3, 10, 5};
        const int readyForDelivery[6];

        // preparo de itens
        int cookingItems(int food);
        
        // entrega de itens
        int deliveryItems(int food);


};