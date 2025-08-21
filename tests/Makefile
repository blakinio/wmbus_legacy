.RECIPEPREFIX := >
CXX=g++
CXXFLAGS=-std=c++17

WMBUS_SRC=../components/wmbus/driver_apator162.cpp \
          ../components/wmbus/meters.cpp \
          ../components/wmbus/dvparser.cpp \
          ../components/wmbus/Telegram.cpp \
          ../components/wmbus/utils.cpp \
          ../components/wmbus/address.cpp \
          ../components/wmbus/translatebits.cpp \
          ../components/wmbus/formula.cpp \
          ../components/wmbus/types.cpp \
          ../components/wmbus/units.cpp \
          ../components/wmbus/manufacturer_specificities.cpp \
          ../components/wmbus/aes.cpp \
          ../components/wmbus/crc.cpp \
          ../components/wmbus/decode3of6.cpp

WMBUS_FLAGS=-I../components/wmbus -Istubs -include cstdint -include arduino_stubs.h

TESTS=datetime_flags_test render_analysis_json_test driver_apator162_test rf_cc1101_test

all: $(TESTS)

datetime_flags_test: datetime_flags_test.cpp
>$(CXX) $(CXXFLAGS) $< -o $@

render_analysis_json_test: render_analysis_json_test.cpp
>$(CXX) $(CXXFLAGS) $< -o $@

driver_apator162_test: driver_apator162_test.cpp $(WMBUS_SRC)
>$(CXX) $(CXXFLAGS) $(WMBUS_FLAGS) $^ -o $@

rf_cc1101_test: rf_cc1101_test.cpp $(WMBUS_SRC) \
                 ../components/wmbus/rf_cc1101.cpp \
                 ../components/wmbus/utils_my.cpp
>$(CXX) $(CXXFLAGS) $(WMBUS_FLAGS) $^ -o $@

test: $(TESTS)
>./datetime_flags_test
>./render_analysis_json_test > /dev/null
>./driver_apator162_test
>./rf_cc1101_test

clean:
>rm -f $(TESTS)

.PHONY: all test clean
