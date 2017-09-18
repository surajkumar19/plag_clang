
/*proto type declaration*/
static void scan_dir(const char *dir);
void bagofwords();
void lcs();
void fingerprinting();


/*file names from a directory are stored in this file array and number of files is stored in fcount*/
char file[10][100]={'\0'};
int fcount=0;


/*plagarism percentage storage*/
float bagofwordsplag[100]={'\0'};
float lcsplag[100]={'\0'};
float fingerplag[100]={'\0'};
int mcount=0;

/*words and string storing for 2 files*/
char strings1[10][10]={'\0'};
char strings2[10][10]={'\0'};
char strings1_1[50]={'\0'};
char strings2_2[50]={'\0'};
