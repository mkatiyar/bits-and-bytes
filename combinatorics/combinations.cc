/* Generate combinations of a given string
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void helper(string &S, int r, int start,
	     string& partial,
	     vector <string>& result) {

	if (partial.length() == r) {
		result.emplace_back(partial);
		return;
	}

	for (int i = start; i < S.size(); i++) {
		partial += string(1, S[i]);
		helper(S, r, i + 1, partial, result);
		partial = partial.substr(0, partial.length() - 1);
	}
}

void combinations(string &S, int r)
{
	string partial;
	vector <string> result;

	helper(S, r, 0, partial, result);

	cout << "\nTotal combinations : " << result.size() << endl;
	for (auto p : result) {
		cout << p << endl;
	}
}

int main()
{
	string S;
	int n, len;

	cout << "Enter the string and length for combinations :";
	cin >> S >> n;

	len = S.length();

	combinations(S, min(n, len));
}
