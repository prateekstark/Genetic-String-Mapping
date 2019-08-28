FLAG = -std=c++11

all: GeneMapping

GeneMapping: MainFile GeneSequence HillClimbingRR HillClimbingIter UCS UCSState HillClimbingState Helper
		g++ outputs/MainFile outputs/GeneSequence outputs/HillClimbingRR outputs/HillClimbingIter outputs/UCS outputs/UCSState outputs/HillClimbingState outputs/Helper -o GeneMapping

MainFile: src/MainFile.cpp include/GeneSequence.h
		g++ -c src/MainFile.cpp -o outputs/MainFile

GeneSequence: src/GeneSequence.cpp include/GeneSequence.h
		g++ -c src/GeneSequence.cpp -o outputs/GeneSequence

HillClimbingRR: src/HillClimbingRR.cpp include/GeneSequence.h
		g++ -c $(FLAG) src/HillClimbingRR.cpp -o outputs/HillClimbingRR

HillClimbingIter: src/HillClimbingIter.cpp include/GeneSequence.h
		g++ -c src/HillClimbingIter.cpp -o outputs/HillClimbingIter

UCS: src/UCS.cpp include/GeneSequence.h
		g++ -c src/UCS.cpp -o outputs/UCS

UCSState: src/UCSState.cpp include/UCSState.h
		g++ -c src/UCSState.cpp -o outputs/UCSState

HillClimbingState: src/HillClimbingState.cpp include/HillClimbingState.h
		g++ -c src/HillClimbingState.cpp -o outputs/HillClimbingState

Helper: src/Helper.cpp include/Helper.h
		g++ -c $(FLAG) src/Helper.cpp -o outputs/Helper

clean:
		rm -rf outputs/* GeneMapping
