//
//  main.cpp
//  GTests
//
//  Created by roko on 7/22/16.
//  Copyright © 2016 roko. All rights reserved.
//

#include "gtest/gtest.h"
#include "AdFilter.h"

void checkUniqueIds(const std::vector<helper::Banner> & banners)
{
    std::set<decltype(helper::Banner::id)> ids;
    for (const auto & b : banners) {
        ids.insert(b.id);
    }
    ASSERT_EQ(ids.size(), banners.size());
}

void checkUniquePrices(const std::vector<helper::Banner> & banners)
{
    std::set<decltype(helper::Banner::price)> prices;
    for (const auto & b : banners) {
        prices.insert(b.price);
    }
    ASSERT_EQ(prices.size(), banners.size());
}

void checkUniqueIdAndPrices(const std::vector<helper::Banner> & banners)
{
    checkUniqueIds(banners);
    checkUniquePrices(banners);
}

#pragma mark AdFilterTest

class AdFilterTest: public ::testing::Test {
    
public:
    
    AdFilterTest()
    {
        
    }
    const std::vector<helper::Banner> & getBanners() const
    {
        return _banners;
    }
   
protected:
    void SetUp()
    {
        _banners =
        {
            {
                100,// price;
                1,// id;
                {"a", "b", "c"}// validCountries;
            },
            {
                200,// price;
                2,// id;
                {"a", "c"}// validCountries;
            },
            {
                300,// price;
                2,// id;
                {"a"}// validCountries;
            },
            {
                400,// price;
                4,// id;
                {"a", "b", "d"}// validCountries;
            },
            {
                500,// price;
                5,// id;
                {"a", "r", "c"}// validCountries;
            },
            {
                600,// price;
                10,// id;
                {"b", "c"}// validCountries;
            },
            {
                700,// price;
                8,// id;
                {"t", "c"}// validCountries;
            },
            {
                800,// price;
                17,// id;
                {"t"}// validCountries;
            },
            {
                900,// price;
                11,// id;
                {"d", "b"}// validCountries;
            },
            {
                1000,// price;
                20,// id;
                {"d"}// validCountries;
            },
            {
                1100,// price;
                21,// id;
                {"a", "b", "c", "t"}// validCountries;
            },
            {
                1200,// price;
                12,// id;
                {}// validCountries;
            },
            {
                1300,// price;
                13,// id;
                {"b"}// validCountries;
            }
        };
    }
    
    void TearDown()
    {
        _banners.clear();
    }
    
private:
    std::vector<helper::Banner> _banners;
};

TEST_F(AdFilterTest, Test0)
{
    const auto banners = helper::extractBanners(getBanners(), 1, "a");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 1);
}

TEST_F(AdFilterTest, Test1)
{
    const auto banners = helper::extractBanners(getBanners(), 2, "a");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 2);
}

TEST_F(AdFilterTest, Test2)
{
    const auto banners = helper::extractBanners(getBanners(), 3, "a");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 3);
}

TEST_F(AdFilterTest, Test3)
{
    const auto banners = helper::extractBanners(getBanners(), 4, "a");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 4);
}

TEST_F(AdFilterTest, Test4)
{
    const auto banners = helper::extractBanners(getBanners(), 5, "a");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 5);
}

TEST_F(AdFilterTest, Test5)
{
    const auto banners = helper::extractBanners(getBanners(), 6, "a");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 6);
}

TEST_F(AdFilterTest, Test6)
{
    const auto banners = helper::extractBanners(getBanners(), 7, "a");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 6);
}

TEST_F(AdFilterTest, Test7)
{
    const auto banners = helper::extractBanners(getBanners(), 6, "b");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 6);
}

TEST_F(AdFilterTest, TestNewState)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "NewState");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 1);
}

#pragma mark AdFilterEqualPricesTest

class AdFilterEqualPricesTest: public ::testing::Test {
    
public:
    
    AdFilterEqualPricesTest()
    {
        
    }
    const std::vector<helper::Banner> & getBanners() const
    {
        return _banners;
    }
    
protected:
    void SetUp()
    {
        _banners =
        {
            {
                100,// price;
                1,// id;
                {"a", "b", "c"}// validCountries;
            },
            {
                200,// price;
                2,// id;
                {"a", "c"}// validCountries;
            },
            {
                100,// price;
                2,// id;
                {"a"}// validCountries;
            },
            {
                400,// price;
                4,// id;
                {"a", "b", "d"}// validCountries;
            },
            {
                100,// price;
                5,// id;
                {"a", "r", "c"}// validCountries;
            }
        };
    }
    
    void TearDown()
    {
        _banners.clear();
    }
    
private:
    std::vector<helper::Banner> _banners;
};

TEST_F(AdFilterEqualPricesTest, Test0)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "a");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 3);
}

TEST_F(AdFilterEqualPricesTest, Test1)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "c");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 2);
}

TEST_F(AdFilterEqualPricesTest, Test2)
{
    const auto banners = helper::extractBanners(getBanners(), 1, "c");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 1);
}

TEST_F(AdFilterEqualPricesTest, Test3)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "r");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 1);
}

#pragma mark AdFilterPredicatTest

class AdFilterPredicatTest: public ::testing::Test {
    
public:
    
    AdFilterPredicatTest()
    {
        
    }
    const std::vector<helper::Banner> & getBanners() const
    {
        return _banners;
    }
    
protected:
    void SetUp()
    {
        _banners =
        {
            {
                100,// price;
                1,// id;
                {"a", "b", "c"}// validCountries;
            },
            {
                200,// price;
                2,// id;
                {"a", "c"}// validCountries;
            },
            {
                100,// price;
                2,// id;
                {"a"}// validCountries;
            },
            {
                400,// price;
                4,// id;
                {"a", "b", "d"}// validCountries;
            },
            {
                100,// price;
                5,// id;
                {"a", "r", "c"}// validCountries;
            }
        };
    }
    
    void TearDown()
    {
        _banners.clear();
    }
    
private:
    std::vector<helper::Banner> _banners;
};

TEST_F(AdFilterPredicatTest, Test0)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "c", [](const helper::Banner & banner) -> bool {
        return banner.price > 100;
    });
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 1);
}

TEST_F(AdFilterPredicatTest, Test2)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "c", [](const helper::Banner & banner) -> bool {
        return banner.price < 400;
    });
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 2);
}

TEST_F(AdFilterPredicatTest, Test3)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "a", [](const helper::Banner & banner) -> bool {
        return banner.price > 100;
    });
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 2);
}

TEST_F(AdFilterPredicatTest, Test4)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "a", [](const helper::Banner & banner) -> bool {
        return banner.price > 1000;
    });
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 0);
}

#pragma mark AdFilterEmptyStateTest

class AdFilterEmptyStateTest: public ::testing::Test {
    
public:
    
    AdFilterEmptyStateTest()
    {
        
    }
    const std::vector<helper::Banner> & getBanners() const
    {
        return _banners;
    }
    
protected:
    void SetUp()
    {
        _banners =
        {
            {
                200,// price;
                2,// id;
                {}// validCountries;
            },
            {
                300,// price;
                2,// id;
                {}// validCountries;
            }
        };
    }
    
    void TearDown()
    {
        _banners.clear();
    }
    
private:
    std::vector<helper::Banner> _banners;
};

TEST_F(AdFilterEmptyStateTest, Test0)
{
    const auto banners = helper::extractBanners(getBanners(), 10, "cfvd");
    checkUniqueIdAndPrices(banners);
    ASSERT_EQ(banners.size(), 1);
    ASSERT_EQ(banners[0].price, 200);
    ASSERT_EQ(banners[0].id, 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
