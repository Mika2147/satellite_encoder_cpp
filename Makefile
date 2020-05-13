satellitedecoder: main.o SatelliteChipCodeGenerator.o
	g++ main.o SatelliteChipCodeGenerator.o -o satellitedecoder

main.o: main.cpp
	g++ -c main.cpp

SatelliteChipCodeGenerator.o: SatelliteChipCodeGenerator.cpp
	g++ -c SatelliteChipCodeGenerator.cpp

clean:
	rm *.o satellitedecoder
