#include <stdlib.h>
#include <stdio.h>


typedef struct SparseMatrix{
    int row, col;
    int** room;
}SM;

SM Create(int,int);
SM Transpose(SM);
SM Add(SM,SM);
SM Multiply(SM,SM);
void Remove(SM);
void printM(SM);

void main(){
    SM sm1,sm2;
    sm1=Create(2,5);
    sm2=Create(5,2);
    for(int i =0; i<sm1.row;i++){//테스트용 행렬 만들기
        for(int j =0; j<sm1.col;j++){
            sm1.room[i][j]=i+j;
        }
    }
    for(int i =0; i<sm2.row;i++){
        for(int j =0; j<sm2.col;j++){
            sm2.room[i][j]=i+j;
        }
    }
    printM(sm1);
    printM(sm2);
    printM(Add(sm1,sm2));
    printM(Multiply(sm1,sm2));
}


void printM(SM sm){//행렬 출력
    for(int i =0; i<sm.row;i++){
        for(int j =0; j<sm.col;j++){
            printf("%2d ",sm.room[i][j]);
        }
        printf("\n");
    }
    printf("--------------------\n");
}
SM Create(int maxrow,int maxcol){//행렬 생성, 내용물 생성(초기화)은 하지 않음.
    SM sm;
    sm.col=maxcol;
    sm.row = maxrow;
    sm.room=(int**)malloc(maxrow*sizeof(int*));
    for(int i =0; i<maxrow;i++){
        sm.room[i]=(int*)malloc(maxcol*sizeof(int));
    }
    return sm;
}
void Remove(SM sm){//행렬 메모리 해제
    for(int i =0; i<sm.row;i++){
        free(sm.room[i]);
    }
    free(sm.room);
}
SM Transpose(SM sm){
    SM tsm=Create(sm.row, sm.col);
    for(int i =0; i<sm.row;i++){
        for(int j =0; j<sm.col;j++){
            tsm.room[i][j]=sm.room[j][i];//행과 열을 바꾼 자리에 집어넣기
        }
    }
    Remove(sm);
    return tsm;
}
SM Add(SM sm1 ,SM sm2){
    if((sm1.row==sm2.row)&&(sm1.col==sm2.col)){//row와 col의 값이 같을 때만 덧셈 가능
        SM sum=Create(sm1.row,sm1.col);
        for(int i =0; i<sm1.row;i++){
            for(int j =0; j<sm1.col;j++){
                sum.room[i][j]=sm1.room[i][j]+sm2.room[i][j];
            }
        }
        return sum;
    }
    else{
        printf("Addition impossible");
        return sm1;
    }
    
}
SM Multiply(SM sm1,SM sm2){
    int sum;
    if(sm1.col==sm2.row){//행렬 곱셈 조건
        SM mulm=Create(sm1.row,sm2.col);
        for(int i =0; i<sm1.row;i++){//A*B에서 A의 row 결정
            for(int k=0;k<sm2.col;k++){// B의 col 결정
                sum=0;
                for(int j =0; j<sm1.col;j++){//A의 row와 B의 col 각각 곱해서 더하기
                    sum+=sm1.room[i][j]*sm2.room[j][k];
                }
                mulm.room[i][k]=sum;//결과 행렬에 넣기
            }
            
        }
        return mulm;    
    }
    else{
        printf("Multiply impossible");
    }

}