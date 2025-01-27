#include "zonemaps.h"
#include <algorithm>

/**
 * Constructor that initializes all data members
 */
template <typename T>
zonemap<T>::zonemap(std::vector<T> _elements, uint _num_elements_per_zone)
    : elements(_elements), num_elements_per_zone(_num_elements_per_zone) 
{   
    // + num_elements_per_zone - 1 allows it to have an end zone even if it doesn't get filled
    num_zones = (elements.size() + num_elements_per_zone - 1) / num_elements_per_zone; // correct

    build();
}

/**
 * Builds the zonemap using the elements list. Maintains invariant that no. of elements in every zone
 * is less than or equal to num_elements_per_zone 
 */
template <typename T>
void zonemap<T>::build()
{
    // Iterates over the first elements in each zone
    for (size_t i = 0; i < elements.size(); i += num_elements_per_zone) 
    {
        // Creates the zone
        zone<T> z;

        // Finds the end index, if it reaches the end of the elements list, 
        // selects the end of the elements list 
        size_t end = std::min(i + num_elements_per_zone, elements.size());

        // Assigns the elements field using list.assign function
        z.elements.assign(elements.begin() + i, elements.begin() + end);

        // Creates the sorted elements that is used to find min and max
        std::vector<T> sorted_z_elements = z.elements;
        std::sort(sorted_z_elements.begin(), sorted_z_elements.end());

        // Assigns the min, max, and size fields
        z.min = sorted_z_elements.front(); 
        z.max = sorted_z_elements.back(); 
        z.size = z.elements.size();

        // Puts the zone in the zonemap
        zones.push_back(z);
    }
}

/**
 * Sorts the elements in the list
 */
template <typename T>
void zonemap<T>::sort_elements()
{
    std::sort(elements.begin(), elements.end());
}

/**
 * Queries a key using the zonemap 
 */
template <typename T>
size_t zonemap<T>::query(T key)
{
    // Stores how many instances of the key in the list
    size_t count = 0;

    // Iterates over all the zones
    for (const auto& z : zones) 
    {
        // If the key is not in the zone
        if (key < z.min || key > z.max) 
        {
            continue;
        }
        // If the key is in the zone
        else {
            // Counts how many of the key is in the zone elements
            count += std::count(z.elements.begin(), z.elements.end(), key);
        }
    }

    return count;
}

/*
 * Query a range of keys using the zonemap that are between a lower and higher limit
 */
template <typename T>
std::vector<T> zonemap<T>::query(T low, T high)
{
    // Stores the list of elements found using the query
    std::vector<T> result;

    // Iterates over all the zones
    for (const auto& z : zones) 
    {
        // If there can't be a desired element in the zone
        if (high < z.min || low > z.max) 
        {
            continue;
        }
        // If it is possible that there is a desired element
        else {
            // Iterates over all the element in the zone
            for (const auto& element : z.elements) 
            {
                // If the value of element is within min and max
                if (element >= low && element <= high) 
                {
                    // Adds to the results list
                    result.push_back(element);
                }
            }
        }
    }

    return result;
}
