#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <map>
#include <queue>
#include <string>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

class Node{
    public:
    int freq;
    char x;
    Node *left;
    Node *right;
};

struct compare{
    bool operator()(const Node* n1, const Node* n2){
        return (n1->freq) < (n2->freq);
    }
};

map<char, string>mapping;
void dfs(Node* node, vector<char> s);
Node* tree;

int main(int argc, char* argv[])
{
    char* name = argv[2];
    FILE* fp = fopen(name, "r");
    char check = argv[1][1];
    if(check == 'c')
    {
        //cout<<"1!!!!!";
        char result[12]; 
        for(int i=0; i<9; i++){
            result[i] = argv[2][i];
        }
        result[9] = '.'; result[10] = 'z'; result[11] = 'z';
	    //cout<<"result = "<<result<<endl;
        FILE* wfp = fopen(result, "w");
        char ch;
        int a = 0;
        map<char, int>mp;
        priority_queue<Node*, vector<Node*>, compare>pq;
        long long length = 0;
        while(1)
        {
            ch = fgetc(fp);
            if(ch == EOF)break;
            length++;
            if(mp.find(ch) == mp.end()){
                mp[ch] = 1;
            }
            else{
                mp[ch]++;
            }
        } 
        fprintf(wfp, "%lld", length); // 글자 개수 정보 
        //cout<<length;
        map<char, int>::iterator iter;
        for(iter = mp.begin(); iter != mp.end(); iter++)
        {
            Node *nd = new Node;
            nd->freq = -1 * (iter->second);
            nd->x = iter->first;
            nd->left = NULL;
            nd->right = NULL;
            pq.push(nd);
        }
        while(pq.size()!=1)
        {
            Node *n1 = pq.top();
            pq.pop();
            Node *n2 = pq.top();
            pq.pop();
            Node *pu = new Node;
            pu->freq = n1->freq + n2->freq;
            pu->left = n1;
            pu->right = n2;
            pq.push(pu);
        }
        tree = pq.top();
        vector<char>str;
        dfs(tree, str);
        //////////////////////////////
        fprintf(wfp, "%c", (char)mapping.size()); // map size
        map<char, string>::iterator ite;
        for(ite = mapping.begin(); ite!=mapping.end(); ite++)
        {
            //cout<<ite->first<<' '<<ite->second<<endl;
            fprintf(wfp, "%c%c", ite->first, (char)ite->second.size());
        }
        int cnt = 0;
        unsigned char bit = (char)0;
        char plus = (char)1;
        for(ite = mapping.begin(); ite!=mapping.end(); ite++)
        {
            string s = ite->second;
            for(int i=0; i<s.size(); i++)
            {
                if(s[i] == '0')
                {
                    bit = bit<<1;
                }
                else{
                    bit = bit<<1;
                    bit += plus;
                }
                cnt++;
                if(cnt==8)
                {
                    fprintf(wfp, "%c", bit);
                    //cout<<bitset<8>(bit)<<' ';
                    bit = (char)0;
                    cnt = 0;
                }
            }
        }
        while(cnt != 8){
            bit = bit<<1;
            cnt++;
        }
        fprintf(wfp, "%c", bit);
        //cout<<bitset<8>(bit)<<endl;
        //////////////////////////////
        fclose(fp);
        fp = fopen(name, "r");
        bit = (char)0;
        cnt = 0;
        while(1)
        {
            ch = fgetc(fp);
            if(ch == EOF)break;
            for(int i=0; i<mapping[ch].size(); i++)
            {
                if(mapping[ch][i]=='0')
                {
                    bit = bit << 1;
                    cnt++;
                }
                else{
                    bit = bit << 1;
                    bit += plus;
                    cnt++;
                }
                if(cnt==8)
                {
                    fprintf(wfp, "%c", bit);
                    //cout<<bitset<8>(bit)<<endl;
                    bit = (char)0;
                    cnt = 0;
                }
            }
        }
        while(cnt!=8){
            bit = bit<<1;
            cnt++;
        }
        //cout<<bitset<8>(bit)<<endl;

        fprintf(wfp, "%c", bit);
        fclose(wfp);
    }
    if(check == 'd')
    {
        char* name = argv[2];
        FILE* fp;
        fp = fopen(name, "r");
        char nm[15];
        for(int i=0; i<12; i++){
            nm[i] = name[i];
        }
        nm[12]='.'; nm[13]='y'; nm[14]='y';
        FILE* wfp = fopen(nm, "w");
        int all_size;
        fscanf(fp, "%d", &all_size);
        //cout<<all_size<<endl;
        char xxx;
        int mp_size;
        fscanf(fp, "%c", &xxx);
        mp_size = (int)xxx;
        //cout<<mp_size<<endl;
        map<char, int>semi_map;
        char ch, sz;
        string order;
        char x;
        for(int i=0; i<mp_size; i++)
        {
            fscanf(fp, "%c%c", &ch, &sz);
            //cout<<ch<<' '<<(int)sz<<endl;
            x = ch;
            semi_map.insert({ch, (int)sz});
            order.push_back(ch);
        }
        map<string, char>mp;
        vector<string>v;
        int cnt = 8;
        char bit;
        bitset<8>bs;
        string pu;
        //cout<<mp_size<<endl;
        for(int i=0; i<mp_size; i++)
        {
            char c = order[i]; int siz = semi_map[c];
            //cout<<c<<"size = "<<siz<<endl;
            for(int j=0; j<siz; j++)
            {
                if(cnt==8){
                    fscanf(fp, "%c", &bit);
                    cnt = 0;
                    bs = bitset<8>(bit);
                    //cout<<"bs = "<<bs<<endl;
                }
                if(bs[7-cnt] == false){
                    pu.push_back('0');
                }
                if(bs[7-cnt] == true){
                    pu.push_back('1');
                }
                cnt++;
            }
            //cout<<c<<' '<<pu<<endl;
            mp.insert({pu, c});
            v.push_back(pu);
            pu.clear();
        }
        if(mp_size == 1)
        {
            for(int i=0; i<all_size; i++)
            {
                fprintf(wfp, "%c", x);
            }
            return 0;
        }
        sort(v.begin(), v.end());
        cnt = 8;
        for(int i=0; i<all_size; i++)
        {
            pu.clear();
            while(1)
            {
                if(cnt==8){
                    fscanf(fp, "%c", &bit);
                    //cout<<"bit = "<<bit<<endl;
                    bs = bitset<8>(bit);
                    cnt = 0;
                }
                if(bs[7-cnt]==true)
                {
                    pu.push_back('1');
                }
                if(bs[7-cnt]==false)
                {
                    pu.push_back('0');
                }
                cnt++;
                if(binary_search(v.begin(), v.end(), pu)==1){
                    fprintf(wfp, "%c", mp[pu]);
                    //cout<<mp[pu]<<endl;
                    break;
                }
            }
        }
    }
}
void dfs(Node* node, vector<char>s)
{
    if(node->left == NULL && node->right == NULL)
    {
        string pu;
        for(int i=0; i<s.size(); i++)
        {
            pu.push_back(s[i]);
        }
        mapping[node->x] = pu;
        //cout<<node->x<<' '<<s<<endl;
        return;
    }
    if(node->left != NULL){
        s.push_back('0');
        dfs(node->left, s);
        s.pop_back();
    }
    if(node->right != NULL){
        s.push_back('1');
        dfs(node->right, s);
        s.pop_back();
    }
}
