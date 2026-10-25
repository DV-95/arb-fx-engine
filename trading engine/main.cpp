#include <iostream>
#include "order_book.hpp"

int main() {
    fx::OrderBook book;

    // 1. Empty book: there should be no best bid / best ask.
    std::cout << "empty book -> has bid: " << book.bestBid().has_value()
              << ", has ask: " << book.bestAsk().has_value() << "\n";

    // 2. Add orders in scrambled price order: {id, side, price, qty, ts}
    book.add({1, fx::Side::Buy,  10840, 40, 1});
    book.add({2, fx::Side::Buy,  10842, 25, 2});
    book.add({3, fx::Side::Buy,  10838, 60, 3});
    book.add({4, fx::Side::Sell, 10850, 10, 4});
    book.add({5, fx::Side::Sell, 10846, 30, 5});

    // 3. Read the top of the book.
    auto bid = book.bestBid();
    auto ask = book.bestAsk();
    if (bid && ask) {
        std::cout << "best bid: " << *bid << "\n";
        std::cout << "best ask: " << *ask << "\n";
        std::cout << "spread:   " << (*ask - *bid) << "\n";
    }

    // Experiment A: uncomment, rebuild, run again.
    // book.add({6, fx::Side::Buy, 10846, 10, 6});

    // Experiment B: uncomment, rebuild, run again.
    // book.add({7, fx::Side::Sell, 10842, 10, 7});

    return 0;
}