#include "systemc.h"
#include "definition.h"

SC_MODULE (tester) {
    sc_out<bool> takeDrink;
    sc_out<DrinkCode> drinkCode;
    sc_out<CoinValue> coinValue;
    sc_out<bool> resetSignal;

	void prc_tester();

	SC_CTOR( tester) {
		SC_THREAD(prc_tester);
	}
};
