#include <fstream>
#include "retrieve.h"

retrieve::retrieve(int t_pagenumber, int hashlenth):pagenumber(t_pagenumber),table(hashlenth)
{
}

retrieve::~retrieve()
{
}

bool retrieve::exec(const std::string & inputfile, const std::string & outputfile)
{
    std::ifstream input(inputfile);
    std::ofstream output(outputfile);
    if (!input)
        return false;
    
    return false;
}
