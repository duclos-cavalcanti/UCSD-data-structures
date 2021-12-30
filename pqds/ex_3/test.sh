#!/bin/bash

if [ -d tests ]; then
  for f in $(ls tests); do
    if [[ "${#f}" -eq 2 ]]; then
      if [ -e bin/bin ]; then
        cat tests/${f} | ./bin/bin > result.txt
        diff="$(diff result.txt tests/${f}.a --color=always)"
        if [ -z "$diff" ]; then
          echo "Test: ${f}: SUCCESS"
          echo "-------------------------"
        else
          echo "Test: ${f}: FAILED"
          echo ""
          echo -e -n "Given\tCorrect"

          output=""
          size="$(cat result.txt | wc -l)"

          for ((i = 0 ; i <= $size ; i++)); do
            result="$(cat result.txt | head -n $i | tail -n 1)"
            correct="$(cat tests/${f}.a | head -n $i | tail -n 1)"
            if [[ "$result" != "$correct" ]]; then
              output="${result}\t\t${correct}\tWRONG"
            else
              output="${result}\t\t${correct}"
            fi
            echo -e "${output}"
          done
        fi
      else
        echo "Binary wasnt built."
        echo "Aborting tests!"
      fi
    fi
  done
  
  [ -f result.txt ] && rm result.txt
else
  echo "No tests folder found."
  echo "Aborting tests!"
fi
