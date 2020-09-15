
#include<iostream>
#include<boost/multiprecision/cpp_int.hpp>
#include"bigint.h"
#include"RSA.h"
using namespace std;

//void test(){
//	Bigint bi;
//	int a = 1024;
//	int b = 345;
//	cout << a * b << endl;
//	cout << bi.mul("1024", "345") << endl;
//
//}

//void test03() {
//	Bigint ci;
//	int a = 2333384;
//	int b = 323452;
//	cout << a - b << endl;
//	cout << ci.sub("2333384", "323452") << endl;
//
//}

//void test04() {
//	Bigint di;
//	int a = 450098;
//	int b = 4507;
//	cout << a / b << endl;
//	cout << a % b << endl;
//	cout << di.dev("450098", "4507").first << endl;
//	cout << di.dev("450098","4507").second << endl;
//}

//void testBoostBigint() {
//	boost::multiprecision::cpp_int ci;
//	ci = 1024;
//	cout << ci << endl;
//
//}

void testRSA() {
	RSA rsa;
	Key key = rsa.GetallKey();
	cout << "(e,n)" << key._ecryptKey << "," << key._publicKey << endl;
	cout << "(d,n)" << key._decryptKey << "," << key._publicKey << endl;
	rsa.Encrypt("test.txt", "test.encrpry.txt");
	rsa.Decrypt("test.encrpry.txt", "test.decrypt.txt");

}

//void testBoostRandom() {
//	boost::random::mt19937 gen(time(NULL));
//	boost::random::uniform_int_distribution<DataType> dist(0, DataType(1) << 1023);
//	for (int i = 0; i < 100; ++i) {
//		DataType num = dist(gen);
//		cout << num << endl;
//	}
//}

int main() {
	//test02();
	//test03();
	//test();
	//test04();
	testRSA();
	//testBoostRandom();
	system("pause");
	return 0;
}