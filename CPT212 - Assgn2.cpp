// Boyer Moore Algorithm

#include <bits/stdc++.h>
using namespace std;
#define NO_OF_CHARS 256

// Preprocessing function for bad character heuristic
void badCharHeur(string str, int size, int badchar[NO_OF_CHARS])
{
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

// Pattern searching function for bad character heuristic
vector<int> search(string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();
    vector<int> occurrences;

    int badchar[NO_OF_CHARS];

    // To fill bad character in array for the given pattern
    badCharHeur(pat, m, badchar);
    
    // Shift of the pattern with respect to text
    int s = 0; 
    
    while (s <= (n - m)){
        int j = m - 1;

        // loop for reducing index j of pattern until characters of pattern and text are matching at shift s
        while (j >= 0 && pat[j] == txt[s + j]){
        	j--;
		}
        
        // Index j become -1 when pattern is at current shift
        if (j < 0){
        	
        	// Pattern is shift so that the next character in text aligns with the last occurrence in pattern
            occurrences.push_back(s);
            
            // For the case when pattern occurs at the end of text
            s += (s + m < n) ? m - badchar[txt[s + m]] : 1;
        }else{
            // Pattern is shift so that the bad character in text aligns with the last occurrence in pattern
            // Max function to get a positive shift.
            s += max(1, j - badchar[txt[s + j]]);
        }
    }

    return occurrences;
}

int main()
{
    string txt, pat;
    
    cout << "Enter the text: ";
    getline(cin, txt);
    
    // validation for the pattern
    while (true) {
        cout << "Enter the pattern: ";
        getline(cin, pat);

        if (pat.size() <= txt.size()) {
            vector<int> result = search(txt, pat);
            if (!result.empty()) {
                cout << "\nPattern is found at positions: ";
                for (int pos : result) {
                    cout << pos << " ";
                }
                cout << endl;
                break;
            } else {
                cout << "\nPattern is not found in text. Please enter it again." << endl;
            }
        } else {
            cout << "\nPattern length should not be greater or less than text length. Please enter it again." << endl;
        }
    }

    return 0;
}


