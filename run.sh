cd cmake-build-debug
make
prog=$1
name=$(basename $prog .txt)
echo $name
./lab3 $prog &> $name.ll
llvm-as $name.ll
llc -filetype=obj $name.bc
gcc $name.o
./a.out
echo $?