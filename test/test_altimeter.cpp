#include <gtest/gtest.h>
#include "altimeter.h"

TEST(ApogeeDetectionTest, DetectsApogee) {
    int dropCount = 0;
    // Test consecutive drops
    EXPECT_FALSE(detect_apogee(100.0f, 101.0f, &dropCount));
    EXPECT_EQ(dropCount, 1);
    EXPECT_FALSE(detect_apogee(99.0f, 100.0f, &dropCount));
    EXPECT_EQ(dropCount, 2);
    EXPECT_TRUE(detect_apogee(98.0f, 99.0f, &dropCount));
    
    // Test reset on non-drop
    dropCount = 0;
    EXPECT_FALSE(detect_apogee(100.0f, 100.0f, &dropCount));
    EXPECT_EQ(dropCount, 0);
}

TEST(ApogeeDetectionTest, CustomDropCount) {
    int dropCount = 0;
    const int custom_drops = 5;
    // Test with custom required drops
    for (int i = 0; i < custom_drops - 1; i++) {
        EXPECT_FALSE(detect_apogee(100.0f - i, 101.0f - i, &dropCount, custom_drops));
    }
    EXPECT_TRUE(detect_apogee(100.0f - custom_drops, 101.0f - custom_drops, &dropCount, custom_drops));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}