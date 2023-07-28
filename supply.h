#include "systemc.h"
#include "definition.h"

int number_MILK  = 10;
int number_COFFE = 5;

SC_MODULE (supply) {
    sc_in<DrinkCode> drinkCode;
    sc_in<bool> requireReleaseProduct;
    sc_out<bool> availableDrink;
    sc_out<bool> releaseProduct;

	void prc_supply();

	SC_CTOR(supply) {
		SC_THREAD(prc_supply);
		sensitive << drinkCode;
    	sensitive << requireReleaseProduct;
	}
};
