#include <gtest/gtest.h>
#include <string>
#include "sbmlsim/SBMLSim.h"
#include "sbmlsim/internal/util/MathUtil.h"
#include "sbmlsim/internal/util/StringUtil.h"

namespace {

  class MathUtilTest : public ::testing::Test{};

  TEST_F(MathUtilTest, containsTargetTrue) {
    std::string s = "z";
    ASTNode* ast = SBML_parseFormula("x^2 + 3 * y + sin(z)");
    ast->reduceToBinary();
    EXPECT_TRUE(MathUtil::containsTarget(ast, s));
  }

  TEST_F(MathUtilTest, containsTargetFalse) {
    std::string s = "si";
    ASTNode* ast = SBML_parseFormula("x^2 + 3 * y + sin(z)");
    ast->reduceToBinary();
    EXPECT_FALSE(MathUtil::containsTarget(ast, s));
  }

  TEST_F(MathUtilTest, containsTargetFalse2) {
    std::string s = "2";
    ASTNode* ast = SBML_parseFormula("x^2 + 3 * y + sin(z)");
    ast->reduceToBinary();
    EXPECT_FALSE(MathUtil::containsTarget(ast, s));
  }

  TEST_F(MathUtilTest, simplifyTest) {
    ASTNode* ast = SBML_parseFormula("((2 + 3 * 5) / 2) * x");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "8.5 * x");
  }

  TEST_F(MathUtilTest, simplifyTest2) {
    ASTNode* ast = SBML_parseFormula("2 * x + (3 * 5 / 2) * y");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "2 * x + 7.5 * y");
  }

  TEST_F(MathUtilTest, simplifyTest3) {
    ASTNode* ast = SBML_parseFormula("x ^ 2 * 2 + x * 3 + 1");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "2 * x^2 + 3 * x + 1");
  }

  TEST_F(MathUtilTest, simplifyTest4) {
    ASTNode* ast = SBML_parseFormula("2 + x");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "x + 2");
  }

  TEST_F(MathUtilTest, simplifyTest5) {
    ASTNode* ast = SBML_parseFormula("2 * x * 3");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "6 * x");
  }

  TEST_F(MathUtilTest, simplifyTest6) {
    ASTNode* ast = SBML_parseFormula("2 * 4 * 5 * x * 3");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "120 * x");
  }

  TEST_F(MathUtilTest, simplifyTest7) {
    ASTNode* ast = SBML_parseFormula("2 + x + 3");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "x + 5");
  }

  TEST_F(MathUtilTest, simplifyTest8) {
    ASTNode* ast = SBML_parseFormula("2 + 4 + x + 3");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "x + 9");
  }

  TEST_F(MathUtilTest, simplifyTest9) {
    ASTNode* ast = SBML_parseFormula("2 * sin(x) * 3 + y + 7 + 4 + z");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "6 * sin(x) + y + 11 + z");
  }

  TEST_F(MathUtilTest, simplifyTestPower) {
    ASTNode* ast = SBML_parseFormula("3 * x ^ 1 + 4");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "3 * x + 4");
  }

  TEST_F(MathUtilTest, simplifyTestPower2) {
    ASTNode* ast = SBML_parseFormula("3 * x ^ 0 + 4");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "7");
  }

  TEST_F(MathUtilTest, simplifyTestPower3) {
    ASTNode* ast = SBML_parseFormula("(2 * 1 * pow(x, 2 - 1) + 0 * x + 3 * 1 + 0)");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_EQ(s, "2 * x + 3");
  }

  TEST_F(MathUtilTest, simplifyTestFalse) {
    ASTNode* ast = SBML_parseFormula("2 * x + (3 * 5 / 2) * y");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_NE(s, "2 * x + 7 * y");
  }

  TEST_F(MathUtilTest, simplifyTestOneArg) {
    ASTNode* ast = SBML_parseFormula("sin(2 * x * 3)");
    ast->reduceToBinary();
    ASTNode* simp = MathUtil::simplify(ast);
    std::string s = SBML_formulaToString(simp);
    EXPECT_NE(s, "sin(6 * x)");
  }

  TEST_F(MathUtilTest, differentiateTestAdd) {
    ASTNode* ast = SBML_parseFormula("2 * x + x ^ 2 + y ^ 2");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "2 * x + 2");
  }

  TEST_F(MathUtilTest, differentiateTestSub) {
    ASTNode* ast = SBML_parseFormula("2 * x - x ^ 2 - y ^ 2");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "2 - 2 * x");
  }

  TEST_F(MathUtilTest, differentiateTestConst) {
    ASTNode* ast = SBML_parseFormula("x * 13 + 11 * y");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "13");
  }

  TEST_F(MathUtilTest, differentiateTestMul) {
    ASTNode* ast = SBML_parseFormula("x ^ 2 * x ^ 3");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "2 * x * x^3 + x^2 * 3 * x^2");
  }

  TEST_F(MathUtilTest, differentiateTestDiv) {
    ASTNode* ast = SBML_parseFormula("1 / x");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "-1 / x^2");
  }

  TEST_F(MathUtilTest, differentiateTestDiv2) {
    ASTNode* ast = SBML_parseFormula("3 * x^2 / (x - 5)^2");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "(6 * x * (x - 5)^2 - 3 * x^2 * 2 * (x - 5)) / (x - 5)^4");
  }

  TEST_F(MathUtilTest, differentiateTestSin) {
    ASTNode* ast = SBML_parseFormula("sin(x^2+3*x+4)");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "(2 * x + 3) * cos(x^2 + 3 * x + 4)");
  }

  TEST_F(MathUtilTest, differentiateTestCos) {
    ASTNode* ast = SBML_parseFormula("cos(x^2+3*x+4)");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "-1 * (2 * x + 3) * sin(x^2 + 3 * x + 4)");
  }

  TEST_F(MathUtilTest, differentiateTestTan) {
    ASTNode* ast = SBML_parseFormula("tan(x^2+3*x+4)");
    ast->reduceToBinary();
    ASTNode* diff = MathUtil::simplify(MathUtil::differentiate(ast, "x"));
    std::string s = SBML_formulaToString(diff);
    EXPECT_EQ(s, "(2 * x + 3) * sec(x^2 + 3 * x + 4)^2");
  }

} // namespace
