//
// Created by Mika Auer on 09.05.20.
//
#include <vector>
#include <map>
#include "Constants.h"

#ifndef SATELLITE_ENCODER_CPP_SATELLITECHIPCODEGENERATOR_H
#define SATELLITE_ENCODER_CPP_SATELLITECHIPCODEGENERATOR_H


class SatelliteChipCodeGenerator {
    std::map<int, std::vector<int> > satelliteCodes;
    std::map<int, std::pair<int, int> > registerSums;

    std::vector<int> getTopSum();
    std::vector<int> getBottomSum(int satelliteID);
    std::vector<int> topSum;

    std::vector<int> generateSatelliteCode(int satelliteID);

public:
    SatelliteChipCodeGenerator();
    ~SatelliteChipCodeGenerator();

    std::vector<int> chipCode(int satelliteID);

};


#endif //SATELLITE_ENCODER_CPP_SATELLITECHIPCODEGENERATOR_H
