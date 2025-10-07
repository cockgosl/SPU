CXXFLAGS := -g -fsanitize=address -I stack/include -I asm+SPU/include
CPPOBJ := stack/build/canary.o stack/build/StackInit.o stack/build/StackPopPush.o stack/build/Verificator.o stack/build/StackDump.o stack/build/StackDestroy.o asm+SPU/build/ReadBuffer.o asm+SPU/build/SPU.o

all: $(CPPOBJ)
	g++ $(CXXFLAGS) $(CPPOBJ) -o SPU

stack/build/%.o : stack/src/%.cpp
	g++ $(CXXFLAGS) -c $< -o $@

asm+SPU/build/%.o : asm+SPU/src/%.cpp
	g++ $(CXXFLAGS) -c $< -o $@



clean :
	rm -f SPU stack/build/*.o
	rm -f SPU asm+SPU/build/*.o
