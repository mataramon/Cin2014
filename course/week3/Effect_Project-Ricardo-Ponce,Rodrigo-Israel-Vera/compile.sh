echo "--------COMPILING----------";
echo "Determining your operating system"
OS="$(uname)";

if [ -e "$OS"_wave.exec ]
    then
        rm "$OS"_wave.exec
    fi
if [ -e waveoutfile.wav ]
    then
        rm waveoutfile.wav
    fi


echo "Compilation"
if [ $OS = "Linux" ]
then
    g++ main.cpp soundhandler.cpp -std=c++11 -o "$OS"_wave.exec
fi

if [ $OS = "Darwin" ]
    then
    clang++ main.cpp soundhandler.cpp -std=c++11 -stdlib=libc++ -o "$OS"_wave.exec;
fi

echo "Execution privs"
chmod +x "$OS"_wave.exec;

echo "------ DONE -----";
echo "Executing: "
./"$OS"_wave.exec
