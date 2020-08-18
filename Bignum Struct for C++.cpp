/*
Bignum Struct c++
Writter : Nguyễn Bảo Trấn
Nation: Viet Nam
Date : 01/04/2020 11:39 PM
Last Edited : 17/07/2020 11:00 PM
*/
#include <bits/stdc++.h>
#include <conio.h>

#define base 1000000000
#define base_digits 9

using namespace std;

int max(int a, int b) {
	return a > b ? a : b;
}
struct BigNum {
	vector <int> Number;
	friend int max(int a, int b);
	void convert(const string& s) {
		int pos = 0;
		for (int i = (int)s.size() - 1; i >= pos; i -= base_digits) {
			int x = 0;
			for (int j = (int)max(pos, i - base_digits + 1); j <= i; j++)
				x = x * 10 + s[j] - '0';
			Number.push_back(x);
		}
	}
	friend istream& operator >> (istream& in, BigNum& a) {
		string s;
		in >> s;
		cin.ignore();
		a.convert(s);
		return in;
	}
	friend ostream& operator << (ostream& out, const BigNum& a) {
		out << (a.Number.empty() ? 0 : a.Number.back());
		for (int i = (int)a.Number.size() - 2; i >= 0; --i)
			out << setw(base_digits) << setfill('0') << a.Number[i];
		return out;
	}
	void operator = (long long v) {
		for (; v > 0; v /= base)
			this->Number.push_back(v % base);
	}
	void operator = (const string& s) {			//for number super large in string
		this->convert(s);
	}
	void trim() {
		while (!Number.empty() && Number.back() == 0)
			Number.pop_back();
	}
	int compare(const BigNum& a, const BigNum& b) const {
		int size_of_a = (int)a.Number.size(), size_of_b = (int)b.Number.size();
		if (size_of_a != size_of_b)
			return size_of_a > size_of_b ? 1 : -1;
		for (int i = size_of_a - 1; i >= 0; i--)
			if (a.Number[i] != b.Number[i])
				return a.Number[i] > b.Number[i] ? 1 : -1;
		return 0;
	}
	bool operator < (const BigNum& b) const {
		return compare(*this, b) == -1;
	}
	bool operator > (const BigNum& b) const {
		return compare(*this, b) == 1;
	}
	bool operator == (const BigNum& b) const {
		return compare(*this, b) == 0;
	}
	bool operator != (const BigNum& b) const {
		return compare(*this, b) != 0;
	}
	bool operator <= (const BigNum& b) const {
		int tmp = compare(*this, b);
		return tmp == 0 || tmp == -1;
	}
	bool operator >= (const BigNum& b) const {
		int tmp = compare(*this, b);
		return tmp == 0 || tmp == 1;
	}
	BigNum operator + (const BigNum& b) {
		BigNum Result;
		Result = *this;
		int size_of_Result = (int)this->Number.size(), size_of_b = (int)b.Number.size(), maxsize = (int)max(size_of_Result, size_of_b) + 1, carry = 0;
		Result.Number.resize(maxsize);
		for (int i = 0; i < maxsize; i++) {
			Result.Number[i] += carry + (i < size_of_b ? b.Number[i] : 0);
			carry = Result.Number[i] >= base;
			if (carry)
				Result.Number[i] -= base;
		}
		Result.trim();
		return Result;
	}
	BigNum operator + (long long v) {
		BigNum c, Result;
		c = v, Result = *this;
		return Result + c;
	}
	BigNum operator - (const BigNum& b) {
		BigNum Result;
		Result = *this;
		int size_of_Result = (int)this->Number.size();
		for (int i = 0, carry = 0; i < size_of_Result; i++) {
			Result.Number[i] -= carry + (i < (int)b.Number.size() ? b.Number[i] : 0);
			carry = Result.Number[i] < 0;
			if (carry)
				Result.Number[i] += base;
		}
		Result.trim();
		return Result;
	}
	BigNum operator - (long long v) {
		BigNum c, Result;
		c = v, Result = *this;
		return Result - c;
	}
	BigNum operator * (const BigNum& b) {
		BigNum Result;
		Result.Number.resize(this->Number.size() + b.Number.size());
		for (register auto i = b.Number.begin(), endb = b.Number.end(); i != endb; ++i) {
			if (*i == 0)
				continue;
			long long carry = 0;
			register auto location = Result.Number.begin() + (i - b.Number.begin());
			for (register auto j = this->Number.begin(), enda = this->Number.end(); j != enda; ++j, ++location) {
				carry += (long long)(*j) * (long long)(*i) + (long long)(*location);
				*(location) = carry % base;
				carry /= base;
			}
			if (carry) *(location) += (int)carry;
		}
		Result.trim();
		return Result;
	}
	BigNum operator * (long long v) {
		BigNum c, Result;
		c = v, Result = *this;
		return Result * c;
	}
	BigNum operator / (long long v) {
		BigNum Result;
		Result = *this;
		long long carry = 0;
		int size_of_Result = (int)this->Number.size();
		for (int i = size_of_Result - 1; i >= 0; i--) {
			carry = carry * base + Result.Number[i];
			Result.Number[i] = int(carry / v);
			carry %= v;
		}
		Result.trim();
		return Result;
	}
	BigNum operator % (int v) {
		BigNum c, Result;
		c = v, Result = *this;
		Result = Result - ((Result / v) * c);
		Result.trim();
		return Result;
	}
};

BigNum giaithua(int n) {
	BigNum N;
	N = 1;
	for (int i = 1; i <= n; i++)
		N = N * i;
	return N;
}

int main()
{
	BigNum a, b, c;
	a = "99999999999";
	b = "999999999999";
	c = a * b;
	cout << c;
	do
		cout << "\nPress any key to continue ";
	while (_getch() == 0);
	return 0;
}