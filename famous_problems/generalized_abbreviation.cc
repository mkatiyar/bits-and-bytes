/* Generate abbreviations of a given word.
 * http://buttercola.blogspot.com/2016/01/leetcode-generalized-abbreviation.html
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

string convert(int n, string& word)
{
	int count = 0;
	int l = word.length();
	string ret = "";
	for (int i = 0; i < word.length(); i++) {
		if (((1 << i) & n) == 0) {
			if (count) {
				ret = string(1, count + '0') + ret;
			}
			ret = string(1, word[l - 1 - i]) + ret;
			count = 0;
		} else {
			count++;
		}
	}

	if (count) {
		ret = string(1, count + '0') + ret;
	}
	return ret;
}

void generate(string &word)
{
	int l = word.length();
	vector <string> result;

	for (int i = 0; i < pow(2, l); i++) {
		result.emplace_back(convert(i, word));
	}

	printf("[");
	for (auto r : result) {
		cout << r << " ";
	}
	printf("]\n");
}

int main()
{
	string str;
	cout << "Enter the word : ";
	cin >> str;
	generate(str);
	return 0;
}
