#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define EPS 0.01

/*Thiet lap cac tham so cho duong cong B-spline noi suy cho cac diem du lieu*/

void toadoD(int n, float D[100]) {
	int z=0;
	for(int i=0; i<=n; i++) {
		printf ("D%i= (%f %f)\n", i, D[z], D[z+1]); //in ra toa do D
		z+=2;
	}
}

void toadoP(int n,float P[100]) {
	int z=0;
	for(int i=0; i<(n+1); i++) {

		printf("P%i= (%f %f)\n",i,P[z],P[z+1]); //in ra toa do P
		z+=2;
	}
}
/*Xay dung vecto tham so T tu tap diem du lieu*/

void dodaidaycung(int n,float D[100],float *d) {
	int i=1;
	for(int k=1; k<=n+1; k++) {
		*d+=sqrt(pow(D[i+1]-D[i-1],2.0)+pow(D[i+2]-D[i],2.0));
		i+=2;
	}

}
void T(int n,float D[100],float t[100],float d) {
	t[0]=0; //t dau tien =0
	t[n]=1; //t cuoi =0

	int i=1;
	for(int k=1; k<=n-1; k++) {
		t[k]=t[k-1] + sqrt(pow(D[i+1]-D[i-1],2.0)+pow(D[i+2]-D[i],2.0))/d;

		i+=2;
	}
}
/*xay dung vecto nut U cho duong cong B-spline noi suy*/

void taovectonutU(int n,float t[100],int p,float u[100]) {
	/*tao vector nut U*/
	for(int i=0; i<=p; i++) {
		u[i]=0;
	}
	double sum=0;
	for(int j=1; j<=n-p; j++) {
		for(int i=j; i<=j+p-1; i++)
			sum+=t[i];
		u[j+p]=sum/(float)p;
		sum=0;
	}
	for(int i=n+1; i<=n+p+1; i++) {
		u[i]=1;
	}
}
/*Xay dung he phuong trinh xac dinh cac dinh dieu khien*/

float hamcosoN(int n,int i,int p,float t,float u[100]) {
	float tich1;
	float tich2;
	if(u[i+p]==u[i]) tich1=0;
	else tich1=((t-u[i])/(u[i+p]-u[i])) * hamcosoN(n,i,p-1,t,u);
	if(u[i+p+1]==u[i+1]) tich2=0;
	else tich2=((u[i+p+1]-t)/(u[i+p+1]-u[i+1]))* hamcosoN(n,i+1,p-1,t,u);
	if(p==0) {
		if(t>=u[i] && t<u[i+1]) return 1;
		else return 0;
	} else {

		return tich1+tich2;
	}
}

void taomatranN(int n,int p,float N[100][100],float t[100],float u[100]) { //tinh mt N & xuat mt N
	N[0][0]=1;
	N[n][n]=1;
	for(int j=1; j<=n; j++) N[0][j]=0; //gan 0 cho cac phan tu hang 0
	for(int j=n-1; j>=0; j--) N[n][j]=0; //gan 0 cho cac phan tu hang n

	for(int i=0; i<=n-1; i++)
		for(int j=0; j<=n; j++) N[i][j] = hamcosoN(n,j,p,t[i],u); //tu hang 1->hang -1 tinh thong qua cosoN

	for(int i=0; i<=n; i++) {
		for(int j=0; j<=n; j++) printf("%f ",N[i][j]); //xuat mt N
		printf("\n");
	}
	printf("\n");
}

void Dx(int n,float N[100][100],float a[100][100],float D[100]) { //gan N[][] cho a[][] va gan Dx cho a[i][n+1]
	for(int i=0; i<=n; i++) {
		for(int j=0; j<=n+1; j++) {
			if(j==n+1) a[i][j]=D[2*i];
			else a[i][j]=N[i][j]; //neu la cot cuoi thi gan Dx vao,ko phai thi gan N[][]
		}
	}

}

void Dy(int n,float N[100][100],float a[100][100],float D[100]) { //gan N[][] cho a[][] va gan Dy cho a[i][n+1]

	for(int i=0; i<=n; i++) {
		for(int j=0; j<=n+1; j++) {
			if(j==n+1) a[i][j]=D[2*i+1];
			else a[i][j]=N[i][j]; //neu la cot cuoi thi gan Dy vao,ko phai thi gan N[][]
		}
	}

}

void hoandoi(int n,float a[][100],int i,int j) {
	printf("doi hang %i va %i",j,i);
	float t;
	for(int k=0; k<=n+1; k++) {

		t=a[j][k];
		a[j][k]=a[i][k];
		a[i][k]=t;
	}
}

void tamgiactren(int n,float a[][100]) {
	int i,j;
	for(i=0; i<n; i++) {

		if(a[i][i]==0)

			for(int j=i+1; j<=n; j++)
				if(a[j][i]!=0) {
					hoandoi(n,a,i,j);
					break; //dung
				} else {
					printf("");
					return ;
				}

		float m;

		for(j=i+1; j<=n; j++) {
			m=-a[j][i]/a[i][i]; //tinh he so rut gon cua hang i+1 so voi i
			for(int k=i; k<=n+1; k++) a[j][k]=a[j][k]+(a[i][k]*m);
		}
	}
}

void nghiem(int n,float x[],float a[][100]) {
	int i;
	for (i = n; i >=0 ; i--) {
		float s=0;

		for (int j = i+1; j <=n; j++) s=s+a[i][j]*x[j];

		x[i] = (a[i][n+1]-s) / a[i][i]; // ( xi=hesotudohangi-CacTongCua(xk*ak) ) / a[i][i]
		//k LaViTriSauI->ViTriN
	}
}

void LuuXVaoP(int n,float x[100],float P[100]) {

	for(int i=0; i<=n; i++)
		P[2*i]=x[i]; //luu nghiem x vua tinh dc vao vi tri chan mang P
}

void LuuYVaoP(int n,float x[100],float P[100]) {

	for(int i=0; i<=n; i++)
		P[2*i+1]=x[i]; //luu nghiem x vua tinh dc vao vi tri le mang P
}


int main() {
	int n;
	int p;
	float d=0;
	
	printf("Nhap n = ", n);
	scanf("%d", &n);
	printf("Nhap p = ", p);
	scanf("%d", &p);

	float t[100];
	float u[100];
	float D[100];
	float P[100];
	float N[100][100];
	float a[100][100];
	float r[100];
	float x[100];


	for(int i=0; i<2*(n+1); i++) {
		printf("Nhap cac diem du lieu D = ", D[i]);
		scanf("%f",&D[i]);
}
	printf("\n\n diem du lieu D :\n");
	toadoD(n,D);
	dodaidaycung(n,D,&d);
	T(n,D,t,d);
	taovectonutU(n,t,p,u);
	printf("\n");
	printf("ma tran N: \n");
	taomatranN(n, p, N, t, u);


	Dx(n,N,a,D);
	tamgiactren(n, a);
	nghiem(n, x, a);
	LuuXVaoP(n,x,P);

	Dy(n,N,a,D);
	tamgiactren(n, a);
	nghiem(n, x, a);
	LuuYVaoP(n,x,P);


	toadoP(n,P); //xuat P
	printf("\n");
	for (int i=0;i<=n+p+1;i++) {     //xuat U
		printf("u[%d]= %.3f",i,u[i]);
		printf("\n");
}
	return 0;
}
