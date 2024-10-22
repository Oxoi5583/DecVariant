@echo on
cd build 
cmake .. --fresh
cmake --build .
cd ..
cd bin
test.exe
cd ..