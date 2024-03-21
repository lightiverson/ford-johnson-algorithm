#!/bin/bash

# Define the directory for logs
logdir="logs"

# Check if the log directory exists, create it if not
if [ ! -d "$logdir" ]; then
    mkdir -p "$logdir"
fi

# Define logfile name
date_stamp=$(date "+%Y-%m-%d_%H-%M-%S")
logfile="./logs/test_output_${date_stamp}.log"

# Test with 5 random numbers
N=5
HI=7
input=$(jot -r $N 1 100000 | tr '\n' ' ')
echo "Testing with [$input]: " >> $logfile
./PmergeMe $input
echo "Test: Comparisons value must be smaller or equal to $HI with $N random numbers." >> $logfile
echo -e >> $logfile

# Test with 8 random numbers
N=8
HI=16
input=$(jot -r $N 1 100000 | tr '\n' ' ')
echo "Testing with [$input]: " >> $logfile
./PmergeMe $input
echo "Test: Comparisons value must be smaller or equal to $HI with $N random numbers." >> $logfile
echo -e >> $logfile

# Test with 13 random numbers
N=13
HI=34
input=$(jot -r $N 1 100000 | tr '\n' ' ')
echo "Testing with [$input]: " >> $logfile
./PmergeMe $input
echo "Test: Comparisons value must be smaller or equal to $HI with $N random numbers." >> $logfile
echo -e >> $logfile

# Test with 37 random numbers
N=37
HI=146
input=$(jot -r $N 1 100000 | tr '\n' ' ')
echo "Testing with [$input]: " >> $logfile
./PmergeMe $input
echo "Test: Comparisons value must be smaller or equal to $HI with $N random numbers." >> $logfile
echo -e >> $logfile

# Test with 56 random numbers
N=56
HI=255
input=$(jot -r $N 1 100000 | tr '\n' ' ')
echo "Testing with [$input]: " >> $logfile
./PmergeMe $input
echo "Test: Comparisons value must be smaller or equal to $HI with $N random numbers." >> $logfile
echo -e >> $logfile