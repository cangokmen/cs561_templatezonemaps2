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

        std::vector<T> sorted_z_elements = z.elements;

        std::sort(sorted_z_elements.begin(), sorted_z_elements.end());

        z.min = sorted_z_elements.front(); 
        z.max = sorted_z_elements.back(); 
        z.size = z.elements.size();

        zones.push_back(z);
    }
}





template <typename T>
void zonemap<T>::sort_elements()
{
    std::sort(elements.begin(), elements.end());
}





template <typename T>
size_t zonemap<T>::query(T key)
{
    size_t count = 0;

    for (const auto& z : zones) 
    {
        if (key < z.min || key > z.max) 
        {
            continue;
        }
        else {
            count += std::count(z.elements.begin(), z.elements.end(), key);
        }
    }

    return count;
}



template <typename T>
std::vector<T> zonemap<T>::query(T low, T high)
{
    std::vector<T> result;

    for (const auto& z : zones) 
    {
        if (high < z.min || low > z.max) 
        {
            continue;
        }

        for (const auto& element : z.elements) 
        {
            if (element >= low && element <= high) 
            {
                result.push_back(element);
            }
        }
    }

    return result;
}
