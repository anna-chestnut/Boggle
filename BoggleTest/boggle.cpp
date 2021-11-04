#include "boggle.h"
#include <vector>
#include <string>
#include <iostream>		// cout

using namespace std;


	c_boggle::c_boggle() {

		root = new TrieNode();
	}

	void c_boggle::buildTrie(const vector<string>& all_words) {

		for ( int i = 0; i < all_words.size(); i++) {

			string word = all_words[i];
			TrieNode* curr = root;

			for ( int j = 0; j < word.size(); j++) {

				char c = word[j] - 'a';
				if (curr->children[c] == nullptr) {
					curr->children[c] = new TrieNode();
				}
				curr = curr->children[c];
			}
			curr->word = word;
			cout << "word: " << word << " \n" << endl;
		}
	}

	/// Prior to solving any board, configure the legal words.
	void c_boggle::set_legal_words( const vector<string>& all_words)		// alphabetically-sorted array of legal words
	{
		buildTrie(all_words);
	}

	void c_boggle::dfs(int r, int c, TrieNode* p,vector<vector<char>>& matrix, vector<string>& ans) {

		if (r < 0 || r >= matrix.size() || c < 0 || c >= matrix[0].size()) return;

		char currchar = matrix[r][c];
		if (currchar == '1' || !p->children[currchar - 'a']) return;

		p = p->children[currchar - 'a'];

		if (p->word != "") {
			ans.push_back(p->word);
			p->word = "";
		}

		matrix[r][c] = '1';

		dfs(r + 1, c, p, matrix, ans);
		dfs(r + 1, c + 1, p, matrix, ans);
		dfs(r + 1, c - 1, p, matrix, ans);
		dfs(r - 1, c, p, matrix, ans);
		dfs(r - 1, c + 1, p, matrix, ans);
		dfs(r - 1, c - 1, p, matrix, ans);
		dfs(r, c - 1, p, matrix, ans);
		dfs(r, c + 1, p, matrix, ans);
		
		matrix[r][c] = currchar;

	}

	/// Find all words on the specified board, returning a list of them.
	vector<string> c_boggle::solve_board(
		int board_width,								// width of the board, e.g. 4 for a retail Boggle game //column
		int board_height,								// height of the board, e.g. 4 for a retail Boggle game //row = [1 2 3]
		const std::string& board_letters)				// board_width*board_height characters in row-major order
	{
		vector<string> ans;

		//construct a matirx
		vector<vector<char>> matrix;
		vector<char> tmp;

		for (int i = 0; i < board_letters.size(); i++) {

			tmp.push_back(board_letters[i]);

			if ((i+1) % board_width == 0) {
				matrix.push_back(tmp);

				for (int j = 0; j < tmp.size(); j++)
					std::cout << tmp[j] << ' ';

				tmp.clear();

			}
			
		}

		//search for every solution
		for (int r = 0; r < board_height; r++) {
			for (int c = 0; c < board_width; c++) {

				dfs(r, c, root, matrix, ans);
			}
		}

		return ans;
	}
