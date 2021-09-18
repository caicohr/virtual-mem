#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int accesses;
int hits;
int misses;
int compulsorymisses;
//int memoryframe;
int switches;
int newest;
/*
int PageTableIndex;

void setPageTable(int pageIndex){
    PageTableIndex = pageIndex;
}

void setSwitch(int switching){
    switches = switching;
}
*/

//typedef enum { F, T } bool;
//struct PageTable PageTableHere;
struct ProcessTable Processing;
struct Memory TheMemory;
struct Disk Storing;

struct PageTableEntry{
    bool valid;
    bool inMemory;
    int frame;
};

struct PageTable{
    //int PTN;
    int PageTableNumber;
    struct PageTableEntry PTE[64];
};

struct ProcessTable{
    struct PageTable PageTableNow[9];
};

struct Memory{
    int memoryframe;
    int PTEinMemory[30];
};

struct Disk{
    struct Memory PageMemory[9];
};


//void setPT(int PTnumber){
    //Processing.PageTableNow[newest].PageTableNumber = PTnumber;
    //PageTableHere.PageTableNumber = PTnumber;
    //printf("You just set the current Page Table to: PageTable[%d]\n", PageTableHere.PageTableNumber);
//};

//void createPT(int PTnumber){
//    struct PageTable PageTableHere[PTnumber];
//}

void setValidity(){
    for (int n = 0;n < 64; n++){
        Processing.PageTableNow[newest].PTE[n].valid = false;
        Processing.PageTableNow[newest].PTE[n].inMemory = false;
        //PageTableHere.PTE[n].valid = false;
        //PageTableHere.PTE[n].inMemory = false;
    }
    /*
    for (int n = 0; n < 30; n++){
        TheMemory.PTEinMemory[n] = 0;
    }
    */
    
};
/*
void refreshMemory() {
    for (int n = 0; n < 30; n++){
        Storing.PageMemory[switches].PTEinMemory[n] = 0;
    }
}
*/

int comparePTEtoMem(int index){
    //printf("Index is %d\n", index);
    for(int n=0;n<30;n++){
        //printf("The PTEinMemory[n] is %d\n", Storing.PageMemory[switches].PTEinMemory[n]);
        if(index == Storing.PageMemory[switches].PTEinMemory[n]){
                //printf("They match!\n");
                return 0;
            }
            else {
                return 1;
            }
        }
        return 1;
};

void checkValidity(int index){
    //printf("Accessing PageTableEntry[%d]\n",index);
    if (Processing.PageTableNow[switches].PTE[index].valid == false) {
        misses++;
        compulsorymisses++;
        accesses++;
        //printf("Setting TheMemory Frame: %d to index: %d\n", TheMemory.PTEinMemory[memoryframe], index);
        Storing.PageMemory[switches].PTEinMemory[Storing.PageMemory[switches].memoryframe] = index;
        //printf("Set The Memory Frame number %d of MemoryNumber %d to index: %d\n", Storing.PageMemory[switches].memoryframe, switches,index);
        Processing.PageTableNow[switches].PTE[index].valid = true;
        Processing.PageTableNow[switches].PTE[index].inMemory = true;
        //printf("Before: %d\n", Storing.PageMemory[switches].memoryframe);
        Storing.PageMemory[switches].memoryframe++;
        //printf("Storing.PageMemory[switches].memoryframe is now: %d\n", Storing.PageMemory[switches].memoryframe);
        if(Storing.PageMemory[switches].memoryframe == 30) {
            //printf("MemoryFrame is now %d. Setting to", memoryframe);
            Storing.PageMemory[switches].memoryframe = 0;
            //printf("%d\n", memoryframe);
        }
        //printf("TheMemory Frame is now: %d\n", memoryframe);
    } else {
        if(Storing.PageMemory[switches].memoryframe == 30) {
            //printf("MemoryFrame is now %d. Setting to", memoryframe);
            Storing.PageMemory[switches].memoryframe = 0;
            //printf("%d\n", memoryframe);
        }
        int result = comparePTEtoMem(index);
        //printf("RESULT COMPARING IS: %d\n", result);
        if (result == 1){
            hits++;
            accesses++;
            //it is in memory
        }
        else{
            misses++;
            accesses++;
            Storing.PageMemory[switches].PTEinMemory[Storing.PageMemory[switches].memoryframe] = index;
            Storing.PageMemory[switches].memoryframe++;
        }
    }
    
};

int main(int argc, char **argv) {
    if (argc == 2) {
        //printf("You have a file named %s!\n", argv[1]);
        //printf("Here is the data of your file:\n");
        char word[10];
        FILE *file;
        file = fopen(argv[1], "r");
        int number;
        int index;
        char str1[] = "new", str2[] = "switch", str3[] = "access";
        while (fscanf(file, "%s", word) != EOF) {
            
            if ((strcmp(word,str1)) == 0 ) {
                //printf("The word is 'new'.\n");
                fscanf(file, "%s\n", word);
                number = atoi(word);
                //createPT(number);
                //printf("PageTable[%d] created!\n", number);
                //setPageTable(number);
                number = newest;
                //setPT(number);
                setValidity();
            }
            else if ((strcmp(word,str2)) == 0 ){
                //printf("The word is switch\n");
                fscanf(file, "%s\n", word);
                number = atoi(word);
                //setSwitch(number);
                //printf("The switch is number %d!\n", number);
                //checkPT(PageTable[PageTableIndex]);
                //printf("Setting validity\n");
                switches = number;
                //printf("switching to %d\n", switches);
                //printf("Done setting validity\n");
                //setValidity();
                //refreshMemory();
            }
            else if ((strcmp(word,str3)) == 0 ){
                //printf("The word is access.\n");
                fscanf(file, "%s\n", word);
                number = atoi(word);
                index = number >> 10;
                //printf("Accessing PageTableEntry[%d]\n",index);
                checkValidity(index);
            }
            else {
                printf("What is this???\n");
            }
        }
        fclose(file);
    }
    
    else {
        printf("You don't have a file to load\n");
    }
    printf("Accesses: %d\n", accesses);
    printf("Hits: %d\n", hits);
    printf("Misses: %d\n", misses);
    printf("Compulsory Misses: %d\n", compulsorymisses);

/*
    int see = 13;
    int seenow = see >> 10;
    printf("Seenow is: %d\n", seenow);
    
   int PTEinMemory1[30];
   PTEinMemory1[0] = 100;
   PTEinMemory1[1] = 200;
   PTEinMemory1[2] = 300;
   printf("PTEinMemory1[0] is %d\n", PTEinMemory1[0]);
   printf("PTEinMemory1[1] is %d\n", PTEinMemory1[1]);
   printf("PTEinMemory1[2] is %d\n", PTEinMemory1[2]);
   */
   return 0;
};