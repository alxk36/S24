#!/bin/bash

make all
EXECUTABLE="program.exe"

for ((i=0; i<=8; i++)); do
  INPUT_FILE="test${i}.mat test${i+1}.mat"
  echo
  echo "Running ${EXECUTABLE} - Test ${i}"
  echo test${i}.mat test${i+1}.mat | ./${EXECUTABLE}
  
  echo test${i}.mat test${i+1}.mat | leaks -c --atExit -- ./${EXECUTABLE}
  
done


make clean


#chmod +x test.sh
#./test.sh