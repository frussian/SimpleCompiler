cd cmake-build-debug
make
./lab3 1&> test.ll
llvm-as test.ll
llc -filetype=obj test.bc
gcc test.o
./a.out
echo $?