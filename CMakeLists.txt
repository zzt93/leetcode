cmake_minimum_required(VERSION 3.6)
project(leetcode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        1-10/atoi.cpp
        1-10/palindromeNum.cpp
        1-10/reverseInt.cpp
        1-10/zigzag.cpp
        11-20/3sumClosest.cpp
        11-20/4sum.cpp
        11-20/container.cpp
        11-20/longestCommonPrefix.cpp
        11-20/phoneNumber.cpp
        11-20/regex.cpp
        11-20/slow4sum.cpp
        21-30/divideTwoIntegers.cpp
        21-30/generateParen.cpp
        21-30/mergeKSortedLists.cpp
        21-30/mergeTwoSortedLists.cpp
        21-30/removeDuplicate.cpp
        21-30/removeElement.cpp
        21-30/reverseNodesInKGroup.cpp
        21-30/slow_strstr.cpp
        21-30/strstr_simple_opt.cpp
        21-30/substringWithConcatenationOfAllWords.cpp
        21-30/swapNodesInPair.cpp
        31-40/combinationSum.cpp
        31-40/combinationSum2.cpp
        31-40/countAndSay.cpp
        31-40/longestValidParentheses.cpp
        31-40/nextPermutation.cpp
        31-40/searchForARange.cpp
        31-40/searchInRotatedSortedArray.cpp
        31-40/searchInsertPosition.cpp
        31-40/sudokuSolver.cpp
        31-40/validSudoku.cpp
        41-50/firstMissingPositive.cpp
        41-50/multiplyString.cpp
        41-50/trappingRainWater.cpp
        41-50/slowWildcardMatching.cpp
        71-80/minimumWindowSubstring.cpp
        81-90/searchInRotatedSortedArray2.cpp
        91-100/reverseList2.cpp
        41-50/wildcardMatching.cpp
        41-50/permutations.cpp
        41-50/jumpGame2.cpp 41-50/slowPermutations2.cpp 41-50/rotateImage.cpp 41-50/anagrams.cpp contest4/integerReplacement.cpp contest4/evaluateDivision.cpp 51-60/WrongNQueens.cpp 51-60/maxSubArray.cpp 51-60/spiralMatrix.cpp 51-60/spiralMatrix2.cpp 51-60/jumpGame.cpp 51-60/mergeIntervals.cpp 51-60/insertInterval.cpp 51-60/lengthOfLastWord.cpp 51-60/permutationSequence.cpp 61-70/rotateList.cpp 61-70/uniquePaths.cpp 61-70/uniquePath2.cpp 61-70/minimumPathSum.cpp 61-70/validNumber.cpp 61-70/plusOne.cpp 61-70/addBinary.cpp 61-70/textJustification.cpp 61-70/sqrtx.cpp 61-70/ClimbStairs.cpp)

add_executable(leetcode ${SOURCE_FILES})
add_executable(a.out 61-70/sqrtx.cpp)