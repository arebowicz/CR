#!/bin/bash

# code taken from:
# https://stackoverflow.com/questions/10118381/bash-script-to-automatically-test-program-output-c

# If number of arguments less then 1; print usage and exit
if [ $# -lt 1 ]; then
    printf "Usage: %s <application>\n" "$0" >&2
    exit 1
fi

bin="$1"           # The application (from command arg)
diff="diff -iad"   # Diff command, or what ever

# An array, do not have to declare it, but is supposedly faster
declare -a file_base=("01" "02" "03" "04" "05" "06" "07" "08" "09" "10" "11" "12" "13" "14")

# Loop the array
for file in "${file_base[@]}"; do
    # Padd file_base with suffixes
    file_in="tests/in/$file.input"               # The in file
    file_out_val="tests/out/$file.output"        # The out file to check against
    file_out_test="tests/out-tests/$file.output.test"   # The outfile from test application

    # Validate infile exists (do the same for out validate file)
    if [ ! -f "$file_in" ]; then
        printf "In file %s is missing\n" "$file_in"
        continue;
    fi
    if [ ! -f "$file_out_val" ]; then
        printf "Validation file %s is missing\n" "$file_out_val"
        continue;
    fi

    printf "Testing against %s\n" "$file_in"

    # Run application, redirect in file to app, and output to out file
    "./$bin" < "$file_in" > "$file_out_test"

    # Execute diff
    $diff "$file_out_test" "$file_out_val"


    # Check exit code from previous command (ie diff)
    # We need to add this to a variable else we can't print it
    # as it will be changed by the if [
    # Iff not 0 then the files differ (at least with diff)
    e_code=$?
    if [ $e_code != 0 ]; then
            printf "TEST FAIL : %d\n" "$e_code"
    else
            printf "TEST OK!\n"
    fi

    # Pause by prompt
    read -p "Enter a to abort, anything else to continue: " input_data
    # Iff input is "a" then abort
    [ "$input_data" == "a" ] && break

done

# Clean exit with status 0
exit 0