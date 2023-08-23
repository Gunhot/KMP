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
void match(char *str, int m, char *pat, int n, int *num, int *pos){

	int end_pos = n-1; //str소속, 검사하는 부분의 끝자리
	int start_pos = 0; //str소속, 검사하는 부분의 시작자리
	int i; //str 소속
	int j; //pat 소속
	
	//출력할 파일 stream open
	FILE* rp;
	rp = fopen("result_naive.txt","w");
	if(rp == NULL){
		printf("Output File error\n"); 
	}

	//endpos과 strpos 같이 한칸씩 배열의 끝으로 이동하면서 검사
	for (i = 0; end_pos < m; end_pos++, start_pos++){
		//일치하면 그 startpos부터 i(str소속),j(pat소속)를 사용해서 startpos과 endpos 사이를 검사
		if(str[end_pos] == pat[n-1]){
			//j초기화 i초기화
			j = 0; i = start_pos;
			//j가 n-1이 되기 전에 다른 부분이 있으면 반복문 stop
			while(j < n - 1 && str[i] == pat[j]){
				i++; j++;
			}
		}
		//일치 횟수가 pat의 길이와 같다면(j == n-1), 해당 startpos에 하나씩 넣어준다.
		if (j == n - 1){
			(*num)++;
			pos[*num - 1] = start_pos;
		}
	}

	fprintf(rp, "%d\n", *num);
	for (i = 0; i < *num; i++){
		fprintf(rp,"%d ", pos[i]);
	}
	if(i == *num){
		printf("Program complete. Result saved to result_naive.txt\n");
	}
	fclose(rp);
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

