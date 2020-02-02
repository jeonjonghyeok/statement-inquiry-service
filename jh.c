//수정사항1: dbConn함수에서 접속정보를 자신의 정보로 세팅할것
//수정사항2: useDB함수에서 쿼리구문을 자신의 DB명으로 변경할것

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
#include<errno.h>
#include<time.h>
#include <math.h>


MYSQL mysql;
MYSQL_RES *res;
MYSQL_ROW row;
int rows,fields;

void init();
void dbConn();
void useDB();
void errPrint1(MYSQL *);
void errPrint2(int);

void execQuery(char *);
void printResult();
void searchAll();
void searchTitle();
void searchPrice();
void menuPrint();
void userPrint();
void manager();
void insertBook();
void deleteBook();
void menu_close();
void user();
void cust_fee();
void bill();
void usage();
void cust_info();
void pay_ment();
int * user_usage(char *);
int * f_basic(char *);
int exceed();
int * excess();
void insert_exceed(int);
void num();
void menu_resister();
void custEdit();
void print_custInfo();
void user_info();
void insert_fee();
void insert_tot();
void print_addr();
void month_fee();
void res_date(char *);
void s_date();
void insert_p_res(int);
int phone_price();
void price();
void userManager();
void userPrintMenu();
void printUserInfo();
void printResultCust();
void searchNumber();
void searchName();
void delUser();
void delBill2();
void delBill(char *);
void closeMenu();
void changeFee();
void insertUser();
void insertConsumption();
void insertBill();
void insertCustInfo();
void printPhone();
void userResult();
void consumptionResult();
//void billResult();
void printBill();
void custResult2();
void custResult(char *);
void printCustInfo();
void GradePrintMenu();
void PrintGradeInfo();
void SearchGrade();
void AddGrade();
void DelGrade();
void ChangeGrade();
void GradeManager();
void PrintGradeResult();
void les_price(int,int);
void insert_les_price(int,int);
void insertMonth();
int monthFee();
int discount();

void fee_PrintMenu();
void show_Fee();
void search_Fee();
void add_Fee();
void del_Fee();
void manager_Fee();
void fee_printMenu1();
void change_Fee();
void change_FeeName();
void change_FeeText();
void change_FeeCall();
void change_FeeData();
void printResult_Fee();
void printResult_Fee2();
void result_Fee();
void pass_Fee();
char q1[100] = "'";
char q2[100] = ",";
char q3[100] = ")";
char q4[100] = " ";
char d[20];//delUser
char number[40];
char number2[40];//insertUser
char number3[40];//delUser
int v;//insertUser
int main()
{
	init();
	dbConn();
	useDB();
	manager();
	mysql_close(&mysql);

	return 0;
}

void init()
{
	mysql_init(&mysql);
}

void dbConn()
{
	errPrint1(mysql_real_connect(&mysql,"localhost","root","jjh5942","db",0,NULL,0));
	printf("db connected.....\n");
}

void useDB()
{
	char query[] = "use db";
	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));	
}

void errPrint1(MYSQL *p)
{
	if(!p){
		fprintf(stderr,"%s\n",mysql_error(&mysql));
		exit(1);
	}
}
void errPrint2(int n)
{
	if(n == 0){
		fprintf(stderr,"%s\n",mysql_error(&mysql));
		exit(1);
	}
}

void menuPrint()
{
	printf("---------------------------\n");
	printf(" 1. 고객\n");
	printf(" 2. 관리자\n");
	printf(" 0. 종료\n");
	printf("---------------------------\n");
}
void num() //휴대폰입력 @0
{
	printf("번호입력 : ");
	scanf("%s",number);
	getchar();
	char query[100] = "select number from user where number='";

	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	if(rows == 0)
	{
		printf("없는 번호 입니다!!!\n");
		printf("정확히 다시 입력해주세요\n");
		return ;
	}
	mysql_free_result(res);
	insert_tot(); //명세서업데이트
	user(); //고객
}
void managerMenu(){
	printf("---------------------------\n");
	printf("1. 고객관리\n");
	printf("2. 요금제관리\n");
	printf("3. 등급관리\n");
	printf("0. 이전메뉴\n");
	printf("---------------------------\n");

}

void sel_manager(){ // 관리자-1
	int menu;
	while(1)
	{
		managerMenu();
		printf("메뉴를 선택하세요: ");
		scanf("%d", &menu);

		if(menu == 0){
			printf("관리자 메뉴 종료\n");
			break;
		}

		switch(menu){
			case 1:
				userManager();
				break;
			case 2:
				manager_Fee();
				break;
			case 3:
				GradeManager();
				break;
			default:
				printf("메뉴를 잘못 입력하였습니다. 다시 시도해주세요!\n");
		}
	}
}

void manager() //관리자
{
	int menu;
	char c;
		system("clear");
	while(1)
	{
		//system("clear");
		menuPrint();
		printf("메뉴를 선택하세요: ");
		scanf("%d",&menu);

		if(menu == 0)
		{
			printf("명세서 조회 서비스를 이용해주셔서 감사합니다!\n");
			break;
		}

		switch(menu)
		{
			case 1:
				num();
				break;
			case 2:
				pass_Fee();
				break;
			case 0:
				menu_close();
				break;
			default:
				printf("메뉴를 잘못 입력하였습니다. 다시 시도해주세요!\n");
		}
	}
}
void userPrint()
{
	printf("---------------------------\n");
	printf(" 1. 명세서\n");
	printf(" 2. 사용량 조회\n");
	printf(" 3. 가입정보\n");
	printf(" 4. 요금제\n");
	printf(" 0. 이전\n");
	printf("---------------------------\n");
}
void resisterPrint()
{
	printf("---------------------------\n");
	printf(" 1. 가입 정보 보기\n");
	printf(" 2. 고객 정보 보기\n");
	printf(" 3. 주소 수정\n");
	printf(" 0. 이전\n");
	printf("---------------------------\n");
}

	

void user() // 고객화면
{
	int menu;
	while(1)
	{
		userPrint();
		printf("메뉴를 선택하세요: ");
		scanf("%d",&menu);

		if(menu == 0)
		{
		//	printf("bye~~~~~");
			break;
		}

		switch(menu)
		{
			case 1:
				bill();  //명세서보기
				break;
			case 2:
				usage(); // 사용량보기
				break;
			case 3:
				menu_resister(); //고객정보
				break;
			case 4:
				pay_ment(); // 요금제보기
				break;
			case 0:
				menu_close(); 
				break;
			default:
				printf("메뉴를 잘못 입력하였습니다. 다시 시도해주세요!\n");
		}
	}
}
void menu_resister() //고객정보
{
	int menu;
	while(1)
	{
		resisterPrint();
		
		printf("메뉴를 선택하세요: ");
		scanf("%d",&menu);

		if(menu == 0)
		{
			break;
		}

		switch(menu)
		{
			case 1:
				cust_info(); //고객정보
				break;
			case 2:
				user_info(); //가입정보
				break;
			case 3:
				custEdit(); //주소수정
				break;
			case 0:
				menu_close();
				break;
			default:
				printf("메뉴를 잘못 입력하였습니다. 다시 시도해주세요!\n");
		}
	}
}
void print_custInfo() //고객정보매뉴
{
	printf("---------------------------\n");
	printf(" 1. 가입정보\n");
	printf(" 2. 고객정보\n");
	printf(" 3. 주소변경\n");
	printf(" 0. 이전\n");
	printf("---------------------------\n");

}
void custEdit()//주소변경
{
	system("clear");
	user_info();
	char addr[40];
	printf("변경할 주소 입력:");
	scanf("%s",addr);
	getchar();
	char query[1000] = "update user set addr='";
	char query2[60] = "' where number='";
	strcat(query,addr);
	strcat(query,query2);
	strcat(query,number);
	strcat(query,q1);
	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));
	print_addr();

}
void print_addr() //고객정보 주소 프린트
{
	char query[100] = "select * from user where number ='";
	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	mysql_free_result(res);
	printResult();
	
}

	
void execQuery(char *query)
{
	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));

	res = mysql_store_result(&mysql);
	fields = mysql_num_fields(res);
	rows = (int)mysql_num_rows(res);	
}

void printResult() //결과출력
{
	int i,j;
	MYSQL_FIELD *field ;
	printf("\n================================================================================\n");
	field =  mysql_fetch_fields(res);
	for(i=0; i<fields; i++)
	{
		printf("%9s\t",field[i].name);
	}

	printf("\n================================================================================\n");
	for(i=0; i<rows; i++)
	{
		row = mysql_fetch_row(res);
		for(j=0; j<fields; j++)
			printf("%9s\t",row[j]);
		printf("\n");
	}
	printf("\n================================================================================\n");
}

void menu_close()
{
	exit(1);
}
void bill() // 명세서최종
{
	system("clear");
	printf("*******************************2019년 6월 명세서********************************\n");
	char query[1000] = "select name,f_price,e_charge,p_res,month_fee,les_price from user,bill,custInfo where user.number=custInfo.number and bill.bnum=custInfo.bnum and custInfo.number='";
	strcat(query,number);
	strcat(query,q1);

	execQuery(query);
	int i,j;
	printf("\n================================================================================\n\n");
	printf("\t%s님의 이번달 납부요금은 %s원 입니다.\n",row[0],row[4]);
	printf("\n================================================================================\n\n");
	printf("\t월정액\t\t\t\t\t%s원\n\n",row[1]);
	printf("\t초과요금\t\t\t\t%s원\n\n",row[2]);
	printf("\t단말기 분할상환금\t\t\t%s원\n\n",row[3]);
	printf("\t잔여 할부금\t\t\t\t%s원\n",row[5]);
	printf("\n================================================================================\n");
	


	mysql_free_result(res);
}
int discount() //할인율
{
	int buf;
	char sd[10];
	char query[200] = "select discount from grade,fee,custInfo where grade.g_name=fee.grade and fee.f_name=custInfo.f_name and number='";
	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	strcpy(sd,row[0]);
	buf = atoi(sd);
	mysql_free_result(res);
	return buf;
}
int monthFee() //당월요금 업데이트하기전
{
	int a= discount();
	int buf;
	int b,c;
	int result;
	char sd[10];
	char query[200] = "select month_fee from bill,custInfo where bill.bnum=custInfo.bnum and number='";
	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	strcpy(sd,row[0]);
	mysql_free_result(res);

	c = atoi(sd);
	b= c*a/100;
	result = c-b;
	return result;
}
void insertMonth() //당월요금 할인적용해서 업데이트 @11
{
	int result=monthFee();
	char buf[20];
	sprintf(buf,"%d",result);
	char query[200] = "update bill set month_fee = ";
       char query2[60] = " where bnum in (select bnum from custInfo where number='";
       strcat(query,buf);
       strcat(query,query2);
       strcat(query,number);
       strcat(query,q1);
       strcat(query,q3);
	
	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));

}
void insert_p_res(int a) //단말기분할상관금 @8
{
	char buf[10];
	sprintf(buf,"%d",a);
	char query[1200] ="update bill set p_res ='";
	char query2[100] = "' where bnum in(select bnum from custInfo where number= '";
	strcat(query,buf);
	strcat(query,query2);
	strcat(query,number);
	strcat(query,q1);
	strcat(query,q3);

	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));

}

int phone_price() // 단말기가격
{

	char query[100] = "select p_price from phone, custInfo where phone.p_name = custInfo.p_name and number ='";
	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	int a;
	a = atoi(row[0]);
	mysql_free_result(res);
	return a; //기기값
}
void price() // 단말기가격 약정기간 @7 
{
	int a;
	int b;
	char query[100] = "select term from custInfo where number='";
	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	a = atoi(row[0]);
	a=a*12;
	mysql_free_result(res);
	b = phone_price()/a; //b=한달납부기기값
	insert_p_res(b); //명세서에 한달기기값 업데이트
	les_price(b,a); //a = 약정기간 개월

	
}
void les_price(int b,int s) //남은할부개월수 @9
{
	char query[1000] = "select s_date from custInfo where number='";
	char sd[50] ;
	int term;
	int month, year;
	int month1,year1;
	int res_month;
	int a;
	int res_term;
	int mon_phone;
	int cnt=0;
	int cnt1 = 0;
	int q=0;
	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	strcpy(sd,row[0]);
	mysql_free_result(res);
	a = atoi(sd);
	year = a/10000;
	a = a/100;
	month = a%100;
	q=s/12;
	year = year+q;
	
	time_t timer;
	struct tm *t;
	timer = time(NULL);
	t = localtime(&timer);
	year1 = t->tm_year+1900;
	month1 = t->tm_mon+1;
	if(year==0 && month==0)
		cnt =1;
	year = year-year1;
	if(year ==0 && month-month1<0)
		cnt1=1;
	month = month-month1;
	year =year*12;
	res_month = year+month;
	if(cnt==1) //오늘가입한고객
		res_month = s; //약정기간
	if(cnt1==1) //약정끝난고객
		res_month=0;
	insert_les_price(res_month,b); //남은할부기간,단말기분할상환금
	
}
void insert_les_price(int les_month, int b) //잔여할부금 @10
{

	char query[1000] = "update bill set les_price = ";
	char query1[100] = " where bnum in(select bnum from custInfo where bill.bnum = custInfo.bnum and number='";
	char buf[50];
	sprintf(buf,"%d",les_month*b);
	strcat(query,buf);
	strcat(query,query1);
	strcat(query,number);
	strcat(query,q1);
	strcat(query,q3);
	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));


}
void res_date(char *sd)
{
	printf("%s",sd);
}
int * excess() //초과요금표 @4
{
	char query[200] = "select e_mesg,e_call,e_data from excess";
	int *a = (int *)malloc(sizeof(int *));
	execQuery(query);
	//row = mysql_fetch_row(res);
	a[0] =atoi(row[0]);
	a[1] =atoi(row[1]);
	a[2] =atoi(row[2]);
	mysql_free_result(res);
	return a;
}
void usage() //사용량출력
{
	system("clear");
	printf("사용량조회\n");
	char query[200] = "select c_mesg,c_call,c_data from consumption where number =";
	strcat(query,q1);
	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	printf("-----------사용량----------\n");
	printf("문자 : %s ",row[0]);
	printf("전화 : %s ",row[1]);
	printf("데이터 : %s\n",row[2]);
	mysql_free_result(res);

}
void month_fee() //당월요금 (할인전) @10
{
	char query[300] = "update bill set month_fee = e_charge+f_price+p_res where bnum in(select bnum from custInfo where number = '";

	strcat(query,number);
	strcat(query,q1);
	strcat(query,q3);
	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));
}

void cust_info() //가입정보
{
	system("clear");
	printf("**********가입 정보**********\n");
	char query[100] = "select * from custInfo where number=";

	strcat(query,q1);
	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	printResult();
	mysql_free_result(res);

	//menu_resister();
}	
void user_info() //유저정보
{
	system("clear");
	printf("**********유저 정보**********\n");
	char query[100] = "select * from user where number='";

	strcat(query,number);
	strcat(query,q1);
	execQuery(query);
	printResult();
	mysql_free_result(res);

}
void pay_ment()
{
	printf("**********인기요금제**********\n");
	char query2[100] = " select fee.* from fee,custInfo where fee.f_name=custInfo.f_name group by f_name having count(*)>=3";
	execQuery(query2);
	printResult();
	printf("**********요금제**********\n");
	char query[100] = "select * from fee";
	execQuery(query);
	printResult();
	mysql_free_result(res);
}
void insert_exceed(int a) //초과요금 업데이트 @6
{
	char buf[40];
	char query[1000] = "update bill set e_charge =";
	char e_query[100] = " where bnum in(select bnum from custInfo where number ='"; 
	sprintf(buf,"%d",a);
	strcat(query,buf);
	
	strcat(query,e_query);
	strcat(query,number);
	strcat(query,q1);
	strcat(query,q3);
	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));

}
int exceed() // 초과요금 @5
{

	int *s = (int *)malloc(sizeof(int)*20);
	int *u = (int *)malloc(sizeof(int)*20);
	int *a = (int *)malloc(sizeof(int)*20);
	static int e[20];
	
	s = user_usage(number); //유저사용량
	u = f_basic(number); //기본요금제
	a = excess(); //초과요금표
	e[0] = s[0]-u[0];
	e[1] = s[1]-u[1];
	e[2] = s[2]-u[2];
	if((s[0]-u[0])<=0) //기본제공량보다 적게사용했으면 초과량은 0
	{
		e[0] = 0;
	}
	if((s[1]-u[1])<=0)
	{
		e[1] = 0;
	}
	if((s[2]-u[2])<=0)
	{
		e[2] = 0;
	}
	
	return ((a[0]*e[0])+(a[1]*e[1])+(a[2]*e[2]));



}

int * user_usage(char * temp) //사용량 @2
{
	int *a = (int *)malloc(sizeof(int)*20);
	char query[100] = "select c_mesg,c_call,c_data from consumption where number =" ;
	char sd[100];

	strcat(query,q1);
	strcat(query,temp);
	strcat(query,q1);

	execQuery(query);
	row = mysql_fetch_row(res);
	strcpy(sd,row[0]);
	a[0] = atoi(sd);
	strcpy(sd,row[1]);
	a[1] = atoi(sd);
	strcpy(sd,row[2]);
	a[2] = atoi(sd);
	mysql_free_result(res);
	return a; //int형배열로 사용량 변환
}
void insert_fee() //명세서에 기본요금 업데이트 @1
{
	char query[200] = "update bill set f_price = (select fee.f_price from fee,custInfo where fee.f_name =custInfo.f_name and custInfo.bnum=bill.bnum)";
	errPrint2(!mysql_real_query(&mysql,query,strlen(query)));

}
void insert_tot() //최종 명세서업데이트
{
	insert_fee();
	insert_exceed(exceed());
	price();
	
	month_fee();
	insertMonth();
}
int * f_basic(char * temp) //기본제공량 @3
{
	char query[200] = "select f_mesg,f_call,f_data from fee,custInfo where custInfo.f_name = fee.f_name and custInfo.number = ";
	strcat(query,q1);
	strcat(query,temp);
	strcat(query,q1);

	execQuery(query);
	int *a = (int *)malloc(sizeof(int *)) ;
	a[0] = atoi(row[0]);
	a[1] = atoi(row[1]);
	a[2] = atoi(row[2]);
	mysql_free_result(res);
	return a;
}
///////////////////////////////////////////////////////////////////////////
//MANAGER

void userPrintMenu(){
        printf("------------------------------\n");
        printf("1 .전체 고객정보 보기\n");
        printf("2. 고객정보 이름으로 검색\n");
        printf("3. 고객정보 휴대폰번호로 검색\n");
        printf("4. 고객 삭제\n");
        printf("5. 고객 요금제 변경\n");
	printf("6. 고객추가\n");
        printf("0. 이전 메뉴\n");
        printf("------------------------------\n");
}

void userManager(){
        int menu;
        while(1)
        {
                userPrintMenu();
                printf("메뉴를 선택하세요: ");
                scanf("%d", &menu);

                if(menu == 0){
                        printf("고객관리 메뉴 종료\n");
                        break;
                }

                switch(menu){
                        case 1:
                                printUserInfo();//고객정보 전체보기
                                break;
                        case 2:
                                searchName();//고객정보 이름으로 검색
                                break;
                        case 3:
                                searchNumber();//고객정보 번호로 검색
                                break;
                        case 4:
				delBill2();
                                delUser();//고객 삭제
                                break;
                        case 5:
                                changeFee();//고객요금제 변경
                                break;
			case 6:
				insertUser();//고객 추가
				break;
                        default:
                                printf("메뉴를 잘못 입력하였습니다. 다시 시도해주세요!\n");
                }
        }
}

void printUserInfo(){
	 char query2[] ="select user.*,grade from user,fee,custInfo where user.number=custInfo.number and custInfo.f_name = fee.f_name and grade = 'Vip'";
	        printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★ViP★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★");
	execQuery(query2);
	printResult();
		printf("★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★");
        char query[] = "select * from user";
        execQuery(query);
        printResult();
        mysql_free_result(res);
}

void searchName(){
        char temp[100];
        char query[100] = "select * from user where name = '";

        printf("검색할 고객의 이름을 입력하세요: ");
        scanf("%s", temp);
        strcat(query, temp);
        strcat(query, q1);

        execQuery(query);
        printResult();
        mysql_free_result(res);
}

void searchNumber(){
        char temp[100];
        char query[100] = "select * from user where number = '";
        printf("검색할 휴대폰번호를 입력하세요: ");
        scanf("%s", temp);
        strcat(query, temp);
        strcat(query, q1);
        execQuery(query);
        printResult();
        mysql_free_result(res);
}
void delUser(){
        char query[100] = "delete from user where number = '";

	//printf("삭제할 휴대폰번호를 입력하세요: ");
        //scanf("%s", number3);
        //getchar();
        strcat(query, number3);
        strcat(query, q1);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));

        printUserInfo();
}
void delBill2(){
        char query[100] = "select bnum from custInfo where number = '";
	char d[20];

	printf("삭제할 휴대폰번호를 입력하세요: ");
        scanf("%s", number3);
        getchar();
        strcat(query, number3);
        strcat(query, q1);
        execQuery(query);
        row = mysql_fetch_row(res);
        strcpy(d,row[0]);
        mysql_free_result(res);
	delBill(d);
}
void delBill(char * d){
        char query[100] = "delete from bill where bnum = ";

        strcat(query, d);
        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
}
void changeFee(){
        char query[100] = "update custInfo set f_name = '";
        char temp[100];
        char q5[100] = "' where number = '";

        printCustInfo();
        printf("변경하고싶은  요금제의 이름을 입력하세요: ");
        scanf("%s", temp);
        getchar();
        strcat(query, temp);
        strcat(query, q5);
        printf("요금제를 변경해서  사용할 휴대폰번호를 입력하세요: ");
        scanf("%s", temp);
	getchar();
        strcat(query, temp);
        strcat(query, q1);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
        custResult(temp);
	strcpy(number, temp);
	insert_tot();
}
void insertUser(){
        char query[100] = "insert into user values('";
        char temp[100];

        printf("추가할 고객 정보 입력");
        printf("전화번호: ");
        scanf("%s", number2);
        getchar();
        strcat(query, number2);
        strcat(query, q1);
        strcat(query, q2);
        strcat(query, q1);
        printf("이름: ");
        scanf("%s", temp);
        getchar();
        strcat(query, temp);
        strcat(query, q1);
        strcat(query, q2);
        strcat(query, q1);
        printf("주소: ");
        scanf("%s", temp);
        getchar();
        strcat(query, temp);
        strcat(query, q1);
        strcat(query, q2);
        strcat(query, q1);
        printf("주민등록번호: ");
        scanf("%s", temp);
        getchar();
        strcat(query, temp);
        strcat(query, q1);
        strcat(query, q3);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
        insertConsumption();
        insertBill();
        insertCustInfo();

}
void insertConsumption(){
        char query[100] = "insert into consumption values('";
        char query2[100] = "', 0, 0, 0)";

        strcat(query, number2);
        strcat(query, query2);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
}
void insertBill(){
        char query[100] = "insert into bill(bnum) values(";
        char buf[10];
        printBill();
        sprintf(buf, "%d", v);
        strcat(query, buf);
        strcat(query, q3);
        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));

}
void insertCustInfo(){
        struct tm *t;
        time_t timer;
        timer = time(NULL);
        t = localtime(&timer);
        char query[1000] = "insert into custInfo values('";
        char temp[100];
        char buf[100];
        char year[20];
        char month[20];
        char day[20];
        char month2[30];
        int q = 0;
        int cnt=0;
        sprintf(buf,"%d",q);
        sprintf(year, "%d", t->tm_year+1900);
        if((t->tm_mon+1) <10)
                cnt++;
        sprintf(month, "%d", t->tm_mon+1);

        sprintf(day, "%d", t->tm_mday);

        strcat(query, number2);
        printf("휴대폰기종목록\n");
        strcat(query, q1);
        strcat(query, q2);
        printPhone();
        printf("사용할 휴대폰: ");
        scanf("%s", temp);
        getchar();
        strcat(query, q1);
        strcat(query, temp);
        strcat(query, q1);
        strcat(query, q2);
        printf("요금제목록\n");
        show_Fee();
        printf("사용할 요금제이름: ");
        scanf("%s", temp);
        getchar();
        strcat(query, q1);
        strcat(query, temp);
        strcat(query, q1);
        strcat(query, q2);
        //휴대폰 구매 현재 날짜
        strcat(query, q1);
        strcat(query, year);
        if(cnt==1){
                strcat(buf,month);
                strcat(query, buf);
        }
        else
                strcat(query, month);
        strcat(query, day);
        strcat(query, q1);
        strcat(query, q2);

        printf("약정기간 입력: ");
        scanf("%s", temp);
        getchar();
        strcat(query, temp);
        strcat(query, q2);

        sprintf(buf, "%d", v);
        strcat(query, buf);
        strcat(query, q3);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
        userResult();
        consumptionResult();
        custResult2();
	//strcpy(number, number2);
        //insert_tot();
	//billResult();
}
void printPhone(){
        char query[100] = "select * from phone";

        execQuery(query);
        printResult();
        mysql_free_result(res);
}
void printCustInfo(){
	char query[100] = "select * from custInfo";

        execQuery(query);
        printResult();
        mysql_free_result(res);
}
void userResult(){
        char query[100] = "select * from user where number = '";
        strcat(query, number2);
        strcat(query, q1);

        execQuery(query);
        printResult();
        mysql_free_result(res);
}
void consumptionResult(){
        char query[100] = "select * from consumption where number = '";
        strcat(query, number2);
        strcat(query, q1);

        execQuery(query);
        printResult();
        mysql_free_result(res);
}
/*void billResult(){
        char query[100] = "select * from bill where bnum = ";
        char buf[20];
        sprintf(buf, "%d", v);
        strcat(query, buf);

        execQuery(query);
        printResult();
        mysql_free_result(res);

}*/
void printBill(){
        char query[100] = "select max(bnum) from bill";
	char a[20];
        execQuery(query);
	row = mysql_fetch_row(res);
	strcpy(d,row[0]);
	strcpy(a, row[0]);
	v = atoi(a);
        v += 1;

        mysql_free_result(res);

}
void custResult2(){
        char query[100] = "select * from custInfo where number = '";
        strcat(query, number2);
        strcat(query, q1);

        execQuery(query);
        printResult();
        mysql_free_result(res);
}
void custResult(char * temp){
        char query[100] = "select * from custInfo where number = '";
        strcat(query, temp);
        strcat(query, q1);

        execQuery(query);
        printResult();
        mysql_free_result(res);
}

void GradePrintMenu(){					//등급
	printf("------------------------------\n");
	printf("1. 전체 등급 보기\n");
	printf("2. 등급 추가\n");
	printf("3. 등급 삭제\n");
	printf("4. 등급 변경\n");
	printf("0. 이전 메뉴\n");
	printf("------------------------------\n");
}

void GradeManager(){
	int menu;
	while(1)
	{
		GradePrintMenu();		
		printf("메뉴를 선택하세요: ");
		scanf("%d", &menu);
	
		if(menu == 0){
			printf("이전 메뉴\n");
			break;
		}

	
		switch(menu){
			case 1:
				PrintGradeInfo();	//전체 등급보기
				break;
			case 2:
				AddGrade();		//등급 추가
				break;
			case 3:
				DelGrade();		//등급 삭제
				break;
			case 4:
				ChangeGrade();		//등급 변경
				break;
			default:
				printf("메뉴를 잘못 입력하였습니다. 다시 시도해>주세요!\n");
		}
	}
}

void PrintGradeInfo(){		//전체 등급 보기
	char query[] = "select * from grade order by discount asc";
	execQuery(query);
	PrintGradeResult();
	mysql_free_result(res);
}

void AddGrade(){		//등급 추가
	char temp[100];
	char query[100] = "insert into grade values('";
	char q1[] = "'";
	char q2[] = ",";
	char q3[] = ")";
	printf("추가할 등급을 입력하세요: ");
	scanf("%s", temp);
	strcat(query, temp);
	strcat(query, q1);
	strcat(query, q2);
	printf("추가한 등급의 마일리지를 입력하세요: ");
	scanf("%s", temp);
	strcat(query, temp);
	strcat(query, q3);

	errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
	PrintGradeInfo();
}

void DelGrade(){		//등급 삭제
	char query[100] = "delete from grade where g_name = '";
	char temp[100];
	char q1[] = "'";

	printf("삭제할 등급을 입력하세요: ");
	scanf("%s", temp);
	strcat(query, temp);
	strcat(query, q1);
	printf("%s\n", query);

	errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
	PrintGradeInfo();
}

void ChangeGrade(){		//등급 변경
	char query[100] = "update grade set discount=";
	char temp[100];
	char temp2[100];
	char q1[] = "'";
	char query2[100] = " where g_name='";

	printf("변경하고싶은 등급의 이름을 입력하세요: ");
	scanf("%s", temp);
	printf("선택한 등급의 마일리지를 입력하세요: ");
	scanf("%s", temp2);
	strcat(query, temp2);
	strcat(query, query2);
	strcat(query, temp);
	strcat(query, q1);

	errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
	PrintGradeInfo();
}


void PrintGradeResult(){
        int i, j;
        printf("\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
        for(i=0; i<rows; i++){
                row = mysql_fetch_row(res);
                for(j=0; j<fields; j++)
                        printf("%15s\t", row[j]);
                printf("\n");
        }

        printf("\n★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★\n");
}


void fee_PrintMenu() //요금제 관리메뉴
{
        printf("------------------------------\n");
        printf("1. 요금제 보기\n");
        printf("2. 요금제 검색\n");
        printf("3. 요금제 추가\n");
        printf("4. 요금제 삭제\n");
        printf("5. 요금제 수정\n");
        printf("0. 이전 메뉴\n");
        printf("------------------------------\n");
}

void manager_Fee(){
        int menu;
        while(1)
        {
                fee_PrintMenu();
                printf("메뉴를 선택하세요: ");
                scanf("%d", &menu);

                if(menu == 0){
                        printf("고객관리 메뉴 종료\n");
                        break;
                }

                switch(menu){
                        case 1:
                                show_Fee();	//요금제 보기
                                break;
                        case 2:
                                search_Fee();	//요금제 검색
                                break;
                        case 3:
                                add_Fee();	//요금제 추가
                                break;
                        case 4:
                                del_Fee();	//요금제 삭제
                                break;
                        case 5:
                                change_Fee();	//요금제 수정
                                break;
                        default:
                                printf("메뉴를 잘못 입력하였습니다. 다시 시도해>주세요!\n");
                }
        }
}


void show_Fee()	//요금제 보기
{
        char query[] = "select * from fee  ";
        execQuery(query);
        printResult_Fee();	//결과
        mysql_free_result(res);
}

void search_Fee() //요금제 검색
{
        char temp[100];
        char query[100] = "select * from fee where f_name =  '";
        char q1[] = "'";
        printf("요금제 이름을 입력하시오 : ");
        scanf("%s", temp);
        strcat(query, temp);
        strcat(query, q1);
        execQuery(query);
        printResult_Fee();
        mysql_free_result(res);
}


void add_Fee()	// 요금제 추가
{
        char query[100] = "insert into fee values('";
        char q1[] = ",";
        char q2[] = "'";
        char q3[] = ")";
        char temp[50];

        printf("이름을 입력하시오 : ");
        scanf("%s",temp);
        getchar();
        strcat(query,temp);
        strcat(query,q2);
        strcat(query,q1);
        printf("메세지량을 입력하시오 :");
        scanf("%s",temp);
        getchar();
        strcat(query,temp);
        strcat(query,q1);

        printf("전화량을 입력하시오 :");
        scanf("%s",temp);
        getchar();
        strcat(query,temp);
        strcat(query,q1);

        printf("데이터량을 입력하시오 :");
        scanf("%s",temp);
        getchar();
        strcat(query,temp);
        strcat(query,q1);
        printf("가격을 입력하시오 :");
        scanf("%s",temp);
        getchar();
        strcat(query,temp);
        strcat(query,q1);
        strcat(query,q2);
        printf("등급을 입력하시오 : ");
        scanf("%s",temp);
        getchar();
        strcat(query,temp);
        strcat(query,q2);
        strcat(query,q3);

        errPrint2(!mysql_real_query(&mysql,query,strlen(query)));
        show_Fee();	//추가 확인

}


void del_Fee() //요금제 삭제	
{
        char query[100] = "delete from fee where f_name = '";
        char temp[100];
        char q1[] = "'";

        printf("삭제할 요금제를 입력하시오: ");
        scanf("%s",temp);
        getchar();
        strcat(query, temp);
        strcat(query, q1);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
        show_Fee();	//삭제 확인
}

void fee_printMenu1()	//요금제 수정메뉴
{

        printf("------------------------------\n");
        printf("1 요금제 이름 수정\n");
        printf("2. 요금제 문자량 수정\n");
        printf("3. 요금제 통화량 수정\n");
        printf("4. 요금제 데이터 수정\n");
        printf("0. 이전메뉴\n");
        printf("------------------------------\n");

}


void change_Fee()	//요금제 수정
{

        int menu;
        while(1)
        {
                fee_printMenu1();
                printf("메뉴를 선택하세요: ");
                 scanf("%d", &menu);
                if(menu == 0){
                        printf("고객관리 메뉴 종료\n");
                        break;
                }

                switch(menu){
                        case 1:
                                change_FeeName();	//이름 수정
                                break;
                        case 2:
                                change_FeeText();	//문자량 수정
                                break;
                        case 3:
                                change_FeeCall();	//통화량 수정
                                break;
                        case 4:
                                change_FeeData();	//데이터 수정
                                break;
                        default:
                                printf("메뉴를 잘못 입력하였습니다. 다시 시도해>주세요!\n");
                }
        }
}



void change_FeeName()	//이름 수정
{

	pay_ment();	//요금제 보여주기
        char query[1000] = "update fee set f_name = '";
        char query1[100] = " where f_name ='";
        //char q1[]="'";
        char temp[100];
	char temp1[100];

        printf("현재 요금제의 이름을 입력하세요:");
        scanf("%s", temp1);
	getchar();
        printf("변경하고싶은 요금제의 이름을 입력하세요: ");
        scanf("%s", temp);
        getchar();
        strcat(query, temp);
        strcat(query, q1);
	strcat(query,query1);
        strcat(query, temp1);
        strcat(query, q1);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
        result_Fee(temp);


}

void change_FeeText()	//문자량 수정
{
  char query[100] = "update fee set f_mesg = ";
        char query1[100] = " where f_name ='";
        //char q1[]="'";
        char temp[100];
        printf("변경하고싶은 요금제의 메세지량을 입력하세요: ");
        scanf("%s", temp);
        strcat(query, temp);
        getchar();
        strcat(query, query1);
        printf("현재 요금제의 이름을 입력하세요:");
        scanf("%s", temp);
        strcat(query, temp);
        strcat(query, q1);


        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
        result_Fee(temp);
        mysql_free_result(res);

}


void change_FeeCall()	//통화량 수정
{

 char query[100] = "update fee set f_call = ";
        char query1[100] = " where f_name ='";
        //char q1[]="'";
        char temp[100];
        printf("변경하고싶은 요금제의 통화량을 입력하세요: ");
        scanf("%s", temp);
        strcat(query, temp);
        strcat(query,query1);
        printf("현재 요금제의 이름을 입력하세요:");
        scanf("%s", temp);
        strcat(query, temp);
        strcat(query, q1);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
        result_Fee(temp);
        mysql_free_result(res);


}

void change_FeeData()	//데이터 수정
{
        char query[100] = "update fee set f_data = ";
        char query1[100] = " where f_name ='";
        //char q1[]="'";
        char temp[100];
        printf("변경하고싶은 요금제의 데이터량을 입력하세요: ");
        scanf("%s", temp);
        strcat(query, temp);
        strcat(query,query1);
        printf("현재 요금제의 이름을 입력하세요:");
        scanf("%s", temp);
        strcat(query, temp);
        strcat(query, q1);

        errPrint2(!mysql_real_query(&mysql, query, strlen(query)));
        result_Fee(temp);
        mysql_free_result(res);

}

void result_Fee(char * temp){
        char query[100] = "select * from fee where f_name = '";
        char q1[] = "'";
        strcat(query, temp);
        strcat(query, q1);

        execQuery(query);
        printResult_Fee();
        mysql_free_result(res);
}

void pass_Fee()	//관리자 -> 비밀번호
{
       char passwd[40] = "abc123";
       char passwd1[40];
       printf("비번 입력\n");
        scanf("%s",passwd1);
        getchar();
        if(strcmp(passwd,passwd1))
        {
                printf("번호 입력 에러\n");
                return ;
        }
        sel_manager();	//관리자
}

void printResult_Fee2(){
        int i, j;
        for(i=0; i<rows; i++){
                row = mysql_fetch_row(res);
                for(j=0; j<fields; j++)
                        printf("%15s\t", row[j]);
                printf("\n");
        }

}
void printResult_Fee()	//결과출력
{
        int i, j;
        printf("\n==============================\n");
        for(i=0; i<rows; i++){
                row = mysql_fetch_row(res);
                for(j=0; j<fields; j++)
                        printf("%15s\t", row[j]);
                printf("\n");
        }

        printf("\n==============================\n");
}
      
