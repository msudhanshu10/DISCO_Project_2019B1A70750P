#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

void printMatrix(int N,int **matrix)
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}

void printWebsites(int N, char **matrix)
{
    for (int loop = 0; loop < N; loop++)
    {
        printf("[%2d]: %s\n", loop, matrix[loop]);
    }
}

void displayWebsites(int i, char **matrix)
{
    printf(matrix[i]);
}

int writeToCsv(int N, int **mat, char **labels,char *input)
{
    FILE *fp;
    fp = fopen(input, "w");
    fprintf(fp,"%s", ",");
    for(int i=0;i<N;i++)
    {
        if(i==(N-1))
        {
            fprintf(fp,"%s", labels[i]);
            break;
        }
        fprintf(fp,"%s%s", labels[i], ",");
    }
    fprintf(fp,"%s","\n");
    for(int i=0;i<N;i++)
    {
        fprintf(fp,"%s%s", labels[i], ",");
        for(int j=0;j<N;j++)
        {
            if(j==(N-1))
            {
                fprintf(fp,"%d", mat[i][j]);
                break;
            }
            fprintf(fp,"%d%s", mat[i][j], ",");
        }
        if(i==N-1)
        {
            break;
        }
        fprintf(fp,"%s","\n");
    }
    fclose(fp);
    return 1;

}


// Main Menu 1
bool isReflexive(int N,int **mat)
{
    for(int i=0; i< N; i++)
    {
        if(mat[i][i] != 1)
            return false;
    }
    return true;
}

// Main Menu 2
bool isSymmetric(int N,int **mat)
{
    bool flag=true;
    for(int i=0; i< N; i++)
    {
        for(int j=0; j< N; j++)
        {
            if(mat[i][j]!= mat[j][i])
            {
                flag=false;
                break;
            }
        }
    }
    return flag;
}

// Main Menu 3
bool isTransitive(int N,int **mat)
{
    int mat2[N][N];
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            mat2[i][j]=0;
        }
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++) 
        {
            for (int k = 0; k < N; k++) 
            {
                mat2[i][j] += mat[i][k] * mat[k][j];
            }
        }
    }

   for(int m=0; m< N; m++)
   {
       for(int n=0; n<N; n++)
       {
            if(mat2[m][n]!=0 && mat[m][n]==0)
                return false;
       }
   }
    return true;
}

// Main Menu 4
bool isLoop(int N, int **mat)
{
    for(int i=0; i< N; i++)
    {
        if(mat[i][i] == 1)
            return true;
    }
    return false;
}
// Main Menu 5
bool isAnySymmetricPair(int N, int **mat)
{ 
    bool flag=false;
        for(int i=0; i< N; i++)
        {
            for(int j=0; j< N; j++)
            {
                if(mat[i][j] == 1 && mat[j][i]==1)
                {
                    flag=true;
                    break;
                }
            }
        }   
    
    return flag;
}

// Main Menu 6
bool isAnySymmetricPair2(int N, int **mat)
{
    bool flag=false;
    for(int i=0; i< N; i++)
    {
        for(int j=0; j< N; j++)
        {
            if(i!=j && mat[i][j] == 1 && mat[j][i]==1)
            {
                flag=true;
                break;
            }
        }
    }
    return flag;
}
// calculating anti-symmetric
bool isAntiSymmetric(int N,int **mat)
{
    bool flag=true;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            if(i!=j && mat[i][j]==1 && mat[j][i]==1)
                flag=false;
        }
    }
    return flag;
}
// Main Menu 8
bool isPoset(int N,int **mat)
{
    if(isReflexive(N,mat) && isAntiSymmetric(N,mat) && isTransitive(N,mat))
    {
        return true;
    }
    return false;
}

//Main Menu 7
bool isEquivalence(int N, int **mat)
{
    if (isReflexive(N,mat) && isSymmetric(N,mat) && isTransitive(N,mat))
    {
        return true;
    }
    return false;
}

void calculateEquivalentClasses(int n, int **mat)
{
    int arr1[n];
    int arr2[n][n];
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            arr2[i][j]=0;
        }
    }

    for(int i=0;i<n;i++){
        arr1[i]=1;
    }
    for(int i=0;i<n;i++){
        if(arr1[i]==0) continue;
        for(int j=i;j<n;j++){
            if(mat[i][j]==1){
                arr2[i][j]=1;
                arr1[j]=0;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(arr2[i][i]==0) continue;
        else{
            printf("{ ");
            for(int j=i;j<n;j++){
                if(arr2[i][j]==1){
                    printf("%d ,",j);
                }
            }
            printf("}\n");
        }
    }
}

void reflexiveClosure(int N,int **mat, char **labels)
{
    int **arr;

    arr = malloc(sizeof(int*) * N);
    for(int i=0;i<N;i++)
    {
        arr[i] = malloc(sizeof(int*) * N);
        for(int j=0;j<N;j++)
        {
            arr[i][j]=mat[i][j];
        }
    }

    for (int i=0; i<N; i++)
    {
        arr[i][i]= 1;
    }

    writeToCsv(N,arr,labels,"ReflexClos.csv");
}

void symmetricClosure(int N,int **mat, char **labels)
{
    int **matT;

    matT = malloc(sizeof(int*) * N);
    for(int i=0;i<N;i++)
    {
        matT[i] = malloc(sizeof(int*) * N);
        for(int j=0;j<N;j++)
        {
            matT[i][j]=mat[j][i];
        }
    }

    int **sym;
    sym = malloc(sizeof(int*) * N);
    for(int m=0; m< N; m++)
    {
        sym[m] = malloc(sizeof(int*) * N);
        for(int n=0; n< N; n++)
        {
            sym[m][n]= matT[m][n]+mat[m][n];
            if(sym[m][n]>0)
                sym[m][n]=1;
        }
    }
    
    writeToCsv(N,sym,labels,"SymClos.csv");
    
}
void transitiveClosure(int N, int **mat, char **labels)
{ 
    int **matTransClos;

    matTransClos = malloc(sizeof(int*) * N);
    for(int i=0;i<N;i++)
    {
        matTransClos[i] = malloc(sizeof(int*) * N);
        for(int j=0;j<N;j++)
        {
            matTransClos[i][j]=mat[i][j];
        }
    }

    for (int k = 0; k < N; k++)
    {
         for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                matTransClos[i][j]= matTransClos[i][j] || (matTransClos[i][k]&&matTransClos[k][j]);
            }
        }
    }
    writeToCsv(N,matTransClos,labels,"TransClos.csv");
}

// equivalence closure
void equivalenceClosure(int N, int **mat, char **labels)
{
    int arr[N][N];
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            arr[i][j]=mat[i][j];
        }
    }

    for (int i=0; i<N; i++)
    {
        arr[i][i]= 1;
    }

    int matT[N][N];
    for(int i=0; i< N; i++)
    {
        for(int j=0; j< N; j++)
        {
            matT[j][i]=arr[i][j];
        }
    }
    int sym[N][N];
    for(int m=0; m< N; m++)
    {
        for(int n=0; n< N; n++)
        {
            sym[m][n]= matT[m][n]+arr[m][n];
            if(sym[m][n]>0)
                sym[m][n]=1;
        }
    }

    int i,j,k; 
    int matTransClos[N][N];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++){
            matTransClos[i][j] = sym[i][j];
        }
    }
    for (k = 0; k < N; k++)
    {
        
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                matTransClos[i][j]= matTransClos[i][j] || (matTransClos[i][k] && matTransClos[k][j]);
            }
        }
    }

    int **transClosure;
    transClosure=malloc(sizeof(int *)*N);
    for(int i=0; i<N; i++)
    {
        transClosure[i]=malloc(sizeof(int *)*N);
        for(int j=0; j<N; j++)
        {
            transClosure[i][j]=matTransClos[i][j];
        }
    }

    writeToCsv(N,transClosure,labels,"EquiClos.csv");
}

// Menu 4-1
void menu4_1(int N, int **mat, char **labels)
{
    int **arr;

    arr = malloc(sizeof(int*) * N);
    for(int i=0;i<N;i++)
    {
        arr[i] = malloc(sizeof(int*) * N);
        for(int j=0;j<N;j++)
        {
            arr[i][j]=mat[i][j];
        }
    }

    // remove reflexive
    for(int i=0;i<N;i++)
    {
        if(arr[i][i]==1)
            arr[i][i]=0;
    }

    // remove transitivity
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(arr[i][j]==1)
            {
                for(int k=0;k<N;k++)
                {
                    if(arr[j][k]==1 && arr[i][k]==1)
                    {
                        arr[i][k]=0;
                    }
                }
            }
        }
    }

    writeToCsv(N,arr,labels,"HasseOutput.csv");
}

//Menu 4-2
void menu4_2(int N, int **mat, char **labels)
{
    bool flag= true;
    bool flag2=false;
    for(int j=0; j<N; j++)
    {
        flag= true;
        for(int i=0; i<N; i++)
        {
            if(mat[i][j]!=1)
            {
                flag= false; 
                break;   
            }
            
        }
        if(flag== true)
        {
            displayWebsites(j,labels);
            printf("\t");
            flag2=true;
        }
    }
    if(flag2==false)
        printf("No such website exists!\n");
}

// Menu 4-3
void menu4_3(int N, int **mat, char **labels)
{
    bool flag= true;
    bool flag2= false;
    for(int j=0; j<N; j++)
    {
        flag= true;
        for(int i=0; i<N; i++)
        {
            if(mat[j][i]!=1)
            {
                flag= false; 
                break;   
            }          
        }
        if(flag== true)
        {
            displayWebsites(j,labels);
            printf("\t");
            flag2=true;
        }
    }
    if(flag2==false)
        printf("No such website exists!\n");
}

// Menu 4-4
void menu4_4(int N,int **mat, char **labels)
{
    bool flag= true;
    bool flag2=false;
    for(int i=0; i<N; i++)
    {
        flag= true;
        for(int j=0; j<N; j++)
        {
            if(i==j && mat[i][j]!=1)
            {
                flag= false;
                break;
            }    
            else if(i!=j && mat[i][j]==1)
            {
                flag= false;
                break;
            }
        }
        if(flag== true)
        {
            displayWebsites(i,labels);
            printf("\t");
            flag2=true;
        }
    }
    if(flag2==false)
        printf("No such website exist!\n"); 
}
// Menu 4-5
void menu4_5(int N, int **mat, char **labels)
{
    bool flag= true;
    bool flag2= false;
    for(int i=0; i<N; i++)
    {
        flag= true;
        for(int j=0; j<N; j++)
        {
            if(i==j && mat[j][i]!=1)
            {
                flag= false;
                break;
            }    
            else if(i!=j && mat[j][i]==1)
            {
                flag= false;
                break;
            }
        }
        if(flag== true)
        {
            displayWebsites(i,labels);
            printf("\t");
            flag2=true;
        }
    }
    if(flag2==false)
        printf("No such website exists!\n");
}
// Menu 4-6
void menu4_6(int N, int **mat, char **labels)
{
    printWebsites(N,labels);

    int ninput;
    int index;
    printf("Enter the number of websites you want to enter: ");
    scanf("%d", &ninput);
    int arr[ninput];
    printf("Enter the indexes of the website.");
    for(int j=0; j<ninput; j++)
    {
        scanf("%d", &index);
        arr[j]= index;
    }


    bool flag= true;
    bool flag2=false;
    for(int i=0; i<N; i++) // for column
    {
        flag=true;
        for(int j=0; j<ninput; j++) // for arr
        {
            if(mat[arr[j]][i]==0)
                flag=false;
        }
        if(flag==true)
        {
            displayWebsites(i,labels);
            printf("\t");
            flag2=true;
        }
    }
    if(flag2==false)
    {
        printf("No such website exists!\n");
    }
}

// Menu 4-7
void menu4_7(int N, int **mat, char **labels)
{
    printWebsites(N,labels);
    int ninput;
    int index;
    printf("Enter the number of websites you want to enter: ");
    scanf("%d", &ninput);
    int arr[ninput];
    printf("Enter the indexes of the website.");
    for(int j=0; j<ninput; j++)
    {
        scanf("%d", &index);
        arr[j]= index;
    }
    bool flag= true;
    bool flag2=false;
    for(int i=0; i<N; i++) // for row
    {
        flag=true;
        for(int j=0; j<ninput; j++) // for arr
        {
            if(mat[i][arr[j]]==0)
                flag=false;
        }
        if(flag==true)
        {
            displayWebsites(i,labels);
            printf("\t");
            flag2=true;
        }
    }
    if(flag2==false)
    {
        printf("No such website exists!\n");
    }
}

bool isLattice2(int N, int **mat, char **labels) // checking if one complete row and one column column is zero
{
    int flag1;
    int checkRow=0;
    for(int i=0;i<N;i++)
    {
        flag1=1;
        for(int j=0;j<N;j++){
            if(mat[i][j]!=0){
                flag1=0;
                break;
            }
        }
        if(flag1==0)
            continue;
        else
        {
            checkRow++;
        }
    }
    if(checkRow==1)
    {
        int checkColumn=0;
        for(int i=0;i<N;i++){
            flag1=1;
            for(int j=0;j<N;j++){
                if(mat[j][i]!=0){
                    flag1=0;
                    break;
                }
            }
            if(flag1==0) 
                continue;
            else
            {
                checkColumn++;
            }
        }
        if(checkColumn==1) 
            return true;
    }
    return false;
}

bool isLattice(int N, int **mat, char **labels)
{
    int flag=0;
    if(isLattice2(N, mat, labels))
    {
        for(int i=0; i<N; i++)
        {
            for(int j=i+1; j<N; j++)
            {
                flag=0;
                for(int k=0; k<N; k++)
                {
                    if(mat[i][k]==1 && mat[j][k]==1)
                    {
                        flag++;
                    }
                }
                if(flag>1)
                {
                    return false;
                }
            }
        }
    }
    else
        return false;
    return true;
}

// menu 4-8
void menu4_8(int N, int **mat, char **labels)
{
    int **arr;

    arr = malloc(sizeof(int*) * N);
    for(int i=0;i<N;i++)
    {
        arr[i] = malloc(sizeof(int*) * N);
        for(int j=0;j<N;j++)
        {
            arr[i][j]=mat[i][j];
        }
    }

    // remove reflexive
    for(int i=0;i<N;i++)
    {
        if(arr[i][i]==1)
            arr[i][i]=0;
    }

    // remove transitivity
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(arr[i][j]==1)
            {
                for(int k=0;k<N;k++)
                {
                    if(arr[j][k]==1 && arr[i][k]==1)
                    {
                        arr[i][k]=0;
                    }
                }
            }
        }
    }

    int x= isLattice(N,arr,labels);
    if(x==0)
        printf("No\n");
    else if(x==1)
    {
        printf("Yes\n");
        //Menu5(N,arr,labels);
    }
}

void Menu_2(int i,int N,int **mat, char **labels)
{
    printf("-----------------------------------------------------------------------------------------------\n");
    int input;
    printf("Do you want to visualize how the network will look if we add minimum links to satisfy the property? Enter 1 for Yes 0 for No.   ");
    scanf("%d",&input);
    if(input==1 && i==1)
    {
        reflexiveClosure(N,mat, labels);
    }
    if(input==1 && i==2)
    {
        symmetricClosure(N,mat, labels);
    }
    if(input==1 && i==3)
    {
        transitiveClosure(N,mat, labels);
    }
    if(input==1 && i==4)
    {
        equivalenceClosure(N,mat, labels);
    }
}

void Menu_3(int N,int **mat)
{
    printf("-----------------------------------------------------------------------------------------------\n");
    printf("Do you want to know the nodes in each piece? Enter 1 for Yes, 0 for No\n");
    int input;
    scanf("%d",&input);
    if(input==1)
    {
        calculateEquivalentClasses(N,mat);
    }
}

void Menu_4(int N,int **mat,char **labels)
{
    int n;
    int x;
    Menu_4_goto:

    printf("-----------------------------------------------------------------------------------------------\n");
    printf("MENU 4\n");
    printf("1. Display the Hasse diagram.\n");
    printf("2. Display the website whose link is available in every website.\n");
    printf("3. Display the website which has links of every website.\n");
    printf("4. Display the website that do not have link to any other website except itself.\n");
    printf("5. Display the websites which can't be reached from any other website except itself.\n");
    printf("6. Given some websites, display the websites which are reachable from all of them.\n");
    printf("7. Given some websites, display the websites from which you can reach all those websites.\n");
    printf("8. Is this relation an example of lattice?\n" );
    printf("9. Return to Main Menu\n");

    printf("Enter an integer corresponding to the option you want to select:");

    scanf("%d",&n);
    switch(n)
    {
        case 1:
            menu4_1(N,mat,labels);
            break;
        case 2:
            menu4_2(N,mat,labels);
            break;
        case 3:
            menu4_3(N,mat,labels);
            break;
        case 4:
            menu4_4(N,mat,labels);
            break;
        case 5:
            menu4_5(N,mat,labels);
            break;
        case 6:
            menu4_6(N,mat,labels);
            break;  
        case 7:
            menu4_7(N,mat,labels);
            break; 
        case 8: 
            menu4_8(N,mat,labels);
            break;
        case 9:
            break;
        default:
            printf("ERROR: Enter an integer from 1 to 9:");
            goto Menu_4_goto;
    }
}

void Main_Menu(int N, int **mat,char **labels)
{
    int n;
    char ch;
    Main_Menu_goto:
    
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("MAIN MENU\n\n");
    printf("1. Does Every website has a link to itself?\n");
    printf("2. Is it always possible to return back to previous website from current website itself?\n");
    printf("3. Does every website has all the links to the websites which are reachable from it?\n");
    printf("4. Does there exist any website that contains a link to itself?\n");
    printf("5. Is it impossible to return to the previous website from the current website in one step?\n");
    printf("6. Is it impossible to return to the previous website from the current website in one step?\n");
    printf("   (excluding the cases where the current and previous website is same)\n");
    printf("7. Is it possible to divide the network into multiple pieces such that every website in a piece is reachable from every other website from that piece?\n");
    printf("8. Is this relation an example of poset?\n" );
    printf("9. Exit\n");
    printf("Enter an integer corresponding to the option you want to select:");

    //Main_Menu_goto:

    scanf("%d",&n);

    int x=0;
    switch(n)
    {
    case 1:
        x = isReflexive(N, mat);
        if(x==1)
            printf("Yes\n");
        else
        {
            printf("No\n");
            Menu_2(1,N,mat,labels);
        }
        break;
    case 2:
        x = isSymmetric(N, mat);
        if(x==1)
            printf("Yes\n");
        else
        {
            printf("No\n");
            Menu_2(2,N,mat, labels);
        }
        break;
    case 3:
        x = isTransitive(N, mat);
        if(x==1)
            printf("Yes\n");
        else
        {
            printf("No\n");
            Menu_2(3,N,mat, labels);
        }
        break;
    case 4:
        x = isLoop(N, mat);
        if(x==1)
            printf("Yes\n");
        else
        {
            printf("No\n");
        }
        break;
    case 5:
        x = isAnySymmetricPair(N, mat);
        if(x== 1)
        {
            printf("No\n");
        }
        else 
        {
            printf("Yes\n");
        }
        break;
    case 6:
        x = isAnySymmetricPair2(N, mat);
        if(x== 1)
        {
            printf("No\n");
        }
        else 
        {
            printf("Yes\n");
        }
        break;
    case 7:
        x= isEquivalence(N,mat);
        if(x==0)
        {
            printf("No\n");
            Menu_2(4,N,mat, labels);
        }
        else if(x==1)
        {
            printf("Yes\n");
            Menu_3(N,mat);
        }
        break;
    case 8:
        x= isPoset(N,mat);
        if(x==1){
            printf("Yes\n");
            Menu_4(N,mat,labels);
        }
        else{
            printf("No\n");
        }
        break;
    case 9:
        printf("Performing Exit!");
        exit(0);
        break;
    default:
        printf("ERROR: Enter an integer from 1 to 9:");
        goto Main_Menu_goto;
    }
    printf("\nEnter any key to display the Main Menu again.\n");
    ch=getch();
    goto Main_Menu_goto;
}

int main()
{
FILE *fp = fopen("SampleInput.csv", "r");
    int **matrix;
    char **labels;
    char strarr[1024][1024];

    int size;
    char buffer[1024];

    if (fp == NULL)
    {
        printf("The File is null\n");
        return 0;
    }

    int index = 0;

    while ((fgets(buffer, 1024, fp)) != NULL)
    {
        strcpy(strarr[index], buffer);
        index++;
    }

    index--;

    matrix = malloc(index * sizeof(int *));

    for (int i = 0; i < index; i++)
    {
        *(matrix + i) = malloc(sizeof(int) * index);
    }
    labels = malloc(sizeof(char *) * index);

    for (int i = 1; i <= index; i++)
    {
        char *token = strtok(strarr[i], ",");
        *(labels + i - 1) = token;
        token = strtok(NULL, ",");

        int row_no = 0;
        while (token != NULL)
        {
            *(*(matrix + i - 1) + row_no) = atoi(token);
            row_no++;
            token = strtok(NULL, ",");
        }
    }

    int N=index;
    printMatrix(N,matrix);
    printWebsites(N, labels);
    Main_Menu(N,matrix,labels);

}