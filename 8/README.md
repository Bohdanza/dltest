HOW TO RUN:
Run main.exe (compiled for Windows 10 64-bit) or compile and run main.cpp together with any other .cpp files present in the directory

COMPLEXITY:
O(K * log K) - time complexity. Solution uses an array of laptops sorted by cost in O(K * log K) and ordered set of laptops available for sale, where insertion and deletion happen in O(log K) time no more than K times. 
O(K) - space complexity

INPUT NOTES:
Each one of two arrays should be in one line, after N and C.

Input example:

5 10
10 5 6 5 100
5 10 30 11 1000