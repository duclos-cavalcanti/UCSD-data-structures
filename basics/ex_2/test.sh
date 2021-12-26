#!/bin/bash

if [ -f tests ]; then
  for f in $(ls tests); do
    if [[ "${#f}" -eq 2 ]]; then
      if [ -e bin/bin ]; then
        cat tests/${f} | ./bin/bin > result.txt
        result="$(diff result.txt tests/${f}.a --color=always)"
        if [ -z "$result" ]; then
          echo "Test: ${f}: SUCCESS"
          echo "-------------------------"
        else
          echo "Test: ${f}: FAILED"
          echo "YOURS"
          cat result.txt
          
          echo ""
  
          echo "CORRECT"
          cat tests/${f}.a
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
