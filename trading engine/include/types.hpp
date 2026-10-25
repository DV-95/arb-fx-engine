#pragma once
#include <cstdint>

namespace fx {

using OrderId   = std::uint64_t;   // unique id, never negative
using Timestamp = std::uint64_t;   // sequence number: 1, 2, 3, ...
using Price     = std::int64_t;    // price in ticks
using Quantity  = std::int64_t;    // number of units

enum class Side { Buy, Sell };

struct Order {
    OrderId   id;
    Side      side;
    Price     price;
    Quantity  qty;
    Timestamp ts;
};

struct Trade {
    OrderId   buyId;
    OrderId   sellId;
    Price     price;
    Quantity  qty;
    Timestamp ts;
};

}  