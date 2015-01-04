echo "--------COMPILING----------";
echo "Determining your operating system"
OS="$(uname)";

if [ -e Linux_wave.exec ]
    then
        rm "$OS"_wave.exec
    fi
    
if [ $OS = "Linux" ]
then
    echo "Compilation"
    g++ main.cpp soundhandler.cpp -std=c++11 -o "$OS"_wave.exec
    echo "Execution privs"
    chmod +x "$OS"_wave.exec;
fi

if [ $OS = "Darwin" ]
then
    echo $OS;
fi

echo "------ DONE -----";
echo "Executing: "
./"$OS"_wave.exec