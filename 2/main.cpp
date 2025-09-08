#include "maze.hpp"

using namespace std;
using namespace mazeGenerator;

int main()
{
    Maze m(20);

    m.GeneratePassages();
    m.GenerateFarExit();

    m.PrintMap();

    cin.get();

    return 0;
}