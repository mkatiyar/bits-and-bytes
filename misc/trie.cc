/* Case insensitive implementation of a Trie.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <iostream>
using namespace std;

class TrieNode {
public:
	bool isword;
	struct TrieNode* child[26];
	TrieNode() {
		for (int i = 0; i <  26; i++) {
			child[i] = NULL;
		}
		isword = false;
	}
};

TrieNode *groot; /* Global Trienode root */

/* Recursive function to add a node in trie */
void add_word_helper(TrieNode *root, string S)
{
	if (S == "") {
		root->isword = true;
		return;
	}

	int idx = S[0] - 'a';
	if (root->child[idx] == NULL) {
		root->child[idx] = new TrieNode();
	}

	add_word_helper(root->child[idx], S.substr(1));
}

void add_word(string S)
{
	add_word_helper(groot, S);
}

/* Recursive function to search a node in trie */
bool search_word_helper(TrieNode *root, string S)
{
	if (root == NULL) {
		return false;
	}

	if (S == "") {
		return root->isword;
	}

	int idx = S[0] - 'a';
	return search_word_helper(root->child[idx], S.substr(1));
}

bool search_word(string S)
{
	return search_word_helper(groot, S);
}

/* Only lower case words allowed */
bool validate(string S)
{
	for (auto x : S) {
		if (x < 'a' || x > 'z') {
			cout << "Error ... word is not all lowercase alphabet.\n";
			return false;
		}
	}
	return true;
}

int main()
{
	/* Initialize the global root */
	groot = new TrieNode();

	string s;
	char choice;

	while (1) {
		printf("Add / search /exit string : (a/s/x ?) ");
		cin >> choice;

		switch(choice) {
			case 'a' : {
					   cout << "Enter word : ";
					   cin >> s;
					   if (validate(s)) {
						   add_word(s);
					   }
					   break;
				   }
			case 's' : {
					   cout << "Enter word : ";
					   cin >> s;
					   cout << "Word \"" << s << "\"";
					   if (search_word(s)) {
						   cout << " found.\n";
					   } else {
						   cout << " not found.\n";
					   }
					   break;
				   }
			case 'x': exit(0);
		}
	}
}
