//202051178
// Hetvi Soni

#include <stdio.h>
#include <string.h>
#include <stdio.h>

int inverse(int a, int m) 
{ 
    int m0 = m; 
    int y = 0, x = 1; 
  
    if (m == 1) 
      return 0; 
  
    while (a > 1) 
    { 
        int q = a / m; 
        int t = m; 
        // Euclid's algo 
        m = a % m, a = t; 
        t = y; 

        y = x - q * y; 
        x = t; 
    } 
    if (x < 0) 
       x += m0; 
  
    return x; 
} 

int main(int argc, char const *argv[])
{
    /* code */
    //declaring variables
    char plaintext[10];
    char delta[15];
    char K1[15];
    char C1[15];
    char C2[15];
    char C3[15];
    char E1[15];
    char E2[15];
    char E3[15];
    char matrix[5][5];
    char arr_of_matrix[25];
    char alphabets[] = "abcdefghijklmnopqrstuvwxyz";
    int k3;
    char c='*';

    printf("Enter the plaintext:\n");
    scanf("%s",&plaintext);
    printf("Enter the key k1: \n");
    scanf("%s",&K1);
    printf("\n Enter the key k3 for shift cipher\n");
    scanf("%d",&k3);
    printf("================================\n");
    printf("Your plaintext is %s\n",plaintext);
    printf("Your key is %s\n",K1);
    printf("================================\n");

    //ENCRYPTION
    //Modifying key
    for(int i=0;K1[i];i++)
    {
    	if(!(K1[i]==c))
    	{
    		for(int j=i+1;K1[j];j++)
            {
            	if(K1[i]==K1[j])
            	   K1[j]=c;
        	
		    }
    		
		} 	
    }
    int k=0;
    for(int i=0;K1[i];i++)
    {
     	K1[i]=K1[i+k];
        if(K1[i]==c)
     	{
		  k++;
		  i--;
	    }
    }
    //converting j to i
    for(int i=0;i<15;i++)
    {
        if(K1[i]=='j')
            K1[i]='i';
    }
    printf("After removing duplicates from key : %s\n",K1);

    //Modifying plaintext
    //inserting x between repeated letters
    int tplain =1, tdelta=1;
    delta[0]=plaintext[0];
    int deltalen= strlen(plaintext);
    while(plaintext[tplain]!='\0')
    {
        if(plaintext[tplain]==delta[tdelta-1])
        {
            delta[tdelta]='x';
            deltalen++;
            tdelta++; 
        }
        else{
            delta[tdelta] = plaintext[tplain];
            tdelta++;
            tplain++;
        }
    }
    for(int j=deltalen;delta[j]!='\0';j++)
    {
        delta[j]='\0';
    }

    //inserting x if length of plaintext is odd

    if(strlen(delta)%2!=0)
    {
        delta[strlen(delta)]='x';
    }

    // converting j to i
    for(int i=0;i<15;i++)
    {
        if(delta[i]=='j')
            delta[i]='i';
    }
    printf("Delta is %s\n",delta);
    
    printf("============================\n");
    //creating array for the matrix
    int count;
    for (int i = 0; K1[i] != '\0'; i++) 
    {
        arr_of_matrix[i]=K1[i];
        int a = arr_of_matrix[i] -'a';
        alphabets[a]='*';
        count=i;
    }
    count++;
 
    for(int j=count;j<25;j++)
    {
        for(int i=0;i<26;i++)
        {
            if(alphabets[i]!='*' && i!=9)
            {
                arr_of_matrix[j]=alphabets[i];
                alphabets[i]='*';
                break;
            }
        }
    }
    printf("\n Matrix::\n");
    int temp=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            matrix[i][j]=arr_of_matrix[temp];
            printf("%c ",matrix[i][j]);
            temp++;
        }
        printf("\n");
    }

    int tc1=0;
    while(tc1<strlen(delta))
    {
        char b1 = delta[tc1];
        char b2 = delta[tc1+1];
        int row_b1,col_b1,row_b2,col_b2;
        //finding row and col of b1 and b2
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
            {
                if(matrix[i][j]==b1)
                {
                    row_b1 = i;
                    col_b1 = j;
                }
                if(matrix[i][j]==b2)
                {
                    row_b2 = i;
                    col_b2 = j;
                }
            }
        }
        
        //if both characters are from same row
        if(row_b1==row_b2)
        {
            C1[tc1] = matrix[row_b1][(col_b1+1)%5];
            tc1++;
            C1[tc1] = matrix[row_b2][(col_b2+1)%5];
            tc1++;
        }

        //if both characters are from same col
        else if(col_b1==col_b2)
        {
            C1[tc1] = matrix[(row_b1+1)%5][col_b1];
            tc1++;
            C1[tc1] = matrix[(row_b2+1)%5][col_b2];
            tc1++;
        }
        else{
            C1[tc1] = matrix[row_b1][col_b2];
            tc1++;
            C1[tc1] = matrix[row_b2][col_b1];
            tc1++;
        }
    }
    for(int i=strlen(delta);C1[i]!='\0';i++)
    {
        C1[i]='\0';
    }
    printf("============================\n");
    printf("\n Ciphertext C1 is  %s",C1);

    //encrypt c1 using affine cipher
    int a = 11;
    int b = 15;
    int aInverse = inverse(a,26);
    
    for (int i = 0; C1[i] != '\0'; i++) 
    {
        //calculating integer equivalent of character
        int x = C1[i]-'a';
        //encrypting each letter
        int cipherCur = (a*x+b)%26;
        C2[i] = cipherCur+'a';
    }
    for(int i=strlen(delta);C2[i]!='\0';i++)
    {
        C2[i]='\0';
    }
    printf("\n Ciphertext C2 is %s",C2);
    
    for (int i = 0; C2[i]!='\0'; i++) 
    {
        //calculating integer equivalent of character
        int cur = C2[i]-'a';
        //encrypting each letter
        int cipherCur = (cur+k3)%26;
        C3[i] = cipherCur+'a';
    }
    for(int i=strlen(delta);C3[i]!='\0';i++)
    {
        C3[i]='\0';
    }
    printf("\n Ciphertext C3 is %s", C3);

    //DECRYPTION
    for (int i = 0; C3[i] != '\0'; i++) 
    {
        int cur = C3[i]-'a';
        int decryptCur = (cur+26-k3)%26;
        E3[i] = decryptCur+'a';
    }
    for(int i=strlen(delta);E3[i]!='\0';i++)
    {
        E3[i]='\0';
    }
    printf("\n Decryption of c3:%s \n",E3);

    //decryption of E3
    for (int i = 0; E3[i] != '\0'; i++) 
    {
        int x = E3[i]-'a';
        int decryptCur = ((x+26-b)*aInverse)%26;
        E2[i] = decryptCur+'a';
        // printf("%c",K2[i]);
    }
    for(int i=strlen(delta); E2[i]!='\0';i++)
    {
        E2[i]='\0';
    }
    printf("Decryption of E3 is %s \n",E2);

    //Decryption of E2
    int te2=0;
    while(te2<strlen(delta))
    {
        char b1 = E2[te2];
        char b2 = E2[te2+1];
        int row_b1,col_b1,row_b2,col_b2;
        //finding row and col of b1 and b2
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<5;j++)
            {
                if(matrix[i][j]==b1)
                {
                    row_b1 = i;
                    col_b1 = j;
                }
                if(matrix[i][j]==b2)
                {
                    row_b2 = i;
                    col_b2 = j;
                }
            }
        }
        
        //if both characters are from same row
        if(row_b1==row_b2)
        {
            E1[te2] = matrix[row_b1][(col_b1+4)%5];
            te2++;
            E1[te2] = matrix[row_b2][(col_b2+4)%5];
            te2++;
        }

        //if both characters are from same col
        else if(col_b1==col_b2)
        {
            E1[te2] = matrix[(row_b1+4)%5][col_b1];
            te2++;
            E1[te2] = matrix[(row_b2+4)%5][col_b2];
            te2++;
        }
        else{
            E1[te2] = matrix[row_b1][col_b2];
            te2++;
            E1[te2] = matrix[row_b2][col_b1];
            te2++;
        }

    }
    for(int i=strlen(delta);E1[i]!='\0';i++)
    {
        E1[i]='\0';
    }
    printf("============================\n");
    printf("After final decryption: %s ",E1);
    return 0;
}
