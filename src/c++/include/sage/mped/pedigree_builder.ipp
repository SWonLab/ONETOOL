#ifndef SPBASE_H
#include "sage/spbase.h"
#endif

namespace SAGE {
namespace MPED {

inline
pedigree_builder::name_pair::name_pair() 
  : state(unused)
{}

inline
pedigree_builder::name_pair::name_pair(const string& f, UseStatus s) 
  : name1(f), name2(), state(s)
{}

inline
pedigree_builder::name_pair::name_pair(const string& f, const string& l, UseStatus s)
  : name1(f), name2(l), state(s)
{
    if (name2 < name1)
    {
        std::swap(name1, name2);
    }
}

}
}
