start=$(date +%s.%N)
# do some stuff here
dur=$(echo "$(date +%s.%N) - $start" | bc)
./a1 -t 1 -r 150000 algorithms are fun a
printf "Execution time: %.6f seconds" $dur