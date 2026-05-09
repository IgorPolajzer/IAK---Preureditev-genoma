#!/bin/bash
cd "/home/igor/Desktop/MAG/1_LETNIK/2_SEMESTER/IZBRANI_ALGORITMI_KOMBINATORIKE/IAK_Preureditev_genoma"

for alg in -rs -ibrs -imp; do
    ./cmake-build-debug/IAK_Preureditev_genoma -t "$alg"
done