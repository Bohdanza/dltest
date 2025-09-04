HOW TO RUN:
Run main.exe (compiled for Windows 10 64-bit) or compile and run main.cpp together with any other .cpp files present in the directory

COMPLEXITY:
Let P be the number of different prices for a buy/sell table, N be the number of orders which exist simultaneously. 

Then time complexity of:
Insertion is O(log P)
Deletion is O(1) if P doesn't change, O(log P) otherwise
Checking if match exists is O(1)

Solution makes use of ordered sets which utilize RB trees, hence the O(log P) deletion/insertion, and linked lists, hence the possible O(1) deletion.

Space complexity is O(N)

INPUT NOTES:

Each order should be written in one string. All spaces should be equal to the ones in the example. 
Side values must be integer numbers and are interpreted as following:
1 = true
Any other number = false

Example:
Order{user_id 0, amount 1, price 1, side true}
