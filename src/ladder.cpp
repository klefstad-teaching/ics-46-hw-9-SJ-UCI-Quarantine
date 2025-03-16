#include "ladder.h"

void error(string word1, string word2, string msg) {
	cerr << msg << ' ' << word1 << ' ' << word2 << endl;
}

inline int min(int a, int b) { return a < b ? a : b; }
inline int abs(int a) { return a < 0 ? -a : a; }
bool edit_distance_within(const string& s1, const string& s2, int d) {
	int a = s1.size(), b = s2.size();
	if(abs(a - b) > d) return false;
	vector<vector<int>> dp(a + 1, vector<int>(b + 1));
	for(int i = 0; i <= a; ++i) dp[i][0] = i;
	for(int i = 0; i <= b; ++i) dp[0][i] = i;
	for(int i = 0; i < a; ++i) {
		for(int j = 0; j < b; ++j) {
			int& c = dp[i + 1][j + 1];
			c = min(dp[i][j + 1], dp[i + 1][j]) + 1;
			c = min(c, dp[i][j] + (s1[i] == s2[j] ? 0 : 1));
		}
	}
	return dp[a][b] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
	int s1 = word1.size(), s2 = word2.size();
	if(s1 == s2) {
		bool flag = false;
		for(int i = 0; i < s1; ++i) {
			if(word1[i] != word2[i]) {
				if(flag) return false;
				else flag = true;
			}
		}
		return flag;
	}else if(abs(s1 - s2) == 1) {
		int i = 0, j = 0, m = min(s1, s2);
		while(i < m && word1[i] == word2[i]) ++i;
		while(j < m && word1[s1 - 1 - j] == word2[s2 - 1 - j]) ++j;
		return i + j >= m; 
	}
	return false;
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
	queue<vector<string>> q;
	q.push({begin_word});
	set<string> visited;
	visited.insert(begin_word);
	while(!q.empty()) {
		vector<string> v = move(q.front());
		q.pop();
		for(const string& s : word_list) {
			if(is_adjacent(v.back(), s) && !visited.count(s)) {
				visited.insert(s);
				vector<string> v2 = v;
				v2.push_back(s);
				if(s == end_word) return v2;
				q.push(move(v2));
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
	if(ladder.empty()) cout << "No word ladder found." << endl;
	else {
		cout << "Word ladder found: ";
		for(const string& s : ladder) cout << s << ' ';
		cout << endl;
	}
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "src/words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}

