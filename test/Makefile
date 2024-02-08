
SRCS = ../src/CRtspSession.cpp ../src/CStreamer.cpp ../src/JPEGSamples.cpp ../src/SimStreamer.cpp ../src/jpeg-compressor/jpge.cpp

run: *.cpp ../src/* ../src/jpeg-compressor/*
	#skill testerver
	g++ -Wall -g -o testserver -I ../src -I . *.cpp $(SRCS) -std=c++11
	#./testserver
