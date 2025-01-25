#include "zonemaps.h"
#include <algorithm>


// this is correct
template <typename T>
zonemap<T>::zonemap(std::vector<T> _elements, uint _num_elements_per_zone)
    : elements(_elements), num_elements_per_zone(_num_elements_per_zone) 
{
    // constructor 
    // Your code starts here ...
    
    num_zones = (elements.size() + num_elements_per_zone - 1) / num_elements_per_zone; // correct

    build();
}



template <typename T>
void zonemap<T>::build()
{
    //sort_elements();

    for (size_t i = 0; i < elements.size(); i += num_elements_per_zone) 
    {
        zone<T> z;

        size_t end = std::min(i + num_elements_per_zone, elements.size());
        z.elements.assign(elements.begin() + i, elements.begin() + end);

        z.min = z.elements.front(); // since not sorted, incorrect!!
        z.max = z.elements.back(); // since not sorted, incorrect!!
        z.size = z.elements.size(); // correct

        zones.push_back(z);
    }
}





template <typename T>
void zonemap<T>::sort_elements()
{
    std::sort(elements.begin(), elements.end());
}



