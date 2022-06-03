// Copyright (c) Vector Informatik GmbH. All rights reserved.

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <unordered_set>

#include "DataMessageDatatypeUtils.hpp"

namespace {

using namespace testing;

using namespace ib::sim::data;

class PubSubMatchingTest : public ::testing::Test
{
protected:
    PubSubMatchingTest() {}
};

TEST_F(PubSubMatchingTest, match_mediatype)
{
    std::string mediaTypePub{"A"};
    std::string mediaTypeSub{"A"};
    EXPECT_EQ(MatchMediaType(mediaTypeSub, mediaTypePub), true); // same string, match

    mediaTypeSub = "";
    EXPECT_EQ(MatchMediaType(mediaTypeSub, mediaTypePub), true); // empty subscriber mediaType = wildcard, match

    mediaTypeSub = "B";
    EXPECT_EQ(MatchMediaType(mediaTypeSub, mediaTypePub), false); // different strings, no match

    mediaTypePub = "";
    EXPECT_EQ(MatchMediaType(mediaTypeSub, mediaTypePub), false); // empty publisher mediaType != wildcard, no match
}

TEST_F(PubSubMatchingTest, match_labels)
{
    std::map<std::string, std::string> innerSet{};
    std::map<std::string, std::string> outerSet{{"KeyA", "ValA"}, {"KeyB", "ValB"}, {"KeyC", "ValC"}};
    EXPECT_EQ(MatchLabels(innerSet, outerSet), true); // Empty innerSet, match

    innerSet = {{"KeyA", "ValA"}};
    outerSet = {{"KeyA", "ValA"}};
    EXPECT_EQ(MatchLabels(innerSet, outerSet), true); // Same key+value pair, match

    innerSet = {{"KeyA", "ValA"}, {"KeyB", "ValB"}, {"KeyC", "ValC"}};
    outerSet = {{"KeyA", "ValA"}, {"KeyB", "ValB"}, {"KeyC", "ValC"}};
    EXPECT_EQ(MatchLabels(innerSet, outerSet), true); // Same 3 key+value pairs, match

    innerSet = {{"KeyC", ""}};
    outerSet = {{"KeyC", "ValC"}};
    EXPECT_EQ(MatchLabels(innerSet, outerSet), true); // Same key+empty value, match

    innerSet = {{"KeyA", "ValA"}};
    outerSet = {{"KeyA", "ValA"}, {"KeyB", "ValB"}};
    EXPECT_EQ(MatchLabels(innerSet, outerSet), true); // All labels of inner set in outer set, match

    innerSet = {{"KeyA", "ValA"}, {"KeyB", "ValB"}};
    outerSet = {{"KeyA", "ValA"}};
    EXPECT_EQ(MatchLabels(innerSet, outerSet), false); // More labels in inner set than outer set, no match

    innerSet = {{"KeyA", "X"}};
    outerSet = {{"KeyA", "ValA"}};
    EXPECT_EQ(MatchLabels(innerSet, outerSet), false); // Wrong value, no match

    innerSet = {{"X", "ValA"}};
    outerSet = {{"KeyA", "ValA"}};
    EXPECT_EQ(MatchLabels(innerSet, outerSet), false); // Wrong key, no match
}

TEST_F(PubSubMatchingTest, announced_sources_same_labels_different_order)
{
    std::map<std::string, std::string> labels1{{"K1", "V1"}, {"K2", "V2"}};
    std::map<std::string, std::string> labels2{{"K2", "V2"}, {"K1", "V1"}};
    EXPECT_EQ(labels1, labels2);

    std::unordered_set<SourceInfo, SourceInfo::HashFunction> announced;
    announced.emplace(SourceInfo{"M", labels1});
    announced.emplace(SourceInfo{"M", labels2}); // Is same, no emplace
    EXPECT_EQ(announced.size(), 1);
}

TEST_F(PubSubMatchingTest, announced_sources_different_labels)
{
    std::map<std::string, std::string> labels1{{"K1", "V1"}};
    std::map<std::string, std::string> labels2{{"K2", "V2"}};

    std::unordered_set<SourceInfo, SourceInfo::HashFunction> announced;
    announced.emplace(SourceInfo{"M", labels1});
    announced.emplace(SourceInfo{"M", labels2});
    EXPECT_EQ(announced.size(), 2);
}

TEST_F(PubSubMatchingTest, announced_sources_empty_labels)
{
    std::map<std::string, std::string> labels1{};
    std::map<std::string, std::string> labels2{};

    std::unordered_set<SourceInfo, SourceInfo::HashFunction> announced;
    announced.emplace(SourceInfo{"M", labels1});
    announced.emplace(SourceInfo{"M", labels2}); // Is same, no emplace
    EXPECT_EQ(announced.size(), 1);
}

TEST_F(PubSubMatchingTest, announced_sources_different_mediaype)
{
    std::map<std::string, std::string> labels1{{"K1", "V1"}};
    std::map<std::string, std::string> labels2{{"K1", "V1"}};

    std::unordered_set<SourceInfo, SourceInfo::HashFunction> announced;
    announced.emplace(SourceInfo{"M1", labels1});
    announced.emplace(SourceInfo{"M2", labels2});
    EXPECT_EQ(announced.size(), 2);
}


} // anonymous namespace
