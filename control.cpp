#include "control.h"
#include "definition.h"

void control :: prc_control()
{
    State next_s;

    s = INIT; // Initial state
    next_s = s; // Khởi tạo giá trị ban đầu cho next_s
    returnCoin.write(NO_COIN); // default value, may be overwrite later

    while (true) {
        wait(); // wait for any signal on sensitivity list
 //       wait(2, SC_NS); // delay to produce outputs.

        switch (s) {
        case INIT:
            requireReleaseProduct.write(false);
            returnCoin.write(false);
            totalCoin = 0;
            if (takeDrink)
                next_s = TAKE_PRODUCT;
            break;

        case TAKE_PRODUCT:
            if (!availableDrink || resetSignal)
                next_s = INIT;
            else 
                next_s = RECEIVE_COIN;
            break;

        case RECEIVE_COIN:
            if (resetSignal)
                next_s = INIT;

            // read coin and update totalCoin
            switch (coinValue) {
            case TEN:
                totalCoin += 10;
                break;
            case TWENTY:
                totalCoin += 20;
                break;
            }

            // check condition of price and total cost of these products 
            switch (drinkCode) {
            case COFFE:
                if (totalCoin == coffePrice) {
                    next_s = RELEASE_PRODUCT_AND_NO_RETURN; // Transition to RELEASE_PRODUCT_AND_RETURN state
                } else if (totalCoin > coffePrice) {
                    next_s = RELEASE_PRODUCT_AND_RETURN; // Transition to RELEASE_PRODUCT_AND_NO_RETURN state
                } else {
                    next_s = RECEIVE_COIN;
                }
                break;
            case MILK:
                if (totalCoin == milkPrice) {
                    next_s = RELEASE_PRODUCT_AND_NO_RETURN; // Transition to RELEASE_PRODUCT_AND_RETURN state
                } else if (totalCoin > milkPrice) {
                    next_s = RELEASE_PRODUCT_AND_RETURN; // Transition to RELEASE_PRODUCT_AND_NO_RETURN state
                } else {
                    next_s = RECEIVE_COIN;
                }
                break;
            }
            break;

        case RELEASE_PRODUCT_AND_RETURN:
            requireReleaseProduct.write(true);
            returnCoin.write(true);
            next_s = INIT;
            break;

        case RELEASE_PRODUCT_AND_NO_RETURN:
            requireReleaseProduct.write(true);
            returnCoin.write(false);
            next_s = INIT;
            break;
        }

        s = next_s;
    }
}

