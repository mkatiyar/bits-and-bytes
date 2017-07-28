/* This is a generic template for most of longest substring
 * kind of problems. All of them have the same theme with only
 * the basic logic changed.
 * https://discuss.leetcode.com/topic/30941/here-is-a-10-line-template-that-can-solve-most-substring-problems
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/* Find the length of longest substring which doesn't
 * have any repeated characters.
 */
void longest_sub_without_repeating(string& s)
{
	unordered_map <char, int> M;
	for (int i = 0; i < 255; i++) {
		M[i] = 0;
	}

	int left = 0, maxlen = 0, i = 0, repeat = 0;

	while (i < s.length()) {
		M[s[i]]++;

		if (M[s[i++]] > 1) repeat++;

		while (repeat > 0) {
			M[s[left]]--;
			if (M[s[left++]] == 1) repeat--;
		}

		maxlen = max(maxlen, i - left);
	}


	cout << "Maximum length string without repetition is :" << maxlen;
	return;
}

/* Find the length of longest substring which has 'K'
 * distinct characters.
 */
void longest_sub_with_K_distinct(string &input, int k)
{
	k = max(1, k);

	unordered_map <char, int> M;

	for (int i = 0; i < 255; i++) {
		M[i] = 0;
	}

	int i, left = 0, maxlen = 0, start, distinct = 0;

	for (i = 0; i < input.length(); i++) {
		M[input[i]]++;

		if (M[input[i]] == 1) { /* Found a new char */
			distinct++;
			while (distinct > k) {
				if ((i - left) > maxlen) {
					maxlen = i - left;
					start = left;
				}
				M[input[left]]--;

				/* Check if this was the last distinct element
				 * to go out of window */
				if (M[input[left]] == 0) distinct--;

				left++;
			}
		}
	}

	if (distinct == k) {
		if ((i - left) > maxlen) {
			maxlen = i - left;
			start = left;
		}
	}

	cout << "\nInput string : " << input << endl;
	cout << "Maximum " << k << " distinct character string : " << input.substr(start, maxlen) << endl;
	printf("Starting at index %d of length %d\n", start, maxlen);

	return;
}

string generate_input(int maxlen, int nchars)
{
	nchars = min(nchars, 25);
	nchars = max(1, nchars);

	string result = "";

	while (maxlen--) {
		result += string(1, 1 + 'A' + (random() % nchars));
	}

	return result;
}

int main()
{
	srand(time(NULL));

	int ntests = 1 + random() % 5;

	ntests = max(ntests, 5);

	while (ntests--) {
		string input = generate_input(15, random() % 26);
		longest_sub_with_K_distinct(input, random() % 6);
		longest_sub_without_repeating(input);
		printf("\n");
	}
}
