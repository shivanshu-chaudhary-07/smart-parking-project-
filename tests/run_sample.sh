#!/bin/sh
# Runs the sample session from the report (capacity 2) and checks key lines.
out=$(./parking < tests/sample_input.txt)
echo "$out" | tail -n 25
for s in "MH12AB1234 parked at slot 1" \
         "UP16EF9012 waiting at position 1" \
         "HR26GH3456 waiting at position 2" \
         "DL01CD5678 has left" \
         "UP16EF9012 parked automatically" \
         "UP16EF9012 is already in the system"; do
  echo "$out" | grep -q "$s" || { echo "FAIL: $s"; exit 1; }
done
echo "ALL SAMPLE CHECKS PASSED"
