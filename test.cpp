#include<bits/stdc++.h>
using namespace std;
int main(){
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    string s;
    vector<string>v;
    while(cin>>s){
        v.push_back(s);
    }
    sort(v.begin(),v.end());
    printf("int iarcode[]={");
    printf("%s",v[0].c_str());
    for(int i=1;i<v.size();i++){
        printf(",%s",v[i].c_str());
    }
    puts("};\n");

    printf("char carcode[]={");
    printf("\"%s\"",v[0].c_str());
    for(int i=1;i<v.size();i++){
        printf(",\"%s\"",v[i].c_str());
    }
    puts("};\n");
    fclose(stdin);fclose(stdout);
    return 0;
}