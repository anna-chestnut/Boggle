// Engineering Coding Test Boggle Stub.
// Copyright Bungie Inc. 2020.

#ifndef __BOGGLE_H__
#define __BOGGLE_H__
#pragma once

// ---------- includes

#include <vector>
#include <string>

// An empty default implementation.
struct TrieNode {

	TrieNode* children[26];
	std::string word;

	TrieNode() : word("") {
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}
};

class c_boggle
{
	
public:
	c_boggle();
	void buildTrie(const std::vector<std::string>&);
	/// Prior to solving any board, configure the legal words.
	void set_legal_words(const std::vector<std::string>&);		// alphabetically-sorted array of legal words

	void dfs(int, int, TrieNode*, std::vector<std::vector<char>>&, std::vector<std::string>&);

	/// Find all words on the specified board, returning a list of them.
	std::vector<std::string> solve_board(
		int,								// width of the board, e.g. 4 for a retail Boggle game
		int,								// height of the board, e.g. 4 for a retail Boggle game
		const std::string&);				// board_width*board_height characters in row-major order
private:
	TrieNode* root;

};

#endif __BOGGLE_H__
