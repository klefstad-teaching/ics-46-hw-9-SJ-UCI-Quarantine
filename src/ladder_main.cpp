#include "ladder.h"

int main() {
	set<string> s;
	load_words(s, "words.txt");
	vector<string> v = generate_word_ladder("work", "play", s);
	for(string& i : v) cout << i << ' ';
	cout << endl;
}
