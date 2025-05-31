#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENTS 118

typedef struct {
    int atomicNumber;
    char name[14];
    char symbol[3];
    char groupBlock[22];
    int row;
    int column;
} ChemicalElement;
 
ChemicalElement elements[MAX_ELEMENTS];


void readCSV(){


    
    FILE *file = fopen("elementinfo.csv", "r");
    if (!file) {
        printf("Error opening file, please make sure that elementinfo.csv is installed and on the same folder.\n");
        exit(1);
    }

    int count = 0;
    char line[1054];

    // Skip the header CSV file line
    fgets(line, sizeof(line), file);

    // Read each line from the CSV file
    while (fgets(line, sizeof(line), file) && count < MAX_ELEMENTS) {
            char *token;
            token = strtok(line, ",");
            elements[count].atomicNumber = atoi(token);

            token = strtok(NULL, ",");
            strncpy(elements[count].name, token, sizeof(elements[count].name));

            token = strtok(NULL, ",");
            strncpy(elements[count].symbol, token, sizeof(elements[count].symbol));

            token = strtok(NULL, ",");
            strncpy(elements[count].groupBlock, token, sizeof(elements[count].groupBlock));

            token = strtok(NULL, ",");
            elements[count].row = atoi(token);

            token = strtok(NULL, ",");
            elements[count].column = atoi(token);

            count++;
    }
    
    fclose(file);
    
}

int IntAndCheck(int max){
    int choice;
    do{
        if (scanf("%d",&choice) != 1 || choice > max ){
            while (getchar() != '\n');/*  Empty scanf buffer */
            return max+1;
        }else{
            while (getchar() != '\n');/*  Empty scanf buffer */
            return choice;
        }
    }while (1); 

}

void StringAndCheck(int characterlimit,char *str){

    fgets(str, characterlimit, stdin);

    // Remove the newline character if present
    str[strcspn(str, "\n")] = 0;

    //I didn't want to include <ctype.h> only for this so I invented the wheel. Probably should've included <ctype.h>. oh well...
    if (str[0]>='a' && str[0]<='z')str[0] -= 32; //Convert First Letter to Uppercase
    
    for (int i = 1; str[i] != '\0'; i++) { //Convert all other letters to lowercase
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] +=32;
        }
    }
    
}

int stringsearch(char key[], int searchcase){
    int i=0;
    int rvalue=1;
    if (searchcase == 0){ //Search for Name
        for (i; i<MAX_ELEMENTS; i++){
            rvalue = strcmp(key,elements[i].name);
            if (rvalue==0)return i;
        }
    }else if (searchcase == 1){ //Search for Symbol
        for (i; i<MAX_ELEMENTS; i++){
            rvalue = strcmp(key,elements[i].symbol);
            if (rvalue==0)return i;
        }
    }else{
        
        for (i; i<MAX_ELEMENTS; i++){ //Search if groupBlock exists (CGB check)
            rvalue = strcmp(key,elements[i].groupBlock);
            if (rvalue==0)return 1;
        }    
    }
    return -1;
}

int isitred(int AtomicMin, int AtomicMax, char CGB[], double Massmin, double Massmax,int i){
    double atomicMass[] = { 1.008, 4.0026, 7.0, 9.012183, 10.81, 12.011, 14.007, 15.999, 18.99840316, 20.18,
                        22.9897693, 24.305, 26.981538, 28.085, 30.973762, 32.07, 35.45, 39.9, 39.0983, 40.08,
                        44.95591, 47.867, 50.9415, 51.996, 54.93804, 55.84, 58.93319, 58.693, 63.55, 65.4,
                        69.723, 72.63, 74.92159, 78.97, 79.9, 83.8, 85.468, 87.62, 88.90584, 91.22, 92.90637,
                        95.95, 96.90636, 101.1, 102.9055, 106.42, 107.868, 112.41, 114.818, 118.71,
                        121.76, 127.6, 126.9045, 131.29, 132.905452, 137.33, 138.9055, 140.116, 140.90766,
                        144.24, 144.91276, 150.4, 151.964, 157.25, 158.92535, 162.5, 164.93033, 167.26,
                        168.93422, 173.05, 174.9667, 178.49, 180.9479, 183.84, 186.207, 190.2, 192.22,
                        195.08, 196.96657, 200.59, 204.383, 207, 208.9804, 208.98243, 209.98715, 222.01758,
                        223.01973, 226.02541, 227.02775, 232.038, 231.03588, 238.0289, 237.048172, 244.0642,
                        243.06138, 247.07035, 247.07031, 251.07959, 252.083, 257.09511, 258.09843, 259.101,
                        266.12, 267.122, 268.126, 269.128, 270.133, 269.1336, 277.154, 282.166, 282.169,
                        286.179, 286.182, 290.192, 290.196, 293.205, 294.211, 295.216
    }; //(Δεν τόλμησα να χρησιμοποιήσω strtof και το atof δεν είναι αρκετά accurate :( )

    char zerocheck[22] = "0";

    //Everything is 0 case
    if (AtomicMax == 0 && AtomicMin == 0 && Massmax ==0 && Massmin == 0 && strcmp(CGB,zerocheck)==0)return 0;

    //Out of Atomic Number Range case
    if ((AtomicMin != 0 && AtomicMin > elements[i].atomicNumber) ||
        (AtomicMax != 0 && AtomicMax < elements[i].atomicNumber))return 0;
    

    //Not in Groupblock case
    if (strcmp(CGB,zerocheck)!=0 && strcmp(CGB,elements[i].groupBlock)!=0)return 0;
    

    //Out of Atomic Mass Range case
    if ((Massmin != 0 && Massmin > atomicMass[i])||
        Massmax != 0  && Massmax < atomicMass[i])return 0;

    return 1; //Element is red
}

void printheader(int periodictablecase){ //clears screen and prints the "intro" menu

    if (system("clear"))
    {
        system("cls"); //if one doesnt work the other will
    }  

    if (periodictablecase){
        printf("\t\t\t\t\t\t\t| -------------------------- |\n");
        printf("\t\t\t\t\t\t\t| Periodic Table of Elements |\n");
        printf("\t\t\t\t\t\t\t| -------------------------- |\n");
        return; 
    }
        printf("\t| -------------------------- |\n");
        printf("\t| Periodic Table of Elements |\n");
        printf("\t| -------------------------- |\n");


}

int printperiodic(int AtomicMin, int AtomicMax, char CGB[], double Massmin, double Massmax){
    #define ROWS 9 //Theoretically it has 7 but for the sake of programming it has 9...
    #define COLUMNS 18 
    printheader(1);
    
    printf("Selected group of elements\n\n");
    int elementcount=0;
    int row,column;
    for (row = 0; row<ROWS; row++){
        for(column=0;column<COLUMNS;column++){
            if ((elements[elementcount].column != column+1)){
                printf("     \t");
                continue;
            }

            if (isitred(AtomicMin, AtomicMax, CGB, Massmin, Massmax,elementcount)){ 
                printf("\033[31m");//set color to red
                printf("%3d"":""%.2s\t",elements[elementcount].atomicNumber,elements[elementcount].symbol );
                printf("\033[0m");//reset color
            }else{
                printf("%3d"":""%.2s\t",elements[elementcount].atomicNumber,elements[elementcount].symbol );
            }
            elementcount++;
            
            if (column + 1 == 2 && row + 1 == 6){elementcount = 71;}
            if (column + 1 == 2 && row + 1 == 7){elementcount = 103;}
            if (column + 1 == 18 && row + 1 == 7){elementcount = 56;}
            if (column + 1 == 18 && row + 1 == 8){elementcount = 88;}
        }
        if (elements[elementcount].row != row+1)printf("\n");
    }
    return 0;
}

int F4(){
    printheader(0);
    
    printf("\n\tGroup of Elements Search, define Criteria:\n\t1. Minimum atomic number(<=118): ");
        int minA = IntAndCheck(118);
        if (minA == 119)return 1; //start F4 from the beggining

    printf("\n\t2. Maximum atomic number(>=minimum): ");
        int maxA = IntAndCheck(2147483647); //int limit
   
        if((maxA<minA && maxA != 0)||(maxA == 119)){
            return 1; //start F4 from the beggining
        }
 
    printf("\n\t3. Chemical Group Block: ");
        char CGB[22];
        char zerocheck[22] = "0";
        int foundnumber;
        StringAndCheck(22,CGB); //input for CGB
        foundnumber = stringsearch(CGB,2);
    
        if(foundnumber == -1 && strcmp(CGB,zerocheck)!=0)return 1; //Invalid Chem Group Block input, start over


    printf("\n\t4. Minimum atomic mass: ");
        double minam;

        if (scanf("%lf",&minam) != 1){
            while (getchar() != '\n');/*  Empty buffer */
            return 1;//start F4 from the beggining
        }

    
    printf("\n\t5. Maximum atomic mass(>=minimum): ");
        double maxam;
    
        if (scanf("%lf",&maxam) != 1 || (maxam < minam && maxam !=0)){
            while (getchar() != '\n');/*  Empty buffer */
            return 1;//start F4 from the beggining
        }

    if (printperiodic(minA,maxA,CGB,minam,maxam)==0){
        return 0;
    }else{
        return 1;//start F4 from the beggining
    }
}

int goagain(){
    printf("\n\t Would you like to continue? (1 for yes): ");
    int r; 
    scanf("%d",&r);
    if (r != 1)return 0;
    return r;
}


int F3(int i){
    printheader(0);
    
    double atomicMass[] = { 1.008, 4.0026, 7.0, 9.012183, 10.81, 12.011, 14.007, 15.999, 18.99840316, 20.18,
                        22.9897693, 24.305, 26.981538, 28.085, 30.973762, 32.07, 35.45, 39.9, 39.0983, 40.08,
                        44.95591, 47.867, 50.9415, 51.996, 54.93804, 55.84, 58.93319, 58.693, 63.55, 65.4,
                        69.723, 72.63, 74.92159, 78.97, 79.9, 83.8, 85.468, 87.62, 88.90584, 91.22, 92.90637,
                        95.95, 96.90636, 101.1, 102.9055, 106.42, 107.868, 112.41, 114.818, 118.71,
                        121.76, 127.6, 126.9045, 131.29, 132.905452, 137.33, 138.9055, 140.116, 140.90766,
                        144.24, 144.91276, 150.4, 151.964, 157.25, 158.92535, 162.5, 164.93033, 167.26,
                        168.93422, 173.05, 174.9667, 178.49, 180.9479, 183.84, 186.207, 190.2, 192.22,
                        195.08, 196.96657, 200.59, 204.383, 207, 208.9804, 208.98243, 209.98715, 222.01758,
                        223.01973, 226.02541, 227.02775, 232.038, 231.03588, 238.0289, 237.048172, 244.0642,
                        243.06138, 247.07035, 247.07031, 251.07959, 252.083, 257.09511, 258.09843, 259.101,
                        266.12, 267.122, 268.126, 269.128, 270.133, 269.1336, 277.154, 282.166, 282.169,
                        286.179, 286.182, 290.192, 290.196, 293.205, 294.211, 295.216
                        }; //(Δεν τόλμησα να χρησιμοποιήσω strtof και το atof δεν είναι αρκετά accurate :( )

    
    if (i > 0 && i<119){ //Not really necessary but it is asked sooo
        i -= 1;
        printf("\n\t Element Description\n");
        printf("\t1. Atomic Number: %d\n", elements[i].atomicNumber);
        printf("\t2. Name: %s\n", elements[i].name);
        printf("\t3. Symbol: %s\n", elements[i].symbol);
        printf("\t4. Group Block: %.21s\n", elements[i].groupBlock);
        printf("\t5. Atomic Mass: %lf\n\n", atomicMass[i]);
        return 0;
    }else{
        return 1;
    }
}


void F2(){
    
        printheader(0);
        printf("\n\tIndividual Element Search, based on:\n\t1. Atomic Number\n\t2. Name\n\t3. Symbol\n\n\tType your selection (1, 2 or 3): ");
        int Schoice = IntAndCheck(3); //Second Choice 

    while (Schoice < 1 || Schoice==4){
        printf("\tInvalid input, please try again: ");
        Schoice = IntAndCheck(3); //Second Choice 
    }
    
    printf("\n\n\t");
    int foundnumber;
    switch(Schoice){
        case 1:
            printf("Provide element atomic number: ");
            int atomickey = IntAndCheck(118);
           
            while (atomickey == 119 || atomickey<1){

                printf("Atomic number should be between 1 and 118, try again: ");
                atomickey = IntAndCheck(118);
            }
            
            F3(atomickey);
            break;
        case 2:
            printf("Provide element Name: ");  
            char key[14];
            StringAndCheck(14,key);   
            foundnumber = stringsearch(key,0);

            while (foundnumber == -1){
                printf("This element does not exist, please try again: ");
                StringAndCheck(14,key);   
                foundnumber = stringsearch(key,0);
            } 

            F3(foundnumber+1);
            break;
        case 3:
            printf("Provide element Symbol: ");
            char key2[3];
            StringAndCheck(3,key2);
            foundnumber = stringsearch(key2,1);

            while (foundnumber == -1){
                printf("This element symbol does not exist, please try again: ");
                StringAndCheck(3,key2);
                foundnumber = stringsearch(key2,1);
            }

            
            if (F3(foundnumber+1)==0){
                break;
            }else{
                F2();
                break;
            }
    }
}



int F1(int end){
    printheader(0);
    printf("\n\t1. Search for individual elements\n\t2. Search for group of elements\n\t3. Terminate Application\n\n");
    if (!end){
        int choice;
        do{
            printf("\tType your selection (1,2 or 3): ");
            choice = IntAndCheck(3);
        }while(choice == 4 || choice < 1);
    
        switch (choice){
            case 1:
                F2();
                break;
            case 2:
                while (F4());
                break;
            case 3:
                return 1;
        }
    }
    return 0;
}

int main(){
    readCSV();
    int terminate = 0;
    do{
         terminate = F1(0);
         if (terminate)break;
    }while (goagain());
    F1(1); //Print starting screen, as requested
    return 0;
}
