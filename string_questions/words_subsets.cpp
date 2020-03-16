#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
/*******
We are given two arrays A and B of words.  Each word is a string of lowercase letters.

Now, say that word b is a subset of word a if every letter in b occurs in a, including multiplicity.  For example, "wrr" is a subset of "warrior", but is not a subset of "world".

Now say a word a from A is universal if for every b in B, b is a subset of a. 

Return a list of all universal words in A.  You can return the words in any order.

Example 1:

Input: A = ["amazon","apple","facebook","google","leetcode"], B = ["e","o"]
Output: ["facebook","google","leetcode"]
 ******/

//Observations: You can replace the map's with arrays. Wanted to practice maps
class Solution {
public:
    bool is_universal_string(string A, std::map<int, int> subset_hash) {
        
        for (int i = 0; i < A.size(); i++) {
            int pos = A[i] - 'a';
            if (subset_hash.find(pos) != subset_hash.end()) {
                subset_hash[pos] = subset_hash[pos] - 1;
            }
        }
       
        for (auto v : subset_hash) {
            if (v.second > 0) { 
               return false;
            }
        }
        return true;        
    }
    
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {
        // if every word in B is a substring of 'a', then the word 'a' is a substring.
        /*
        ====================>
        we check for every word of B is in a
            B = [e, o]  a_word = "facebook"
            we can iterate over "facebook" and check if every word of B exists.
                O(len(a)*len(b)*A_length())
        ===========================================>
                
        if we sort each word "abcefkoo"
            find if a subset exists "oo"      "google"                   egloo
                facebook amazon                "gogleo"                  egloo
                                               "goglee"                  egloo  
        "loeo" => "leo" should exists
                  "ecocceo" should exists "ecocceo" ==>create a hash table for this.
        e = 1, o = 1;
         iterate over each word and check count of e is 1 and o is 1; is yes universal.
             e = 1, o = 2; f = 0
                           c = 
                           */ 
       /* std::map<int, int> subset_hash; //maps char to count;
          "lo" "eo"  ==> word count for o should be 1.
          if "oo" "so" == > word count for o should be 2, s should 1.
             sort each one of them 
           ol oe  
        */
        std::map<int, int> subset_hash;
        for (int i = 0; i < B.size(); i++) {
            std::map<int, int> word_map;
            for (int j = 0; j < B[i].size(); j++) {
                int pos = B[i][j] - 'a';
                word_map[pos]++;
            }
            for (auto v: word_map) {
                subset_hash[v.first] = max(subset_hash[v.first], v.second);
            }
        }
        std::vector<string> output;
        
        for (int i = 0; i < A.size(); i++) {
                
            if (is_universal_string(A[i], subset_hash)) {
                output.push_back(A[i]);
            }
        }
        return output;
                
    }
};

int main() {
  std::vector<string> A {
    "amazon","apple",
      "facebook","google",
      "leetcode"};
  std::vector<string> B {"lo","eo"};
  
  std::vector<string> universal_words = wordSubsets(A, B);

}
