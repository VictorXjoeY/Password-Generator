#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

#define MIN_LENGTH 10
#define MAX_LENGTH 32

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

string generate(vector<char> const& characters, int n){
	string s;

	while (n > 0){
		s.push_back(characters[uniform_int_distribution<int>(0, characters.size() - 1)(rng)]);
		n--;
	}

	return s;
}

int main(int argc, char *argv[]){
	int n, l, r, min_lowercase, min_uppercase, min_digits, min_symbols;
	vector<char> lowercase{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	vector<char> uppercase{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	vector<char> digits{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	vector<char> symbols{'!', '?', '@', '#', '$'};
	vector<char> characters;
	string password;

	// Initializing.
	characters.insert(characters.end(), lowercase.begin(), lowercase.end());
	characters.insert(characters.end(), uppercase.begin(), uppercase.end());
	characters.insert(characters.end(), digits.begin(), digits.end());
	characters.insert(characters.end(), symbols.begin(), symbols.end());

	if (argc == 2 and string(argv[1]) == "strong"){
		min_lowercase = min_uppercase = min_digits = min_symbols = 1;
		n = MIN_LENGTH;
	}
	else{
		// Reading constrains.
		printf("Password Length Range [l, r]: ");
		scanf("%d %d", &l, &r);
		assert(1 <= l and l <= r and r <= MAX_LENGTH);
		l = max(l, MIN_LENGTH);
		r = max(r, l);

		printf("Minimum Lowercase (a-z): ");
		scanf("%d", &min_lowercase);
		assert(0 <= min_lowercase and min_lowercase <= MAX_LENGTH);

		printf("Minimum Uppercase (A-Z): ");
		scanf("%d", &min_uppercase);
		assert(0 <= min_uppercase and min_uppercase <= MAX_LENGTH);

		printf("Minimum Digits (0-9): ");
		scanf("%d", &min_digits);
		assert(0 <= min_digits and min_digits <= MAX_LENGTH);

		printf("Minimum Symbols (!?@#$): ");
		scanf("%d", &min_symbols);
		assert(0 <= min_symbols and min_symbols <= MAX_LENGTH);

		n = max(l, min_lowercase + min_uppercase + min_digits + min_symbols);
		assert(l <= n and n <= r);
	}

	// Generating minimum requirements.
	password += generate(lowercase, min_lowercase);
	password += generate(uppercase, min_uppercase);
	password += generate(digits, min_digits);
	password += generate(symbols, min_symbols);

	// Generating remaining password length.
	password += generate(characters, n - password.size());

	// Shuffling the password.
	shuffle(password.begin(), password.end(), rng);

	// Printing resulting password.
	printf("%s\n", password.c_str());

	return 0;
}