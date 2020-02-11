To compile and run:  
$ g++ -g -Wall -std=c++11 Source.cpp -o Source  
$ ./Source  
  
The program requires an input.txt file, in which the first number should be the size of the input array, and then the elements in the array.  
The program will solve the problem and output 1. the answer; 2. the input array; 3. step-by-step breakdown when both players play optimally.  
  
The repo contains a sample input.txt, which contains an input of size 30.  
The sample output should be:  
The maximum point the first player can get is : -78  
The original array was: -22 9 -4 -21 4 -7 -23 -24 -25 -15 10 -3 5 -11 8 -19 -20 7 -6 -8 15 -14 -10 -5 0 -17 14 6 -2 -1  
Your turn:              right 4  
Opponent's turn:        left 3  
Your turn:              left 3  
Opponent's turn:        right 2  
Your turn:              right 7  
Opponent's turn:        right 1  
Your turn:              right 7  
Opponent's turn:        left 2  
Your turn:              take the last integer  
