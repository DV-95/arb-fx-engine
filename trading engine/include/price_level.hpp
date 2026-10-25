#pragma once
#include <algorithm>
#include <cstddef>
#include <deque>
#include "types.hpp"

namespace fx {

// Result of taking quantity from a resting order.
struct Fill {
    OrderId  id;    // which resting order was (partly) filled
    Quantity qty;   // how much we took from it
};

class PriceLevel {
public:
    void add(const Order& o) { orders_.push_back(o); }
    bool empty() const { return orders_.empty(); }
    std::size_t size() const { return orders_.size(); }

    Quantity totalQty() const {
        Quantity sum = 0;
        for (const Order& o : orders_) sum += o.qty;
        return sum;
    }

    const Order& front() const { return orders_.front(); }

    // Take up to `wanted` units from the order at the front of the line.
    // Only call if !empty().
    Fill fillFront(Quantity wanted) {
        Order& first = orders_.front();
        Quantity taken = std::min(wanted, first.qty);

        first.qty -= taken;
        Fill result{first.id, taken};     // build the result BEFORE popping

        if (first.qty == 0) orders_.pop_front();   // fully filled: leaves the line
        return result;
    }

private:
    std::deque<Order> orders_;
};

}  // namespace fx