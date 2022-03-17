#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#define SWAP(a, b) (a += b, b = a - b, a -= b)
#define SAMPLESIZE 100000

void Swap(int *a,int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void Randarray(int *range,int n){
    for(int i = 0; i < n; i++){
        range[i] = rand();
    }
}

void Arrayjudge(int *range,int n){
    for(int i = 0;i<n-1;i++){
        if(range[i] > range[i+1]){
            printf("ソートされていない\n");
            return;
        }
    }
    printf("ソートされている\n");
}

void Printrange(int *range,int n){
    for(int i = 0; i < n; i++){
        printf("%d ",range[i]);
    }
}

void Bubble(int *range,int n){
    int i;
    for(i = 0; i < n - 1; i++){
        for(int j = n - 1;j > i;j--){
            if(range[j-1] > range[j])Swap(&range[j],&range[j-1]);
        }
    }
}

void Serection(int *range,int n){
    int i;
    for(i = 0; i < n-1;i++){
        int j;
        int minpos = i;
        for(j = i+1; j < n;j++){
            if(range[minpos] > range[j]) minpos = j;
            
        }
        Swap(&range[i],&range[minpos]);
    }
}

void Insert(int *range,int n){
    for(int i = 1;i < n; i++){
        int j = i;
        while(j > 0 && range[j-1] > range[j]) {
            Swap(&range[j-1],&range[j]);
            j--;
        }
    }
}

int Partition(int *range,int p ,int r){
    int pivot = range[r];
    int i = p-1;
    for(int j = p; j < r;j++){
        if(range[j] < pivot){
            Swap(&range[j],&range[i+1]);
            i++;
        }
    }
    Swap(&range[i+1],&range[r]);
    return i+1;
}

void Quick(int *range, int p, int r){
    if(p < r){
        int q = Partition(range,p,r);
        Quick(range,p,q-1);
        Quick(range,q+1,r);
    }
}

int Partition2(int *range, int l, int r){
    int i,j,pivot;
    i = l-1; j = r+1;
    pivot = range[r];
    do{
        do{i++;}while(range[i] < pivot);
        do{j--;}while(range[j] >= pivot && j >= 0);
        if(i < j){Swap(&range[i],&range[j]);}
    }while(j > i);
    range[r] = range[i]; range[i] = pivot;
    return i;
}

void Quick2(int *range, int l, int r){
    int i;
    if(l < r){
        i = Partition2(range,l,r);
        Quick2(range,l,i-1);
        Quick2(range,i+1,r);
    }
}

void Merge(int *range,int l,int r){
    int i,j,k,m;
    int *range2 = (int*)malloc((SAMPLESIZE) * sizeof(int));
    if(l < r){
        m = (l+r)/2;
        Merge(range,l,m);
        Merge(range,m+1,r);
        for(i = m; i >= l;i--){range2[i] = range[i];}
        i = l;
        for(j = m+1; j <= r;j++){range2[r+m+1-j] = range[j];}
        j = r;
        for(k=l;k <= r;k++){
            if(range2[i] < range2[j]){range[k] = range2[i++];}
            else{range[k] = range2[j--];}
        }
    }
    free(range2);
}

void Shell(int *range,int n){
    int i,j,h;

    //間隔hを決めている
    for(h = 1; h <= n/9; h = 3*h + 1);  

    for(;h > 0; h/=3){
        //挿入ソートと同じ
        for(i = h; i < n;i++){
            j = i;
            while((j > h-1) && (range[j-h] > range[j])){
                Swap(&range[j-h],&range[j]); 
                j -= h;
            }
        }
    }
}

void Pushdown(int *range, int first, int last){
    int r = first; int k = 2*r;
    while(k <= last){
        if(k < last && range[k] < range[k+1]){k++;}
        if(range[r] >= range[k]){break;}
        Swap(&range[r],&range[k]);
        r = k; k = 2*r;
    }
}

void Heap(int *range, int n){
    int i;
    //ヒープ木を作成
    for(i = n/2 /* 要素数の半分でOK*/; i >= 0; i--){Pushdown(range,i,n-1);}
    //木の根を配列の後ろから詰めていく
    for(i = n-1; i > 0; i--){
        Swap(&range[0],&range[i]);
        Pushdown(range,0,i-1);
    }
}

int bits(int x,int k,int j){
    return(x>>k) & ~(~0<<j);
}

/*
void Radix(int *range, int l,int r, int b){
    int i,j;
    if(r > l && b >= 0){
        i = l;j = r;
    }
    do{
        while(bits(range[i],b,1) == 0 && (i < j)){i++;}
        while(bits(range[j],b,1) == 1 && (i < j)){j--;}
        if(i != j){Swap(&range[i],&range[j]);}
    }while(i != j);
    if(bits(range[r],b,1) == 0){j++;}
    Radix(range,l,j-1,b-1);
    Radix(range,j,r,b-1);
}
*/


int main(void){
    FILE *file;
    file = fopen("test.txt","w");
    int range[SAMPLESIZE];
    int n = SAMPLESIZE;
    clock_t start,end;

    //バブルソート
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Bubble(range,n);
    end = clock();
    Arrayjudge(range,n);
    printf("バブルソートの実行時間は%ldms\n",(end-start));
    fprintf(file,"バブルソートの実行時間は%ldms\n",(end-start));
    

    //選択ソート
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Serection(range,n);
    end = clock();
    Arrayjudge(range,n);
    printf("選択ソートの実行時間は%ldms\n",(end-start));
    fprintf(file,"選択ソートの実行時間は%ldms\n",(end-start));
    
    //挿入ソート
    
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Insert(range,n);
    end = clock();
    Arrayjudge(range,n);
    printf("挿入ソートの実行時間は%ldms\n",(end-start));
    fprintf(file,"挿入ソートの実行時間は%ldms\n",(end-start));
    
    //クイックソート
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Quick(range,0,n);
    end = clock();
    Arrayjudge(range,n);
    printf("クイックソートの実行時間は%ldms\n",(end-start));
    fprintf(file,"クイックソートの実行時間は%ldms\n",(end-start));

    //クイックソート2
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Quick2(range,0,n);
    end = clock();
    Arrayjudge(range,n-1);
    printf("クイックソート2の実行時間は%ldms\n",(end-start));
    fprintf(file,"クイックソート2の実行時間は%ldms\n",(end-start));
    
    //マージソート
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Merge(range,0,n-1);
    end = clock();
    Arrayjudge(range,n);
    printf("マージソートの実行時間は%ldms\n",(end-start));
    fprintf(file,"マージソートの実行時間は%ldms\n",(end-start));

    //シェルソート
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Shell(range,n);
    end = clock();
    Arrayjudge(range,n);
    printf("シェルソートの実行時間は%ldms\n",(end-start));
    fprintf(file,"シェルソートの実行時間は%ldms\n",(end-start));


    //ヒープソート
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Heap(range,n);
    end = clock();
    Arrayjudge(range,n);
    printf("ヒープソートの実行時間は%ldms\n",(end-start));
    fprintf(file,"ヒープソートの実行時間は%ldms\n",(end-start));

    //基数ソートわからん
    /*
    Randarray(range,SAMPLESIZE);
    start = clock(); 
    Radix(range,0,SAMPLESIZE-1,30);
    end = clock();
    Arrayjudge(range,n);
    printf("基数ソートの実行時間は%ldms\n",(end-start));
    */

    //Printrange(range,n);
    fclose(file);
    return 0;
}
