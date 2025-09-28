	#include <stdio.h>
	#include <math.h>
	#include <string>
	struct DDK {
	double x;
	double y;
	double z;
	};
	DDK l[100], x[100];
	double t[100];
 double U[100];
	int n, p;
	double N[100][100], NT[100][100];
	double nT[100][100], C[100][100];
	DDK Q[100], q[100];
	int h;
	void xay_dung_vector_T(DDK *l, int n, double *t) {
	double mau = 0;
	for (int i = 0; i < n + 1; i++) {
	mau += sqrt((l[i + 1].x - l[i].x) * (l[i + 1].x - l[i].x) + (l[i + 1].y - l[i].y) * (l[i + 1].y - l[i].y));
	}
	t[0] = 0;
	t[n + 1] = 1;
	for (int i = 1; i < n + 1; i++) {
	t[i] = t[i - 1] + sqrt((l[i].x - l[i - 1].x) * (l[i].x - l[i - 1].x) + (l[i].y - l[i - 1].y) * (l[i].y - l[i - 1].y)) / mau;
	}
	 
	}
	 
	void xay_dung_vector_U(int p, int h, double *U, double *t) {
	for (int i = 0; i <= p; i++) {
	U[i] = 0;
	}
	double sum = 0;
	for (int j = 1; j <= h - p; j++) {
	for (int i = j; i <= j + p - 1; i++) {
	sum += t[i];
	}
	U[j + p] = sum;
	sum = 0;
	}
	for (int i = h + 1; i <= h + p + 1; i++) {
	U[i] = 1;
	}
	}
	 
	void Xay_dung_phuong_trinh_xac_dinh_cac_dinh_dieu_khien(int h, int n, int p, double *t, double *U, double N[][100], double nT[][100], DDK *Q, DDK *l, DDK *q) {
	for (int i = 0; i <= n + 1; i++) {
	//xay dung ham co so,chay cac tham so t;
	for (int k = 0; k <= p; k++) {
	for (int j = 0; j <= (h + p - k); j++) {
	if (k == 0) {
	if (U[j] <= t[i] && t[i] < U[j + 1])
	N[j][0] = 1;
	else
	N[j][0] = 0;
	}
	if (k >= 1) {
	double alpha1;
	double alpha2;
	if (U[j + k] == U[j]) {
	//tranh truong hop mau=0;
	alpha1 = 0;
	} else
	alpha1 = (t[i] - U[j]) / (U[j + k] - U[j]);
	if (U[j + k + 1] == U[j + 1]) {
	//tranh truong hop mau=0;
	alpha2 = 0;
	} else
	alpha2 = (U[j + k + 1] - t[i]) / (U[j + k + 1] - U[j + 1]);
	 
	N[j][k] = alpha1 * N[j][k - 1] + alpha2 * N[j + 1][k - 1];
	}
	if (0 < i && i < n + 1 && k == p) {
	if (j != 0 && j <= h - 1) {
	nT[j][i] = N[j][p];
 	 
	}
	}
	}
	}
	 
	Q[i].x = l[i].x - N[0][p] * l[0].x - N[h][p] * l[n].x;
	Q[i].y = l[i].y - N[0][p] * l[0].y - N[h][p] * l[n].y;
	Q[i].z = l[i].z - N[0][p] * l[0].z - N[h][p] * l[n].z;
 
	for (int m = 0; m <= h; m++) {
	q[m].x += Q[i].x * N[m][p];
	q[m].y += Q[i].y * N[m][p];
	q[m].z += Q[i].z * N[m][p];
}
	}
	 
}
	 
	void chuyen_vi(double nT[][100], int n, int h, double NT[][100]) {
	for (int j = 1; j <= h - 1; j++)
	for (int i = 1; i <= n; i++) {
	NT[i][j] = nT[j][i];
	}
	 
	}
	void tinh_NT_nhan_nT(int n, int h, double NT[][100], double nT[][100], double C[][100]) {
	for (int i = 1; i <= h - 1; i++)
	for (int j = 1; j <= h - 1; j++) {
	C[i][j] = 0;
	for (int k = 1; k <= n; k++)
	C[i][j] += nT[i][k] * NT[k][j];
	}
	for (int i = 1; i <= h - 1; i++)
	for (int j = 1; j <= h - 1; j++)
	printf("%lf",C[i][j]);
	}
	void xuat(double C[100][100], int h) {
	printf("\n");
	for (int i = 1; i <= h - 1; i++) {
	printf("\n");
	for (int j = 1; j <= h - 1; j++)	printf("%lf\t", C[i][j]);
	}
	}
	void xuat_nghiem(DDK x[], int h, char s) {
	printf("\nNghiem cua he phuong trinh tuyen tinh");
	for (int i = 1; i <= h - 1; i++) {
	printf("s");
	printf("%d", i);
	printf("=");
	printf("%lf,%lf,%lf\n", x[i].x, x[i].y, x[i].z);
	}
	}
	bool he_tam_giac_duoi(double C[][100], DDK x[], DDK q[], int h) {
	for (int i = 1; i <= h - 1; i++) {
	if (C[i][i] != 0) {// neu khong co phân tu duong chéo bàng 0
	if (i == 1) {//dong dau tien c*x=q->x=q/c
	x[i].x = q[i].x / C[i][i];
	x[i].y = q[i].y / C[i][i];
	x[i].z = q[i].z / C[i][i];
	} else {//neu khong thi x=q ròi trù dòn c*x khác 
	x[i].x = q[i].x;
    x[i].y = q[i].y;
	x[i].z = q[i].z;
	for (int j = 1; j < i; j++) {
	x[i].x = x[i].x - C[i][j] * x[j].x;
	x[i].y = x[i].y - C[i][j] * x[j].y;
	x[i].z = x[i].z - C[i][j] * x[j].z;
	}
	x[i].x = x[i].x / C[i][i];
	x[i].y = x[i].y / C[i][i];
	x[i].z = x[i].z / C[i][i];
	 
	}
	} else
	return 0;
	}
	return 1;
	}
	bool he_tam_giac_tren(double C[][100], DDK x[], DDK q[], int h) {
	for (int i = h - 1; i >= 1; i--) {
	if (C[i][i] != 0) {//neu không có phan tu tren duong cheo bang 0
	if (i == h - 1) {//neu la phan tu cuoi c*x=q
	x[i].x = q[i].x / C[i][i];
	x[i].y = q[i].y / C[i][i];
	x[i].z = q[i].z / C[i][i];
	} else {//neu khong thi x=q ròi trù dòn c*x khác 
	x[i].x = q[i].x;
	x[i].y = q[i].y;
	x[i].z = q[i].z;
	for (int j = i + 1; j <= h - 1; j++) {
	x[i].x = x[i].x - C[i][j] * x[j].x;
	x[i].y = x[i].y - C[i][j] * x[j].y;
	x[i].z = x[i].z - C[i][j] * x[j].z;
	}
	x[i].x = x[i].x / C[i][i];
	x[i].y = x[i].y / C[i][i];
	x[i].z = x[i].z / C[i][i];
	 
	}
	} else
	return 0;
	}
	return 1;
	}
	void phan_ra_lu(double C[100][100], double L[100][100], double U[100][100], int h) {
	for (int k = 1; k <= h - 1; k++) {
	U[k][k] = C[k][k];//hàng chéo ma trân U bàng hàng chéo ma trân C
	L[k][k] = 1;//hàng chéo ma trân L bàng 1
	for (int i = k + 1; i <= h - 1; i++) {
	L[i][k] = C[i][k] / U[k][k];// dòng tiêp theo L  bàng dòng tieeeeps theo ma trân C chia phân tu cheo ma trân U
	U[k][i] = C[k][i];//ma trân U cùng dòng dó các côt tiêp theo bang phan tu ma tran C cung dong dó các côt tiêp theo tuong ung
	U[i][k] = 0;// phan tu ma  trân U dong tiep theo cung cot bang 0
	L[k][i] = 0;//phan tu ma L cot tiep theo  cùng dòng bang 0 
	}
	for (int i = k + 1; i <= h - 1; i++)
	for (int j = k + 1; j <= h - 1; j++)
	C[i][j] = C[i][j] - L[i][k] * U[k][j];//cap nhat phan tu ma tran C côt tiêp theo và dòng tiêp theo
	}
	}
	 
	void giai_he_pttt(double C[100][100], DDK x[100], DDK q[100], int h) {
double L[100][100], U[100][100];
	DDK Y[100];
	 
	phan_ra_lu(C, L, U, h);
	 
	if (he_tam_giac_duoi(L, Y, q, h)) {
	 
	if (he_tam_giac_tren(U, x, Y, h))
	xuat_nghiem(x, h, 'x');
	else
	printf("\n He pttt ko co ngiem duy nhat");
	} else
	printf("\n He pttt ko co ngiem duy nhat");
	}
	void input() {
	int choice ;
	while(true) {
	printf("Enter 1 : Nhap tu Console \n");
	printf("Enter 2 : Nhap tu file \n");
	scanf("%d",&choice);
	if(choice == 1 || choice == 2) break ;
	else printf("Lua chon khong hop le\n");
	}
	if(choice==2) {
	FILE* file=fopen("input.txt","r");
	fscanf(file,"%d", &h);
	fscanf(file,"%d", &n);
	printf("so dinh dieu khien la %d:\n",h+1);
	for (int i = 0; i <= n + 1; i++) {
	fscanf(file,"%lf%lf", &l[i].x, &l[i].y);
	}
	fscanf(file, "%d", &p);
	} else {
	printf("nhap h:");
	scanf("%d",&h);
	printf("so dinh dieu khien la %d:",h+1);
	printf("\n nhap n:");
	scanf("%d",&n);
	printf("\n nhap diem du lieu:");
	for(int i=0; i<=n+1; i++) {
	scanf("%lf%lf",&l[i].x,&l[i].y);
	}
	printf("bac p =");
	scanf("%d",&p);
	}
	}
	void solve() {
xay_dung_vector_T(l, n, t);
	 
	xay_dung_vector_U(p, h, U, t);
	 
	Xay_dung_phuong_trinh_xac_dinh_cac_dinh_dieu_khien(h, n, p, t, U, N, nT, Q, l, q);
	 
	chuyen_vi(nT, n, h, NT);
	 
	tinh_NT_nhan_nT(n, h, NT, nT, C);
	 
	giai_he_pttt(C, x, q, h);
	}
	int main() {
	input();
	solve();
	return 0;
	}

