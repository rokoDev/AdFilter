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
#include <set>
#include <functional>

namespace helper
{
    struct Banner
    {
        uint32_t price;
        uint32_t id;
        std::vector<std::string> validCountries;
    };
    
    std::vector<Banner> extractBanners(const std::vector<Banner> & banners, const uint32_t numAdPlaces, const std::string & country, const std::function<bool(const Banner & banner)> & condition = nullptr);
} // helper namespace

#endif /* AdFilter_h */
