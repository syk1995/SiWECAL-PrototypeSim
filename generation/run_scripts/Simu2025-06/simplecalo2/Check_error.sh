#!/bin/bash
dir="Submit"
for file in "$dir"/*GeV/run.sh.o*; do
    if grep -i "error" "$file"; then
        echo "Found 'error' in $file"
    else
        echo "No 'error' found in $file"
    fi
done
