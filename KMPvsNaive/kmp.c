#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define STR_LIM 10000000
#define PAT_LIM 3000
//string을 담을 배열
char str[STR_LIM] = {0,};
//pattern을 담을 배열
char pat[PAT_LIM] = {0,};
//position을 담을 배열
int pos[STR_LIM] = {0,};
void fail(int* failure,char *pat){
	int i;
	int n = strlen(pat);
	failure[0] = -1;
	for (int j = 1; j < n; j++){
		i = failure[j-1];
		while((pat[j] != pat[i+1]) && (i >= 0)) i = failure[i];
		if(pat[j] == pat[i+1]) failure[j] = i+1;
		else failure[j] = -1;
	}
}
void match(char *str, int m, char *pat, int n, int *num, int *pos){
	int i = 0;//str소속
	int j = 0;//pat소속
	int *failure;
	failure = (int*)calloc(n, sizeof(int));
	//fail배열 만들기
	fail(failure, pat);

	//출력할 파일 streamp 생성
	FILE *rp;
	rp = fopen("result_kmp.txt", "w");
	if (rp == NULL){
		printf("Output File error\n");
	}

	//파일을 끝까지 검색함
	while(i < m - n){
		while(j < n && i < m){
			//pat과 str이 일치하는 순간이 오면 다음부분 같이 검사
			if (str[i] == pat[j]){
				i++; j++;
			}
			//일치할 때까지는 str과 pat의 첫 부분을 비교
			else if(j == 0) i++;
			//pat의 첫 부분이 0이 아니라면 fail배열을 이용하여 조정해준다.
			else j = failure[j-1] + 1;
		}
		//일치 횟수가 pat의 길이와 같다면
		if (j == n){
			//일치 횟수를 1 늘려준다.
			(*num)++;;
			//시작 position을 배열에 대입해준다.
			pos[(*num) - 1] = i - j;
			//i는 시작position 다음 index로 변경해준다.
			//j는 맨처음 position으로 변경해준다.
			i = i - j + 1; j = 0;			
		}
	}
	//출력한다.
	fprintf(rp, "%d\n", *num);
	for(i = 0; i < *(num); i++){
		fprintf(rp, "%d ", pos[i]);
	}
	if(i == *num){
		printf("Program complete. Result saved to result_kmp.txt\n");
	}

}


int main(){
	int m = 0; //length of string
	int n = 0; //length of pattern

	int number = 0;
	int *num = &number; //the number of appearnace

	//string 입력 완료
	FILE *sp = fopen("string.txt", "r");
	if (sp == NULL){
		printf("The string file does not exist.\n");
		return -1;
	}
	fgets(str, STR_LIM, sp);
	m = strlen(str);
	
	//pattern 입력 완료
	FILE *pp = fopen("pattern.txt", "r");
	if (pp == NULL){
		printf("The string file does not exist.\n");
		return -1;
	}
	fgets(pat, PAT_LIM, pp);
	n = strlen(pat);
	
	
	//pattern 매칭 후에 출력할 함수
	match(str, m, pat, n, num, pos); 

	fclose(sp);
	fclose(pp);
	return 0;
}
