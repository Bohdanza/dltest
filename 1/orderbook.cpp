#include "orderbook.hpp"

using namespace std;
using namespace orderbook;

OrderBook::OrderBook()
{}

void OrderBook::AddOrder(Order* orderToAdd)
{
    if(orderToAdd->Side)
        addOrderToMap(m_buy, orderToAdd);
    else
        addOrderToMap(m_sell, orderToAdd);
}

void OrderBook::ResolveMax()
{
    while(resolveOne());
}

void OrderBook::addOrderToMap(map<long long, list<Order*>*> &mapToAddTo, Order* orderToAdd)
{
    auto it=mapToAddTo.find(orderToAdd->Price);

    if(it==mapToAddTo.end())
    {
        auto currentPriceList=new list<Order*>();
        currentPriceList->push_back(orderToAdd);
        mapToAddTo.insert(make_pair(orderToAdd->Price, currentPriceList));
    }
    else
        it->second->push_back(orderToAdd);
}

void OrderBook::deleteOrderFromMap(map<long long, std::list<Order*>*>& mapToDeleteFrom, 
    list<Order*>* listToDeleteFrom, list<Order*>::const_iterator orderToDelete)
{
    auto actualOrder=*orderToDelete;

    if(listToDeleteFrom->size()<2)
    {
        mapToDeleteFrom.erase((*orderToDelete)->Price);

        delete listToDeleteFrom;
    }
    else
        listToDeleteFrom->erase(orderToDelete);
    
    delete actualOrder;
}

bool OrderBook::resolveOne()
{
    if(m_buy.empty()||m_sell.empty())
        return 0;

    Order* topSell=*(m_sell.begin()->second->begin());

    auto pb=m_buy.end();
    pb--;
    Order* topBuy=*(pb->second->begin());

    if(topSell->Price>topBuy->Price)
        return false;

    int realPrice=topBuy->Price;
    int realAmount=min(topBuy->Amount, topSell->Amount);

    if(topSell->Time<topBuy->Price)
        realPrice=topSell->Price;

    topBuy->Amount-=realAmount;
    topSell->Amount-=realAmount;

    cout<<"BalanceChange{user_id "<<topBuy->UserId<<", value "<<realAmount<<", currency UAH}\n";
    cout<<"BalanceChange{user_id "<<topBuy->UserId<<", value "<<-realAmount*realPrice<<", currency USD}\n";
    
    cout<<"BalanceChange{user_id "<<topSell->UserId<<", value "<<-realAmount<<", currency UAH}\n";
    cout<<"BalanceChange{user_id "<<topSell->UserId<<", value "<<realAmount*realPrice<<", currency USD}\n";

    if(topBuy->Amount<1)
        deleteOrderFromMap(m_buy, pb->second, pb->second->begin());
        
    if(topSell->Amount<1)
        deleteOrderFromMap(m_sell, m_sell.begin()->second, m_sell.begin()->second->begin());

    return true;
}
