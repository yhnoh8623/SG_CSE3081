#include<iostream>
#include<vector>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<cstdio>
using namespace std;
//vector<int>arr;
vector<int>v;

void selectionsort();
void quicksort(int p, int r);
void mergesort(int left, int right);
void mergetwoarea(int left, int mid, int right);
int partition(int p, int r);
void quick_insertion_sort(int n, int p, int r);
int good_partition(int p, int r);

//#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
int main(int argc, char* argv[])
{
    char* name = argv[1];
    int algonum; algonum = (int)argv[2][0] - 48;
    FILE *fp;
    fp = fopen(name, "r");
    int size;
    fscanf(fp, "%d", &size);
    for(int i=0; i<size; i++)
    {
      int num;
      fscanf(fp, "%d", &num);
      v.push_back(num);
    }
    clock_t start, finish;
    char result[24] = "result_";
    result[7] = argv[2][0];
    result[8] = '_';
    for(int i=9; i<24; i++)
    {
      result[i] = name[i-9];
    }
    fp = fopen(result, "w");
    fprintf(fp, "%s\n", name);
    fprintf(fp, "%d\n", algonum);
    fprintf(fp, "%d\n", size);
    start = clock();
    if(algonum==1)
    {
      selectionsort();
    }
    else if(algonum==2)
    {
      quicksort(0, size-1);
    }
    else if(algonum==3)
    {
      mergesort(0, size-1);
    }
    else if(algonum==4)
    {
      quick_insertion_sort(size, 0, size-1);
    }
    finish = clock();
    double duration = finish-start;
    fprintf(fp, "%.6f\n", duration/CLOCKS_PER_SEC);
    for(int i=0; i<size; i++)
    {
      fprintf(fp, "%d ", v[i]);
    }
    fclose(fp);
    return 0;
}

void selectionsort()
{
    int size = v.size();
    for(int i=0; i<size; i++)
    {
        int minidx = i;
        for(int j=i+1; j<size; j++)
        {
            if(v[j] < v[minidx])
                minidx = j;
        }
        int temp = v[i];
        v[i] = v[minidx];
        v[minidx] = temp;
    }
}
int partition(int p, int r)
{
   int pivot = v[r];
   int idx = p-1;
   for(int j=p; j<r; j++)
   {
      if(v[j]<=pivot)
      {
         idx++;
         int temp = v[idx];
         v[idx] = v[j];
         v[j] = temp;
      }
   }
   int temp = v[idx+1];
   v[idx+1] = v[r];
   v[r] = temp;
   return idx+1;
}
void quicksort(int p, int r)
{
   if(p<r)
   {
      int pivotidx = partition(p, r);
      quicksort(p, pivotidx-1);
      quicksort(pivotidx+1, r);
   }
}
void mergesort(int left, int right)
{
   int mid;
   if(left<right)
   {
      mid = (left+right)/2;
      mergesort(left, mid);
      mergesort(mid+1, right);
      mergetwoarea(left, mid, right);
   }
}
void mergetwoarea(int left, int mid, int right)
{
   int* copyary = (int*)malloc(sizeof(int) * (right+1));
   int lidx = left;
   int ridx = mid+1;
   int idx = left;

   while(lidx<=mid && ridx<=right)
   {
      if(v[lidx] <= v[ridx])
         copyary[idx++] = v[lidx++];
      else
         copyary[idx++] = v[ridx++];
   }

   if(lidx>mid)
   {
      for(int i=ridx; i<=right; i++)
         copyary[idx++] = v[i];
   }
   else if(ridx>right)
   {
      for(int i=lidx; i<=mid; i++)
         copyary[idx++] = v[i];
   }

   for(int i=left; i<=right; i++)
      v[i] = copyary[i];
   
   free(copyary);
}
void quick_insertion_sort(int n, int p, int r)
{
   if(n<50)
   {
      int j;
      for(int i=1; i<n; i++){
         int key = v[i];
         for(j=i-1; j>=0 && v[j]>key; j--){
            v[j+1] = v[j];
         }
         v[j+1] = key;
      }
      return;
   }
   else
   {
      if(p<r)
      {
         int mid = (p+r)/2;
         int arr[3] = {p, mid, r};
         int j;
         for(int i=1; i<3; i++)
         {
            int key = arr[i];
            for(j=i-1; j>=0 && v[arr[j]]>v[key]; j--){
               arr[j+1] = arr[j];
            }
            arr[j+1] = key;
         }
         //printf("%d %d %d\n", v[arr[0]], v[arr[1]], v[arr[2]]);
         int pivotid = arr[1];
         //printf("%d\n", pivotid);
         int tmp = v[pivotid];
         v[pivotid] = v[r];
         v[r] = tmp;
         int pivotidx = partition(p, r);
         quick_insertion_sort(n, p, pivotidx-1);
         quick_insertion_sort(n, pivotidx+1, r);
      }
   }
}
