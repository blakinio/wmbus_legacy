#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "meters.h"
#include "utils.h"
#include "Telegram.h"
#include "units.h"

int main() {
    std::string hex = "4E4401068686140005077A350040852F2F0F005B599600000010AA55000041545A42850BD800437D037301C5500000564B00009E4600006A410000A01778EC03FFFFFFFFFFFFFFFFFFFFFFFFFFE393";
    std::vector<uchar> frame;
    hex2bin(hex, &frame);

    Telegram t;
    t.about = AboutTelegram{"", 0, FrameType::WMBUS};
    MeterKeys mk;
    bool ok = t.parse(frame, &mk, false);
    assert(ok);

    MeterInfo mi;
    bool mi_ok = mi.parse("TestMeter", "apator162", t.addresses[0].id + ",", "");
    assert(mi_ok);
    auto meter = createMeter(&mi);

    std::vector<Address> addresses;
    bool id_match = false;
    AboutTelegram about{"test", 0, FrameType::WMBUS};
    meter->handleTelegram(about, frame, false, &addresses, &id_match, &t);
    assert(id_match);

    double total = meter->getNumericValue("total", Unit::M3);
    assert(std::abs(total - 21.93) < 0.001);

    std::cout << "All tests passed\n";
    return 0;
}
