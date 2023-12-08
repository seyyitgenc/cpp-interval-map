#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

#define _DEBUG  1

// note: later on this can be templated like this
// K = Key, V = value
// template<typename K,typename V> 
// note: we assume that our value is default contructed
class interval_map
{
public:
    interval_map(char val) : m_valBegin(val){};
    ~interval_map() = default;

    // inserts range between keybegin and keyend with the val
    // our range according to the map conanical will be
    // keyBegins included keyEnd not included
    void assign(int key_begin,int key_end, char val){
        // we need to find upper and lower bound first to compare the range with key
        // lets assume our keyBegin = 1, keyEnd is = 5 so our range [1,5)
        // this means that 1,2,3,4 is given val
        // lets assume i already have inserted the range between [1,3) and [5,10) 
        // this means i have conflict between ranges [1,3 and [1,5);
        // i need to redefine range between [1,5)
        // if we have conflict we need to delete range between
        // how can we do that??
        auto it_lower = m_map.lower_bound(key_begin); // this may return m_map.begin()
        auto it_upper = m_map.upper_bound(key_end); // this may return m_map.end()

        m_map.insert_or_assign(key_begin,val);
        m_map.erase(it_lower,it_upper); // this will return range between [key_begin,key_end);
    }
    char& operator[](int key){
        // this will return m_valbegin if 
        // our key is out of range
        // lets imagine our map contains , 1-3/A , 4,7/B ranges
        // assume that user try to reach 0 range // so we must return m_valBegin
        auto it = m_map.upper_bound(key);
        if (it == m_map.begin())
            return m_valBegin;
        else 
            // if we found upper bound lets return previous one to reach our actual value
            // because upper bound return it to the next value greater then our key
            (--it)->second;
    }
    
private:

#if _DEBUG
    void print(){
        for (auto &&item : m_map)
        {
            auto key = item.first; 
            auto val = item.second; 
            std::cout << "key = "  << key << " value = " << val << std::endl;
        }
    }
    friend void testIntervalMap();
#endif
    std::map<int,char> m_map; 
    char m_valBegin;
};
// test cases
#if _DEBUG
void testIntervalMap(){
    interval_map test1('A');
    test1.assign(1,3,'B'); // key 1,2 will be B
    test1.print();
    test1.assign(3,5,'C'); // key 3,4 will be C
    test1.print();
}
#endif

int main(){
    testIntervalMap();
    return 0;
}