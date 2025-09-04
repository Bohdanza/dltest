namespace orderbook
{
    class Order
    {
        public:
            long long Amount;
            const long long& Time=m_time;
            const long long& UserId=m_userId;
            const long long& Price=m_price;
            const bool& Side=m_side;
        private:
            long long m_time;
            long long m_userId;
            long long m_price;
            bool m_side;
        public:
            Order(long long time, long long userId, long long amount, long long price, bool side)
                : m_userId(userId), Amount(amount), m_price(price), m_side(side), m_time(time) {} 
    };   
}
