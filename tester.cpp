#include "tester.h"

void tester::prc_tester() {
    // Case 1: Chosen drink is available and enough money was inserted
    takeDrink.write(false);
    drinkCode.write(NO_DRINK);
    coinValue.write(NO_COIN);
    resetSignal.write(false);
    wait(10, SC_NS);

    takeDrink.write(true);
    drinkCode.write(COFFE);
    wait(10, SC_NS);

    coinValue.write(TEN);
    wait(5, SC_NS);
    coinValue.write(TEN);
    wait(5, SC_NS);
    coinValue.write(TEN);
    wait(25, SC_NS);


    // Case 2: the chosen drink is available, but insert over needed coins and return coins
    resetSignal.write(true);
    wait(5, SC_NS);
    resetSignal.write(false);
    takeDrink.write(false);
    drinkCode.write(NO_DRINK);
    coinValue.write(NO_COIN);
    wait(10, SC_NS);

    takeDrink.write(true);
    drinkCode.write(MILK);
    wait(10, SC_NS);

    coinValue.write(TEN);
    wait(5, SC_NS);
    coinValue.write(TEN);
    wait(5, SC_NS);
    coinValue.write(TWENTY);
    wait(25, SC_NS);


    // Case 3: money is not enough, and the coin insertion has stopped.
    // After some cycles of the clock, the coins are returned

    sc_stop();
}
