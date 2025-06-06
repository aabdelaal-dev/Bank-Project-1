#pragma once 
#include<iostream>
#include <string>
#include <vector>
using namespace std;


namespace str {

	string ReplaceString(string s, string StrToReplace, string ReplaceToStr) {

		short pos = s.find(StrToReplace);

		while (pos != string::npos)
		{
			s.replace(pos, StrToReplace.length(), ReplaceToStr);
			pos = s.find(StrToReplace);
		}
		return s;

	}

	string JoinString(vector <string> vString, string delim) {

		string NewString;

		for (string& s : vString) {

			NewString += s + delim;
		}

		return NewString.substr(0, NewString.length() - delim.length());

	}

	vector <string> SplitString(string s, string delim) {

		string word;
		short pos;
		vector <string> vNames;

		while ((pos = s.find(delim)) != string::npos) {

			word = s.substr(0, pos);
			if (word != "") {
				vNames.push_back(word);
			}
			s.erase(0, pos + delim.length());

		}
		if (s != "") {
			vNames.push_back(s);
		}
		return vNames;

	}

	string ToLowerString(string s) {

		string LowerStr;
		for (char& c : s)
			c = tolower(c);

		return s;
	}

	string MyReplaceString(string s, string StrToReplace, string ReplaceToStr, bool IsMatchCase = 1) {

		vector <string> vString = SplitString(s, " ");
		string FinalString;

		for (string& word : vString)
		{
			if (IsMatchCase && word == StrToReplace) {

				word = ReplaceToStr;
			}
			else if ((!IsMatchCase) && (ToLowerString(word) == ToLowerString(StrToReplace))) {
				word = ReplaceToStr;
			}

		}

		return str::JoinString(vString, " ");

	}

	string EnterString() {
		string s;
		cout << "Please enter Your string ? ";
		getline(cin >> ws, s);
		return s;
	}

	string EnterString(string Message) {
		string s;
		cout << Message;
		getline(cin >> ws, s);
		return s;
	}

	char EnterChar(string Message) {
		char c;
		cout << Message;
		cin >> c;
		return c;
	}
	char EnterChar() {
		char c;
		cin >> c;
		return c;
	}

	string RemoveStringPunc(string s) {
		string S2;
		for (short i = 0; i < s.length(); i++)
		{
			if (!ispunct(s[i])) {
				S2 += s[i];
			}
		}
		return S2;
	}


};
namespace num {

	int ReadNumber() {
		int N;
		cout << "Please Enter Number : ";
		cin >> N;
		return N;

	}

	int ReadNumber(string Message) {
		int N;
		cout << Message;;
		cin >> N;
		return N;

	}

}