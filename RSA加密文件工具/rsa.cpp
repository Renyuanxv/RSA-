#include<iostream>
#include<Time.h>
#include<math.h>
#include<fstream>
#include"RSA.h"

using namespace std;

RSA::RSA() {
	GetKeys();
}

void RSA::Encrypt(const char* filename, const char* fileout){
	std::ifstream fin(filename,std::ifstream::binary);
	std::ofstream fout(fileout,std::ifstream::binary);
	if (!fin.is_open()) {
		perror("input file open failed!");
		return;
	}
	char* buffer = new char[NUMBER];
	DataType* bufferout = new DataType[NUMBER];
	while (!fin.eof()) {
		fin.read(buffer, NUMBER);
		long curnum = fin.gcount();
		for (int i = 0; i < curnum; i++) {
			bufferout[i] = Encrypt((DataType)buffer[i], _key._ecryptKey, _key._publicKey);
		}
		fout.write((char*)bufferout, curnum * sizeof(DataType));
	}
	//delete[] buffer;
	//delete[] bufferout;

	fin.close();
	fout.close();
}

void RSA::Decrypt(const char* filename, const char* fileout) {
	ifstream fin(filename, ifstream::binary);
	ofstream fout(fileout, ofstream::binary);
	if (!fin.is_open()) {
		perror("file open failed!");
		return;
	}
	DataType* buffer = new DataType[NUMBER];
	char* bufferout = new char[NUMBER];
	while (!fin.eof()) {
		fin.read((char*)buffer, NUMBER * sizeof(DataType));
		int num = fin.gcount();
		num /= sizeof(DataType);
		for (int i = 0; i < num; ++i) {
			bufferout[i] = (char)Decrypt(buffer[i],_key._decryptKey,_key._publicKey);
		}
		fout.write(bufferout, num);
	}
	//delete[] buffer;
	//delete[] bufferout;

	fout.close();
	fin.close();
}

void RSA::GetKeys() {
	DataType prime1 = GetPrime();
	DataType prime2 = GetPrime();
	while (prime1 == prime2) {
		prime2 = GetPrime();
	}
	DataType orla = GetOrla(prime1, prime2);
	_key._publicKey = GetPKey(prime1, prime2);
	_key._ecryptKey = GetEKey(orla);
	_key._decryptKey = GetDKey(_key._ecryptKey, orla);

}

Key RSA::GetallKey() {
	return _key;
}


//�����ȡһ����
DataType RSA::GetPrime(){
	cout<<"grtprime()"<<endl;
	brdm::mt19937 gen(time(NULL));
	brdm::uniform_int_distribution<DataType> dist(0, DataType(1) << 256);

	DataType prime;
	//srand(time(NULL));
	while (true) {
		prime = dist(gen); 
		cout << "Bigint Random:" <<prime << endl;
		if (isPrimeBigInt(prime))
			break;
	}
	return prime;
}

//�ж������ȡ�����Ƿ�Ϊ����
bool RSA::isPrime(DataType data) {//�жϴ�2~sqrt(data)�����ܲ��ܱ�����
	cout << "isPrime" << endl;

	if (data<= 0)
		return false;
	for (int i = 2; i <= sqrt(data); ++i) {
		if (data % i == 0)
			return false;
	}
	cout << "isPrime finish!" << endl;
	return true;
}

bool RSA::isPrimeBigInt(DataType data)
{
	brdm::mt11213b gen(time(NULL));
	if (miller_rabin_test(data, 25, gen))
	{
		if (miller_rabin_test((data - 1) / 2, 25, gen));
		{
			return true;
		}
	}
	return false;
}

//��n=pq
DataType RSA::GetPKey(DataType prime1, DataType prime2) {
	return prime1 * prime2;
}

//��ŷ������f(n)
DataType RSA::GetOrla(DataType prime1, DataType prime2) {
	return (prime1 - 1) * (prime2 - 1);
}

//�������Կe�� 1<e<f(n)
DataType RSA::GetEKey(DataType orla) {
	brdm::mt19937 gen(time(NULL));
	brdm::uniform_int_distribution<DataType> dist(2, orla);

	DataType ekey;
	while (true) {
		ekey = dist(gen);
		if (GetGCD(ekey,orla)==1)//���������Լ��Ϊ1 ����
			return ekey;
	}
}

//�������Կd��e*d%f(n)=1
DataType RSA::GetDKey(DataType ekey, DataType orla) {
	DataType x = 0, y = 0;
	exGcd(ekey, orla, x, y);
	//�任���ý�����Կ��һ���Ƚ�С����ֵ(��չ��ŷ����ö���)
	return (x % orla + orla) % orla;
}

//�����Լ��
/*շת�ദ����
a, b--->b, a% b--->a& b, a% b % (a% b)
cΪa, b���Լ��
a = kc, b = mc
a % b = rΪ����
a = b + r;
kc = mc + r;
r = (k - m)c;*/

DataType RSA::GetGCD(DataType data1, DataType data2) {
	DataType residual;
	while (residual = data1 % data2) {
		data1 = data2;
		data2 = residual;
	}
	return data2; 

}

DataType RSA::exGcd(DataType a, DataType b, DataType& x, DataType& y) {
	if (b == 0){
		x = 1;
		y = 0;
		return a;
	}
	DataType gcd = exGcd(b, a % b, x, y);
	DataType x1 = x, y1 = y;
	x = y1;
	y = x1 - a / b * y1;
	return gcd;

}
//���ܹ���a^b%n 
DataType RSA::Encrypt(DataType data, DataType ekey, DataType pkey){
	//pow�������
	/*return (DataType)pow(data, ekey) % pkey;*/

	//i:0.....���һλ
	DataType Ai = data;
	DataType msgE = 1;
	while (ekey) {
		if (ekey & 1)
			msgE = (msgE * Ai) % pkey;
		ekey >>= 1;
		Ai = (Ai * Ai) % pkey;

	}
	return msgE;
}

//���ܹ���
DataType RSA::Decrypt(DataType data, DataType dkey, DataType pkey) {
	return Encrypt(data, dkey, pkey);
}