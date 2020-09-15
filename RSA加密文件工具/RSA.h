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
	DataType _ecryptKey;//加密密钥
	DataType _decryptKey;//解密密钥
	DataType _publicKey;//公共密钥
};
//1.产生素数 
//2.求n 
//3.求f(n) 
//4.求e 1<e<f(n) e和f(n)互质 随机选择
//5.求d e*d%f(n)=1
//(e,n) (d,n)
class RSA
{
public:
	RSA();
	
	void Encrypt(const char* filename, const char* fileout);
	void Decrypt(const char* filename, const char* fileout);

	DataType Encrypt(DataType data, DataType ekey, DataType pkey);//加密过程a^b%n 
	DataType Decrypt(DataType data, DataType dkey, DataType pkey);//解密过程

	void GetKeys();
	Key GetallKey();

	DataType GetPrime();//随机获取一个数
	bool isPrime(DataType data);//判断随机获取的数是否为素数
	bool isPrimeBigInt(DataType data);
	DataType GetPKey(DataType prime1, DataType prime2);//求n=pq
	DataType GetOrla(DataType prime1, DataType prime2);//求欧拉函数f(n)
	DataType GetEKey(DataType orla);//求e
	DataType GetDKey(DataType ekey, DataType orla);//求d e*d%f(n)=1
	DataType GetGCD(DataType data1, DataType data2);//求最大公约数
	DataType exGcd(DataType a, DataType b, DataType& x, DataType& y);

private:
	Key _key;
};