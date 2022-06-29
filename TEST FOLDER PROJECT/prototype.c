#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//global declarations
int constnum_of_items, n, sum = 0;
struct dish{
  char dname[100];
  float kcal;
};

void dishes(struct dish d[constnum_of_items]){//To append the name of the dishes
  FILE *fp = fopen("list.txt", "r");
  if(fp == NULL){
    printf("File not found");
    exit(1);
  }
    int MAX_LINE = 200; char buffer[100];
    for(int i = 0; i <= constnum_of_items; i++){
    if(i == 0)
      fgets(d[i].dname, MAX_LINE, fp);//get rid of the count
    else
      fgets(d[i-1].dname,MAX_LINE,fp);}
    fclose(fp);
  }



void calories(struct dish d[constnum_of_items]){//to append calories
    FILE *fp = fopen("calories.txt", "r");

    int MAX_LINE = 200; char buffer[100];
    for(int i = 0; i <= constnum_of_items; i++){
        fscanf(fp, "%f", &d[i].kcal);
      }
    fclose(fp);
}


void List_of_items(struct dish d[]){//Menu to be printed in console
  for(int i = 0; i < constnum_of_items; i++){
    printf("%d.Name :: %s\n",i, d[i].dname);
    printf("Calories :: %.3f per 100 gram\n\n", d[i].kcal);
  }
}

void Output_Files(char* arr[], int n, float kcal){//Writing output in file
    FILE *p = fopen("orderlist.txt", "w");
    fseek(p, 0, SEEK_SET);
    fprintf(p," THE FINAL LIST FOR FOOD ORDER \n");
    for(int j = 0; j < n; j++){
      fprintf(p,"%s",*(arr+j));
    }
    fprintf(p, "The total calories for the meal is %f", kcal);
    fclose(p);
}

int Avg_kcal_cal(float tot){//devising healthy meal
  float tot_kcal;
  printf("Please enter the average calories needed for a person (usually 667 per meal for adult) ::  \n");
  scanf("%f", &tot_kcal);
  float per = (30.00/100.0)*tot_kcal;
  if(tot_kcal+per >= tot && tot_kcal-per <= tot && tot){
    printf("The calorie intake is perfect");
    return 1;}
  else{
    printf("Please replan the menu from first");
    return 0;}
}

int main(){
  //mandatory code for prequisites
  FILE *fp = fopen("list.txt", "r");
  fscanf(fp, "%d", &constnum_of_items);
  struct dish items[constnum_of_items];
  fclose(fp);
  dishes(items);
  calories(items);
  List_of_items(items);

  //User-Interaction phase
  int opt, nofdishes, i = 0;
  float sum = 0;
  printf("\n\nPlease enter the number of dishes:: \n");
  scanf("%d", &nofdishes);
  char* fin_list[nofdishes];//pointer string array
  while(nofdishes--){//Selecting the meal from menu
    printf("\nPress the number for the desired dish :: \n");
    scanf("%d", &opt);
    if(opt > constnum_of_items || opt < 0){//wrong option
      printf("Please enter a valid option");
      nofdishes++;
      continue;
    }
    printf("Dish selected :: %s\n", items[opt].dname);
    printf("Total calories = %f\n", sum += items[opt].kcal);
    *(fin_list+i) = items[opt].dname;//Final list for menu
    i++;
    }

    if(Avg_kcal_cal(sum))
      Output_Files(fin_list, i, sum);

    return 0;
  }
