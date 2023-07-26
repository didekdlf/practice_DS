#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
#define COMPARE(x,y) (((x)>(y)) ? -1 : ((x)==(y))? 0 : 1)
void selectionSort(void);
int binsearch(int [], int , int , int );
void pro_2(int);
void printfx(int*,int,int );
void pro_3(int,int*,int);



void main(){
    int n=4;
    int* combi=(int*)malloc(n*sizeof(int));

    pro_3(n,combi,n);
    pro_2(5);
    int list[8]={1,2,3,4,5,6,7,8};
    int i = binsearch(list,6,2,7);
    //selectionSort();
    printf("%d\n",i);
    

    printf("성공적 실행");

    free(combi);
}

void pro_3(int n,int* combi,int size){
    char* c1[2]={"True","False"};
    for(int i=0;i<2;i++){
        combi[n]=i;
        if(n>0)
            pro_3(n-1,combi,size);
        else{
            printf("<");
            for (int j=0;j<size;j++){
                printf("%5s, ",c1[combi[j]]);
            }
            printf(">\n");
        }
    
    }
    n--;

    
}

















void pro_2(int deg){
    int* co1;
    co1 = (int*)malloc(deg*sizeof(int));
    int* co2;
    co2=co1;
    for (int i =0;i<deg;i++){
        co1[i]=i+1;
    }
    printf("%d\n",co1[1]);
    printfx(co1,deg,0);
}
void printfx(int* coef,int deg,int i){
    printf("(");
    
    if(i<deg-1)
        printfx(coef,deg,i+1);
    if(i==0){
        printf("%d\n",coef[i],i);
    }
    else{
        printf("%d)X +",coef[i],i);
    }
}

void selectionSort(void){
    int li[10]={10,9,-1,7,6,6,14,4,6,2};
    int len = sizeof(li)/sizeof(int);
    int j,i,k,a,min, loca;
    for(j =0; j<len;j++)
    {
        loca=j;
        for (int i =1+j;i<len;i++)
        {
            if (li[loca]>li[i]){
                loca=i;
            }
        }
        printf("%d\n",loca);
        //place it next in the sorted list.
        SWAP(li[j],li[loca],min);
        for(a =0; a<len;a++)
        {
            printf(" %d ",li[a]);    
        }
        printf("\n");
    } 

}

int binsearch(int list[], int searchnum, int left, int right){
    int m;
    while(left<right){
        m= ((left+right)/2);
        if(list[m]<searchnum){
            left = m+1;
        }
        else if(list[m]==searchnum){
            return m;
        }
        else{
            right =m-1;
        }
        printf("left : %d, right : %d, m : %d\n",left, right,m);
    }
    if (list[m]==searchnum)
        return m;
    else{
        return -1;
    }



}

void sorting(void)
{
    int li[8] = {8,7,6,5,4,3,2,1};
    int i,j,k;
    int len=sizeof(li)/sizeof(int);
    for(j=1;j<len;j++){
        i=0;
        while(li[j]>li[i]){
            i++;
        }
        int m=li[j];
        printf("\n%d",j);
        printf("%d\n",i);
        for (k=j;k>=1+i;k--){
            li[k]=li[k-1];
        }
        li[i]=m;
        for(int a =0; a<len;a++)
        {
            printf(" %d ",li[a]);    
        }
        printf("\n");
    }
    for(int a =0; a<len;a++)
    {
        printf(" %d ",li[a]);    
    }
    printf("\n");
}