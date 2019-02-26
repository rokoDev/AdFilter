//
//  AdFilter.h
//  AdFilter
//
//  Created by roko on 09/02/2019.
//

#ifndef AdFilter_h
#define AdFilter_h

#include <vector>
#include <string>

namespace helper
{
    struct Banner
    {
        std::size_t price;
        std::size_t id;
        std::vector<std::string> validCountries;
    };
    
    std::vector<Banner> extractBanners(const std::vector<Banner> & banners, const std::size_t numAdPlaces, const std::string & country);
} // helper namespace

#endif /* AdFilter_h */
