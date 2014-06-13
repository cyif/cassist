#include "C_Assist.h"

void removeComment(char *filename)
{
	FILE *f1,*f2;
	int i,j,n;
	int flag=0;
	int flag2=0;
	char buff[200];

	f1 = fopen(filename,"r");
	f2 = fopen("remove.tmp","w");
	while (fgets(&buff[0],199,f1)!=NULL)
	{
		n = strlen(buff);
		flag = 0;
		for (i=0; i<n-1; i++)
		{
			if (buff[i] == '/' && buff[i+1] == '/')
			{
				for (j=0; j<i; j++)
				{
					fprintf(f2,"%c",buff[j]);
				}
				flag = 1;
				fprintf(f2, "%c", '\n');
				break;
			}
			if (buff[i] == '/' && buff[i+1] == '*')
			{
				for (j=0; j<i; j++)
				{
					fprintf(f2, "%c", buff[j]);
				}
				flag2 = 1;
			}
			if (buff[i] == '*' && buff[i+1] == '/')
			{
				for (j=i+2; j<n-1; j++)
				{
					fprintf(f2, "%c", buff[j]);
				}
				flag = 1;
				flag2 = 0;
				fprintf(f2, "%c", '\n');
			}
		}
		//printf("haha\n");
		if (flag == 0 && flag2 == 0)
		{
		//	printf("hehe\n");
			fprintf(f2, "%s", buff);
		}
	}
	fclose(f1);
	fclose(f2);
	return;
}

/*int main()
{
	removeComment("test.c");
	return 0;
}*/
