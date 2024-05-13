//Jordan Flores
//CECS 325-01 Prog 6 - BigInt class (arbitrarily large integers)
//Due 5/8/2024
//I certify that this program is my own original work. I did not copy any part of this program from any other source, I further certify that I typed each and every line of code in this program.


#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>
#include <iomanip>

using namespace std;

class BigInt{
  private:
    vector<char> v;//store the digits of large number in reverse order

    BigInt fiboHelper(BigInt n, BigInt a = 0, BigInt b = 1) { //helper for fibonacci recursion
      if (n == 0)
        return a;
      else if (n == 1)
        return b;
      else
        return fiboHelper(n - 1, b, a + b);
    }

  public:
    BigInt(){ //default constructor
      // v.push_back(0);
    } 

    BigInt(int num){
      if (num == 0)
        v.push_back(0);
      else{
        while (num != 0){
          v.push_back(num % 10);
          num /= 10;
        }
      }
    }

    BigInt(string str){ 
      for (int i = str.length() - 1; i >= 0; --i){
        if (isdigit(str[i]))
        v.push_back(str[i]- '0');
      }
    }

    BigInt operator+ (BigInt num){ // add to bigInt nums
      BigInt results;
      int carry = 0;
      int i = 0;
      while(i < v.size() || i < num.v.size() || carry !=0){
        if(i < v.size()) carry += v[i];
        if(i < num.v.size()) carry += num.v[i];
        results.v.push_back(carry % 10);
        carry /= 10;
        ++i;
      }

      return results;
    }

    BigInt operator - (BigInt num){ //subtract one bigInt from another
      BigInt results;
      int borrow = 0;
      for(int i = 0; i < v.size(); ++i){
        char sub = v[i] - borrow;
        if (i < num.v.size()) sub -= num.v[i];
        if(sub < 0){
          sub += 10;
          borrow = 1;
        }
        else
        {
          borrow = 0;
        }
        results.v.push_back(sub);
      }
      int i = results.size() - 1;
      while (results.v[i] == 0 && i > 0) {
        results.v.pop_back();
        i--;
      }
      return results;
    }

    BigInt operator - (int num){
       BigInt n(num);
       return (*this) - n;
    }


    BigInt operator*(BigInt num){
      BigInt results;
      results.v.resize(v.size() + num.v.size(), 0);
      for(int i=0; i < v.size(); ++i){
        int carry = 0;
        for(int j = 0; j < num.v.size() || carry; ++j){
          long long cur = results.v[i + j]+ v[i]* 1ll * (j < num.v.size() ? num.v[j]: 0) + carry;
          results.v[i + j] = cur % 10;
          carry = cur / 10;
        }
      }

      while(results.v.size()> 1 && results.v.back() == 0){
        results.v.pop_back();
      }
      return results;
    }

    BigInt operator/(BigInt num){
      BigInt quotientDigit;
      BigInt remainder = *this;
      if(num == BigInt(0)){
        throw runtime_error("Division by zero");
      }
        while (remainder >=num){
          quotientDigit = quotientDigit + BigInt(1);
          remainder = remainder - num;
      }
      return quotientDigit;
    }

    BigInt operator% (const BigInt& num)const{
    if (num == BigInt(0)){
      throw runtime_error("Division by zero");
    }

    BigInt quotientDigit;
    BigInt remainder = *this;

    while (remainder >= num) {
      remainder = remainder - num;
  }
    return remainder;
}

    BigInt operator++(int){	//increment
      BigInt temp = *this;
      *this = *this + 1;
      return temp;
    }

    BigInt operator++ (){
      *this = *this + 1;
      return *this;
    }

    bool operator == (const BigInt& num) const{
      if (v.size() != num.v.size()){
        return false;
      }
      for (size_t i = 0; i < v.size(); ++i){
        if (v[i]!= num.v[i]){
          return false;
        }
      }
      return true;
    }

    bool operator <= (const BigInt& num) const{
      if(v.size() != num.v.size()) {
        return v.size() < num.v.size();
      }
      for(int i = v.size() - 1; i >=0; --i){
        if(v[i] != num.v[i]){
          return v[i] < num.v[i];
        }
      }
      return true;
    }
    bool operator >= (const BigInt& num) const {
      if (v.size() != num.v.size()) {
        return v.size() > num.v.size();
      }
      for (int i = v.size() - 1; i >= 0; --i) {
        if (v[i] != num.v[i]) {
          return v[i] > num.v[i];
        }
      }
      return true;
    }


    BigInt operator[](int index){
      if(index >= 0 && index < v.size())
        return v[index];
      else
        return 0;
    }		

    void print()const{
      for(int i = v.size()-1; i >= 0; --i){
        cout << int(v[i]);
      }
    }

    int size() const{
      return v.size();
    }

    BigInt fibo(){
      return fiboHelper(*this);
    }

    BigInt fact() {
      BigInt result = 1;
      for(BigInt i=1; i <= *this; ++i){
        result = result * i;
      }
      return result;
    }

    friend ostream & operator<<(ostream & out, const BigInt & bigInt){
      if(bigInt.size()<= 12){
        bigInt.print();
      }
      else{
        out << int(bigInt.v[bigInt.size() - 1]) << '.';
        for(int i = bigInt.size()-2; i >= bigInt.size() - 7; --i){
          out << int(bigInt.v[i]);
        }
        out << 'e' << bigInt.size()-1;
      }
      return out;
    }

    friend BigInt operator+(int num, const BigInt & bigInt)
    {
      return BigInt(num) + bigInt;
    }
};


void testUnit()
{
  int space = 10;
  cout << "\nTestUnit:\n"<<flush;
  system("whoami");
  system("date");
  // initialize variables
  BigInt n1(25);
  BigInt s1("25");
  BigInt n2(1234);
  BigInt s2("1234");
  BigInt n3(n2);
  BigInt fibo(12345);
  BigInt fact(50);
  BigInt imax = INT_MAX;
  BigInt big("9223372036854775807");
  // display variables
  cout << "n1(int) :"<<setw(space)<<n1<<endl;
  
  cout << "s1(str) :"<<setw(space)<<s1<<endl;
  cout << "n2(int) :"<<setw(space)<<n2<<endl;
  cout << "s2(str) :"<<setw(space)<<s2<<endl;
  cout << "n3(n2) :"<<setw(space)<<n3<<endl;
  cout << "fibo(12345):"<<setw(space)<<fibo<<endl;
  cout << "fact(50) :"<<setw(space)<<fact<<endl;
  cout << "imax :"<<setw(space)<<imax<<endl;
  cout << "big :"<<setw(space)<<big<<endl;
  cout << "big.print(): "; big.print(); cout << endl;
  cout << n2 << "/"<< n1<< " = "<< n2/n1 <<" rem "<<n2%n1<<endl;
  cout << "fibo("<<fibo<<") = "<<fibo.fibo() << endl;
  cout << "fact("<<fact<<") = "<<fact.fact() << endl;
  cout << "10 + n1 = " << 10+n1 << endl;
  cout << "n1 + 10 = " << n1+10 << endl;
  cout << "(n1 == s1)? --> "<<((n1==s1)?"true":"false")<<endl;
  cout << "n1++ = ? --> before:"<<n1++<<" after:"<<n1<<endl;
  cout << "++s1 = ? --> before:"<<++s1<<" after:"<<s1<<endl;
  cout << "s2 * big = ? --> "<< s2 * big<<endl;
  cout << "big * s2 = ? --> "<< big * s2<<endl;
}

int main(){
  testUnit();
  return 0;
}
