#include <iostream>
#include <unordered_map>
#include <list>

struct LRUCache
{
    void update(int i)
    {
        auto k = keys.find(i);
        if(k != keys.end())
        {
            priority.erase(k->second);
            priority.push_back(i);
        }
        else
        {
            if(priority.size() == max_count)
            {
                keys.erase(priority.front());
                priority.pop_front();
            }
            priority.push_back(i);
            keys[i] = --priority.end();
        }
    }

    bool exists(int i)
    {
       keys.count(i);
    }

    static const int max_count = 2;
    std::unordered_map<int, std::list<int>::iterator> keys;
    std::list<int> priority;
};

int main()
{
}
