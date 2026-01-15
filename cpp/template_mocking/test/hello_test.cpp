#include <gtest/gtest.h>

#include "A.h"
#include "impl.h"

class mock {
public:
    std::string getString() {
        return "mocked";
    }
};

TEST(MockTestSuite, MockImpl) {
    UnitA<mock> mocked;
    EXPECT_EQ(mocked.getString(), "mocked");
}

TEST(MockTestSuite, RealImpl) {
    UnitA<impl> implementation;
    EXPECT_EQ(implementation.getString(), "implementation");
}