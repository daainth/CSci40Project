// C++ program to encode a word to a Pig Latin. 
#include <iostream>
using namespace std; 
  
bool isVowel(char c) 
{ 
    return (c == 'A' || c == 'E' || c == 'I' ||  
            c == 'O' || c == 'U' || c == 'a' ||  
            c == 'e' || c == 'i' || c == 'o' || 
            c == 'u'); 
} 
  
string pigLatin(string s) 
{ 
    // the index of the first vowel is stored. 
    int len = s.length(); 
    int index = -1; 
    for (int i = 0; i < len; i++) { 
        if (isVowel(s[i])) { 
            index = i; 
            break; 
        } 
    } 
  
    // Pig Latin is possible only if vowels 
    // is present 
    if (index == -1) 
        return "-1"; 
  
    // Take all characters after index (including 
    // index). Append all characters which are before 
    // index. Finally append "ay" 
    return s.substr(index) + s.substr(0, index) + "ay"; 
} 
  
// Driver code 
int main() 
{ 
    string help;
    cin>>help;
    string str = pigLatin(help); 
    if (str == "-1") 
        cout << "No vowels found. Pig Latin not possible"; 
    else
        cout << str; 
} 
https://codereview.stackexchange.com/questions/91048/c-pig-latin-program
