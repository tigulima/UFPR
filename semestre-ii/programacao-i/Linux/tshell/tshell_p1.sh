#!/usr/bin/env bash

dpm=$1
ds=$2
t1=$3
t2=$4
t3=$5

# Loop through each file in the input directory
for file in $dpm/*.csv; do
    # Extract the filename without the extension
    filename=$(basename "$file" .csv)

    # Filter the file based on search terms
    if [ -z "$t2" ]; then
        grep -E "*<$t1>*" "$file" > "$ds/$filename.csv"
    else
        if [ -z "$t3" ]; then
            grep -E "*<$t1>*" "$file" | grep -E "*<$t2>*" > "$ds/$filename.csv"
        else
            grep -E "*<$t1>*<$t2>*<$t3>*|*<$t1>*<$t3>*<$t2>*|*<$t2>*<$t1>*<$t3>*|*<$t2>*<$t3>*<$t1>*|*<$t3>*<$t2>*<$t1>*|*<$t3>*<$t1>*<$t2>*" "$file" > "$ds/$filename.csv"
        fi
    fi
done