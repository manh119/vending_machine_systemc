#include "systemc.h"
#include "definition.h"
SC_MODULE (control) {

	enum State {
      INIT,
      TAKE_PRODUCT,
      RECEIVE_COIN,
      RELEASE_PRODUCT_AND_RETURN,
      RELEASE_PRODUCT_AND_NO_RETURN
    };


	int totalCoin;

	sc_in<bool> clk;
    State s;
	sc_in<DrinkCode> drinkCode;
	sc_in<bool> resetSignal;
	sc_in<bool> availableDrink;
	sc_in<CoinValue> coinValue;
	sc_in<bool> takeDrink;
	sc_out<bool> requireReleaseProduct; 
	sc_out<bool> returnCoin;

	void prc_control();

	SC_CTOR(control) {
		SC_THREAD(prc_control);
		sensitive << takeDrink << drinkCode << coinValue << availableDrink << resetSignal;
		sensitive_pos(clk);
	}
};