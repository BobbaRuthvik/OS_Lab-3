run: compile output1 output2
	./output1
	./output2

compile: setup.cpp main.cpp
	g++ setup.cpp -o output1
	g++ main.cpp -o output2

	
clean: 
	rm -rf output1 output2
