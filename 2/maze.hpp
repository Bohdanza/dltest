#include <bits/stdc++.h>

namespace mazeGenerator
{
    const int NOT_FILLED=0;

    //Must be 4 consecutive numbers
    const int DIR_UP=1;
    const int DIR_RIGHT=2;
    const int DIR_DOWN=3;
    const int DIR_LEFT=4;

    const int PASSAGE=5;
    const int WALL=6;
    const int ENTRANCE=7;
    const int EXIT=8;

    class Maze
    {
        public:
            const int& Size= m_size;
        private:
            int* m_map;
            int m_size;
            std::default_random_engine* rng;
            std::pair<int, int> m_entranceCoords, m_exitCoords;
        public:
            Maze(int size);
            ~Maze();
            void GeneratePassages();
            void GenerateFarExit();
            void PrintMap();
        private:
            int& getCell(int x, int y);
            bool advanceEnd(std::pair<int, int>& coords);
            bool moveInDirection(std::pair<int, int>& coords, int direction, bool fill);
            bool correctCoords(int x, int y);
    };
}