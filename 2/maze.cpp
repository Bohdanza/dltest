#include "maze.hpp"

using namespace mazeGenerator;
using namespace std;

Maze::Maze(int size)
{
    rng=new default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    m_size=size;
    m_map = new int[m_size*m_size];

    for(auto i=0; i<m_size*m_size; i++)
        m_map[i]=NOT_FILLED;
}

Maze::~Maze()
{
    delete m_map;
    delete rng;
}

void Maze::GeneratePassages()
{
    int entranceCoord=(*rng)()%(m_size*4-4);
    pair<int, int> ent=make_pair(((entranceCoord/(m_size-1))%2==0)*(entranceCoord%m_size), 
            ((entranceCoord/(m_size-1))%2==1)*(entranceCoord%m_size)), 
        cCoord=make_pair(ent.first, ent.second);

    getCell(ent.first, ent.second)=DIR_RIGHT;

    do
    {
        if(!advanceEnd(cCoord))
            moveInDirection(cCoord, (getCell(cCoord.first, cCoord.second)-DIR_UP+2)%4+DIR_UP, 0);
    } while (cCoord!=ent);
    
    for(auto i=0; i<m_size*m_size; i++)
        if(m_map[i]==NOT_FILLED)
            m_map[i]=WALL;
        else
            m_map[i]=PASSAGE;

    getCell(ent.first, ent.second)=ENTRANCE;
    m_entranceCoords=make_pair(ent.first, ent.second);
}

void Maze::GenerateFarExit()
{
    vector<pair<int, int>> v;

    for(int i=0; i<m_size*4-4; i++)
    {
        int x=((i/(m_size-1))%2==0)*(i%m_size), 
            y=((i/(m_size-1))%2==1)*(i%m_size);

        if(getCell(x, y)==PASSAGE)
            v.push_back(make_pair(x, y));
    }

    int ind=(*rng)()%v.size();
    m_exitCoords=v[ind];

    getCell(m_exitCoords.first, m_exitCoords.second)=EXIT;
}

bool Maze::advanceEnd(std::pair<int, int>& coords)
{
    vector<int> dirs{DIR_UP, DIR_LEFT, DIR_DOWN, DIR_RIGHT};
    shuffle(dirs.begin(), dirs.end(), *rng);

    for(auto cdir : dirs)
        if(moveInDirection(coords, cdir, 1))
            return 1;

    return 0;
}
 
bool Maze::moveInDirection(std::pair<int, int>& coords, int direction, bool fill)
{
    int x=coords.first, y=coords.second;

    if(direction==DIR_UP)
        y-=2;

    if(direction==DIR_RIGHT)
        x+=2;

    if(direction==DIR_DOWN)
        y+=2;

    if(direction==DIR_LEFT)
        x-=2;

    if(!correctCoords(x, y)||(fill&&getCell(x, y)!=NOT_FILLED))
        return 0;

    if(fill)
    {
        int xdf=x-coords.first, ydf=y-coords.second;
        xdf/=2;
        ydf/=2;

        getCell(coords.first+xdf, coords.second+ydf)=direction;
        getCell(coords.first+2*xdf, coords.second+2*ydf)=direction;
    }
    
    coords.first=x;
    coords.second=y;

    return 1;
}

bool Maze::correctCoords(int x, int y)
{
    return x>=0&&y>=0&&x<m_size&&y<m_size;
}

void Maze::PrintMap()
{
    for(auto i=0; i<m_size; i++)
    {
        for(auto j=0; j<m_size; j++)
        {
            cout<<getCell(i, j);
        }

        cout<<"\n";
    }
}

int& Maze::getCell(int x, int y)
{
    return m_map[x*m_size+y];
}