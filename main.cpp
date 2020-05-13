#include <iostream>
#include <vector>
#include <fstream>
#include "SatelliteChipCodeGenerator.h"
#include "Constants.h"
#include <math.h>


std::vector<int> fileValue = std::vector<int>();

int readInFile(std::string &filename) {
    std::ifstream source(filename);

    std::vector<int> values = std::vector<int>();

    if (source.is_open()) {
        std::copy(std::istream_iterator<int>(source), std::istream_iterator<int>(), std::back_inserter(values));
    } else{
        std::cerr << "Can not open file" << std::endl;
        return -1;
    }

    fileValue = values;

    return 0;
}

int crossCorrelate(std::vector<int> first,std::vector<int> second){
    int value = 0;

    for(int i = 0; i < CODE_SIZE; i++){
        value = value + (first[i] * second[i]);
    }

    return value;
}

std::vector<int>shiftCode(std::vector<int> code, int count){
    std::vector<int> result = std::vector<int>();

    for(int i = count; i < CODE_SIZE; i++){
        result.push_back(code.at(i));
    }

    for (int i = 0; i < count; i++) {
        result.push_back(code.at(i));
    }

    return result;
}

int getPositiveNoiseValue(){
    return (pow(2, (NUMBER_OF_REGISTERS + 2) / 2) - 1) * (NUMBER_OF_SATELLITES - 1) ;
}

int getNegativeNoiseValue(){
    return (-1 * pow(2, (NUMBER_OF_REGISTERS + 2) / 2) - 1) * (NUMBER_OF_SATELLITES - 1);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "Please enter input file name as a parameter\n" << std::endl;
        return -1;
    }

    std::string filename = std::string(argv[1]);

    int res = readInFile(filename);

    if (res < 0) {
        return res;
    }

    SatelliteChipCodeGenerator codeGenerator = SatelliteChipCodeGenerator();

    for(int s = 1; s < 25; s++) {
        std::vector<int> code = codeGenerator.chipCode(s);
        for (int i = 0; i < CODE_SIZE; i++) {
            std::vector<int> shiftedCode = shiftCode(fileValue, i);
            int correlation = crossCorrelate(code, shiftedCode);
            if(correlation > CODE_SIZE + getNegativeNoiseValue()){
                std::cout << "Satellite " << s << " has sent bit 1 (delta = " << i << ")" << std::endl;
            }else if(correlation < ((-1) * CODE_SIZE + getPositiveNoiseValue())){
                std::cout << "Satellite " << s << " has sent bit 0 (delta = " << i << ")" << std::endl;
            }
        }
    }

    return 0;

}


