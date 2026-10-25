#pragma once
#include <functional>
#include <map>
#include <optional>
#include "price_level.hpp"
#include "types.hpp"

namespace fx {

class OrderBook {
public:
    void add(const Order& o) {
        if (o.side == Side::Buy) bids_[o.price].add(o);
        else                     asks_[o.price].add(o);
    }

    // Highest price any buyer will pay (empty if no bids).
    std::optional<Price> bestBid() const {
        if (bids_.empty()) return std::nullopt;
        return bids_.begin()->first;
    }

    // Lowest price any seller will accept (empty if no asks).
    std::optional<Price> bestAsk() const {
        if (asks_.empty()) return std::nullopt;
        return asks_.begin()->first;
    }

private:
    std::map<Price, PriceLevel, std::greater<Price>> bids_;  // highest price first
    std::map<Price, PriceLevel>                      asks_;  // lowest price first
};

}  // namespace fx