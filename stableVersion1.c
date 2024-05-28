//stable version 4

// known bugs-> cant handle the view after using search function and deleting 
#include<stdio.h>

#include<windows.h>

#include<string.h> // Added to fix implicit declaration warning for strcmp

#include<conio.h> // Added for getch function

#include<stdbool.h>

#include<ctype.h> //using this for converting any strings to lowercase 

#include<time.h> // for the nano sleep function 

//defining colors 

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"

#define MAX_ATTEMPTS 3
#define PASSWORD "project"


void printSlowly(const char *message, int delay_ms);

void printSlowly(const char *message, int delay_ms) {
    // Loop through each character of the message
    for (int i = 0; message[i] != '\0'; i++) {
        putchar(message[i]); // Print the current character
        fflush(stdout); // Flush the output buffer to ensure the character is printed immediately
        
        struct timespec delay;
        delay.tv_sec = 0; // Delay in seconds
        delay.tv_nsec = delay_ms * 1000000; // Convert milliseconds to nanoseconds
        nanosleep(&delay, NULL); // Introduce a delay between each character
    }
}

char departments[][10] = {
  "CSE",
  "SWE",
  "EEE",
  "NFE"
}; 

void Password();
void mainmenu(void);
void addStudent(void);
void view(void);
void edit(void);
void delete_record(void);
int checkid(int);
void search(void);
void strToLower(char *str);


COORD coord = {
  0,
  0
}; // sets coordinates to 0,0
COORD max_res, cursor_size;

void gotoxy(int x, int y) {
  coord.X = x;
  coord.Y = y; // X and Y coordinates
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

FILE * fp, * ft;
int s;
char findStudent;
char password[10] = {
  "project"
};

struct student {
  char name[50];
  int id;
  char email[50];
  char * dep;
  int studentNumber;
};

struct student a;

int main()

{
  Password();
  getch();
  return 0;

}

void mainmenu() {

  system("cls");

  int i;
  gotoxy(20, 3);
  printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU ");
  printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
  gotoxy(20, 5);
  printf("\xDB\xDB\xDB\xDB\xB2 1. Add Student");
  gotoxy(20, 7);
  printf("\xDB\xDB\xDB\xDB\xB2 2. View Student");
  gotoxy(20, 9);
  printf("\xDB\xDB\xDB\xDB\xB2 3. edit Student");
  gotoxy(20, 11);
  printf("\xDB\xDB\xDB\xDB\xB2 4. delete info");
  gotoxy(20, 13);
  printf("\xDB\xDB\xDB\xDB\xB2 5. Search Student");
  gotoxy(20, 15);
  printf("\xDB\xDB\xDB\xDB\xB2 6. Close Application");
  gotoxy(20, 17);
  printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
 
  gotoxy(20, 21);
  printf("Enter your choice:");
  switch (getch()) {
  case '1':
    addStudent();
    break;
  case '2':
    view();
    break;
  case '3':
    edit();
    break;
  case '4':
    delete_record();
    break;
  case '5':
    search();
    break;
  case '6':
    close();
    break;

  default: {
    gotoxy(10, 23);
    printSlowly(RED"\aWrong Entry!! Please re-enter correct option"RESET , 50);
    if (getch())
      mainmenu();
  }

  }
}

void Password(void) {
    system("cls");
    gotoxy(15, 3);
    printSlowly("STUDENT DATABASE MANAGEMENT SYSTEM", 40);

    gotoxy(15, 5);
    printSlowly("********Password Protected********", 30);

    char ch, pass[10];
    int i = 0;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
       
        gotoxy(15, 9);
        printf("                                         "); // Clear previous attempt count

        // Prompt for password entry
        gotoxy(15, 7);
        printf("Enter Password: ");

        i = 0;
        ch = 0;
        while (ch != 13) { // Unless ch returns "Enter", keep getting single chars
            ch = getch();
       fflush(stdin); // Clearing input buffer
            if (ch != 13 && ch != 8) { // When ch doesn't return "Enter" or "Backspace"
                putch('#');
                pass[i] = ch;
                i++;
            }
        }

        pass[i] = '\0'; // Null-terminate the password

        if (strcmp(pass, PASSWORD) == 0) {
            gotoxy(15, 9);
            printSlowly(GREEN"Password match"RESET, 50);
            gotoxy(15, 11);
            printSlowly("Press any key to continue......",20);
            getch();
            mainmenu();
            return; // Exit the function
        } else {
            attempts++;
            system("cls"); //clearing screen before entering pass again
            gotoxy(15,3);
            printf("STUDENT DATABASE MANAGEMENT SYSTEM");
            gotoxy(15,5);
            printf("********Password Protected********");

            gotoxy(15, 9);
            printf(RED"Attempt %d of %d: WRONG PASSWORD !!!"RESET, attempts, MAX_ATTEMPTS);
            gotoxy(15, 11);
            printSlowly("Press any key to try again.....", 30);
            
            getch();
        }
    }

    // Maximum attempts reached
    system("cls");
    gotoxy(15, 9);
    printSlowly(RED"Maximum attempts reached. PROGRAM TERMINATED..." RESET,50);
    printf("\n");
    printf("\n");
    printf("\n");
    // Additional cleanup or exit code here
    exit(1);
}

void strToLower(char *str) { //this function converts any chars to lowercase
    while (*str != '\0') {
        *str = tolower(*str);
        str++;
    }
}


void addStudent(void) {

  system("cls");
  int i;

  gotoxy(20, 5);
  printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2SELECT DEPARTMENT");
  printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
  gotoxy(20, 7);
  printf("\xDB\xDB\xDB\xDB\xB2 1. CSE");
  gotoxy(20, 9);
  printf("\xDB\xDB\xDB\xDB\xB2 2. SWE");
  gotoxy(20, 11);
  printf("\xDB\xDB\xDB\xDB\xB2 3. EEE");
  gotoxy(20, 13);
  printf("\xDB\xDB\xDB\xDB\xB2 4. NFE");
  gotoxy(20, 15);
  printf("\xDB\xDB\xDB\xDB\xB2 5. Back to main menu");
  gotoxy(20, 21);
  printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
  gotoxy(20, 22);
  printf("Enter your choice:");
  scanf("%d", & s);
  if (s == 5)
    mainmenu();

  system("cls");
  fp = fopen("another.dat", "ab+");
  if (getdata() == 1) {
    a.dep = departments[s - 1];
    a.studentNumber = 1;
    fseek(fp, 0, SEEK_END);
    fwrite( & a, sizeof(a), 1, fp);
    fclose(fp);
a.studentNumber++;
    gotoxy(21, 14);
    printf(GREEN"The record is sucessfully saved"RESET);
    // a.studentNumber++;
    gotoxy(21, 15);
    printf("Save any more?(Y / N):");
    if (getch() == 'n')
      mainmenu();
    else
      system("cls");
    addStudent();
  }
  fflush(stdin);
}

int getdata() {
  int t;
  gotoxy(20, 3);
  printf("Enter the Information Below");

  gotoxy(21, 5);
  printf("Department:");
  gotoxy(31, 5);
  printf(" %s", departments[s - 1]);
  gotoxy(21, 6);
  printf("Student ID:\t");
  gotoxy(33, 6);
  scanf("%d", & t);
  if (checkid(t) == 0) {
    gotoxy(21, 13);
    printf(RED"\aThe student already exist\a"RESET);
    gotoxy(21, 15);
    printf("\aPress any key to continue..\a");
    getch();
    addStudent();
    return 0;
  }
  
  a.id = t;
  gotoxy(21, 7);
  printf("Student Name:");
  gotoxy(36, 7);
  scanf("%s", a.name);
  gotoxy(21, 8);
  printf("Email:");
  gotoxy(28, 8);
  scanf("%s", a.email);
  return 1;
  fflush(stdin);
}



int checkid(int t) //check whether the student is exist in database or not
{
  rewind(fp);
  while (fread( & a, sizeof(a), 1, fp) == 1)
    if (a.id == t)
      return 0; //returns 0 if student exists

  return 1; //return 1 if it doesn't exist
}

void edit() {
  system("cls");
  int d;
  char another = 'y';

  while (another == 'y') {
    system("cls");

    FILE * fp = fopen("another.dat", "rb+");
    if (fp == NULL) {
      gotoxy(10,10);
      printf(RED"Error: Cannot open file for editing\n"RESET);
      return;
    }

    gotoxy(15, 8);
    printf("********Edit Student Information********");
    gotoxy(15, 10);
    printf("Enter Student ID to be edited: ");
    scanf("%d", & d);

    bool found = false;
    while (fread( & a, sizeof(a), 1, fp) == 1) {
      if (a.id == d) {
        found = true;
        // Display student info for editing
        gotoxy(15, 12);
        printf("ID: %d", a.id);
        gotoxy(15, 13);
        printf("Name: %s", a.name);
        gotoxy(15, 14);
        printf("Email: %s", a.email);
        gotoxy(15, 16);
        printf("Enter new name: ");
        scanf("%s", a.name);
        gotoxy(15, 17);
        printf("Enter new email: ");
        scanf("%s", a.email);

        // Update record
        fseek(fp, -sizeof(a), SEEK_CUR);
        fwrite( & a, sizeof(a), 1, fp);
        gotoxy(15,18);
        printf(GREEN"The record is modified\n"RESET);
        break;
      }
    }

    if (!found) {
      gotoxy(15,11);
      printf(RED"No record found\n"RESET);
    }

    fclose(fp);
    gotoxy(15,19);
    printf(GREEN"Modify another Record? (Y/N): "RESET);
    // system("cls");
    gotoxy(15,20);
    fflush(stdin); // Clearing input buffer
    fflush(stdout);
    another = getch();
  }

  returnfunc();
}


void view(void) //function to view students
{
  int i=0,j;

  system("cls");
  gotoxy(1, 1);
  printf("*********************************Student List*****************************");
  gotoxy(2, 2);
  printf(" DEPARTMENT     ID    STUDENT NAME          EMAIL");
  j = 4;
  fp = fopen("another.dat", "rb");
  while (fread( & a, sizeof(a), 1, fp) == 1) {
    gotoxy(3, j);
    printf("%s", a.dep);
    gotoxy(18, j);
    printf("%d", a.id);
    gotoxy(24, j);
    printf("%s", a.name);
    gotoxy(46, j);
    printf("%s", a.email);
    printf("\n\n");
    j++;
    i = i + a.studentNumber;
  }
  gotoxy(3,28);
  printf("Total Students = %d ", i);
  fclose(fp);
  returnfunc();

}

void search(void) {
// printf("%d",a.studentNumber); 
if(a.studentNumber!=0)
{  
  system("cls");
  int d;
  findStudent = false;
  gotoxy(20,4);
  printf("**********************Search Student Information******************\n");
  gotoxy(20, 10);
  printf("1. Search by ID\n");
  gotoxy(20, 14);
  printf("2. Search by Name\n");
  gotoxy(15, 20);
  printf("Enter your choice : ");
  fp = fopen("another.dat", "rb+");
  rewind(fp);
  switch (getch()) {
  case '1': {
    system("cls");
    gotoxy(20, 4);
    printf("*********************Search by ID*********************\n");
    gotoxy(20, 5);
    printf("Enter the student ID: ");
    scanf("%d", & d);
    gotoxy(20, 7);
    printSlowly("Searching............",80);
    while (fread( & a, sizeof(a), 1, fp) == 1) {
      if (a.id == d) {
        gotoxy(20, 7);
        printf("The student is available\n");
        gotoxy(20, 9);
        printf("ID: %d\n", a.id);
        gotoxy(20, 10);
        printf("Name: %s\n", a.name);
        gotoxy(20, 11);
        printf("Email: %s\n", a.email);
        findStudent = true;
      }
    }
    if (!findStudent) {
      gotoxy(20, 7);
      printf(RED"\aNo Record Found.......\n"RESET);
    }
    gotoxy(20, 12);
    printf("Try another search? (Y/N)");
    if (getch() == 'y')
      search();
    else
      mainmenu();
    break;
  }
  case '2': {
    char s[50];
    int d = 0;
    system("cls");
    gotoxy(20, 4);
    printf("*********************Search by Name*********************\n");
    gotoxy(20, 5);
    printf("Enter the Student Name: ");
    scanf("%s", s);
    strToLower(s);
    while (fread( & a, sizeof(a), 1, fp) == 1) {
      if ((strcmp(a.name,s)== 0)) {
        gotoxy(20, 7);
        printSlowly("Searching............",80); 
        gotoxy(20, 7);
        printf(GREEN"The student is available\n"RESET);
        gotoxy(20, 9);
        printf("ID: %d\n", a.id);
        gotoxy(20, 10);
        printf("Name: %s\n", a.name);
        gotoxy(20, 11);
        printf("Email: %s\n", a.email);
        d++;
      }
    }
    if (d == 0) {
      gotoxy(22, 9);
      printf(RED"\aNo Record Found\n"RESET);
    }
    gotoxy(20, 17);
    printf("Try another search? (Y/N)");
    if (getch() == 'y')
      search();
    else
      mainmenu();
    break;
  }
  default:
    printf(RED"\aInvalid choice\n"RESET);
    fclose(fp);
    mainmenu();
  }
  fclose(fp);
  }else {
    system("cls");
    gotoxy(10,10);
    printSlowly(RED"NO STUDENT IN THE RECORD YET !!!"RESET,50);
    gotoxy(10,11);
    printf("Press any key to continue..........");
    // Sleep(2000);//creating a delay on purpose to show the user that button had beeen pressed animation
    if (getch())
     mainmenu();
    Sleep(3000); //delay 3 sec to show the message 
    system("cls");
    returnfunc();
  }
}




void returnfunc(void) {
  {
    gotoxy(3,29);
    printf("Press ENTER to return to main menu");
  }
  a:
    if (getch() == 13) //allow only use of enter
      mainmenu();
    else
      goto a;
}

bool find = false;

void delete_record() {
if(a.studentNumber!=0)
  {system("cls");
  int d;
  bool another = true;

  fp = fopen("another.dat", "rb+");
  if (fp == NULL) {
    system("cls");
    gotoxy(10, 10);
    fprintf(stderr, RED"THERE's NO RECORD YET!!\n"RESET);
    //also new
    return;
  

  }

  while (another) {
    system("cls");
    gotoxy(10, 5);
    printf("Enter the student id to delete: ");
    scanf("%d", & d);

    rewind(fp);
    find = false;

    while (fread( & a, sizeof(a), 1, fp) == 1) {
      if (a.id == d) {
        find = true;
        gotoxy(10, 7);
        printf(GREEN"This student is listed in the record\n"RESET);
        gotoxy(10, 9);
        printf("Student name: %s\n", a.name);
        gotoxy(10, 10);
        printf("Department: %s\n", a.dep);
        break;
      }
    }

    if (!find) {
        gotoxy(10,6);
      fprintf(stderr,RED"No student found with this ID!\n"RESET);
      fflush(stdin); //added to clear if there's any input buffers 
      gotoxy(10,10);
      printSlowly("Enter any key to continue.............",30);
      getch();
     
      mainmenu();  

      break;
      
    }
    gotoxy(10,12);
    printf("Do you want to delete it? (Y/N): ");
    if (getch() == 'y') {
      
      ft = fopen("test.dat", "wb+");
      rewind(fp);
      while (fread( & a, sizeof(a), 1, fp) == 1) {
        if (a.id != d) {
          fwrite( & a, sizeof(a), 1, ft);
        }
      }
      fclose(ft);
      fclose(fp);
      remove("another.dat");
      rename("test.dat", "another.dat");
      fp = fopen("another.dat", "rb+");
      if (find) {
        a.studentNumber--;
        gotoxy(10,14);
        printf(GREEN"The student information has been deleted successfully\n"RESET);
        gotoxy(10,15);
        printf("Delete another record? (Y/N):");
      }
    } else {
      fclose(fp);
      mainmenu(); 
      break;
    }

    fflush(stdin); //this clears the input buffer from the heap
    another = (getch() == 'y');
  }

  fclose(fp);
  
  mainmenu(); 
}else{
  
    system("cls");
    gotoxy(10,10);
    printSlowly(RED"NO STUDENT IN THE RECORD YET !!!"RESET,50);
    gotoxy(10,11);
    printf("Press any key to continue..........");
    // Sleep(2000);//creating a delay on purpose to show the user that button had beeen pressed animation
    if (getch())
     mainmenu();
    Sleep(3000); //delay 3 sec to show the message 
    system("cls");
    returnfunc();

}

}




void close(void) {
  system("cls");
  gotoxy(20, 4);
  printf("\n");
  printf("\n");
  printf(GREEN "Program closing in 3 seconds..........."RESET);
  // printSlowly(GREEN"Program closed successfully............."RESET,50);
  //create a delay of this line and exit too
  Sleep(3000);
 
  printf("\n");
  printf("\n");
  printf("\n");
  exit(0);
}
