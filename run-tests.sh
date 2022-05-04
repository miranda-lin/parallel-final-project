#!/bin/bash

solvers=( alphabeta paraalphabeta paraminimax minimax )
core_counts=( 1 2 4 8 16 32 64 128 )
search_depths=( 1 3 5 7 9 11 13 15 )

make othello_bench

for solver in "${solvers[@]}"
do
  for d in "${search_depths[@]}"
  do
    if [ "$solver" == "paraalphabeta" ] || [ "$solver" == "paraminimax" ]
    then
      for n in "${core_counts[@]}"
      do
        echo "${solver}: d = ${d}, n = ${n}"
        (timeout 600 ./othello_bench ${n} ${solver} ${d} || echo "timed out") > ${solver}_${d}_${n}.txt
      done
    else
      echo "${solver}: d = ${d}, n = 1"
      (timeout 600 ./othello_bench 1 ${solver} ${d} || echo "timed out") > ${solver}_${d}_1.txt
    fi
  done
done
