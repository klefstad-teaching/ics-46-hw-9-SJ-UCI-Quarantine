#include "ladder.h"

int main() {
	set<string> s;
	load_words(s, "src/words.txt");
	vector<string> v = generate_word_ladder("cat", "dog", s);
	for(string& i : v) cout << i << ' ';
	cout << endl;
}
