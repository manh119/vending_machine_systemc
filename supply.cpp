#include "supply.h"

void supply::prc_supply() {
	// Initialize the outputs
	availableDrink.write(false);
	releaseProduct.write(false);
    while (true) {

        // Wait for any change
        wait();

        // Check if the releaseProductCode signal has changed
        if (requireReleaseProduct) {
            releaseProduct.write(true);
        }
        else 
        	releaseProduct.write(false);

        // check available of an product by drinkCode
        switch(drinkCode) {
       	case MILK:
       		if (number_MILK > 0)
       			availableDrink.write(true);
       		else 
       			availableDrink.write(false); 
   			break;

        case COFFE:
       		if (number_COFFE > 0)
       			availableDrink.write(true);
       		else 
       			availableDrink.write(false);
       		break;
        }


    }
}