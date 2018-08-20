#include <iostream>
#include <vector>
 
using namespace std;
 
int main()
{
    typedef vector<uint64_t> v_type;
    v_type g1;
    v_type :: iterator i;
 
    for (int i = 1; i <= 5; i++)
        g1.push_back(i);
 
    cout << "Output of begin and end\t:\t";
    for (i = g1.begin(); i != g1.end(); ++i)
        cout << *i << '\t';

    return 0;
 
}

