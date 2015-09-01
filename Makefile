all: exe

exe: dll
	cd build; g++ ../src/game/*.cpp -o ./Prototype.exe -I../src/ -L./ -lbeardengine
	
dll:
	cd build; g++ -c ../src/engine/*.cpp; g++ -shared -o beardengine.dll *.o
	
clean:
	rm build/* -rf