#!/bin/sh

rm ./OG/crackme
cp ./OG/original ./OG/crackme

echo "\n./crackme test test \n returns:\n";
./OG/crackme test test
echo "\n\n./1crackme \n"
./crack_ex/a.out
echo "./crackme test test \n returns:\n";
./OG/crackme test test
echo "\n\n./2keygen \n"
./keygen_ex/a.out
echo "./crackme test test \n returns:\n";
./OG/crackme test test
echo "\n"
