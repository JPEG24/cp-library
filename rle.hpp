#include <vector>
#include <utility>
#include <string>
using namespace std;

vector<pair<char, int>> RunLengthEncode(const string& s) {
	vector<pair<char,int>> res;
	for (char c : s) {
		if (res.empty() || res.back().first != c) {
			res.emplace_back(c,1);
		} else {
			res.back().second++;
		}
	}
	return res;
}