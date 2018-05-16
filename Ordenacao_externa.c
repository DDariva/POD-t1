#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAL 50

char* reduz(char p[PAL]){
    if(p!=NULL){
        int n=strlen(p);
        for (int i = 0; i < n; i++){
            if (p[i]<'a'){
                p[i]+=('a'-'A');
            }
        }
    }
    return p;
}

void quickSort(char **strings, int esq, int dir){

    int i = esq, j = dir;
    char *x;
    char temp[50];

    if(j - i >= 1){
        x = strings[i];
        strcpy(temp, strings[esq]);
        strcpy(strings[esq], x);
        strcpy(x, temp);
        while(j > i){
            //  palavra[i] é menor que o pivô e i < direita
            while((strcmp(reduz(strings[i]),x) <= 0) && i < dir && j > i){
                i++;
            }
            //  palavra[j] é maior que o pivô e j > esquerda
            while((strcmp(reduz(strings[j]),x) >= 0) && j > esq && j >= i){
                j--;
            }
            // troca as palavras
            if(j > i){
                strcpy(temp, strings[i]);
                strcpy(strings[i], strings[j]);
                strcpy(strings[j], temp);
            }
        }

        strcpy(temp, strings[esq]);
        strcpy(strings[esq], strings[j]);
        strcpy(strings[j], temp);

        quickSort(strings, esq, j-1);

        quickSort(strings, j+1, dir);
    } 
}

int NumPalavras(char *NomeArq){
    int comecouPalavra = 0, numPalavras = 0, numLinhas = 0;
    FILE *descritor;
    char *caracter=(char*)malloc(sizeof(char));

    descritor = fopen(NomeArq, "r");
    while (!feof(descritor)) {
          fread(caracter, 1, 1, descritor);
          if  ((*caracter!=' ') && (*caracter!='\n') && (!comecouPalavra)) {
             comecouPalavra = 1;
          }
          if  (((*caracter==' ') || (*caracter == '\n')) && (comecouPalavra)) {
             comecouPalavra = 0;
             numPalavras++;
          }
          if (*caracter=='\n') {
             numLinhas++;
             }
   }
   free(caracter);
   return numPalavras + 1;
}

int LimpaArquivo(char Arq[]){
    
    FILE *entrada, *saida;
    entrada=fopen(Arq,"r+");
    saida=fopen("limpo.txt", "w+");
    char c;
    while(1){
        c=fgetc(entrada);
        if (feof(entrada)){
            break;
        }
        if (c==' ' || (c>='0' && c<='9') || (c>='A' && c<='Z') || (c>='a' && c<='z') || c =='\n'){
            if(c == '\n'){
                c = ' ';
            }
            fprintf(saida, "%c", c);
        }
    }
    fclose(entrada);
    fclose(saida);

    return 0;
}

void geraNomeArq(int n, char *retorno){
    char num[2];
    char part[5];
    char txt[5];
    char name[15];

    strcpy(part,"part");
    strcpy(txt,".txt");

    strcpy(name,part);
    num[0]=n+'0';
    num[1]='\0';
    strcat(name,num);
    strcat(name,txt);

    strcpy(retorno, name);
}

void separaArq(void){
    FILE * inicio=fopen("limpo.txt","r");
    FILE *parte;
    int n=NumPalavras("limpo.txt");
    int narq=0;
    int i=0;

    char name[15];
    char palavra[50];
    n=(n/4)+1;
    while(!feof(inicio)){
        geraNomeArq(narq,name);

        parte=fopen(name, "w+");
        while(i<n && !feof(inicio)){
            fscanf(inicio, "%s", palavra);
            fprintf(parte, "%s ", palavra);
            i++;    
        }

        i=0;
        narq++;
        fclose(parte);
    }
    fclose(inicio);
    while(narq<4)
    {
        geraNomeArq(narq,name);
        parte=fopen(name, "w+");
        fclose(parte);
        narq++;
    }
}

void ordenaBlocos(void){

    int flag=0;
    FILE *part0, *part1, *part2, *part3;
    part0 = fopen("part0.txt","r");
    part1 = fopen("part1.txt","r");
    part2 = fopen("part2.txt","r");
    part3 = fopen("part3.txt","r");

    int n,i;
    char **strings;

    // ordena primeiro bloco
        i=0;
        n = NumPalavras("part0.txt");
        if(n>0){
            flag=1;
            strings=(char**)malloc(sizeof(char*)*n);
            for (int i = 0; i < n; i++)
            {
                strings[i]=(char*)malloc(sizeof(char)*50);
                strings[i][0]='\0';
            }
        }
        i=0;
        while(!feof(part0)){
            fscanf(part0,"%s",strings[i]);
            i++;
        }
        fclose(part0);
        if(!feof(part0)){
            remove("part0.txt");
            part0=fopen("part0.txt","w+");
            quickSort(strings, 0, n-1);
            for (i = 0; i < n; i++)
            {
                fprintf(part0,"%s ",strings[i]);
            }
        }
        fclose(part0);
        if(flag==1){   
            for (int i = 0; i < n; i++)
            {
                free(strings[i]);
            }
            free(strings);
        }
        flag=0;

    // ordena segundo bloco
        i = 0;
        n = NumPalavras("part1.txt");
            if(n>0){  
            strings=(char**)malloc(sizeof(char*)*n);
            for (int i = 0; i < n; i++)
            {
                strings[i]=(char*)malloc(sizeof(char)*50);
                strings[i][0]='\0';
            }
            flag=1;
          }
        i=0;
        while(!feof(part1)){
            fscanf(part1,"%s",strings[i]);
            i++;
        }
        fclose(part1);
        if(!feof(part1)){
            remove("part1.txt");
            quickSort(strings, 0, n-1);
            part1=fopen("part1.txt","w+");
            for (i = 0; i < n; i++)
            {
                fprintf(part1,"%s ",strings[i]);
            }
            fclose(part1);
        }
        if(flag==1){   
            for (int i = 0; i < n; i++)
            {
                free(strings[i]);
            }
            free(strings);
        }
        flag=0;

    // ordena terceiro bloco
        i = 0;
        n = NumPalavras("part2.txt");
        strings=(char**)malloc(sizeof(char*)*n);
        if(n>0){
            for (int i = 0; i < n; i++)
            {
                strings[i]=(char*)malloc(sizeof(char)*50);
                strings[i][0]='\0';
            }
            flag=1;
        }
        i=0;
        while(!feof(part2)){
            fscanf(part2,"%s",strings[i]);
            i++;
        }
        fclose(part2);
        if(!feof(part2)){
            remove("part2.txt");    
            quickSort(strings, 0, n-1);
            part2=fopen("part2.txt","w+");
            for (i = 0; i < n; i++)
            {
                fprintf(part2,"%s ",strings[i]);
            }
            fclose(part2);
        }
        if(flag==1){
            for (int i = 0; i < n; i++)
                {
                    free(strings[i]);
                }
            free(strings);
        }
        flag=0;

    // ordena quarto bloco
        i = 0;
        n = NumPalavras("part3.txt");
        if(n>0){ 
            strings=(char**)malloc(sizeof(char*)*n);
            for (int i = 0; i < n; i++)
            {
               strings[i]=(char*)malloc(sizeof(char)*50);
               strings[i][0]='\0';
            }
            flag=1;
        }
        i=0;
        while(!feof(part3)){
            fscanf(part3,"%s",strings[i]);
            i++;
        }
        fclose(part3);
        if(!feof(part3)){
            remove("part3.txt");
            quickSort(strings, 0, n-1);
            part3=fopen("part3.txt","w+");
            for (i = 0; i < n; i++)
            {
                fprintf(part3,"%s ",strings[i]);
            }
            fclose(part3);
        }
        if(flag==1){
            for (int i = 0; i < n; i++)
            {
                free(strings[i]);
            }
            free(strings);
        }
}

void uneArq(void){
	FILE *part0, *part1, *part2, *part3, *saida;
	saida=fopen("ordenado.txt", "w+");
	part0=fopen("part0.txt", "r");
	part1=fopen("part1.txt", "r");
	part2=fopen("part2.txt", "r");
	part3=fopen("part3.txt", "r");

	char p1[PAL], p2[PAL], p3[PAL], p4[PAL], menor[PAL];
		strcpy(p1,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
		strcpy(p2,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
		strcpy(p3,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
		strcpy(p4,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");

	if(!feof(part0)){
		fscanf(part0, "%s",p1);
	}
	if (!feof(part1)){
		fscanf(part1, "%s",p2);
	}
	if (!feof(part2)){
		fscanf(part2, "%s",p3);
	}
	if (!feof(part3)){
		fscanf(part3, "%s",p4);
	}
	while(!feof(part0) || !feof(part1) || !feof(part2) || !feof(part3)){
		if (strcmp(p1,p2)<0){
			if (strcmp(p1,p3)<0){
				if (strcmp(p1,p4)<0){
					if (!feof(part0)){
						strcpy(menor,p1);
						fscanf(part0,"%s",p1);
						if(feof(part0)){
							strcpy(p1,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
						}
					}
				}
				else{
					if (!feof(part3)){
						strcpy(menor,p4);
						fscanf(part3,"%s",p4);
						if(feof(part3)){
							strcpy(p4,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
						}
					}
				}
			}
			else{
				if (strcmp(p3,p4)<0){
					if (!feof(part2)){
					strcpy(menor,p3);
					fscanf(part2,"%s",p3);
						if(feof(part2)){
							strcpy(p3,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
						}
					}
				}
				else{
					if (!feof(part3)){
						strcpy(menor,p4);
						fscanf(part3,"%s",p4);
						if(feof(part3)){
							strcpy(p4,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
						}
					}
				}
			}
		}
		else{
			if (strcmp(p2,p3)<0)
			{
				if (strcmp(p2,p4)<0)
				{
					if (!feof(part1)){
					strcpy(menor,p2);
					fscanf(part1,"%s",p2);
						if(feof(part1)){
							strcpy(p2,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
						}
					}
				}
				else{
					if (!feof(part3)){
						strcpy(menor,p4);
						fscanf(part3,"%s",p4);
						if(feof(part3)){
							strcpy(p4,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
						}
					}
				}
			}
			else{
				if (strcmp(p3,p4)<0)	{
					if (!feof(part2)){
					strcpy(menor,p3);
					fscanf(part2,"%s",p3);
						if(feof(part2)){
							strcpy(p3,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
						}
					}
				}
				else{
					if (!feof(part3)){
						strcpy(menor,p4);
						fscanf(part3,"%s",p4);
						if(feof(part3)){
							strcpy(p4,"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz\0");
						}
					}
				}
			}
		}
		fprintf(saida, "%s ", menor);
	}
	fclose(saida);
	fclose(part0);
	fclose(part1);
	fclose(part2);
	fclose(part3);

	remove("part0.txt");
	remove("part1.txt");
	remove("part2.txt");
	remove("part3.txt");
	remove("limpo.txt");
    
}

int main(){
    //cria uma string com o nome do arquivo
    char arquivo[25] = "aristotle-on-267.txt";

    //retira todos os caracteres especiais
    LimpaArquivo(arquivo);

    //separa os arquivo em blocos menores
    separaArq();

    //ordena cada bloco menor
    ordenaBlocos();

    //unifica os blocos menores em um maior ordenado
    uneArq();

    getchar();
    return 0;
}
