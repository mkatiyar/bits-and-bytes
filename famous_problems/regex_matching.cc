/* Given a string and a pattern, print true or false
 * depending on the given regex criteria.
 *
 * Source : Leetcode
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <vector>

/* The general approach to solving these problems is to only consider
 * the last characters of both the string and the pattern, and "literally"
 * write the conditions mentioned in the problem. See examples below.
 */


/* Regex-1 : https://leetcode.com/problems/regular-expression-matching/description

   Implement regular expression matching with support for '.' and '*'.
'.' Matches any single character.
'*' Matches zero or more of the preceding element.

  At any point of time, let's consider the string as "Match = Sx" and
  "Pattern = Py", where x is
  the last character in original string, S is the remaining prefix, y is the
  last character in pattern, and P is the remaining prefix pattern.

  Following rules follow directly from the given problem statement.

  a) If pattern == "", then it can be a match only if Match == "", otherwise it
     is not a match.
  b) if (x == y) or (y == '.'), then the problem reduces to finding a match
  between S and P.
  c) if (y == '*"), then since it matches zero or more of preceding element,
  problem reduces to :-
         (ci) Match between 'Sx' and 'P' (if character preceding 'y' matched zero characters)
	 (cii) Match between 'S' and 'Py' (if character preceding 'y' matched 'x')
	 ie... (x == (y - 1)) || ((y - 1) == '.'))
	    ** (y - 1) is the character before y.


   Now, just write above conditions and make sure that you fix the values of
   indexes 'i' and 'j' such that code doesn't panic.
 */

void isMatch_reg1(string s, string p)
{
	int ls = s.length(), lp = p.length();
	vector <vector <bool>> dp(ls + 1, vector <bool>(lp + 1, false));

	for (int i = 0; i <= ls; i++) {
		for (int j = 0; j <= lp; j++) {

			/* Case (a) */
			if (j == 0) {
				dp[i][j] = i == 0;
				continue;
			}

			/* Case b */
			if (i > 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '.')) {
				dp[i][j] = dp[i - 1][j - 1 ];
			}

			/* Case c */
			if (j > 1 && p[j - 1] == '*') {
				bool a = dp[i][j - 2];  /* Case ci */

				/* Case cii */
				bool b = (i > 0 &&
					  (s[i - 1] == p[j - 2] ||
					   p[j - 2] == '.')) && dp[i - 1][j];

				dp[i][j] = a || b;
			}
		}
	}

	cout << "String : " << s << endl;
	cout << "Pattern : " << p << endl;
	printf("Match : %s \n", dp[ls][lp] ? "True" : "False");
}
