// Written by Adam Rizk
// adamrizk9@gmail.com
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

long long nCr(int n, int r){ //This function calculates the number of way r items can be picked from a collection of n items
   long long p = 1, k = 1;
   if(n-r<r) r=n-r;
   if(r!=0){
    while(r){
    p*=n;
    k*=r;
    long long m=__gcd(p, k);
    p/=m;
    k/=m;
    n--;
    r--;
    }
   }
   else p = 1;
   return p;
}

int generateCombinations(int n, int r, vector<vector<int>> &arr){ //Generates all possible combinations of nCr and inserts them into vector arr
  std::vector<bool> v(n);
  int j=0; int z=0; int c=0;
  std::fill(v.begin(),v.begin()+r,true);
  do{for(int i=0;i<n;++i){if(v[i]){arr[j][z]=i; ++z;}}
    ++j; z=0; ++c;}
    while(prev_permutation(v.begin(),v.end()));
  return 0;
}

string insertBlanks(const string input,int i){ //Helper function for insertions
    string word=input;
    word.insert(0,i,'$');
    //word.insert(word.length(),i,'$');
    int j=i;
    while(j<word.length()){
        if(word[j+1]!='$') {word.insert(j+1,i,'$'); j=j+i;}
        ++j;
    }
    return word;
}

int processInput(string input){ //Preprocesses user inputs
    char num='a';
    for(int i=0;i<input.length();++i)
        if(char(input[i])>47&&char(input[i])<58) return int(char(input[i])-'0');
    return -1;
}

int variate(const string input, const int number_of_insertions, const int number_of_deletions, const int number_of_substitutions){ //This function generates misspellings
  string word="";
  int count=0;
  const int len=input.length();
  if(number_of_deletions>len||number_of_substitutions>len){cout<<"The number of deletions or substitutions cannot exceed the length of the word\n"; return 0;}
  cout<<"Generating misspellings for word \'"<<input<<"\'"<<endl<<endl;
  
  for(int i=1;i<4;++i){

  if(i<=number_of_deletions){ //This loop prints all misspellings involving deletions
    long long combo=nCr(len,i);
    count=0;
    word="";
    //cout<<"len="<<len<<" and "<<"i="<<i<<" and combo="<<combo<<endl;
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

  if(i<=number_of_substitutions){ //This loop prints all misspellings involving substitutions
    long long combo=nCr(len,i);
    char char2='a';
    count=0;
    bool present=true;
    vector<vector<int>> arr2(combo,vector<int>(i, 0));
    generateCombinations(len,i,arr2); //Get all combinations of i indexes selected from array with len elements, and place them in vector arr
    int alphabet_combo=nCr(26,i);
    vector<vector<int>> arr3(alphabet_combo,vector<int>(i, 0));
    generateCombinations(26,i,arr3);
    cout<<i<<" substitutions:"<<endl;
    for(int j=combo-1;j>=0;--j){
      for(int u=0;u<alphabet_combo;++u){
        word=input;
        present=true;
        for(int t=0;t<i;++t){
          if(char(arr3[u][t]+'a')==word[arr2[j][t]]){present=false; break;}
          word[arr2[j][t]] = char(arr3[u][t]+'a');
        } if(present==true){cout<<word<<", "; ++count; if(count%15==0) cout<<endl;}

      }

    } printf("\b \b\b \b\n\n");
  }

  if(i<=number_of_insertions){ //This loop prints all misspellings involving insertions
    int len2=(len+1)*i;
    long long combo=nCr(len2,i);
    char char2='a';
    count=0;
    vector<vector<int>> arr4(combo,vector<int>(i, 0));
    generateCombinations(len2,i,arr4); //Get all combinations of i indexes selected from array with len2 elements, and place them in vector arr
    int alphabet_combo=nCr(26,i);
    vector<vector<int>> arr5(alphabet_combo,vector<int>(i, 0));
    generateCombinations(26,i,arr5);
    cout<<i<<" insertions:"<<endl;
    for(int j=combo-1;j>=0;--j){
      for(int u=0;u<alphabet_combo;++u){
        word=insertBlanks(input,i);
        string word2=word;
        for(int t=0;t<i;++t){
            int dcount=-1;
            for(int v=0;v<word.length();++v){
               bool flag=false;
               if(word2[v]=='$') {++dcount; flag=true;}
               if(flag==true && dcount==arr4[j][t]) {word[v]=char(arr5[u][t]+'a');}
            } 
        } 
          word.erase(remove(word.begin(), word.end(), '$'), word.end()); 
          cout<<word<<", "; ++count; if(count%15==0) cout<<endl;

      }

    } printf("\b \b\b \b\n\n");
  }
  }

  return 0;
}


int main(){
  string word="";
  int no_in=1;
  int no_del=2;
  int no_sub=1;
  string input;

  printf("Type in a word:\n"); //Getting user inputs
  cin>>word;
  cin.ignore(numeric_limits <streamsize>::max(),'\n'); //Flushing newline character
  printf("Type in number of insertions that can be made: (default=1 if this field is left blank)\n");
  getline(cin,input);
  no_in=processInput(input); //Preprocess user input
  if(no_in==-1) no_in=1;
  printf("Type in number of deletions that can be made: (default=2 if this field is left blank)\n");
  getline(cin,input);
  no_del=processInput(input); //Preprocess user input
  if(no_del==-1) no_del=2;
  printf("Type in number of substitutions that can be made: (default=1 if this field is left blank)\n");
  getline(cin,input);
  no_sub=processInput(input); //Preprocess user input
  if(no_sub==-1) no_sub=1;

  for(int i=0;i<word.length();++i)
    if(word[i]>64&&word[i]<91) word[i]+=32; //Making the string all lower-case
  
  variate(word,no_in,no_del,no_sub); //Generating all misspellings
  
  return 0;
}