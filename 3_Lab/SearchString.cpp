#include <string>
#include<string.h>

# define NO_OF_CHARS 256

using namespace std;

  // Fills lps[] for given patttern pat[0..M-1]
  void +computeLPSArray(char* pat, int M, int* lps)
  {
      // length of the previous longest prefix suffix
      int len = 0;

      lps[0] = 0;

      // lps[i] for i = 1 to M-1
      int i = 1;
      while (i < M)
      {
          if (pat[i] == pat[len])
          {
              len++;
              lps[i] = len;
              i++;
          }
          else
          {
              if (len != 0)
              {
                  len = lps[len - 1];

              }
              else
              {
                  lps[i] = 0;
                  i++;
              }
          }
      }
  }

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
    bool founded = false;
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N)
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            founded = true;
            cout << "Found pattern at index " << (i - j) << endl;
            j = lps[j - 1];
        }

            // mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    if (!founded)
    {
        cout << "There is no pattern at string";
    }
}

void badCharHeuristic( string str, int size,
                       int badchar[NO_OF_CHARS])
{
    int i;

    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int) str[i]] = i;
}

void BM( string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int s = 0;
    while(s <= (n - m))
    {
        int j = m - 1;

        while(j >= 0 && pat[j] == txt[s + j])
            j--;

        if (j < 0)
        {
            cout << "pattern occurs at shift = " <<  s << endl;

            s += (s + m < n)? m-badchar[txt[s + m]] : 1;
        }

        else
            s += max(1, j - badchar[txt[s + j]]);
    }
}