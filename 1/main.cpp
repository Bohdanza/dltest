#include "orderbook.hpp"

using namespace std;
using namespace orderbook;

int main()
{
    unsigned long long time=0;
    OrderBook ob;

    while(true)
    {
        long long uid, amt, prc;
        int side;

        scanf(" Order{user_id %lld, amount %lld, price %lld, side %d}", &uid, &amt, &prc, &side);

        ob.AddOrder(new Order(time, uid, amt, prc, side==1));
        ob.ResolveMax();

        time++;
    }

    return 0;
}