# This script prints out the time needed by the T_nw + T_write and averages it
if [ "$#" -ne 5 ]; then
	echo "Usage: $0 executable inputfile k nworkers niterations"
	exit -1;
fi

# Call the given program with its parameters
for(( i=0; i<$5; i++ )); do
	./$1 $2 $3 $4;
done |

# Search for "Knn" (which is the string initialized in the utimer object)
grep Knn |

# Calculate the average (in milliseconds)
awk '{ avg += ($4/1000); print $4/1000 " ms"} END { print "On average: "avg / NR " milliseconds"}'
