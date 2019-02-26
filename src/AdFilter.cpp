//
//  AdFilter.cpp
//  AdFilter
//
//  Created by roko on 09/02/2019.
//

#include "AdFilter.h"
#include <iostream>
#include <random>

namespace helper
{
    std::vector<Banner> extractBanners(const std::vector<Banner> & banners, const uint32_t numAdPlaces, const std::string & country, const std::function<bool(const Banner & banner)> & condition)
    {
        auto cmpUniquePrice = [](const Banner &a, const Banner &b) { return a.price < b.price; };
        std::multiset<Banner, decltype(cmpUniquePrice)> bannersSortedByPrice(cmpUniquePrice);
        
        std::set<decltype(Banner::id)> uniqueIds;
        
        std::vector<Banner> retVal;
        retVal.reserve(numAdPlaces);
        
        for (const auto & someBanner : banners) {
            auto foundIt = std::find_if(someBanner.validCountries.begin(), someBanner.validCountries.end(), [&country](const std::string & state) -> bool {
                return country == state;
            });
            if (!((foundIt != someBanner.validCountries.end()) || someBanner.validCountries.empty()))
            {
                continue;
            }
            //satisfy condition for country
            
            if (uniqueIds.find(someBanner.id) != uniqueIds.end())
            {
                continue;
            }
            //satisfy condition for id
            
            const bool shouldBeAdded = condition ? condition(someBanner) : true;
            if (shouldBeAdded) {
                uniqueIds.insert(someBanner.id);
                bannersSortedByPrice.insert(someBanner);
            }
        }
        
        std::random_device rd;
        std::mt19937 mt(rd());
        
        while (!bannersSortedByPrice.empty() && (retVal.size() < numAdPlaces)) {
            const auto count = bannersSortedByPrice.count(*bannersSortedByPrice.begin());
            if (count > 1) {
                std::uniform_int_distribution<std::size_t> dist(0, count-1);
                const auto randIndex = dist(mt);
                for (std::size_t i = 0; i < count; ++i)
                {
                    if (i == randIndex)
                    {
                        retVal.push_back(*bannersSortedByPrice.begin());
                        bannersSortedByPrice.erase(*bannersSortedByPrice.begin());
                    }
                    
                }
            }
            else
            {
                retVal.push_back(*bannersSortedByPrice.begin());
                bannersSortedByPrice.erase(bannersSortedByPrice.begin());
            }
        }
        
        return retVal;
    }
} // helper namespace
