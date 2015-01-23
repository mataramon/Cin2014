/*
Author: Octavio Gómez Navarro, Jorge Hernández, Internet

Using c++11
*/
#include <iostream>
#include <fstream>
#include <math.h>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <set>
using namespace std;
class Trie {
	public:
		map<char, Trie> children;
		string value;
		bool flag;
		Trie(const string &);
		void add(char);
		string find(const string &);
		void insert(const string &);
		vector<string> all_prefixes();
		vector<string> autocomplete(const string &);
};
Trie::Trie(const string &val="") {
	value = val;
	flag = false;
}
void Trie::add(char c) {
	if (value == "")
		children[c] = Trie(string(1, c));
	else
		children[c] = Trie(value + c);
}
void Trie::insert(const string &word) {
	Trie * node = this;
	for (int i = 0; i < word.length(); i++) {
		const char c = word[i];
		if (node->children.find(c) == node->children.end())
			node->add(c);
		node = &node->children[c];
	}
	node->flag = true;
}
vector<string> Trie::all_prefixes() {
	vector<string> results;
	if (flag)
		results.push_back(value);
	if (children.size()) {
		map<char, Trie>::iterator iter;
		vector<string>::iterator node;
		for(iter = children.begin(); iter != children.end(); iter++) {
			vector<string> nodes = iter->second.all_prefixes();
			results.insert(results.end(), nodes.begin(), nodes.end());
		}
	}
	return results;
}
vector<string> Trie::autocomplete(const string &prefix) {
	Trie * node = this;
	vector<string> results;
	for (int i = 0; i < prefix.length(); i++) {
		const char c = prefix[i];
		if (node->children.find(c) == node->children.end())
			return results;
		else
			node = &node->children[c];
	}
	return node->all_prefixes();
}

void showmsg (string name){
	string line;
	ifstream file;
	file.open(name);
	if (!file.is_open()) {
		cerr<<"\n\tError... no such file or directory (test_data.data)\n"<<endl;
		}
	while (getline(file, line)){
		cout << line << "\n";
	}
	file.close();
}

int main(int argc, char *argv[ ]){
	Trie example;
	example.insert("cat");
	example.insert("dog");
	example.insert("bird");
	example.insert("fish");
	example.insert("turtle");
	example.insert("rabbit");
	example.insert("tiger");
	example.insert("lion");
	example.insert("snake");
	example.insert("rodent");
	example.insert("hamster");
	example.insert("spider");
	example.insert("chameleon");
	example.insert("frog");
	example.insert("pig");
	example.insert("horse");
	example.insert("duck");
	example.insert("lizard");
	example.insert("shark");
	example.insert("chicken");
	example.insert("porcupine");
	example.insert("ferret");
	example.insert("bunnyificus");
	int i;
	vector<string> ListV;
	vector<string> petnames = {"cat", "dog", "bird", "fish", "turtle", "bunny", "tiger", "lion", "snake", "rodent", "hamster", "spider", "chameleon", "frog", "pig", "horse", "duck", "lizard", "shark", "chicken", "porcupine", "ferret", "bunnyficus"};
	string name;
	string resulting;
	cout << "What pet are you looking for? ";
	cin >> name;
	transform(name.begin(), name.end(), name.begin(), ::tolower);
	cout << "\n";
	for(i=0 ;i < petnames.size();i++){
		if(name == petnames[i]){
			cout << "Found " << name << "\n\n";
			showmsg(name);
			return 0;
		}
	}
	ListV = example.autocomplete(name);
	cout << "Is this what you were looking for? \n" << ListV[0] << "\n\n";
	showmsg(ListV[0]);
return 0;
}

