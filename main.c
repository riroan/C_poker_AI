//참고한 내용
//커서이동함수
//system cls함수
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

int random();										//난수발생함수
void Draw_Field();									//필드그리기함수
void Pattern_Set(int x);								//카드모양결정함수
void gotoxy(int x, int y);							//커서이동함수
void Number_Set(int x);									//카드숫자결정함수
int Pair_Check(int c[],int *a);						//페어결정함수
void jockbo(int a,int b);									//족보출력함수
int Pattern_Check(int c[]);							//문양결정함수
int Winner(int a,int b,int c,int d,int *x, int *y);	//승자결정함수
void Play_Game();									//게임하는함수
void How_to_Play();									//게임하는 방법알려주는 함수
void erase();										//필드클리어
int One_pair(int a[]);								//컴퓨터인공지능원페어
int Two_pair(int a[]);								//컴퓨터인공지능투페어
int Triple(int a[]);								//컴퓨터인공지능트리플
float get_money(int a,int b);								//페어승리에 따른 배율 함수

void main()
{
	char ch;
	gotoxy(20, 10);
	printf("포커게임 v1.0\n");
	gotoxy(20, 13);
	printf("(제작자 : 김명기)");
	gotoxy(10, 15);
	printf("(시작하려면 엔터키를 눌러주세요)");
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
	int com = 0, ply = 0;			//com 은 컴퓨터의 페어숫자를 저장, ply 는 플레이어의 페어숫자를 저장, mul은 배율저장
	float mul = 1;
	printf("\n");
	printf("1. 500코인넘기기\n");
	printf("2. 1000코인넘기기\n");
	printf("3. 3000코인넘기기\n");
	printf("4. 5000코인넘기기\n");
	printf("5. 10000코인넘기기\n");
	printf("6. 100000코인넘기기\n");
	gotoxy(0, 0);
	printf("난이도를 설정해주세요 : ");		//얼마를 넘겨야 게임을 승리하나?
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
		printf("배팅할 코인의 개수를 입력하세요 (보유 코인수 : %d): ", Coin);	//코인배팅
		while (1) {
			scanf("%d", &Bet);
			if (Bet <= Coin)	break;
			else printf("금액이 초과되었습니다. 다시 입력해주세요 : ");			//소유코인보다 배팅코인이 많을떄
		}
		Coin -= Bet;
		erase();
		gotoxy(0, 6);
		printf("남은 코인수 : %d", Coin);
		gotoxy(0, 8);
		printf("배팅한 코인수 : %d", Bet);
		gotoxy(0, 0);
		printf("Computer\n");
		Draw_Field();
		printf("\n\n\n");
		printf("You\n");
		Draw_Field();
		for (i = 0; i < 5; i++) {	//카드 다섯장뽑는 반복문
			while (1) {				//중복이 있는지 확인하는 반복문
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
			printf("■");			//컴퓨터 카드패는 보여주지 않음
			gotoxy(4 * i + 2, 4);
			printf("■");
			while (1) {				//중복이 있는지 확인하는 반복문
				cnt = 0;
				p2 = random();
				for (j = 0; j < 5; j++) {
					if (p2 == a3[j] || p2 == b3[j])	cnt += 1;
				}
				if (cnt == 0)	break;
			}
			b1[i] = (p2 - 1) / 13;	//b1은 문양 저장
			b2[i] = p2 % 13;		//b2는 카드숫자저장
			b3[i] = p2;				//b3은 카드고유번호저장
			gotoxy(4 * i + 2, 11);
			Pattern_Set(p2);
			gotoxy(4 * i + 2, 13);
			Number_Set(p2);
		}

		for (j = 0; j < 5; j++) {				//컴퓨터카드 오름차순정렬(선택정렬)
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
		sa1 = Pattern_Check(a1);				//컴퓨터 플러쉬확인
		sb1 = Pair_Check(a2,&com);					//컴퓨터 숫자패확인

		//여기서부터 컴퓨터 인공지능
		if (sa1 == 0 && sb1 == 0) {				//노페어일경우
			for (i = 0; i < 3; i++)	ch1[i] = i+1;
		}
		else if (sa1 == 0 && sb1 == 1) {		//원페어일경우
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
		else if (sa1 == 0 && sb1 == 2) {		//투페어일경우
			two = Two_pair(a2);
			if (two == 1)	ch[0] = 5;
			else if (two == 2)	ch[0] = 3;
			else if (two == 3)	ch[0] = 1;
		}
		else if (sa1 == 0 && sb1 == 3) {		//트리플일경우
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

		for (i = 0; i < 3; i++) {				//만약 바꿀 카드가 없으면 change1 = -1 이 될것이다.
			if (ch1[i] == 0) {					//바꿀카드갯수 세기
				change1 = i - 1;
				break;
			}
			else change1 = 2;					//셋다 바꾸기
		}

		if (change1 != -1) {					//change = -1 이면 카드를 바꾸지 않는다.
			for (i = 0; i <= change1; i++) {
				a1[ch1[i] - 1] = 0;
				a2[ch1[i] - 1] = 0;
				a3[ch1[i] - 1] = 0;
				while (1) {						//중복이 있는지 확인하는 반복문
					cnt = 0;
					p1 = random();
					for (j = 0; j < 5; j++) {
						if (p1 == a3[j] || p1 == b3[j])	cnt += 1;
					}
					if (cnt == 0)	break;
				}
				a1[ch1[i] - 1] = (p1 - 1) / 13;	//새로뽑은 카드의 문양
				a2[ch1[i] - 1] = p1 % 13;		//새로뽑은 카드의 숫자
				a3[ch1[i] - 1] = p1;			//새로뽑은 카드의 인터페이스
			}
		}

		for (j = 0; j < 5; j++) {				//카드 바꾼 후 컴퓨터카드 오름차순정렬(선택정렬)
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

		//여기까지 컴퓨터 인공지능


		sa1 = Pattern_Check(a1);				//바꾸고 난 뒤 컴퓨터 플러쉬확인
		sb1 = Pair_Check(a2,&com);					//바꾸고 난 뒤 컴퓨터 숫자패확인
		gotoxy(0, 18);
		for (i = 0; i < 3; i++) {				//카드바꾸기반복문
			printf("바꿀 카드번호를 한장씩 입력하세요(최대 3개,없으면 6) : ");
			scanf("%d", &ch[i]);
			while (1) {
				if (ch[i] > 6 || ch[i] < 1)	printf("다시입력하세요 : ");
				else break;
				scanf("%d", &ch[i]);
			}
			if (ch[i] == 6)	break;
		}

		for (i = 0; i < 3; i++) {				//만약 바꿀 카드가 없으면 change = -1 이 될것이다.
			if (ch[i] == 6 || ch[i] == 0) {		//바꿀카드갯수 세기
				change = i - 1;
				break;
			}
			else change = 2;
		}

		if (change != -1) {						//change = -1 이면 카드를 바꾸지 않는다.
			for (i = 0; i <= change; i++) {
				b1[ch[i] - 1] = 0;
				b2[ch[i] - 1] = 0;
				b3[ch[i] - 1] = 0;
				while (1) {						//중복이 있는지 확인하는 반복문
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

		for (j = 0; j < 5; j++) {				//사용자카드 오름차순정렬
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
		sa2 = Pattern_Check(b1);				//사용자 플러쉬확인
		sb2 = Pair_Check(b2,&ply);					//사용자 숫자패확인
		for (i = 0; i < 5; i++) {
			gotoxy(4 * i + 2, 2);
			Pattern_Set(a3[i]);
			gotoxy(4 * i + 2, 4);
			Number_Set(a3[i]);
		}
		gotoxy(0, 15);
		printf("Computer의 패는 : ");
		jockbo(sa1, sb1);
		printf(" ");
		Number_Set(com);
		printf("\n");
		printf("당신의 패는 : ");
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
		if(Coin > 0)printf("계속하려면 enter를 누르십시오"); getchar();
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

void erase()									//필드의 글자지우기
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

void How_to_Play()								//2번째 페이지 게임방법설명
{
	int Coin = 5;
	char ch;
	printf("※게임방법※\n");
	printf("카드뽑기 : enter키\n");
	printf("승리하면 아래 괄호속 배율만큼 받고, 패배하면 몰수당합니다.(무승부시 배팅금 돌려받음)\n");
	printf("족보(위로갈수록 높음)\n\n");
	printf("-로얄스트레이트플러쉬(X50)\n");
	printf("-백스트레이트플러쉬(X20)\n");
	printf("-스트레이트플러쉬(X10)\n");
	printf("-포카드(X8)\n");
	printf("-풀하우스(X7)\n");
	printf("-플러쉬(X6)\n");
	printf("-마운틴(X5)\n");
	printf("-백스트레이트(X4)\n");
	printf("-스트레이트(X3.5)\n");
	printf("-트리플(X3)\n");
	printf("-투페어(X2.5)\n");
	printf("-원페어(X2.3)\n");
	printf("-노페어(X2)\n\n");
	printf("계속하려면 enter를 눌러주세요");
	ch = getch();
	if (ch == 13) {
		system("cls");
		Play_Game();
	}
}

int Winner(int a,int b,int  c,int  d,int *x,int *y)						//a : 컴퓨터 숫자패, b : 사용자 숫자패, c : 컴퓨터 플러쉬, d : 사용자 플러쉬
{
	int e=0;
	gotoxy(0, 25);
	if (c == 1 && d == 1) {
		if (a > b) { 
			printf("컴퓨터 승리!!\n");
			e = 1;
		}
		else if (a < b) { 
			printf("당신의 승리!!\n");
			e = 2;
		}
		else { 
			if (*x > *y) { 
				printf("컴퓨터 승리!!\n"); 
				e = 1;
			}
			else if(*x<*y){ 
				printf("당신의 승리!!\n");
				e = 2;
			}
			else
			{
				printf("무승부!!\n");
				e = 3;
			}
		}
	}
	else if (c > d) { 
		if (b >= 6 && b <= 7 && a < 4) {
			printf("당신의 승리!!\n");
			e = 2;
		}
		else {
			printf("컴퓨터의 승리!!\n");
			e = 1;
		}
	}
	else if (c < d) { 
		if (a >= 6 &&a <= 7 && b < 4) {
			printf("컴퓨터의 승리!!\n");
			e = 1;
		}
		else {
			printf("당신의 승리!!\n");
			e = 2;
		}
	}
	else if (c == 0 && c == 0) {
		if (a > b) { 
			printf("컴퓨터 승리!!\n"); 
			e = 1;
		}
		else if (a < b) { 
			printf("당신의 승리!!\n"); 
			e = 2;
		}
		else {
			if (*x > *y) {
				printf("컴퓨터 승리!!\n");
				e = 1;
			}
			else if (*x<*y) {
				printf("당신의 승리!!\n");
				e = 2;
			}
			else
			{
				printf("무승부!!\n");
				e = 3;
			}
		}
	}
	return e;
}

int Pattern_Check(int c[])		//문자배열 불러오세요
{
	int a=0;
	if (c[0] == c[1] && c[1] == c[2] && c[2] == c[3] && c[3] == c[4])	a += 1;
	return a;
}

void jockbo(int a,int b)				//a는 문양점수, b는 숫자점수
{
	if (a == 1 && b == 6)	printf("로얄 스트레이트 플러쉬");
	else if (a == 1 && b == 5)	printf("백 스트레이트 플러쉬");
	else if (a == 1 && b == 4)	printf("스트레이트 플러쉬");
	else if (a == 0 && b == 8)	printf("포카드");
	else if (a == 0 && b == 7)	printf("풀하우스");
	else if (a == 1 && b < 4)	printf("플러쉬");
	else if (a == 0 && b == 6)	printf("마운틴");
	else if (a == 0 && b == 5)	printf("백스트레이트");
	else if (a == 0 && b == 4)	printf("스트레이트");
	else if (a == 0 && b == 3)	printf("트리플");
	else if (a == 0 && b == 2)	printf("투페어");
	else if (a == 0 && b == 1)	printf("원페어");
	else printf("노페어");
}

int Pair_Check(int c[], int *a)			//숫자배열불러오세요.
{
	int b = 0;
	*a = 0;
	b = 0;
	if (c[0] == c[1] && c[1] == c[2] && c[2] == c[3] || c[1] == c[2] && c[2] == c[3] && c[3] == c[4]) {
		if (c[0] == c[1] && c[1] == c[2] && c[2] == c[3])	*a += c[0];
		else if (c[1] == c[2] && c[2] == c[3] && c[3] == c[4]) *a += c[1];
		b = 8;
	}			//포카드
	else if (c[0] == c[1] && c[1] == c[2] && c[3] == c[4] || c[0] == c[1] && c[2] == c[3] && c[3] == c[4]) {
		if (c[0] == c[1] && c[1] == c[2] && c[3] == c[4])	*a += c[0];
		else if (c[0] == c[1] && c[2] == c[3] && c[3] == c[4])	*a += c[2];
		b = 7;
	}		//풀하우스
	else if (c[0] == 8 && c[1] == 9 && c[2] == 10 && c[3] == 11 && c[4] == 12)	b += 6;							//마운틴
	else if (c[0] == 0 && c[1] == 1 && c[2] == 2 && c[3] == 3 && c[4] == 13) b = +5;							//백스트레이트
	else if (c[4] == c[0] + 4 && c[4] == c[1] + 3 && c[4] == c[2] + 2 && c[4] == c[3] + 1) {
		*a += c[4];
		b = 4;
	}//스트레이트
	else if (c[0] == c[1] && c[1] == c[2] || c[1] == c[2] && c[2] == c[3] || c[2] == c[3] && c[3] == c[4]) {
		if (c[0] == c[1] && c[1] == c[2])	*a += c[0];
		else if (c[1] == c[2] && c[2] == c[3])	*a += c[1];
		else *a += c[2];
		b = 3;
	}	//트리플
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
	}					//투페어
	else if (c[0] == c[1] || c[1] == c[2] || c[2] == c[3] || c[3] == c[4]) {
		if (c[0] == c[1])	*a += c[0];
		else if (c[1] == c[2])	*a += c[1];
		else if (c[2] == c[3])	*a += c[2];
		else if (c[3] == c[4])	*a += c[3];
		b = 1;
	}									//원페어
	else *a += c[4];																										//노페어(탑)
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
		printf("♥");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else if (a == 1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("◆");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	else if (a == 2) {
		printf("♠"); 
	}
	else {
		printf("♣");
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
	printf("┌─┬─┬─┬─┬─┐\n");
	printf("│  │  │  │  │  │\n");
	printf("├─┼─┼─┼─┼─┤\n");
	printf("│  │  │  │  │  │\n");
	printf("└─┴─┴─┴─┴─┘\n");
}

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}