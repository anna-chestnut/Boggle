#include "boggle.h"
#include <vector>
#include <string>
#include <iostream>		// cout

using namespace std;


	c_boggle::c_boggle() {

		root = new TrieNode();
	}

	void c_boggle::buildTrie(const vector<string>& all_words) {

		for (unsigned int i = 0; i < all_words.size(); i++) {

			string word = all_words[i];
			TrieNode* curr = root;

			for (unsigned int j = 0; j < word.size(); j++) {

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

	void c_boggle::dfs(unsigned int r, unsigned int c, TrieNode* p,vector<vector<char>>& matrix, vector<string>& ans) {

		
		char currchar = matrix[r][c];
		if (currchar == '1' || !p->children[currchar - 'a']) return;
		printf("char: %c\n", currchar);
		cout << "p word: " << p->word << " \n" << endl;
		p = p->children[currchar - 'a'];
		cout << "p children word: " << p->word << " \n" << endl;
		if (p->word != "") {
			ans.push_back(p->word);
			p->word = "";
		}

		matrix[r][c] = '1';
		if (r + 1 < matrix.size()) {
			dfs(r + 1, c, p, matrix, ans);
			if (c + 1 < matrix[0].size()) dfs(r+1, c + 1, p, matrix, ans);
			if (c != 0) dfs(r+1, c - 1, p, matrix, ans);
		}
		if (r != 0) {
			dfs(r - 1, c, p, matrix, ans);
			if (c + 1 < matrix[0].size()) dfs(r - 1, c + 1, p, matrix, ans);
			if (c != 0) dfs(r - 1, c - 1, p, matrix, ans);
		}
		if(c+1 < matrix[0].size()) dfs(r, c+1, p, matrix, ans);
		if(c!=0) dfs(r, c-1, p, matrix, ans);
		matrix[r][c] = currchar;

	}

	/// Find all words on the specified board, returning a list of them.
	vector<string> c_boggle::solve_board(
		int board_width,								// width of the board, e.g. 4 for a retail Boggle game //column
		int board_height,								// height of the board, e.g. 4 for a retail Boggle game //row = [1 2 3]
		const std::string& board_letters)				// board_width*board_height characters in row-major order
	{
		//printf("string: %s", board_letters);
		vector<string> ans;

		//construct a matirx
		vector<vector<char>> matrix;
		vector<char> tmp;

		for (unsigned int i = 0; i < board_letters.size(); i++) {

			tmp.push_back(board_letters[i]);
			//std::cout << board_letters[i-1] << ", " << std::endl;
			if ((i+1) % board_width == 0) {
				matrix.push_back(tmp);
				//printf("string: %v", tmp);
				for (int j = 0; j < tmp.size(); j++)
					std::cout << tmp[j] << ' ';
				//std::cout << tmp  << ", " << std::endl;
				std::cout << " // " << std::endl;
				tmp.clear();

			}
			
		}

		//search for every solution
		for (unsigned int r = 0; r < board_height; r++) {
			for (unsigned int c = 0; c < board_width; c++) {
				//std::cout << matrix[r][c] << ", " << std::endl;
				dfs(r, c, root, matrix, ans);
			}
		}

		return ans;
	}
