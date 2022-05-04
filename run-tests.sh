#!/bin/bash

solvers=( alphabeta paraalphabeta paraminimax minimax )
core_counts=( 1 2 4 8 16 32 64 )
search_depths=( 1 3 5 7 9 11 13 15 )

make othello_bench

run_one () {
  if ! test -f "$1_$2_$3.txt"
  then
    echo "$1: d = $2, n = $3"
    (timeout 600 ./othello_bench $3 $1 $2 || echo "timed out") > $1_$2_$3.txt
  fi
}

for solver in "${solvers[@]}"
do
  for d in "${search_depths[@]}"
  do
    if [ "$solver" == "paraalphabeta" ] || [ "$solver" == "paraminimax" ]
    then
      for n in "${core_counts[@]}"
      do
        run_one $solver $d $n
      done
    else
      run_one $solver $d 1
    fi
  done
done
