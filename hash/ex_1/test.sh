#!/bin/bash

if [ -d tests ]; then
  for f in $(ls tests); do
    if [[ "${#f}" -eq 2 ]]; then
      if [ -e bin/bin ]; then
        result_file="result_${f}.txt"
        cat tests/${f} | ./bin/bin > $result_file
        diff="$(diff $result_file tests/${f}.a --color=always)"
        if [ -z "$diff" ]; then
          echo "Test: ${f}: SUCCESS"
          echo "-------------------------"
        else
          echo "Test: ${f}: FAILED"
          echo ""
          vimdiff $result_file tests/${f}.a
        fi
        [ -f $result_file ] && rm $result_file
      else
        echo "Binary wasnt built."
        echo "Aborting tests!"
      fi
    fi
  done
  
else
  echo "No tests folder found."
  echo "Aborting tests!"
fi
