#!/usr/bin/env sh
echo "Compiling\n";
g++ client_linux_x64.cpp -o client.exec;
g++ server_linux_x64.cpp -o server.exec;

echo "Changing permissions";
chmod +x client.exec;
chmod +x server.exec;

echo "...done";
