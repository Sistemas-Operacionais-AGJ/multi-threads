#include <iostream>
#include <chrono>
using namespace std;
using namespace chrono;

class Cozinha{
    public:
        ~Cozinha();

        //get 6 alimentos

        int getSalad();
        int getDessert();
        int getRice();
        int getBean();
        // alimento variado
        int getComplement(); 

        int getMeat();

        //set 6 alimentos

        void setSalad(int valor);
        void setDessert(int valor);
        void setRice(int valor);
        void setBean(int valor);
        void setComplement(int valor);
        void setMeat(int valor);

        // preparo de itens
        void cookingItems(int food);
        
        // entrega de itens
        int deliveryItems(int food);

    private:
        // 6 alimentos: Salada, Sobremesa, Arroz, Feijão, Complemento, Carne
        const int productionTime[6] = {10, 5, 20, 20, 35, 50};
        const int productionTimeVariance[6] = {2, 1, 3, 3, 10, 5};
        int readyForDelivery[6];
};