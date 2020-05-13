//
// Created by Mika Auer on 09.05.20.
//

#include <iostream>
#include "SatelliteChipCodeGenerator.h"

SatelliteChipCodeGenerator::SatelliteChipCodeGenerator() {
    satelliteCodes = std::map<int, std::vector<int> >();
    topSum = std::vector<int>();

    std::pair<int, int> rSum1 = std::pair<int, int>(2, 6);
    std::pair<int, int> rSum2 = std::pair<int, int>(3, 7);
    std::pair<int, int> rSum3 = std::pair<int, int>(4, 8);
    std::pair<int, int> rSum4 = std::pair<int, int>(5, 9);
    std::pair<int, int> rSum5 = std::pair<int, int>(1, 9);
    std::pair<int, int> rSum6 = std::pair<int, int>(2, 10);
    std::pair<int, int> rSum7 = std::pair<int, int>(1, 8);
    std::pair<int, int> rSum8 = std::pair<int, int>(2, 9);
    std::pair<int, int> rSum9 = std::pair<int, int>(3, 10);
    std::pair<int, int> rSum10 = std::pair<int, int>(2, 3);
    std::pair<int, int> rSum11 = std::pair<int, int>(3, 4);
    std::pair<int, int> rSum12 = std::pair<int, int>(5, 6);
    std::pair<int, int> rSum13 = std::pair<int, int>(6, 7);
    std::pair<int, int> rSum14 = std::pair<int, int>(7, 8);
    std::pair<int, int> rSum15 = std::pair<int, int>(8, 9);
    std::pair<int, int> rSum16 = std::pair<int, int>(9, 10);
    std::pair<int, int> rSum17 = std::pair<int, int>(1, 4);
    std::pair<int, int> rSum18 = std::pair<int, int>(2, 5);
    std::pair<int, int> rSum19 = std::pair<int, int>(3, 6);
    std::pair<int, int> rSum20 = std::pair<int, int>(4, 7);
    std::pair<int, int> rSum21 = std::pair<int, int>(5, 8);
    std::pair<int, int> rSum22 = std::pair<int, int>(6, 9);
    std::pair<int, int> rSum23 = std::pair<int, int>(1, 3);
    std::pair<int, int> rSum24 = std::pair<int, int>(4, 6);

    registerSums.insert(std::make_pair(1, rSum1));
    registerSums.insert(std::make_pair(2, rSum2));
    registerSums.insert(std::make_pair(3, rSum3));
    registerSums.insert(std::make_pair(4, rSum4));
    registerSums.insert(std::make_pair(5, rSum5));
    registerSums.insert(std::make_pair(6, rSum6));
    registerSums.insert(std::make_pair(7, rSum7));
    registerSums.insert(std::make_pair(8, rSum8));
    registerSums.insert(std::make_pair(9, rSum9));
    registerSums.insert(std::make_pair(10, rSum10));
    registerSums.insert(std::make_pair(11, rSum11));
    registerSums.insert(std::make_pair(12, rSum12));
    registerSums.insert(std::make_pair(13, rSum13));
    registerSums.insert(std::make_pair(14, rSum14));
    registerSums.insert(std::make_pair(15, rSum15));
    registerSums.insert(std::make_pair(16, rSum16));
    registerSums.insert(std::make_pair(17, rSum17));
    registerSums.insert(std::make_pair(18, rSum18));
    registerSums.insert(std::make_pair(19, rSum19));
    registerSums.insert(std::make_pair(20, rSum20));
    registerSums.insert(std::make_pair(21, rSum21));
    registerSums.insert(std::make_pair(22, rSum22));
    registerSums.insert(std::make_pair(23, rSum23));
    registerSums.insert(std::make_pair(24, rSum24));
}

SatelliteChipCodeGenerator::~SatelliteChipCodeGenerator() {

}

std::vector<int> SatelliteChipCodeGenerator::chipCode(int satelliteID) {
    if (satelliteCodes.find(satelliteID) == satelliteCodes.end()) {
        std::vector<int> chipCode = generateSatelliteCode(satelliteID);
        satelliteCodes.insert(std::pair<int, std::vector<int> >(satelliteID, chipCode));
    }

    return satelliteCodes[satelliteID];
}

std::vector<int> SatelliteChipCodeGenerator::generateSatelliteCode(int satelliteID) {
    std::vector<int> top = getTopSum();
    std::vector<int> bottom = getBottomSum(satelliteID);

    std::vector<int> result = std::vector<int>();

    for(int i = 0; i < CODE_SIZE; i++){
        int newResultValue = top.at(i) ^ bottom.at(i);
        if(newResultValue == 0){
            newResultValue = -1;
        }
        result.push_back(newResultValue);

    }

    return result;
}

std::vector<int> SatelliteChipCodeGenerator::getTopSum() {
    if (topSum.empty()) {

        std::vector<int> registerValues = std::vector<int>();
        //Nicht sehr elegante variante dies zu tun aber der compiler zwingt mich dazu, in clion ohne makefile hat die direkte intitialisierung mit {} geklappt, mit makefile aber nicht
        for (int j = 0; j < 10; ++j) {
            registerValues.push_back(1);
        }

        std::vector<int> result = std::vector<int>();

        for (int i = 0; i < CODE_SIZE; i++) {
            result.push_back(registerValues.back());
            int newFrontValue = registerValues.at(2) ^ registerValues.at(9);
            registerValues.pop_back();
            registerValues.insert(registerValues.begin(), newFrontValue);
        }
        topSum = result;
    }

    return topSum;
}

std::vector<int> SatelliteChipCodeGenerator::getBottomSum(int satelliteID) {

    std::vector<int> registerValues = std::vector<int>();
    //Nicht sehr elegante variante dies zu tun aber der compiler zwingt mich dazu, in clion ohne makefile hat die direkte intitialisierung mit {} geklappt, mit makefile aber nicht
    for (int j = 0; j < 10; ++j) {
        registerValues.push_back(1);
    }

    std::vector<int> result = std::vector<int>();
    std::pair<int, int> registerSum = registerSums.at(satelliteID);

    for (int i = 0; i < CODE_SIZE; i++) {
        int newFrontValue = ((((registerValues.at(1) ^ registerValues.at(2)) ^ registerValues.at(5)) ^ registerValues.at(7)) ^ registerValues.at(8)) ^ registerValues.at(9);
        int newResultValue = registerValues.at(registerSum.first - 1) ^ registerValues.at(registerSum.second - 1);
        result.push_back(newResultValue);
        registerValues.pop_back();
        registerValues.insert(registerValues.begin(), newFrontValue);
    }

    return result;
}
