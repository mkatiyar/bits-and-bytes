/* Generate permutations of a given string
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void helper(string &S, int r, int start,
	     string& partial,
	     vector <string>& result,
	     vector <bool>& chosen) {

	if (partial.length() == r) {
		result.emplace_back(partial);
		return;
	}

	for (int i = 0; i < S.size(); i++) {
		if (chosen[i] == false) {
			chosen[i] = true;
			partial += string(1, S[i]);
			helper(S, r, i + 1, partial, result, chosen);
			partial = partial.substr(0, partial.length() - 1);
			chosen[i] = false;
		}
	}
}

void permuations(string &S, int r)
{
	string partial;
	vector <string> result;
	vector <bool> chosen(S.length(), false);

	helper(S, r, 0, partial, result, chosen);

	cout << "\nTotal permutations : " << result.size() << endl;
	for (auto p : result) {
		cout << p << endl;
	}
}

int main()
{
	string S;
	int n, len;

	cout << "Enter the string and length for permutations :";
	cin >> S >> n;

	len = S.length();

	permuations(S, min(n, len));
}
