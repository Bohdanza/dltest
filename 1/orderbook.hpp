#include <bits/stdc++.h>
#include "order.hpp"

namespace orderbook
{
    class OrderBook
    {
        public:
            const std::map<long long, std::list<Order*>*>& Buy=m_buy;
            const std::map<long long, std::list<Order*>*>& Sell=m_sell;
        private:
            std::map<long long, std::list<Order*>*> m_buy, m_sell;
        public:
            OrderBook();
            void AddOrder(Order* orderToAdd);
            void ResolveMax();
        private:
            bool resolveOne();
            void addOrderToMap(std::map<long long, std::list<Order*>*>& mapToAddTo, Order* orderToAdd);
            void deleteOrderFromMap(std::map<long long, std::list<Order*>*>& mapToDeleteFrom, 
                std::list<Order*>* listToDeleteFrom, std::list<Order*>::const_iterator orderToDelete);
    };
}