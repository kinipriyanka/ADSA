//Marks-100/100
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

string alphabets = "abcdefghijklmnopqrstuvwxyz";
int isEmpty = 0;
struct HashTable
{
	std::vector<char> key;
	std::vector<string> value;
	std::vector<string> status;
	
	int search(HashTable*, int, string, char);
	int searchKey(HashTable*, int, string,char);
	HashTable* insertValue(HashTable*, string);
	void printHashtable(HashTable*);
	HashTable* deleteValue(HashTable*, string);
};

int HashTable::search(HashTable* hashtable,int i,string value,char decide){
	for(unsigned int j=i+1;j<hashtable->key.size();j++){
		if(hashtable->status[j] == "empty" && decide == 'A'){
			return j;
		}
		else if(hashtable->status[j] != "empty" && hashtable->value[j] == value){
			if(decide == 'A')
				return -1;
			else 
				return j;
		}
	}
	for (int j = 0; j < i; j++){
		if(hashtable->status[j] == "empty" && decide == 'A'){
			return j;
		}
		else if(hashtable->status[j] != "empty" && hashtable->value[j] == value){
			if(decide == 'A')
				return -1;
			else 
				return j;
		}		
	}
	return -1;
}

int HashTable::searchKey(HashTable* hashtable, int i,string value, char decide){
	if(hashtable->status[i] == "empty"){
		if(decide == 'A')
			return i;
		else
			return -1;
	}
	else if(hashtable->status[i] != "empty" && hashtable->value[i]== value){
		if(decide == 'A')
			return -1;
		else
			return i;
	}
	else{
		return search(hashtable,i,value,decide);
	}
}

HashTable* HashTable::insertValue(HashTable* hashtable, string value){
	int search = 26; unsigned int loop=0;
	char key = value.at(value.length()-1);
	if(hashtable == NULL){
		hashtable = new HashTable();
		for(unsigned int i=0; i<alphabets.size();i++){
			hashtable->key.push_back(alphabets[i]);
			hashtable->status.push_back("empty");
			hashtable->value.push_back(" ");
		}
	}
	while((search<0 || search>25) && loop<hashtable->key.size()){
		if(key == hashtable->key[loop]){
			search = searchKey(hashtable,loop,value,'A');
		}
		loop++;
	}
	if(search!=-1){
		hashtable->value[search] = value;
		hashtable->status[search] = "occupied";
	}
	return hashtable;
}

HashTable* HashTable::deleteValue(HashTable* hashtable,string value){
	int search = 26; unsigned int loop =0;
	if(hashtable == NULL)
		return hashtable;
	else{
		char key = value.at(value.length()-1);
		while((search<0 || search>25) && loop<hashtable->key.size()){
			if(key == hashtable->key[loop]){
				search = searchKey(hashtable,loop,value,'D');
			}
			loop++;
		}
		if(search!=-1){
			hashtable->value[search] = " ";
			hashtable->status[search] = "empty";
		}
	}
	return hashtable;
}

void HashTable::printHashtable(HashTable* hashtable){
	if(hashtable!=NULL){
		for(unsigned int i=0; i<hashtable->key.size();i++){
			if(hashtable->status[i]!= "empty"){
				cout<<hashtable->value[i] << " ";
				if(isEmpty ==0) isEmpty=1;
			}
		}
	}
	
}


int main(){
	char largechars[1000000];
	std::vector<char*> v;
	string decision;
	string value;
	HashTable* hashtable = NULL;

	//reading input
	cin.getline(largechars, 1000000);

	//split based on space
	char* chars_array = strtok(largechars, " ");
	while(chars_array)
	{
		v.push_back(chars_array);
		chars_array = strtok(NULL, " ");
	}

	//check if to add or delete
	for(unsigned int i=0;i<v.size();i++){
		decision=v[i];
		value = decision.substr(1, decision.size()-1);
		if(decision[0]== 'A'){
			hashtable = hashtable->insertValue(hashtable,value);
		}else if(decision[0]== 'D'){
			hashtable = hashtable->deleteValue(hashtable,value);
		}
	}
	hashtable->printHashtable(hashtable);
	if(isEmpty==0) cout << "EMPTY";
	cout << endl;
}
