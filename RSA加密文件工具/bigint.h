#pragma once
#include<string>
using namespace std;
class Bigint {
public:
	Bigint() {}
	Bigint(const string& num);
	Bigint(const int num);
	Bigint operator+(Bigint& b);
	Bigint operator-(Bigint& b);
	Bigint operator*(Bigint& b);
	Bigint operator/(Bigint& b);
	Bigint operator%(Bigint& b);
private:
	string add(string num1, string num2);
	string sub(string num1, string num2);
	string mul(string num1, string num2);
	pair<string,string> dev (string num1, string num2);
	bool less(string& num1, string& num2);
	string _number;

};
