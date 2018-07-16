#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    //typedef uint64_t IndexType;
    //typedef std::vector<IndexType> v_type;



    typedef std::vector<uint64_t> v_type;

    v_type g1;

    v_type :: iterator i;

 
    for (int i = 1; i <= 5; i++)
        g1.push_back(i);
 
    std::cout << "Output of begin and end\t:\t";
    for (i = g1.begin(); i != g1.end(); ++i)
        std::cout << *i << '\t';

  return 0;
}
