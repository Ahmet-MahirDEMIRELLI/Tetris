#include<stdio.h>
#include<time.h>
#include <stdbool.h>                        
#define MAX_SIZE 50							
#define MIN_SIZE 4
#define FILENAME users										
#define PIECE_ROW 3										
#define PIECE_COLUMN 3
void clean(int[]);
int main(){
	bool tetris(int []);
	bool isDone;
	int score[2];
	score[0] = 0;
	score[1] = 0;
	do{
		isDone = tetris(score);	
	}while(!isDone);
	printf("\n\n	Elde edilen max skor : %d",score[1]);
	return 0;
}
bool tetris(int score[]){
	int MENU(int []);
	bool makeMove(int [][MAX_SIZE],int,int[]);
	void printGameRules();
	int size,i,j;
	int matrix[MAX_SIZE][MAX_SIZE];
	bool isDone;
	for(i = 0;i < MAX_SIZE;i++){
		for(j = 0;j < MAX_SIZE;j++){
			matrix[i][j] = 0;
		}
	}
	size = MENU(score);
	if(size == 0){
		return true;
	}
	clean(score);
	printGameRules();
	clean(score);
	do{
		isDone = makeMove(matrix,size,score);
	}while(!isDone);
	printf("\n\n	Skorunuz : %d",score[0]);
	if(score[0] > score[1]){
		score[1] = score[0];
	}
	score[0] = 0;
	printf("	Devam etmek icin enter'a basiniz		");
	getch();
	return false;
}
bool makeMove(int matrix[][MAX_SIZE],int size, int score[]){
	void printGameTable(int [][MAX_SIZE], int);
	void printPiece(int [][PIECE_COLUMN], int);
	void fillPieceMatrix(int [][PIECE_COLUMN],int);
	bool isInsertional(int [][MAX_SIZE], int , int [][PIECE_COLUMN]);
	void updateMatrix(int [][MAX_SIZE], int , int [][PIECE_COLUMN],int ,int );
	int tryInsertion(int [][MAX_SIZE], int , int [][PIECE_COLUMN],int);
	void rotateClockwise90(int [][PIECE_COLUMN],int);
	int clearFullLines(int [][MAX_SIZE], int);
	bool checkFirstLine(int [][MAX_SIZE], int );
	void printGameRules();
	int piece[PIECE_ROW][PIECE_COLUMN],pieceNo;
	bool isFinished = false,found = false,playable,done;
	int i,j,choise;
	int tmp;
	srand(time(NULL));
	printGameTable(matrix,size);
	printf("\n\n");
	pieceNo = rand() % 7;
	fillPieceMatrix(piece,pieceNo);
	printPiece(piece,PIECE_ROW);
	printf("\n\n");
	i = 4;
	while(i > 0){
		playable = isInsertional(matrix,size,piece);
		if(playable){
			i = 0;
		}
		rotateClockwise90(piece,pieceNo);
		i--;
	}
	fillPieceMatrix(piece,pieceNo);						
	if(!playable){
		printf("	Parca yerlestirilemez. Oyun bitti.\n");
		printf("	Devam etmek icin enter'a basiniz		");
		getch();
		return true;
	}
	done = false;
	while(!done){
		clean(score);
		printGameTable(matrix,size);
		printf("\n\n");
		printPiece(piece,PIECE_ROW);
		if(pieceNo != 2 && pieceNo != 6){
			printf("	Parcayi saat yonune 90 derece dondurmek icin 1 giriniz			");
			scanf("%d",&choise);
			if(choise == 0){
				clean(score);
				printGameRules();
				clean(score);
				printGameTable(matrix,size);
				printf("\n\n");
				printPiece(piece,PIECE_ROW);
				printf("	Parcayi saat yonune 90 derece dondurmek icin 1 giriniz			");
				scanf("%d",&choise);
			}
			else if(choise == -1){
				score[0] = 0;
				return true;
			}
			while(choise == 1){
				rotateClockwise90(piece,pieceNo);
				clean(score);
				printGameTable(matrix,size);
				printf("\n\n");
				printPiece(piece,PIECE_ROW);
				printf("	Parcayi saat yonune 90 derece dondurmek icin 1 giriniz			");
				scanf("%d",&choise);
				if(choise == 0){
					clean(score);
					printGameRules();
					clean(score);
					printGameTable(matrix,size);
					printf("\n\n");
					printPiece(piece,PIECE_ROW);
					printf("	Parcayi saat yonune 90 derece dondurmek icin 1 giriniz			");
					scanf("%d",&choise);
				}
				else if(choise == -1){
					score[0] = 0;
					return true;
				}
			}
		}
		printf("	Parca hangi sutuna yerlestirilsin		");
		scanf("%d",&j);
		if(j == 0){
			clean(score);
			printGameRules();
			clean(score);
			printGameTable(matrix,size);
			printf("\n\n");
			printPiece(piece,PIECE_ROW);
			printf("	Parca hangi sutuna yerlestirilsin		");
			scanf("%d",&j);
		}
		else if(j == -1){
			score[0] = 0;
			return true;
		}
		j--;                                                      // kullanýcý için 1 matris için 0
		i = tryInsertion(matrix,size,piece,j);
		clean(score);      												                       		  
		if(i < 0){
			printf("	Parca %d. sutuna yerlestirilemez. Lutfen tekrar giris yapiniz\n",j + 1);
			getch();
		}
		else{
			done = true;
		}
	}
	updateMatrix(matrix,size,piece,i,j);
	score[0] += clearFullLines(matrix,size);
	isFinished = checkFirstLine(matrix,size);
	return isFinished;
}
bool isInsertional(int matrix[][MAX_SIZE], int size, int piece[][PIECE_COLUMN]){
	int tryInsertion(int [][MAX_SIZE], int , int [][PIECE_COLUMN],int);
	int i,j;
	j = 0;
	i = -2;
	while(i <= 0 && j < size){
		i = tryInsertion(matrix,size,piece,j); 
		if(i!=-1){
			j = size;
		}               
		j++;
	}
	if(i >= 0){
		return true;
	}
	else{
		return false;
	}
}
int tryInsertion(int matrix[][MAX_SIZE], int size, int piece[][PIECE_COLUMN],int column){
	int i,j,k;
	int row_of_piece;
	int column_of_first = PIECE_COLUMN;
	int column_of_piece;
	int tmp;
	int num_of_row = 0;
	bool possible;
	bool overlap;
	for(i = 0;i < PIECE_ROW;i++){
		for(j = 0;j < PIECE_COLUMN;j++){
			if(piece[0][j] == 1 && j < column_of_first){
				column_of_first = j;
			}
			if(piece[i][j] == 1 && i + 1 > num_of_row){
				num_of_row = i + 1;
			}
		}
	}
	if(column_of_first == 0){                   // sol üst piece[0][0] da : matrix üzerinden column, column + 1 ve column + 2 ile ilgilenicem
		if(num_of_row == 1){					// parça 1 satýr
			i = size - 1;
			possible = false;
			while(!possible && i >= 0){
				overlap = false;
				j = column;
				column_of_piece = 0;
				while(!overlap && j < column + PIECE_COLUMN){
					if(j >= size && piece[0][column_of_piece] == 1){
						overlap = true;
					}
					if(piece[0][column_of_piece] == 1 && matrix[i][j] == 1){
						overlap = true;
					}
					j++;
					column_of_piece++;
				}
				possible = !overlap;
				if(possible == true){
					return i;
				}
				i--;
			}
		}
		else if(num_of_row == 2){				// parça 2 satýr
			i = size - 2;
			possible = false;
			while(!possible && i >= 0){
				k = i;
				row_of_piece = 0;
				tmp = 0;
				overlap = false;
				while(!overlap && tmp < 2){
					j = column;
					column_of_piece = 0;
					while(!overlap && j < column + PIECE_COLUMN){
						if(j >= size && piece[row_of_piece][column_of_piece] == 1){
							overlap = true;
						}
						if(piece[row_of_piece][column_of_piece] == 1 && matrix[k][j] == 1){
							overlap = true;
						}
						j++;
						column_of_piece++;
					}
					k++;
					row_of_piece++;
					tmp++;
				}
				possible = !overlap;
				if(possible == true){
					return i;
				}
				i--;	
			}
		}
		else{								   // parça 3 satýr
			i = size - 3;
			possible = false;
			while(!possible && i >= 0){
				k = i;
				tmp = 0;
				row_of_piece = 0;
				overlap = false;
				while(!overlap && tmp < 3){
					j = column;
					column_of_piece = 0;
					while(!overlap && j < column + PIECE_COLUMN){
						if(j >= size && piece[row_of_piece][column_of_piece] == 1){
							overlap = true;
						}
						if(piece[row_of_piece][column_of_piece] == 1 && matrix[k][j] == 1){
							overlap = true;
						}
						j++;
						column_of_piece++;
					}
					k++;
					row_of_piece++;
					tmp++;
				}
				possible = !overlap;
				if(possible == true){
					return i;
				}
				i--;	
			}								
		}
	}
	else if(column_of_first == 1){			   // sol üst piece[0][1] de : matrix üzerinden column - 1, column ve column + 1 ile ilgilenicem
		                                       // S parçasý;                                       
		i = size - 2;
		possible = false;
		while(!possible && i >= 0){
			k = i;
			row_of_piece = 0;
			tmp = 0;
			overlap = false;
			while(!overlap && tmp < 2){
				overlap = false;
				j = column - 1;
				column_of_piece = 0;
				while(!overlap && j < column + PIECE_COLUMN - 1){
					if(j >= size && piece[row_of_piece][column_of_piece] == 1){
						overlap = true;
					}
					if(piece[row_of_piece][column_of_piece] == 1 && matrix[k][j] == 1){
						overlap = true;
					}
					j++;
					column_of_piece++;
				}
				k++;
				row_of_piece++;
				tmp++;
			}
			possible = !overlap;
			if(possible == true){
				return i;
			}
			i--;	
		}
	}
	else{							     	   // sol üst piece[0][2] de : matrix üzerinden column - 2, column -1  ve column  ile ilgilenicem
											   // 3 kere döndürülmüþ L parçasý
		i= size - 2;
		possible = false;
		while(!possible && i >= 0){
			k = i;
			tmp = 0;
			row_of_piece = 0;
			overlap = false;
			while(!overlap && tmp < 3){
				overlap = false;
				j = column - 2;
				column_of_piece = 0;
				while(!overlap && j < column + PIECE_COLUMN - 2){
					if(j >= size && piece[row_of_piece][column_of_piece] == 1){
						overlap = true;
					}
					if(piece[row_of_piece][column_of_piece] == 1 && matrix[k][j] == 1){
						overlap = true;
					}
					j++;
					column_of_piece++;
				}
				k++;
				row_of_piece++;
				tmp++;
			}
			possible = !overlap;
			if(possible == true){
				return i;
			}
			i--;	
		}
	}
	return -1;
}
void updateMatrix(int matrix[][MAX_SIZE], int size, int piece[][PIECE_COLUMN],int row,int column){
	int i,j,k;
	int row_of_piece;
	int column_of_first = PIECE_COLUMN;
	int column_of_piece;
	int tmp;
	int num_of_row = 0;
	for(i = 0;i < PIECE_ROW;i++){
		for(j = 0;j < PIECE_COLUMN;j++){
			if(piece[0][j] == 1 && j < column_of_first){
				column_of_first = j;
			}
			if(piece[i][j] == 1 && i + 1 > num_of_row){
				num_of_row = i + 1;
			}
		}
	}
	if(column_of_first == 0){                   // sol üst piece[0][0] da : matrix üzerinden column, column + 1 ve column + 2 ile ilgilenicem
		if(num_of_row == 1){					// parça 1 satýr
			column_of_piece = 0;
			i = row;
			j = column;
			while(j < column + PIECE_COLUMN){
				if(piece[0][column_of_piece] == 1){
					 matrix[i][j] = piece[0][column_of_piece];
				}
				j++;
				column_of_piece++;
			}
		}
		else if(num_of_row == 2){				// parça 2 satýr
				i = row;
				row_of_piece = 0;
				while(i <= row + 1){
					j = column;
					column_of_piece = 0;
					while(j < column + PIECE_COLUMN){
						if(piece[row_of_piece][column_of_piece] == 1){
							 matrix[i][j] = piece[row_of_piece][column_of_piece];
						}
						j++;
						column_of_piece++;
					}
					row_of_piece++;
					i++;
				}	
		}
		else{								   // parça 3 satýr
				i = row;
				row_of_piece = 0;
				while(i <= row + 2){
					j = column;
					column_of_piece = 0;
					while(j < column + PIECE_COLUMN){
						if(piece[row_of_piece][column_of_piece] == 1){
							 matrix[i][j] = piece[row_of_piece][column_of_piece];
						}
						j++;
						column_of_piece++;
					}
					row_of_piece++;
					i++;
				}								
		}
	}
	else if(column_of_first == 1){			   // sol üst piece[0][1] de : matrix üzerinden column - 1, column ve column + 1 ile ilgilenicem
		                                       // S parçasý
		i = row;
		row_of_piece = 0;
		while(i <= row + 1){
			j = column - 1;
			column_of_piece = 0;
			while(j < column + PIECE_COLUMN - 1){
				if(piece[row_of_piece][column_of_piece] == 1){
					matrix[i][j] = piece[row_of_piece][column_of_piece];
				}
				j++;
				column_of_piece++;
			}
			row_of_piece++;
			i++;
		}	
	}
	else{							     	   // sol üst piece[0][2] de : matrix üzerinden column - 2, column -1  ve column  ile ilgilenicem
											   // 3 kere döndürülmüþ L parçasý
		i = row;
		row_of_piece = 0;
		while(i <= row + 1){
			j = column - 2;
			column_of_piece = 0;
			while(j < column + PIECE_COLUMN - 2){
				if(piece[row_of_piece][column_of_piece] == 1){
					matrix[i][j] = piece[row_of_piece][column_of_piece];
				}
				j++;
				column_of_piece++;
			}
			row_of_piece++;
			i++;
		}
	}
}
bool checkFirstLine(int matrix[][MAX_SIZE], int size){
	int i,counter;
	i = 0;
	while(i < size){
		if(matrix[0][i] == 1){
			i = size + 1;
		}
		else{
			i++;
		}
	}
	if(i > size){
		return true;
	}
	else{
		return false;
	}
}
void rotateClockwise90(int piece[][PIECE_COLUMN],int pieceNo){
	void fillPieceMatrix(int [][PIECE_COLUMN], int );
	int i,j,tmp;
	switch(pieceNo){
		case 0:
			if(piece[1][0] == 1){
				fillPieceMatrix(piece,4);
			}
			else{
				fillPieceMatrix(piece,0);
			}
			break;
		case 1:
			if(piece[0][2] == 1){
				if(piece[1][2] == 1){
					fillPieceMatrix(piece,1);
				}
				else{
					for(i = 0;i < PIECE_ROW;i++){
						for(j = 0;j < PIECE_COLUMN;j++){
							if((i==0 && j==0) || (i==0 && j==1) || (i==1 && j==1) || (i==2 && j==1)){
								piece[i][j] = 1;
							}
							else{
								piece[i][j] = 0;
							}
						}
					}
				}
			}
			else{
				if(piece[0][1] == 1){
					for(i = 0;i < PIECE_ROW;i++){
						for(j = 0;j < PIECE_COLUMN;j++){
							if((i==0 && j==2) || (i==1 && j==0) || (i==1 && j==1) || (i==1 && j==2)){
								piece[i][j] = 1;
							}
							else{
								piece[i][j] = 0;
							}
						}
					}
				}
				else{
					for(i = 0;i < PIECE_ROW;i++){
						for(j = 0;j < PIECE_COLUMN;j++){
							if((i==0 && j==0) || (i==0 && j==1) || (i==0 && j==2) || (i==1 && j==0)){
								piece[i][j] = 1;
							}
							else{
								piece[i][j] = 0;
							}
						}
					}
				}
			}
			break;
		case 3:
			if(piece[0][0] == 1){
				fillPieceMatrix(piece,3);
			}
			else{
				for(i = 0;i < PIECE_ROW;i++){
					for(j = 0;j < PIECE_COLUMN;j++){
						if((i==0 && j==0) || (i==1 && j==0) || (i==1 && j==1) || (i==2 && j==1)){
							piece[i][j] = 1;
						}
						else{
							piece[i][j] = 0;
						}
					}
				}
			}
			break;
		case 4:
			if(piece[0][1] == 1){
				fillPieceMatrix(piece,0);
			}
			else{
				fillPieceMatrix(piece,4);
			}
			break;
		case 5:
			tmp = piece[1][0];
			piece[1][0] = piece[0][1];
			piece[0][1] = tmp;
			break;
	}
}
void fillPieceMatrix(int piece[][PIECE_COLUMN], int pieceNo){
	int i,j;
	switch(pieceNo){
		case 0:											// I
			for(i = 0;i < PIECE_ROW;i++){
				for(j = 0;j < PIECE_COLUMN;j++){
					if(j == 0){
						piece[i][j] = 1;
					}
					else{
						piece[i][j] = 0;
					}
				}
			}  			
			break;
		case 1:											// L
			for(i = 0;i < PIECE_ROW;i++){
				for(j = 0;j < PIECE_COLUMN;j++){
					if((i==0 && j==0) || (i==1 && j==0) || (i==2 && j==0) || (i==2 && j==1)){
						piece[i][j] = 1;
					}
					else{
						piece[i][j] = 0;
					}
				}
			}  					
			break;
		case 2:											// O
			for(i = 0;i < PIECE_ROW;i++){
				for(j = 0;j < PIECE_COLUMN;j++){
					if((i==0 && j==0) || (i==0 && j==1) || (i==1 && j==0) || (i==1 && j==1)){
						piece[i][j] = 1;
					}
					else{
						piece[i][j] = 0;
					}
				}
			}					
			break;
		case 3:											// S
			for(i = 0;i < PIECE_ROW;i++){
				for(j = 0;j < PIECE_COLUMN;j++){
					if((i==0 && j==1) || (i==0 && j==2) || (i==1 && j==0) || (i==1 && j==1)){
						piece[i][j] = 1;
					}
					else{
						piece[i][j] = 0;
					}
				}
			} 					
			break;
		case 4:											// yatay I
			for(i = 0;i < PIECE_ROW;i++){
				for(j = 0;j < PIECE_COLUMN;j++){
					if(i == 0){
						piece[i][j] = 1;
					}
					else{
						piece[i][j] = 0;
					}
				}
			} 					
			break;
		case 5:											// i
			for(i = 0;i < PIECE_ROW;i++){
				for(j = 0;j < PIECE_COLUMN;j++){
					if((i==0 && j==0) || (i==1 && j==0)){
						piece[i][j] = 1;
					}
					else{
						piece[i][j] = 0;
					}
				}
			} 					
			break;
		case 6:											// .
			for(i = 0;i < PIECE_ROW;i++){
				for(j = 0;j < PIECE_COLUMN;j++){
					if(i==0 && j==0){
						piece[i][j] = 1;
					}
					else{
						piece[i][j] = 0;
					}
				}
			} 					
			break;
	}
}
int clearFullLines(int matrix[][MAX_SIZE], int size){
	void clearTheLine(int [][MAX_SIZE], int ,int);
	int i,j,counter,score;
	score = 0;
	for(i = 1;i < size;i++){
		counter = 0;
		for(j = 0;j < size;j++){
			if(matrix[i][j] == 1){
				counter++;
			}
		}
		if(counter == size){
			clearTheLine(matrix,size,i);
			score += size;
		}
	}
	return score;
}
void clearTheLine(int matrix[][MAX_SIZE], int size,int i){
	int j,k;
	for(k = i;k > 0;k--){
		for(j = 0;j < size;j++){
			matrix[k][j] = matrix[k-1][j];
		}
	}
	for(j = 0;j < size;j++){
		matrix[0][j] = 0;
	}
}
int MENU(int score[]){
	void clean(int []);
	int choise,size;
	clean(score);
	printf("	Yeni oyun acmak icin icin 1\n	Programi sonlandirmak icin 0 giriniz			");
	scanf("%d",&choise);
	while(choise != 0 && choise != 1){
		printf("	Hatali giris yaptiniz lutfen tekrar deneyin\n");
		printf("	Yeni oyun acmak icin icin 1\n	Programi sonlandirmak icin 0 giriniz		");
		scanf("%d",&choise);
	}
	if(choise == 1){
		clean(score);
		printf("	Oyun tahtasi boyutunu giriniz		");
		scanf("%d",&size);
		while(size < MIN_SIZE || size > MAX_SIZE){
			printf("	Oyun alani en az %dx%d en fazla %dx%d olabilir. Bu durumu goz onune alarak tekrar deger giriniz		",MIN_SIZE,MIN_SIZE,MAX_SIZE,MAX_SIZE);
			scanf("%d",&size);
		}
	}
	else{
		size = 0;
	}
	return size;
}
void printGameRules(){
	printf("	Oyun kurallari: \n");
	printf("		1: Size her adimda parca ve oyun alani sunulacaktir ve sizden sutun numarasi istenecektir\n");
	printf(" Ornek: 7 girmeniz durumunda 7. sutundaki uygun olan en alttaki karaye parcanin en ust satirinda bulunan en soldaki kare gelecek sekilde parca oyun alanina yerlestirilecektir.\n");
	printf(" (Not: Eger parca o alana yerlestirilemiyorsa sizden tekrar bilgi istenir)\n");
	printf("		2: Oyun alanindaki x ifadeleri bos alani 1 ifadeleri ise dolu alani ifade eder.\n");
	printf("		3: Oyun alaninin en ust satirina parcanin bir kismi gelecek sekilde ekleme yapildiginda en az bir satir parcalanmiyorsa oyun biter\n");
	printf("		4: Sutun numaralari oyun alaninin ustunde bulunur.(Not:Hizzayi kaydirmamasi icin 9 dan sonra 0 ile devam eder yani 10 u ifade eder)\n");
	printf("		5: Oyunun tamamlanmasi sonucunda skorunuz maksimum skor ise kayit edilir\n");
	printf("		6: Sizden bilgi istenen herhangi bir durumda -1 girerek oyunu sonlandirabilirsiniz. (Not : anlik skorunuz gecersiz sayilir)\n");
	printf("		7: Sizden bilgi istenen herhangi bir durumda 0 girerek oyun kurallarini goruntuleyebilirsiniz. (Not: arka arkaya kullanilamaz)\n (Not:0 kullanildiktan hemen sonra -1 kullanilamaz)\n");
	printf("	Devam etmek icin enter'a basiniz		");
	getch();
}
void clean(int score[]){
	system("cls");
	printf("									TETRIS							\n");
	printf("	score:%d														max score:%d \n\n",score[0],score[1]);
}
void printGameTable(int matrix[][MAX_SIZE], int size){
	int i,j;
	printf("	");
	for(j = 1;j <= size ;j++){
		if(j <= 9){
			printf("%d ",(j));
		}else{
			printf("%d ",(j) % 10);	
		}
	}
	printf("\n");
	for(i = 0;i < size ;i++){
		printf("	");
		for(j = 0;j < size;j++){
			if(matrix[i][j] == 0){
				printf("x ");
			}
			else{
				printf("1 ");
			}
		}
		printf("\n");
	}
}
void printPiece(int piece[][PIECE_COLUMN], int size){
	int i,j;
	for(i = 0;i < PIECE_ROW ;i++){
		printf("	");
		for(j = 0;j < PIECE_COLUMN;j++){
			if(piece[i][j] == 0){
				printf(" ");
			}
			else{
				printf("1");
			}
		}
		printf("\n");
	}
}
