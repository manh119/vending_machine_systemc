#include "systemc.h"
#include "control.h"
#include "supply.h"
#include "tester.h"
#include "definition.h"

int sc_main(int ac, char *av[])
{
    sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
    sc_signal<DrinkCode> drinkCode;
    sc_signal<bool> resetSignal;
    sc_signal<bool> availableDrink;
    sc_signal<bool> insertCoin;
    sc_signal<CoinValue> coinValue;
    sc_signal<bool> takeDrink;
    sc_signal<bool> requireReleaseProduct; 
    sc_signal<bool> returnCoin;
    sc_signal<bool> releaseProduct;

    sc_trace_file *tf;

    sc_clock clk ("ID", 10, SC_NS, 0.5, 10, SC_NS, true);


    tester test("generateInputs");
    test.takeDrink(takeDrink);
    test.drinkCode(drinkCode);
    test.coinValue(coinValue);
    test.resetSignal(resetSignal);

    control ctrol("control module");
    ctrol.takeDrink(takeDrink);
    ctrol.drinkCode(drinkCode);
    ctrol.coinValue(coinValue);
    ctrol.availableDrink(availableDrink);
    ctrol.requireReleaseProduct(requireReleaseProduct);
    ctrol.returnCoin(returnCoin);
    ctrol.resetSignal(resetSignal);
    ctrol.clk(clk);


    supply sup("supply module");
    sup.drinkCode(drinkCode);
    sup.requireReleaseProduct(requireReleaseProduct);
    sup.availableDrink(availableDrink);
    sup.releaseProduct(releaseProduct);


    // Waves:
    tf = sc_create_vcd_trace_file("waves");
    tf->set_time_unit(1, SC_NS);

    sc_trace(tf, clk, "clk");
    sc_trace(tf, takeDrink, "takeDrink");
    sc_trace(tf, availableDrink, "availableDrink");
    sc_trace(tf, drinkCode, "drinkCode");
    sc_trace(tf, coinValue, "coinValue");
    sc_trace(tf, ctrol.requireReleaseProduct, "requireReleaseProduct");
    sc_trace(tf, sup.releaseProduct, "releaseProduct");
    sc_trace(tf, ctrol.returnCoin, "returnCoin");
    sc_trace(tf, ctrol.resetSignal, "resetSignal");


    sc_start();

    sc_close_vcd_trace_file(tf);

    return 0;
}
