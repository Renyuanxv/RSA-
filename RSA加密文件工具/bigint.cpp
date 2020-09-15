
#include<iostream>
#include"bigint.h"
using namespace std;
//������������
Bigint::Bigint(const string& num)
	:_number(num)
{}

Bigint Bigint:: operator+(Bigint& b) {
	string ret= add(_number, b._number);
	return Bigint(ret);
}

Bigint Bigint:: operator-(Bigint& b) {
	string ret = sub(_number, b._number);
	return Bigint(ret);
}

Bigint Bigint:: operator*(Bigint& b) {
	string set = mul(_number, b._number);
	return Bigint(set);
}

Bigint Bigint:: operator/(Bigint& b) {
	pair<string, string> ret = dev(_number, b._number);
	return Bigint(ret.first);
}

Bigint Bigint:: operator%(Bigint& b) {
	pair<string, string> ret = dev(_number, b._number);
	return Bigint(ret.second);	
}


//�ӷ� �ȼ��ٸ���
string Bigint::add(string num1, string num2) {
	int len1 = num1.size();
	int len2 = num2.size();
	int diffNum = abs(len1 - len2);
	int longSize = len1 > len2 ? len1 : len2;
	if (len1 < len2)
		num1.insert(0, diffNum, '0');
	else if (len2 < len1)
		num2.insert(0, diffNum, '0');
	string ret;
	ret.resize(longSize);
	int step = 0;//��λ
	for (int i = num1.size() - 1; i >= 0; --i) {
		ret[i] = (num1[i] - '0') + (num2[i] - '0') +step;
		ret[i] += '0';
		if (ret[i] > '9') {
			ret[i] -= 10;
			step = 1;
		}
		else
			step = 0;
	}
	if (step == 1)
		ret.insert(0, 1, '1');
	return ret;
}

//����
string Bigint::sub(string num1, string num2) {
	int len1 = num1.size();
	int len2 = num2.size();
	int diffNum = abs(len1 - len2);
	int longSize = len1 > len2 ? len1 : len2;
	if (len1 < len2)
		num1.insert(0, diffNum, '0');
	else if (len2 < len1)
		num2.insert(0, diffNum, '0');

	string ret;
	ret.resize(longSize);
	for (int i = num1.size() - 1; i >= 0; --i) {
		//�Ƿ���Ҫ��λ
		if (num1[i] < num2[i]) {
			num1[i] += 10;
			//���¸�λ
			num1[i - 1]--;
		}
		ret[i] = (num1[i] - '0') - (num2[i] - '0');
		ret[i] += '0';
	}
	//ɾ��ǰ��0
	while (ret.size() > 1&&ret[0]=='0')
		ret.erase(0, 1);
	return ret;

}

string Bigint::mul(string num1, string num2){
	//С��*���� num1*num2
	if (num2.size() > num1.size())
		swap(num2, num1);
	string ret = "0";
	for (int i = num2.size() - 1; i >= 0; --i) {
		//��ȡ��ǰ������Ӧ��ֵ
		int curNum = num2[i] - '0';
		int step = 0;
		string temp = num1;
		//������ ��˹���
		for (int j = temp.size() - 1; j >= 0; --j) {
			temp[j] = (temp[j] - '0') * curNum + step;//9*9+9 0~90
			//���½�λֵ
			if (temp[j] > 9) {
				step = temp[j] / 10;
				temp[j] = temp[j] - step * 10;
			}
			else
				step = 0;
			temp[j] += '0';//��ԭ���ַ�
		}
		//�ж��Ƿ���Ҫ��λ
		if (step > 0)
			temp.insert(0, 1, step + '0');
		//����
		temp.append((num2.size() - 1 - i), '0');
		//�ۼӸ��γ˷����
		ret = add(ret, temp);

	}
	return ret;
}

bool Bigint::less(string& num1, string& num2) {
	if (num1.size() < num2.size())
		return true;
	if (num1.size() > num2.size())
		return false;
	//��ͬ
	return num1 < num2;
}

pair<string, string> Bigint::dev(string num1, string num2){
	//��
	string ret;
	//����
	string rem = num1; 
	int diffNum = num1.size() - num2.size();
	num2.append(diffNum, '0'); 
	for (int i = 0; i <= diffNum; ++i) {
		//��¼����ִ�еĴ���
		char count = '0';
		while (true) {
			if (less(rem, num2)) 
				break;
			rem = sub(rem, num2);
			++count;
		}
		ret += count;
		//������С10��
		num2.pop_back();
	}
	//ɾ��ǰ��0
	while (ret.size() > 1 && ret[0] == '0')
		ret.erase(0, 1);
	return make_pair(ret, rem);
}