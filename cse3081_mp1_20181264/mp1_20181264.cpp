#include<iostream>
#include<vector>
#include<algorithm>
#include<ctime>
#include<cstdio>
using namespace std;
vector<vector<int>>v;
vector<vector<int>>sumdp;
vector<vector<int>>linesumdp;
int solve1();
int solve2();
int solve3();
int n, m;

int main(int argc, char *argv[])
{
    char* name = argv[1];
    int algonum; algonum = (int)argv[2][0] - 48;
    FILE *fp;
    fp = fopen(name, "r");
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);
    clock_t start, finish;
    for(int i=0; i<n; i++)
    {
        vector<int>v1;
        for(int j=0; j<m; j++){
            int num;
            fscanf(fp, "%d", &num);
            v1.push_back(num);
        }
        v.push_back(v1);
    }
    fclose(fp);
    for(int i=0; i<n; i++)
    {
        vector<int>ldp;
        ldp.push_back(0);
        for(int j=1; j<=m; j++)
        {
            ldp.push_back(ldp[j-1]+v[i][j-1]);
        }
        linesumdp.push_back(ldp);
    }
    for(int i=0; i<=n; i++)
    {
        vector<int>sdp;
        for(int j=0; j<=m; j++){
            sdp.push_back(0);
        }
        sumdp.push_back(sdp);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            sumdp[i][j] = sumdp[i-1][j]+sumdp[i][j-1]-sumdp[i-1][j-1]+v[i-1][j-1];
        }
    }
    char result[22] = "result_";
    for(int i=7; i<22; i++){
        result[i] = name[i-7];
    }
    fp = fopen(result, "w");
    fprintf(fp, "%s\n", name);
    fprintf(fp, "%d\n", algonum);
    fprintf(fp, "%d\n%d\n", n, m);
    start = clock();
    if(algonum==1){
        fprintf(fp, "%d\n", solve1());
        //cout<<"solve1 = "<<solve1()<<endl;
    }
    else if(algonum==2){
        fprintf(fp, "%d\n", solve2());
        //cout<<"solve2 = "<<solve2()<<endl;
    }
    else if(algonum==3){
        fprintf(fp, "%d\n", solve3());
        //cout<<"solve3 = "<<solve3()<<endl;
    };
    finish = clock();
    double duration = finish-start;
    fprintf(fp, "%.1f", duration);
    //cout<<"duration = "<<duration<<endl;
    fclose(fp);
    return 0;
}
int solve1()
{
    int mx = v[0][0];
    for(int cols=0; cols<m; cols++)
    {
        for(int colf=cols; colf<m; colf++)
        {
            for(int rows=0; rows<n; rows++)
            {
                for(int rowf=rows; rowf<n; rowf++)
                {
                    int cmp=0;
                    for(int i=rows; i<=rowf; i++)
                    {
                        for(int j=cols; j<=colf; j++){
                            cmp+=v[i][j];
                        }
                    }
                    if(cmp>mx){
                        mx = cmp;
                    }
                }
            }
        }
    }
    return mx;
}
int solve2()
{
    int mx=v[0][0];
    for(int cols=1; cols<=m; cols++)
    {
        for(int colf=cols; colf<=m; colf++)
        {
            for(int rows=1; rows<=n; rows++)
            {
                for(int rowf=rows; rowf<=n; rowf++)
                {
                    int cmp = sumdp[rowf][colf]-sumdp[rows-1][colf]-sumdp[rowf][cols-1]+sumdp[rows-1][cols-1];
                    if(cmp>mx){
                        mx = cmp;
                    }
                }
            }
        }
    }
    return mx;
}
int solve3()
{
    int mx = v[0][0];
    for(int cols=1; cols<=m; cols++)
    {
        for(int colf=cols; colf<=m; colf++)
        {
            vector<int>col;
            for(int row=0; row<n; row++)
            {
                col.push_back(linesumdp[row][colf]-linesumdp[row][cols-1]);
            }
            int cmp=col[0];
            int ret = col[0];
            for(int i=1; i<n; i++)
            {
                int temp = cmp;
                cmp = max(temp+col[i], col[i]);
                if(ret<cmp){
                    ret = cmp;
                }
            }
            if(mx<ret){
                mx = ret;
            }
        }
    }
    return mx;
}
