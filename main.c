//������ ����
//Ŀ���̵��Լ�
//system cls�Լ�
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

int random();										//�����߻��Լ�
void Draw_Field();									//�ʵ�׸����Լ�
void Pattern_Set(int x);								//ī��������Լ�
void gotoxy(int x, int y);							//Ŀ���̵��Լ�
void Number_Set(int x);									//ī����ڰ����Լ�
int Pair_Check(int c[],int *a);						//�������Լ�
void jockbo(int a,int b);									//��������Լ�
int Pattern_Check(int c[]);							//��������Լ�
int Winner(int a,int b,int c,int d,int *x, int *y);	//���ڰ����Լ�
void Play_Game();									//�����ϴ��Լ�
void How_to_Play();									//�����ϴ� ����˷��ִ� �Լ�
void erase();										//�ʵ�Ŭ����
int One_pair(int a[]);								//��ǻ���ΰ����ɿ����
int Two_pair(int a[]);								//��ǻ���ΰ����������
int Triple(int a[]);								//��ǻ���ΰ�����Ʈ����
float get_money(int a,int b);								//���¸��� ���� ���� �Լ�

void main()
{
	char ch;
	gotoxy(20, 10);
	printf("��Ŀ���� v1.0\n");
	gotoxy(20, 13);
	printf("(������ : ����)");
	gotoxy(10, 15);
	printf("(�����Ϸ��� ����Ű�� �����ּ���)");
	ch = getch();
	if (ch == 13) {
		system("cls");
		How_to_Play();
	}
	system("pause");
}

void Play_Game()
{
	int p1 = 0, p2 = 0, i, j, cnt = 0, c = 0, min = 20, sa1 = 0, sa2 = 0, sb1 = 0, sb2 = 0, change = 0, change1 = 0, Coin = 20, Bet = 0, Flag = 0, difficulty=0,must=0;
	int  a1[5] = { 0 }, a2[5] = { 0 }, a3[5] = { 0 }, b1[5] = { 0 }, b2[5] = { 0 }, b3[5] = { 0 }, tmp[3] = { 0 }, ch[3] = { 0 }, ch1[3] = {0};
	int one = 0, two = 0, tri = 0;
	int com = 0, ply = 0;			//com �� ��ǻ���� �����ڸ� ����, ply �� �÷��̾��� �����ڸ� ����, mul�� ��������
	float mul = 1;
	printf("\n");
	printf("1. 500���γѱ��\n");
	printf("2. 1000���γѱ��\n");
	printf("3. 3000���γѱ��\n");
	printf("4. 5000���γѱ��\n");
	printf("5. 10000���γѱ��\n");
	printf("6. 100000���γѱ��\n");
	gotoxy(0, 0);
	printf("���̵��� �������ּ��� : ");		//�󸶸� �Ѱܾ� ������ �¸��ϳ�?
	scanf("%d", &difficulty);
	if (difficulty == 1)	must = 500;
	else if (difficulty == 2)	must = 1000;
	else if (difficulty == 3)	must = 3000;
	else if (difficulty == 4)	must = 5000;
	else if (difficulty == 5)	must = 10000;
	else if (difficulty == 6)	must = 100000;
	do {
		erase();
		gotoxy(0, 0);
		printf("������ ������ ������ �Է��ϼ��� (���� ���μ� : %d): ", Coin);	//���ι���
		while (1) {
			scanf("%d", &Bet);
			if (Bet <= Coin)	break;
			else printf("�ݾ��� �ʰ��Ǿ����ϴ�. �ٽ� �Է����ּ��� : ");			//�������κ��� ���������� ������
		}
		Coin -= Bet;
		erase();
		gotoxy(0, 6);
		printf("���� ���μ� : %d", Coin);
		gotoxy(0, 8);
		printf("������ ���μ� : %d", Bet);
		gotoxy(0, 0);
		printf("Computer\n");
		Draw_Field();
		printf("\n\n\n");
		printf("You\n");
		Draw_Field();
		for (i = 0; i < 5; i++) {	//ī�� �ټ���̴� �ݺ���
			while (1) {				//�ߺ��� �ִ��� Ȯ���ϴ� �ݺ���
				cnt = 0;
				p1 = random();
				for (j = 0; j < 5; j++) {
					if (p1 == a3[j] || p1 == b3[j])	cnt += 1;
				}
				if (cnt == 0)	break;
			}
			getchar();
			a1[i] = (p1 - 1) / 13;
			a2[i] = p1 % 13;
			a3[i] = p1;
			gotoxy(4 * i + 2, 2);
			printf("��");			//��ǻ�� ī���д� �������� ����
			gotoxy(4 * i + 2, 4);
			printf("��");
			while (1) {				//�ߺ��� �ִ��� Ȯ���ϴ� �ݺ���
				cnt = 0;
				p2 = random();
				for (j = 0; j < 5; j++) {
					if (p2 == a3[j] || p2 == b3[j])	cnt += 1;
				}
				if (cnt == 0)	break;
			}
			b1[i] = (p2 - 1) / 13;	//b1�� ���� ����
			b2[i] = p2 % 13;		//b2�� ī���������
			b3[i] = p2;				//b3�� ī�������ȣ����
			gotoxy(4 * i + 2, 11);
			Pattern_Set(p2);
			gotoxy(4 * i + 2, 13);
			Number_Set(p2);
		}

		for (j = 0; j < 5; j++) {				//��ǻ��ī�� ������������(��������)
			min = 20;
			for (i = j; i < 5; i++) {
				if (a2[i] < min) {
					min = a2[i];
					c = i;
				}
			}
			tmp[0] = a1[j];
			a1[j] = a1[c];
			a1[c] = tmp[0];
			tmp[1] = a2[j];
			a2[j] = min;
			a2[c] = tmp[1];
			tmp[2] = a3[j];
			a3[j] = a3[c];
			a3[c] = tmp[2];
		}
		sa1 = Pattern_Check(a1);				//��ǻ�� �÷���Ȯ��
		sb1 = Pair_Check(a2,&com);					//��ǻ�� ������Ȯ��

		//���⼭���� ��ǻ�� �ΰ�����
		if (sa1 == 0 && sb1 == 0) {				//������ϰ��
			for (i = 0; i < 3; i++)	ch1[i] = i+1;
		}
		else if (sa1 == 0 && sb1 == 1) {		//������ϰ��
			one = One_pair(a2);
			if (one == 0) {
				ch1[0] = 3;
				ch1[1] = 4;
				ch1[2] = 5;
			}
			else if (one == 1) {
				ch1[0] = 1;
				ch1[1] = 4;
				ch1[2] = 5;
			}
			else if (one == 2) {
				ch1[0] = 1;
				ch1[1] = 2;
				ch1[2] = 5;
			}
			else if (one == 3) {
				ch1[0] = 1;
				ch1[1] = 2;
				ch1[2] = 3;
			}
		}
		else if (sa1 == 0 && sb1 == 2) {		//������ϰ��
			two = Two_pair(a2);
			if (two == 1)	ch[0] = 5;
			else if (two == 2)	ch[0] = 3;
			else if (two == 3)	ch[0] = 1;
		}
		else if (sa1 == 0 && sb1 == 3) {		//Ʈ�����ϰ��
			tri = Triple(a2);
			if (tri == 1) {
				ch[0] = 1;
				ch[1] = 2;
			}
			else if (tri == 2) {
				ch1[0] = 1;
				ch1[1] = 5;
			}
			else if (tri == 3) {
				ch1[0] = 4;
				ch1[1] = 5;
			}
		}

		for (i = 0; i < 3; i++) {				//���� �ٲ� ī�尡 ������ change1 = -1 �� �ɰ��̴�.
			if (ch1[i] == 0) {					//�ٲ�ī�尹�� ����
				change1 = i - 1;
				break;
			}
			else change1 = 2;					//�´� �ٲٱ�
		}

		if (change1 != -1) {					//change = -1 �̸� ī�带 �ٲ��� �ʴ´�.
			for (i = 0; i <= change1; i++) {
				a1[ch1[i] - 1] = 0;
				a2[ch1[i] - 1] = 0;
				a3[ch1[i] - 1] = 0;
				while (1) {						//�ߺ��� �ִ��� Ȯ���ϴ� �ݺ���
					cnt = 0;
					p1 = random();
					for (j = 0; j < 5; j++) {
						if (p1 == a3[j] || p1 == b3[j])	cnt += 1;
					}
					if (cnt == 0)	break;
				}
				a1[ch1[i] - 1] = (p1 - 1) / 13;	//���λ��� ī���� ����
				a2[ch1[i] - 1] = p1 % 13;		//���λ��� ī���� ����
				a3[ch1[i] - 1] = p1;			//���λ��� ī���� �������̽�
			}
		}

		for (j = 0; j < 5; j++) {				//ī�� �ٲ� �� ��ǻ��ī�� ������������(��������)
			min = 20;
			for (i = j; i < 5; i++) {
				if (a2[i] < min) {
					min = a2[i];
					c = i;
				}
			}
			tmp[0] = a1[j];
			a1[j] = a1[c];
			a1[c] = tmp[0];
			tmp[1] = a2[j];
			a2[j] = min;
			a2[c] = tmp[1];
			tmp[2] = a3[j];
			a3[j] = a3[c];
			a3[c] = tmp[2];
		}

		//������� ��ǻ�� �ΰ�����


		sa1 = Pattern_Check(a1);				//�ٲٰ� �� �� ��ǻ�� �÷���Ȯ��
		sb1 = Pair_Check(a2,&com);					//�ٲٰ� �� �� ��ǻ�� ������Ȯ��
		gotoxy(0, 18);
		for (i = 0; i < 3; i++) {				//ī��ٲٱ�ݺ���
			printf("�ٲ� ī���ȣ�� ���徿 �Է��ϼ���(�ִ� 3��,������ 6) : ");
			scanf("%d", &ch[i]);
			while (1) {
				if (ch[i] > 6 || ch[i] < 1)	printf("�ٽ��Է��ϼ��� : ");
				else break;
				scanf("%d", &ch[i]);
			}
			if (ch[i] == 6)	break;
		}

		for (i = 0; i < 3; i++) {				//���� �ٲ� ī�尡 ������ change = -1 �� �ɰ��̴�.
			if (ch[i] == 6 || ch[i] == 0) {		//�ٲ�ī�尹�� ����
				change = i - 1;
				break;
			}
			else change = 2;
		}

		if (change != -1) {						//change = -1 �̸� ī�带 �ٲ��� �ʴ´�.
			for (i = 0; i <= change; i++) {
				b1[ch[i] - 1] = 0;
				b2[ch[i] - 1] = 0;
				b3[ch[i] - 1] = 0;
				while (1) {						//�ߺ��� �ִ��� Ȯ���ϴ� �ݺ���
					cnt = 0;
					p2 = random();
					for (j = 0; j < 5; j++) {
						if (p2 == a3[j] || p2 == b3[j])	cnt += 1;
					}
					if (cnt == 0)	break;
				}
				b1[ch[i] - 1] = (p2 - 1) / 13;
				b2[ch[i] - 1] = p2 % 13;
				b3[ch[i] - 1] = p2;
				gotoxy(4 * ch[i] - 2, 11);
				Pattern_Set(p2);
				gotoxy(4 * ch[i] - 2, 13);
				Number_Set(p2);
			}
		}

		for (j = 0; j < 5; j++) {				//�����ī�� ������������
			min = 20;
			for (i = j; i < 5; i++) {
				if (b2[i] < min) {
					min = b2[i];
					c = i;
				}
			}
			tmp[0] = b1[j];
			b1[j] = b1[c];
			b1[c] = tmp[0];
			tmp[1] = b2[j];
			b2[j] = b2[c];
			b2[c] = tmp[1];
			tmp[2] = b3[j];
			b3[j] = b3[c];
			b3[c] = tmp[2];
		}
		sa2 = Pattern_Check(b1);				//����� �÷���Ȯ��
		sb2 = Pair_Check(b2,&ply);					//����� ������Ȯ��
		for (i = 0; i < 5; i++) {
			gotoxy(4 * i + 2, 2);
			Pattern_Set(a3[i]);
			gotoxy(4 * i + 2, 4);
			Number_Set(a3[i]);
		}
		gotoxy(0, 15);
		printf("Computer�� �д� : ");
		jockbo(sa1, sb1);
		printf(" ");
		Number_Set(com);
		printf("\n");
		printf("����� �д� : ");
		jockbo(sa2, sb2);
		printf(" ");
		Number_Set(ply);
		printf("\n");
		getchar();
		Flag=Winner(sb1, sb2, sa1, sa2,&com,&ply);
		if (Flag == 1) {
			Bet = 0;
		}
		else if (Flag == 2) {
			mul=get_money(sa2,sb2);
			Bet *= mul;
		}
		else if (Flag == 3) {
			Bet *= 1;
		}
		Coin +=Bet;
		Bet = 0;
		if (Coin >= must)	break;
		if(Coin > 0)printf("����Ϸ��� enter�� �����ʽÿ�"); getchar();
	}while (Coin > 0);
	if(Coin == 0) printf("Game Over!!\n");
	else if (Coin > 0)	printf("Victory!!\n");
}

int One_pair(int a[])
{
	int i;
	for (i = 0; i < 4; i++) {
		if (a[i] == a[i + 1])	break;
	}
	return i;
}

int Two_pair(int a[])
{
	int i = 0;
	if (a[0] == a[1] && a[2] == a[3])	i = 1;
	else if (a[0] == a[1] && a[3] == a[4])	i = 2;
	else if (a[1] == a[2] && a[3] == a[4])	i = 3;
	return i;
}

int Triple(int a[])
{
	int i = 0;
	if (a[2] == a[3] && a[3] == a[4])	i = 1;
	else if (a[1] == a[2] && a[2] == a[3])	i = 2;
	else if (a[0] == a[1] && a[1] == a[2])	i = 3;
	return i;
}

void erase()									//�ʵ��� ���������
{
	int i, j;
	for (i = 0; i < 60; i++) {
		for (j = 0; j < 30; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
}

float get_money(int a,int b)
{
	float i;
	if (a == 0 && b == 0)	i = 2;
	else if (a == 0 && b == 1)	i = 2.3;
	else if (a == 0 && b == 2)	i = 2.5;
	else if (a == 0 && b == 3)	i = 3;
	else if (a == 0 && b == 4)	i = 3.5;
	else if (a == 0 && b == 5)	i = 4;
	else if (a == 0 && b == 6)	i = 5;
	else if (a == 1 && b <3)	i = 6;
	else if (a == 0 && b == 7)	i = 7;
	else if (a == 0 && b == 8)	i = 8;
	else if (a == 1 && b == 4)	i = 10;
	else if (a == 1 && b == 5)	i = 20;
	else if (a == 1 && b == 6)	i = 50;
	return i;
}

void How_to_Play()								//2��° ������ ���ӹ������
{
	int Coin = 5;
	char ch;
	printf("�ذ��ӹ����\n");
	printf("ī��̱� : enterŰ\n");
	printf("�¸��ϸ� �Ʒ� ��ȣ�� ������ŭ �ް�, �й��ϸ� �������մϴ�.(���ºν� ���ñ� ��������)\n");
	printf("����(���ΰ����� ����)\n\n");
	printf("-�ξ⽺Ʈ����Ʈ�÷���(X50)\n");
	printf("-�齺Ʈ����Ʈ�÷���(X20)\n");
	printf("-��Ʈ����Ʈ�÷���(X10)\n");
	printf("-��ī��(X8)\n");
	printf("-Ǯ�Ͽ콺(X7)\n");
	printf("-�÷���(X6)\n");
	printf("-����ƾ(X5)\n");
	printf("-�齺Ʈ����Ʈ(X4)\n");
	printf("-��Ʈ����Ʈ(X3.5)\n");
	printf("-Ʈ����(X3)\n");
	printf("-�����(X2.5)\n");
	printf("-�����(X2.3)\n");
	printf("-�����(X2)\n\n");
	printf("����Ϸ��� enter�� �����ּ���");
	ch = getch();
	if (ch == 13) {
		system("cls");
		Play_Game();
	}
}

int Winner(int a,int b,int  c,int  d,int *x,int *y)						//a : ��ǻ�� ������, b : ����� ������, c : ��ǻ�� �÷���, d : ����� �÷���
{
	int e=0;
	gotoxy(0, 25);
	if (c == 1 && d == 1) {
		if (a > b) { 
			printf("��ǻ�� �¸�!!\n");
			e = 1;
		}
		else if (a < b) { 
			printf("����� �¸�!!\n");
			e = 2;
		}
		else { 
			if (*x > *y) { 
				printf("��ǻ�� �¸�!!\n"); 
				e = 1;
			}
			else if(*x<*y){ 
				printf("����� �¸�!!\n");
				e = 2;
			}
			else
			{
				printf("���º�!!\n");
				e = 3;
			}
		}
	}
	else if (c > d) { 
		if (b >= 6 && b <= 7 && a < 4) {
			printf("����� �¸�!!\n");
			e = 2;
		}
		else {
			printf("��ǻ���� �¸�!!\n");
			e = 1;
		}
	}
	else if (c < d) { 
		if (a >= 6 &&a <= 7 && b < 4) {
			printf("��ǻ���� �¸�!!\n");
			e = 1;
		}
		else {
			printf("����� �¸�!!\n");
			e = 2;
		}
	}
	else if (c == 0 && c == 0) {
		if (a > b) { 
			printf("��ǻ�� �¸�!!\n"); 
			e = 1;
		}
		else if (a < b) { 
			printf("����� �¸�!!\n"); 
			e = 2;
		}
		else {
			if (*x > *y) {
				printf("��ǻ�� �¸�!!\n");
				e = 1;
			}
			else if (*x<*y) {
				printf("����� �¸�!!\n");
				e = 2;
			}
			else
			{
				printf("���º�!!\n");
				e = 3;
			}
		}
	}
	return e;
}

int Pattern_Check(int c[])		//���ڹ迭 �ҷ�������
{
	int a=0;
	if (c[0] == c[1] && c[1] == c[2] && c[2] == c[3] && c[3] == c[4])	a += 1;
	return a;
}

void jockbo(int a,int b)				//a�� ��������, b�� ��������
{
	if (a == 1 && b == 6)	printf("�ξ� ��Ʈ����Ʈ �÷���");
	else if (a == 1 && b == 5)	printf("�� ��Ʈ����Ʈ �÷���");
	else if (a == 1 && b == 4)	printf("��Ʈ����Ʈ �÷���");
	else if (a == 0 && b == 8)	printf("��ī��");
	else if (a == 0 && b == 7)	printf("Ǯ�Ͽ콺");
	else if (a == 1 && b < 4)	printf("�÷���");
	else if (a == 0 && b == 6)	printf("����ƾ");
	else if (a == 0 && b == 5)	printf("�齺Ʈ����Ʈ");
	else if (a == 0 && b == 4)	printf("��Ʈ����Ʈ");
	else if (a == 0 && b == 3)	printf("Ʈ����");
	else if (a == 0 && b == 2)	printf("�����");
	else if (a == 0 && b == 1)	printf("�����");
	else printf("�����");
}

int Pair_Check(int c[], int *a)			//���ڹ迭�ҷ�������.
{
	int b = 0;
	*a = 0;
	b = 0;
	if (c[0] == c[1] && c[1] == c[2] && c[2] == c[3] || c[1] == c[2] && c[2] == c[3] && c[3] == c[4]) {
		if (c[0] == c[1] && c[1] == c[2] && c[2] == c[3])	*a += c[0];
		else if (c[1] == c[2] && c[2] == c[3] && c[3] == c[4]) *a += c[1];
		b = 8;
	}			//��ī��
	else if (c[0] == c[1] && c[1] == c[2] && c[3] == c[4] || c[0] == c[1] && c[2] == c[3] && c[3] == c[4]) {
		if (c[0] == c[1] && c[1] == c[2] && c[3] == c[4])	*a += c[0];
		else if (c[0] == c[1] && c[2] == c[3] && c[3] == c[4])	*a += c[2];
		b = 7;
	}		//Ǯ�Ͽ콺
	else if (c[0] == 8 && c[1] == 9 && c[2] == 10 && c[3] == 11 && c[4] == 12)	b += 6;							//����ƾ
	else if (c[0] == 0 && c[1] == 1 && c[2] == 2 && c[3] == 3 && c[4] == 13) b = +5;							//�齺Ʈ����Ʈ
	else if (c[4] == c[0] + 4 && c[4] == c[1] + 3 && c[4] == c[2] + 2 && c[4] == c[3] + 1) {
		*a += c[4];
		b = 4;
	}//��Ʈ����Ʈ
	else if (c[0] == c[1] && c[1] == c[2] || c[1] == c[2] && c[2] == c[3] || c[2] == c[3] && c[3] == c[4]) {
		if (c[0] == c[1] && c[1] == c[2])	*a += c[0];
		else if (c[1] == c[2] && c[2] == c[3])	*a += c[1];
		else *a += c[2];
		b = 3;
	}	//Ʈ����
	else if ((c[0] == c[1] && (c[2] == c[3] || c[3] == c[4])) || c[1] == c[2] && c[3] == c[4]) {
		if (c[0] == c[1] && c[2] == c[3]) {
			if (c[0] > c[2])	*a += c[0];
			else *a += c[2];
		}
		else if (c[0] == c[1] && c[3] == c[4]) {
			if (c[0] > c[3])	*a += c[0];
			else *a += c[3];
		}
		else if (c[1] == c[2] && c[3] == c[4]) {
			if (c[1] > c[3])	*a += c[1];
			else *a += c[3];
		}
		b = 2;
	}					//�����
	else if (c[0] == c[1] || c[1] == c[2] || c[2] == c[3] || c[3] == c[4]) {
		if (c[0] == c[1])	*a += c[0];
		else if (c[1] == c[2])	*a += c[1];
		else if (c[2] == c[3])	*a += c[2];
		else if (c[3] == c[4])	*a += c[3];
		b = 1;
	}									//�����
	else *a += c[4];																										//�����(ž)
	return b;
}

void Number_Set(int x)
{
	int a = 0;
	a = x % 13;
	if (a == 0) printf("2 ");
	else if (a == 1) printf("3 ");
	else if (a == 2) printf("4 ");
	else if (a == 3) printf("5 ");
	else if (a == 4) printf("6 ");
	else if (a == 5) printf("7 ");
	else if (a == 6) printf("8 ");
	else if (a == 7) printf("9 ");
	else if (a == 8) printf("10");
	else if (a == 9) printf("J ");
	else if (a == 10) printf("Q ");
	else if (a == 11) printf("K ");
	else printf("A ");
}

void Pattern_Set(int x)
{
	int a = 0;
	a = (x - 1) / 13;
	if (a == 0) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else if (a == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else if (a == 2) {
		printf("��"); 
	}
	else {
		printf("��");
	}
}

int random()
{
	int a;
	srand(GetTickCount());
	a = rand() % 52 + 1;
	return a;
}

void Draw_Field()
{
	printf("����������������������\n");
	printf("��  ��  ��  ��  ��  ��\n");
	printf("����������������������\n");
	printf("��  ��  ��  ��  ��  ��\n");
	printf("����������������������\n");
}

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}