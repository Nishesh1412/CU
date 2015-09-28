#include<iostream>
#include <string>
using namespace std;
int main () {
	
	string word;
	unsigned int distance, alpha;
	
	cout<<"Please enter a word/string!"<<endl;
	getline(cin, word);
	
	int wordLength = word.length();
	if (wordLength < 1) {
		cout<<"Error 666: Input string/word is empty. Exiting Now...";
		return 0;
		}
		
	cout<<"Enter an integer distance to shift all the string characters"<<endl;
	cin>>distance;
	
	for (int i =0; i < wordLength; i++) {
		alpha = distance % 26 + word[i];
		if (word[i]<= 'z' && word[i] >= 'a'){
			word[i] = (alpha > 'z') ? alpha - 'z' + 'a' - 1: alpha;
		}
	}
	
	cout<< "Your word/ string cipher is:"<<word<<endl;
	return 0;
}
