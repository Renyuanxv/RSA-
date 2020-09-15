#pragma once
#include<iostream>
#include<string>
#include<ctime>
#include<fstream>
#include<cmath>
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/multiprecision/random.hpp>
#include<boost/multiprecision/miller_rabin.hpp>
using namespace std;
//typedef long DataType;
#define NUMBER 128
typedef boost::multiprecision::int1024_t DataType;
namespace brdm = boost::random;
struct Key
{
	DataType _ecryptKey;//������Կ
	DataType _decryptKey;//������Կ
	DataType _publicKey;//������Կ
};
//1.�������� 
//2.��n 
//3.��f(n) 
//4.��e 1<e<f(n) e��f(n)���� ���ѡ��
//5.��d e*d%f(n)=1
//(e,n) (d,n)
class RSA
{
public:
	RSA();
	
	void Encrypt(const char* filename, const char* fileout);
	void Decrypt(const char* filename, const char* fileout);

	DataType Encrypt(DataType data, DataType ekey, DataType pkey);//���ܹ���a^b%n 
	DataType Decrypt(DataType data, DataType dkey, DataType pkey);//���ܹ���

	void GetKeys();
	Key GetallKey();

	DataType GetPrime();//�����ȡһ����
	bool isPrime(DataType data);//�ж������ȡ�����Ƿ�Ϊ����
	bool isPrimeBigInt(DataType data);
	DataType GetPKey(DataType prime1, DataType prime2);//��n=pq
	DataType GetOrla(DataType prime1, DataType prime2);//��ŷ������f(n)
	DataType GetEKey(DataType orla);//��e
	DataType GetDKey(DataType ekey, DataType orla);//��d e*d%f(n)=1
	DataType GetGCD(DataType data1, DataType data2);//�����Լ��
	DataType exGcd(DataType a, DataType b, DataType& x, DataType& y);

private:
	Key _key;
};