HOW TO RUN:
Run main.exe (compiled for Windows 10 64-bit) or compile and run main.cpp

COMPLEXITY:
Let N be number of different users, M be number of different pages

Space complexity: O(N * M) in worst-case scenario. More specifically, it's the sum of numbers of different pages visited by each user for all users.

Time complexity: O(N * (N + M * M)) in worst-case scenario, O(N * M) in average-case scenario. Solution uses hash tables, which is why the worst-case scenario (when all hashes collide) is nearly impossible. On average, if no collisions occur, time complexity is equal to space complexity. 

Time complexity of O(N * M) in worst-case scenario can be achieved by using arrays instead of hash tables, but space complexity would be enormous (depending on the maximum id)
