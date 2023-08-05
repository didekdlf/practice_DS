#include<stdlib.h>
#include<stdio.h>

#define MAX_DEGREE 101
#define MAX_TERMS 100
#define MALLOC(x,size) if (!(x)=malloc(size)) { fprintf(stderr,"Insufficient memory"); exit(EXIT_FAILURE); }

typedef struct Poly{
    int degree;
    float coef[MAX_DEGREE];
}Poly;

typedef struct term{    
    int degree;
    float coef;
}term;
term terms[MAX_TERMS];

Poly Zero(Poly);
int IsZero(Poly);
int Coef(Poly,int);
Poly Attatch(int,int,Poly);
Poly Remove(Poly,int);
Poly SingleMult(Poly,Poly);
Poly Add(Poly,Poly);
Poly Mult(Poly,Poly);
void printpoly(Poly);
void main(){

    Poly p1,p2,p3;
    p1=Zero(p1);
    p2=Zero(p2);
    p3=Zero(p3);
    printpoly(p1);
    p1=Attatch(1,2,p1);
    p1=Attatch(5,2,p1);
    p2=Attatch(4,1,p2);
    p2=Attatch(2,0,p2);
    p3=Attatch(3,2,p3);
    p3=Attatch(5,5,p3);
    printpoly(p1);
    printpoly(p2);
    printpoly(p3);
    printf("--------------------\n");
    printpoly(Mult(p2,p3));

}
void printpoly(Poly p){
    for (int i =0;i<=p.degree;i++){
        if (p.coef[i] != 0){
            printf("%.1f X^%d + ",p.coef[i],p.degree-i);
        }
    }
    printf("\n");
}

Poly Zero(Poly p){
    for(int i =0;i<MAX_DEGREE;i++){
        p.coef[i]=0;
    }
    p.degree=0;
    return p;
}
int IsZero(Poly p){
    if(p.coef[0]==0){
        return 1;
    }
    else{
        return 0;
    }
}
int Coef(Poly p, int expon){
    if (p.degree<expon){
        return 0;
    }
    else{
        return p.coef[p.degree-expon];
    }
    
}

Poly Attatch(int coef, int expon,Poly p){
    Poly newp=Zero(newp);
    newp.coef[0]=coef;
    newp.degree=expon;
    p=Add(p,newp);
    return p;
}
Poly Remove(Poly p,int expon){
    Poly rmp;
    rmp.degree =p.degree;
}

Poly SingleMult(Poly p,Poly sp){
    Poly newp=Zero(newp);
    newp.degree=p.degree+sp.degree;
    for(int i =0;i<=p.degree;i++){
        newp.coef[i]=p.coef[i]*sp.coef[0];
    }
    return newp;
}

Poly Add(Poly p1,Poly p2){
    Poly *bigp, *smallp,addp;
    int dif,i;
    if(p1.degree > p2.degree){
        bigp=&p1;
        smallp=&p2;
        dif = p1.degree-p2.degree;
    }
    else{
        bigp=&p2;
        smallp=&p1;
        dif = p2.degree-p1.degree;
    }
    addp.degree = bigp->degree;
    //더하기
    for(i=0;i<dif;i++){
        addp.coef[i]=bigp->coef[i];
    }
    for(i=dif;i<=addp.degree;i++){
        addp.coef[i]=bigp->coef[i]+smallp->coef[i-dif];
    }
    
    return addp;
}

Poly Mult(Poly p1,Poly p2){
    //p1의 요소와 p2 singleMult해서 몽땅 더하기;
    int i;
    Poly p3;
    Poly result=Zero(result);
    for (i=0;i<=p1.degree;i++){
        if(p1.coef[i] != 0){
            p3.degree = p1.degree-i;
            p3.coef[0] = p1.coef[i];
            result = Add(result,SingleMult(p2,p3));
        }

    }
    return result;
}