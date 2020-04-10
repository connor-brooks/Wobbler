#!/bin/bash
# Plays C major chord repeatedly, randomising the synth's parameters every time.
# To use, run "./test.sh | ./wob"

sleep 2

echo "rand"

while true
do
  echo "noteon 36"
  sleep 0.4
  echo "noteoff 36"
  sleep 0.5

  echo "noteon 40"
  sleep 0.4
  echo "noteoff 40"
  sleep 0.5

  echo "noteon 43"
  sleep 0.4
  echo "noteoff 43"
  sleep 2
  
  echo "rand"
done

echo "quit"
