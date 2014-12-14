#/usr/bin/env sh
echo "1- Compiling to object code"
g++ -Wall -g -c data.cpp
ls | grep .o
g++ -Wall -g data.o main.cpp -o final_obj.exec
echo "2- Compiling in the same statement"
g++ -Wall -g data.cpp main.cpp -o final_all.exec
echo "3- Creating Library for compilation"
ar rvs data.a data.o
g++ -Wall -g main.cpp data.a -o final_static_all.exec

chmod +x final_obj.exec
chmod +x final_all.exec
chmod +x final_static_all.exec

./final_obj.exec
./final_all.exec
./final_static_all.exec
