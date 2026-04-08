#!/bin/bash
g++ -O0 -g3 main.cpp pcie-util.cpp -o pcie_basic -std=c++17
g++ -O0 -g3 server.cpp pcie-util.cpp -o server -std=c++17
g++ -O0 -g3 client.cpp -o client -std=c++17
