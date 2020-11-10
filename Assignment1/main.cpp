//Marks - 196/200
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>
#include <functional>
using namespace std;

string multiply(string I1, string I2,int B){
    string result; int carry=0;
	for(int i=I1.size()-1;i >=0 ;i--){
		int mul = (I1[i]-'0')*(I2[0]-'0')+carry;
		if(mul>=B){
				result.append(to_string(mul%B));
				carry = mul/B;
			}
			else{
				result.append(to_string(mul));
				carry=0;
			}
	}
	if(carry!=0) result.append(to_string(carry));
	std::reverse(result.begin(), result.end());
	return result;
}

string kartsuba_add(string I1,string I2,int B){
	if(I1.size()>I2.size()){
		int diff = I1.size()-I2.size();
		I2 = std::string(diff,'0').append(I2);
	}
	if(I2.size()>I1.size()){
		int diff = I2.size()-I1.size();
		I1 = std::string(diff,'0').append(I1);
	}
	int rem,carry=0;
	string sum;
    for(int i=I1.size()-1;i >=0 ;i--){
		int s = (I1[i]-'0') + (I2[i]-'0')+carry;
		if(s>=B){
			rem = s%B;
			carry= s/B;
			sum= sum+ to_string(rem);
		}
		else{
			sum = sum+to_string(s);
			carry=0;
		}

	}
	if(carry!= 0){
		sum = sum+ to_string(carry);
	}
	std::reverse(sum.begin(),sum.end());
	return sum;
}
string kartsuba_sub(string I1,string I2,int B){
	if(I1.size()>I2.size()){
		int diff = I1.size()-I2.size();
		I2 = std::string(diff,'0').append(I2);
	}
	if(I2.size()>I1.size()){
		int diff = I2.size()-I1.size();
		I1 = std::string(diff,'0').append(I1);
	}
	int c=0;int d;
	string diff;
	for(int i=I1.size()-1;i >=0 ;i--){
		int i1 = I1[i]-'0'-c;
		int i2 = I2[i]-'0';
		if(i2>i1){
			d=i1+B-i2;
			c=1;
			diff = diff+to_string(d);
		}
		else{
			d=i1-i2;
			c=0;
			diff= diff+to_string(d);
		}
	}
	std::reverse(diff.begin(), diff.end());
	return diff;

}

string kartsuba(string I1, string I2, int B){
		//mul
		if(I1.size()>I2.size()){
			int diff = I1.size()-I2.size();
			I2 = std::string(diff,'0').append(I2);
		}
		if(I2.size()>I1.size()){
			int diff = I2.size()-I1.size();
			I1 = std::string(diff,'0').append(I1);
		}
	    if(I1.size()==1) return multiply(I1,I2,B);
	   	int k =  I1.size()/2;												//finding size/2
	   	std::reverse(I2.begin(),I2.end());									// splitting string based on value of k
		std::reverse(I1.begin(),I1.end());
		std::string a0_s = I1.substr(0, k);
		std::string a1_s = I1.substr(k,I1.length()-a0_s.length());
		std::string b0_s = I2.substr(0, k);
		std::string b1_s = I2.substr(k, I2.length()-b0_s.length());
		std::reverse(a0_s.begin(),a0_s.end());
		std::reverse(a1_s.begin(),a1_s.end());
		std::reverse(b0_s.begin(),b0_s.end());
		std::reverse(b1_s.begin(),b1_s.end());
		string part1,part2,part3;
		if(a1_s.size()==1)
			part1 = multiply(a1_s, b1_s,B);
		else
			part1 = kartsuba(a1_s, b1_s, B);
		if(a0_s.size()==1)
			part3 =multiply(a0_s, b0_s,B);
		else
			part3 = kartsuba(a0_s, b0_s,B);
		string part2_mul = kartsuba(kartsuba_add(a1_s,a0_s,B),kartsuba_add(b1_s, b0_s,B),B);
		string part2_add = kartsuba_add(part1, part3,B);
		part2 = kartsuba_sub(part2_mul,part2_add,B);

		//padding zeros
		std::reverse(part1.begin(),part1.end());
		std::reverse(part2.begin(),part2.end());
		part1 = std::string(2*k,'0').append(part1);
		part2 = std::string(k,'0').append(part2);
		std::reverse(part1.begin(),part1.end());
		std::reverse(part2.begin(),part2.end());
		string result = kartsuba_add(kartsuba_add(part1, part2,B), part3,B);
		result.erase(0,result.find_first_not_of('0'));
		return result;

}

//divide 
int compare(string I1,string I2){
	unsigned int i=0,flag=0;
	while(flag==0 && i<=I1.size()-1){
		int I1_bit = I1[i]-'0';
		int I2_bit = I2[i]-'0';
		if(I1.size()<I2.size()) flag=1;
		else if (I1.size()> I2.size()) flag=2;
		else if(I1_bit < I2_bit) flag =1;
		else if(I1_bit > I2_bit ) flag=2;
		else if(flag==0 && i== I1.size()-1) flag=3;
		i++;
	}
	return flag;
}

string divide(string I1,string I2, int B){
	string quotient,multi;
	I1.erase(0,I1.find_first_not_of('0'));
	   if(I2.size()>I1.size()){
		   quotient="0";
	   }
	   else if (I2.size()==I1.size()){
		   int flag = compare(I1, I2);
		   if(flag==1) quotient="0";
		   else if(flag == 3) quotient = "1";
		   else if(flag == 2){
			   int q = (I1[0]-'0')/(I2[0]-'0');
			   multi = multiply(I2, to_string(q), B);
			   int flag1 = compare(I1, multi);
			   if(flag1==1) quotient.append(to_string(q-1));
			   else quotient.append(to_string(q));
		   }
	   }
	   else{
		   unsigned int i=0, j=0,diff_append=0,flag=0, c=0,flag1=0,q,dont;string diff;
		   for(i=0;i<=I1.size()-1;i=i+c){
			   j=i;c=0,dont=0;
			   diff_append = I2.size()-diff.size();
			   while(diff_append!=0 && j<I1.size()){
				   if(c>0 && i!=0){ 
				   		quotient.push_back('0');
				  	}
				  		diff.push_back(I1[j]);
				   		j++; diff_append--;c++;
					
			   }
			   flag= compare(diff, I2);
			   if(flag==1){
				   if(j<I1.size()){
					   diff.push_back(I1[j]);
					   if(c>0 && i!=0) quotient.push_back('0');
					   c++;

					}
				   else{
					   quotient.append("0");
					   dont =1;
				   }
			   }else if(flag==3) {
				   quotient.append("1");
				   diff="";
			   }
			   if((flag==2 || c!=0) && flag!=3 && dont==0){
				   q=B;int m=1; flag1=0;
				   while(flag1==0 || flag1==1){
					   q = B-m;
					   multi= multiply(I2, to_string(q), B);
					   flag1= compare(diff, multi);
					   m++;
				   }
				   quotient.append(to_string(q));
				   diff = kartsuba_sub(diff, multi, B);
				   diff.erase(0,diff.find_first_not_of('0'));
				}
		   }
	   }
	   return quotient;
}

int main()
{
    char largechars[205];
    cin.getline(largechars, 205);
    std::vector<char*> v;
    char* chars_array = strtok(largechars, " ");
    while(chars_array)
    {
        v.push_back(chars_array);
        chars_array = strtok(NULL, " ");
    }
    string I1= v[0];
    string I2=v[1];
    string base =v[2];
    int B = std::stoi(base);
	
	string sum = kartsuba_add(I1, I2, B);
   	string muliplication =kartsuba(I1, I2, B);
   	string quotient = divide(I1,I2,B);
    cout<< sum << " " << muliplication << " " << quotient <<endl;
    
}