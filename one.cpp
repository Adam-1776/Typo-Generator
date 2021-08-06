// Written by Adam Rizk
// adamrizk9@gmail.com
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

void printVector(vector<vector<int>> &arr,int r,int c){
  for(int i=0;i<r;++i)
    for(int j=0;j<c;++j)
      cout<<"array["<<i<<"]["<<j<<"] = "<<arr[i][j]<<endl;
}

unsigned nCr(unsigned n, unsigned k){
  if(k>n) return 0;
  if(k*2>n)k=n-k;
  if(k==0) return 1;
  int result=n;
  for(int i=2;i< k;++i){
    result*=(n-i+1);
    result/=i;
  }
  return result;
}

int generateCombinations(int n, int r, vector<vector<int>> &arr){
  std::vector<bool> v(n);
  int j=0; int z=0; int c=0;
  std::fill(v.begin(),v.begin()+r,true);
  do{for(int i=0;i<n;++i){if(v[i]){arr[j][z]=i; ++z;}}
    ++j; z=0; ++c;}
    while(prev_permutation(v.begin(),v.end()));
  return 0;
}

int variate(const string input, const int number_of_insertions, const int number_of_deletions, const int number_of_substitutions){
  string word="";
  int count=0;
  const int len=input.length();
  if(number_of_deletions>len||number_of_substitutions>len){cout<<"The number of deletions or substitutions cannot exceed the length of the word\n"; return 0;}

  for(int i=1;i<=number_of_deletions;++i){ //This loop prints all mispellings involving deletions
    int combo=nCr(len,i);
    vector<vector<int>> arr(combo,vector<int>(i, 0));
    generateCombinations(len,i,arr);
    cout<<i<<" deletions:"<<endl;
    for(int j=combo-1;j>=0;--j){
      for(int u=0;u<len;++u){if(find(arr[j].begin(),arr[j].end(),u)==arr[j].end()) word+=input[u];}
      cout<<word<<", "; //Printing misspelling
      word="";  //Resetting word string for next iteration of loop
      ++count;
      if(count%15==0) cout<<endl; //Insert newline if more than fifteen mispellings have been inserted in one line
    } printf("\b \b\b \b\n\n"); //Deleting last comma insertion and inserting two newlines
  }

  for(int i=1;i<=number_of_substitutions;++i){ //This loop prints all mispellings involving substitutions
    int combo=nCr(len,i);
    char char2='a';
    count=0;
    bool present=true;
    vector<vector<int>> arr2(combo,vector<int>(i, 0));
    generateCombinations(len,i,arr2); //Get all combinations of i indexes selected from array with len elements, and place them in vector arr
    int alphabet_combo=nCr(26,i);
    vector<vector<int>> arr3(alphabet_combo,vector<int>(i, 0));
    generateCombinations(26,i,arr3);
    //cout<<"i = "<<i<<" and combo = "<<combo<<" and alphabet_combo = "<<alphabet_combo<<endl;
    //printVector(arr3,alphabet_combo,i);
    cout<<i<<" substitutions:"<<endl;
    for(int j=combo-1;j>=0;--j){
      for(int u=0;u<alphabet_combo;++u){
        word=input; present=true;
        for(int t=0;t<i;++t){
          if(char(arr3[u][t]+'a')==word[arr2[j][t]]){present=false; break;}
          word[arr2[j][t]] = char(arr3[u][t]+'a');
        } if(present==true){cout<<word<<", "; ++count; if(count%15==0) cout<<endl;}

      }

    } printf("\b \b\b \b\n\n");
  }

  return 0;
}

int main(){
  string word="encyclopedia";
  int no_in=2;
  int no_del=2;
  int no_sub=2; /*
  printf("Type in a word:\n");
  getline(cin,word);
  printf("Type in number of insertions that can be made:\n");
  getline(cin,no_in); //cin>>no_in;
  printf("Type in number of deletions that can be made:\n");
  cin>>no_del;
  printf("Type in number of substiutions that can be made:\n");
  cin>>no_sub;
  for(int i=0;i<word.length();++i)
    if(word[i]>64&&word[i]<91) word[i]+=32; //Making the string all lower-case


  vector<vector<int>> arr(20,vector<int>(3, 0));
  combinations(6,3,arr);
  for(int i=0;i<20;++i){
    for(int j=0;j<3;++j) printf("%d ",arr[i][j]);
    printf("\n");
  } */
  variate(word,no_in,no_del,no_sub);
  return 0;
}
