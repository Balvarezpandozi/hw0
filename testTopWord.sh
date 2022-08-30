#!/bin/bash
curl -o "in#01.txt" http://www2.cs.uh.edu/~dss/teaching/COSC4315/testcases/string-topword/in/[01-11/].txt
curl -o "ans#01.txt" http://www2.cs.uh.edu/~dss/teaching/COSC4315/testcases/string-topword/out/[01-11/].txt

for i in {01..11}
do
  ./topword "input=in$i.txt;output=out$i.txt"
  if cmp -s "ans$i.txt" "out$i.txt"; then
    echo "Test case $i passed"
  else
    echo "Test case $i failed"
  fi
done