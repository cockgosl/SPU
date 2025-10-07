CXXFLAGS := -g -fsanitize=address -Iinclude
CPPOBJ := build/canary.o build/main.o build/StackInit.o build/StackPopPush.o build/Verificator.o build/StackDump.o build/StackDestroy.o

all: $(CPPOBJ)
	g++ $(CXXFLAGS) $(CPPOBJ) -o main

build/StackDestroy.o : src/StackDestroy.cpp
	g++ $(CXXFLAGS) -c $< -o $@

build/StackDump.o : src/StackDump.cpp
	g++ $(CXXFLAGS) -c $< -o $@

build/canary.o : src/canary.cpp 
	g++ $(CXXFLAGS) -c $< -o $@

build/main.o : src/main.cpp 
	g++ $(CXXFLAGS) -c $< -o $@

build/StackInit.o : src/StackInit.cpp 
	g++ $(CXXFLAGS) -c $< -o $@

build/StackPopPush.o : src/StackPopPush.cpp 
	g++ $(CXXFLAGS) -c $< -o $@

build/Verificator.o : src/Verificator.cpp 
	g++ $(CXXFLAGS) -c $< -o $@

clean :
	rm -f build/*.o main