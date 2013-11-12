#ifndef __Minebombers__triple__
#define __Minebombers__triple__

template <typename T1, typename T2, typename T3>
class triple {
public:
    triple() {}
    
    triple(T1& t1, T2& t2, T3 t3) :
    first(t1), second(t2), third(t3) {}
    
    T1 first;
    T2 second;
    T3 third;
};
#endif