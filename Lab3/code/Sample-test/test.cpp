#include "pch.h"

class GraphTest : public ::testing::Test {
protected:
    GraphTest() : graph({ "ape", "apple", "peg", "leg", "egg", "ape"}) {}
    void SetUp() override {
        std::cout << "SetUp runs before each case.\n" ;
    }

    Graph graph;
};

TEST_F(GraphTest, QueryBridgeWords_Success) {
    std::vector<std::string> result = graph.queryBridgeWords("ape", "peg");
    std::vector<std::string> expected = { "apple" };
    EXPECT_EQ(result, expected);
}

TEST_F(GraphTest, QueryBridgeWords_NoBridgeWords) {
    std::vector<std::string> result = graph.queryBridgeWords("apple", "egg");
    EXPECT_TRUE(result.empty());
}

TEST_F(GraphTest, QueryBridgeWords_WordNotFound) {
    std::vector<std::string> result = graph.queryBridgeWords("banana", "egg");
    EXPECT_TRUE(result.empty());
}

TEST_F(GraphTest, CalcShortestPath_BothWordsExistWithPath) {
    std::vector<std::string> result = graph.calcShortestPath("ape", "peg");
    std::vector<std::string> expected = { "ape", "apple", "peg" };
    EXPECT_EQ(result, expected);
}

TEST_F(GraphTest, CalcShortestPath_BothWordsExistNoPath) {
    std::vector<std::string> result = graph.calcShortestPath("ape", "leg");
    std::vector<std::string> expected = { "ape", "apple", "peg", "leg" };
    EXPECT_EQ(result, expected);
}

TEST_F(GraphTest, CalcShortestPath_StartWordNotFound) {
    std::vector<std::string> result = graph.calcShortestPath("nonexistent", "peg");
    EXPECT_TRUE(result.empty());
}

TEST_F(GraphTest, CalcShortestPath_EndWordNotFound) {
    std::vector<std::string> result = graph.calcShortestPath("ape", "nonexistent");
    EXPECT_TRUE(result.empty());
}

TEST_F(GraphTest, CalcShortestPath_SelfToSelf) {
    std::vector<std::string> result = graph.calcShortestPath("apple", "apple");
    std::vector<std::string> expected = { "apple", "peg", "leg", "egg", "ape"};
    EXPECT_EQ(result, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}