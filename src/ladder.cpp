#include "ladder.h"

void error(string word1, string word2, string msg) {
	cerr << msg << ' ' << word1 << ' ' << word2 << endl;
}

bool min(int a, int b) { return a > b ? a : b; }
bool edit_distance_within(const string& s1, const string& s2, int d) {
	int a = s1.size(), b = s2.size();
	vector<vector<int>> dp(a + 1, vector<int>(b + 1, -1));
	for(int i = 0; i < a; ++i) {
		for(int j = 0; j < b; ++j) {
			int& c = dp[i + 1][j + 1];
			c = min(dp[i - 1][j], dp[i][j - 1]) + 1;
			if(s1[i] == s2[j]) c = min(c, dp[i - 1][j - 1]);
		}
	}
	return dp[a][b] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
	return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
	queue<vector<string>> q;
	q.push({begin_word});
	set<string> visited;
	visited.insert(begin_word);
	while(!q.empty()) {
		vector<string> v = q.front();
		q.pop();
		for(const string& s : word_list) {
			if(is_adjacent(v.back(), s) && !visited.count(s)) {
				vector<string> v2 = v;
				v2.push_back(s);
				if(s == end_word) return v2;
				q.push(v2);
			}
		}
	}
	return {};
}

void load_words(set<string>& word_list, const string& name) {
	fstream reader(name, ios::in);
	string s;
	reader >> s;
	for(; !reader.fail(); reader >> s) word_list.insert(s);	
	reader.close();
}

void print_word_ladder(const vector<string>& ladder) {
	for(const string& s : ladder) cout << s << ' ';
	cout << endl;
}

void verify_word_ladder() {
}


