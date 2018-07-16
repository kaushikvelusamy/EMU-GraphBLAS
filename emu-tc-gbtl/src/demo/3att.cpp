#include <iostream>

#include <vector>
#include <fstream>


using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "ERROR: too few arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(1);
    }

   // Read the edgelist and create the tuple arrays

    std::string pathname(argv[1]);
    std::ifstream infile(pathname);

    typedef uint64_t IndexType;
    typedef std::vector<IndexType> v_type;

    v_type :: iterator i;

    v_type iL, iU;
    v_type jL, jU;

    int64_t num_rows = 0;
    int64_t max_id = 0;
    uint64_t src, dst;
    string line;

    while (infile.good())
    {
        getline (infile,line);
        //std::cout << line << endl;
	std::cout<<line;
        //infile >> src >> dst;
       // std::cout << "Read: " << src << ", " << dst << std::endl;


 /*     if (src > max_id) max_id = src;
        if (dst > max_id) max_id = dst;

        if (src < dst)
        {
            iU.push_back(src);
            jU.push_back(dst);
        }
        else if (dst < src)
        {
            iL.push_back(src);
            jL.push_back(dst);
        }
        // else ignore self loops

        ++num_rows;
   */ }



   // for (i = iU.begin(); i != iU.end(); ++i)
     //   cout << *i << '\t';


    return 0;

}

