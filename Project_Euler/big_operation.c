#include <stdio.h>
#include <stdlib.h>

void bigAffiche(char * a){
	int i;
	for(i=0; i<=999; i++){ 
        if(a[i]!='a' && a[i]!='-'){printf("%d", a[i]); }
        if(a[i]=='-'){printf("%c", a[i]);} 
    }
}

char * intToTab(int a){
	int i, j, c, d;
	char * res = malloc(1001*sizeof(char));
	// On remplit le tableau de a.
	for(i=0; i<=999; i++){ res[i]='a';}
	res[1000]='\0';
	c=a; j=999;
	while(c!=0 && j>=0){d = c%10; c = c/10; res[j]=d; j--;}	
	return res;
}

char * plusGrand(char * a, char * b){
    int i=999; char * tp;
    while(i>=0 && (a[i]!='a'|| b[i]!='a')){
        if(a[i]!='a' && b[i]!='a' && a[i] > b[i]){ tp=a; }
        if(a[i]!='a' && b[i]!='a' && a[i] < b[i]){ tp=b; }
        if(a[i]=='a' && b[i]!='a'){ tp=b; }
        if(a[i]!='a' && b[i]=='a'){ tp=a; }
        --i;
    }
   if(tp==a){ return a;}
   else{ return b;}
}

char * bigSomme(char * a, char * b){
	int i=999, ret=0, val;
	while((ret > 0 || a[i]!='a' || b[i]!='a') && i>=0){
		if(a[i]!='a'&& b[i]!='a'){val = a[i]+b[i]+ret; ret = val/10; b[i]= val%10;}
		if(a[i]=='a'&& b[i]!='a'){val = b[i]+ret; ret = val/10; b[i]= val%10;}
		if(a[i]!='a'&& b[i]=='a'){val = a[i]+ret; ret = val/10; b[i]= val%10;}
		if(a[i]=='a'&& b[i]=='a' && ret>0){val = ret; ret = val/10; b[i]= val%10;}
		--i;
	}	
	return b;	
}

char * bigMultiplication(char * a, char * b){
	int i, j, ret=0, val, decal;
	char * res = malloc(1001*sizeof(char)); res[1000]='\0';
	for(i=0; i<=999; i++){res[i]='a';}
    
	for(i=999; i>=0 && b[i]!='a'; i--){
		decal=999-i;
		for(j=999; j>=0 && (a[j]!='a'||ret>0); j--){
			if(a[j]!='a'){ 
				if(res[j-decal]!='a'){ val=a[j]*b[i]+ret+res[j-decal]; res[j-decal]=val%10; ret=val/10;} 
				else { val=a[j]*b[i]+ret; res[j-decal]=val%10; ret=val/10;} 
			}	
			if(a[j]=='a' && ret>0){ 
				if(res[j-decal]!='a'){val=res[j-decal]+ret; res[j-decal]=val%10; ret=val/10;}
				else{
					if(ret >= 10){ res[j-decal]=ret%10; res[j+1-decal]=ret/10; ret=0;}
					else {res[j-decal]=ret; ret=0;}
				}
			}
		}
	}
	return res;
}

char * rendNegatif(char * a){
    int i;
    for(i=0; i<=999; i++){
        if(a[i+1]!='a'){ a[i]='-'; return a; }
    }
    return a;
}

char * bigSoustraction(char * a1, char * b1) /* a-b */ {
    int i, ret=0, val;
    char * a = plusGrand(a1, b1);
    char * b;
    if(a==a1){b=b1;}
    else {b=a1;}
    char * res = malloc(1001*sizeof(char));
	for(i=0; i<=999; i++){res[i]='a';}
    res[1000]='\0';
    for(i=999; i>=0 && (a[i]!='a'|| b[i]!='a' || ret!=0); i--){
		if(a[i]!='a'&& b[i]!='a'){
            if(a[i] > b[i] + ret){ val=a[i]-b[i]-ret; res[i]= val;}
            if(a[i] == b[i] + ret){ res[i]=0;}
            if(a[i] < b[i] + ret){ 
                if(a[i-1]!='a'){val=10+a[i]-b[i]-ret; ret=1; res[i]=val;}
                else { printf("comportement non pris en compte, a[%d]=%d\n", i, a[i]);}
            }
        }
        if(a[i]!='a' && b[i]=='a'){
            if(a[i]-ret>=0){ res[i]=a[i]-ret; } 
            if(a[i]-ret<0){ val=10+a[i]-ret; ret=1; res[i]=val; } 
        }
    }
    if(a!=a1){return rendNegatif(res);}
    return res;
}

void triTab(char *a){ /* tri croissant */
    int i = 0, pos, j, tmp;
    while(a[i]=='a'){++i;}
    pos = i;
    for(i=pos; i<999; ++i){
        for(j=i+1; j<=999; ++j){
            if(a[i] > a[j]){
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void inverseTri(char * a){ /* tri décroissant */
    int i = 0, pos, j, tmp;
    while(a[i]=='a'){++i;}
    pos = i;
    for(i=pos; i<999; ++i){
        for(j=i+1; j<=999; ++j){
            if(a[i] < a[j]){
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

/*Retourne une la position où il y a une cassure
 * où on ne se retrouve plus dans une suite décroissante
 */
int debutPermutation(char *a){
    int i = 999;
    while(a[i-1]>=a[i] && a[i-1]!='a'){--i;}
    if(a[i-1]=='a'){return -1;}else{return i-1;}
}

void sortSubString(char *a, int place){
    int i = place + 1, j, tmp;
    for(i=place+1; i<999; ++i){
        for(j=i+1; j<=999; ++j){
            if(a[i] > a[j]){
                tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
    }
}

void findAndPlacePivot(char *a, int place){
    int posPivot = place + 1, curval = a[place+1], tmp, i; 
    for(i=place+1; i<=999; i++){
        if(a[i] > a[place] && a[i] < curval){
            posPivot = i; curval=a[i];
        }
    }
    tmp = a[place];
    a[place] = a[posPivot];
    a[posPivot] = tmp;
    sortSubString(a, place);
}

char * plusGrandeValeur(char *a){
    char * b = (1001*sizeof(char));
    b[1000] = '\0';
    int i;
    for(i=0; i<=999; ++i){b[i]=a[i];}
    inverseTri(b);
    return b;
}

int egalite(char *a, char *b){
    int counta = 0, countb = 0, i=0;
    while(i<1000){
        if(a[i]!='a'){++counta;}
        if(b[i]!='a'){++countb;}
    }
    if(counta == countb){
        for(i=999; i>=999-counta; --i){ if(a[i]!=b[i]){return 0;} }
    }
    if(counta != countb){return 0;}
    return 1;
}

void permuteValeurSuperieur(char *a, char *max){
    int cassure;
    if(egalite(a, max)==0){
        cassure = debutPermutation(a);
        findAndPlacePivot(a, cassure);
    }
    else{
        bigAffiche(a); printf(" = "); bigAffiche(max); printf("\n"); 
    }
}


int main(){
	int j;
	char * pt, * max;

	for(j=12; j<=1000; j++){ 
		pt = intToTab(j);
        max = plusGrandeValeur(j);
        permuteValeurSuperieur(pt, max);
	}
	return 0;
}
