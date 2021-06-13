#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void swap( int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void CocktailSort(int a[], int n)
{
    int swapped = 1;
    int start = 0;
    int end = n - 1;
	int begin_ptr = -1, end_ptr = 2*n-1;

	
    while (swapped)
    {
        swapped = 0;
 
        for (int i = start; i < end; ++i)
        {
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                swapped = 1;
            }
        }
 
        if (!swapped)
            break;
		else{
			end_ptr-=2;
			// char* ans = (char*)malloc((2*n)*sizeof(char));
			char ans[100];
			strcpy(ans, "");
			for(int j=0;j<2*n-1;j++){
				if((j%2)==1){
					if(j==begin_ptr){
						strcat(ans, "\\");
						// ans[j] = '\\';
					}else if(j==end_ptr){
						strcat(ans, "/");

						// ans[j] = '/';
					}else{
						strcat(ans, " ");
						// ans[j] = ' ';
					}
				}else{
					char str[80];

   					sprintf(str, "%d", a[j>>1]);
					strcat(ans, str);
					// ans[j] = a[j>>1] + '0';;
				}
			}
			printf("%s\n", ans);
			// printf("end: %d\n", end_ptr);
		}

        swapped = 0;
 
        --end;
 
        for (int i = end - 1; i >= start; --i)
        {
            if (a[i] > a[i + 1]) {
                swap(&a[i], &a[i + 1]);
                swapped = 1;
            }
        }
        ++start;

		if (!swapped)
            break;
		else{
			begin_ptr+=2;
			char ans[100];
			strcpy(ans, "");
			for(int j=0;j<2*n-1;j++){
				if((j%2)==1){
					if(j==begin_ptr){
						strcat(ans, "\\");
						// ans[j] = '\\';
					}else if(j==end_ptr){
						strcat(ans, "/");

						// ans[j] = '/';
					}else{
						strcat(ans, " ");
						// ans[j] = ' ';
					}
				}else{
					char str[80];

   					sprintf(str, "%d", a[j>>1]);
					strcat(ans, str);
					// ans[j] = a[j>>1] + '0';;
				}
			}
			printf("%s\n", ans);
		}
    }

	char ans[100];
	strcpy(ans, "");
	for(int j=0;j<2*n-1;j++){
		if((j%2)==1){
			if(j==begin_ptr){
				strcat(ans, "\\");
				// ans[j] = '\\';
			}else if(j==end_ptr){
				strcat(ans, "/");

				// ans[j] = '/';
			}else{
				strcat(ans, " ");
				// ans[j] = ' ';
			}
		}else{
			char str[80];

			sprintf(str, "%d", a[j>>1]);
			strcat(ans, str);
			// ans[j] = a[j>>1] + '0';;
		}
	}
	printf("Answer = %s\n", ans);
}
int main(){
    int a;
    // scanf("This is the value %d", &a);
	char* RUN = NULL;
	char * line = NULL;
	size_t len = 0;
	getline(&RUN, &len, stdin);
	for(int r=0;r<atoi(RUN);r++){
		getline(&line, &len, stdin);
		int* arr = (int*)malloc(20*sizeof(int));
		memset(arr, 0, 20*sizeof(int));
		int len =0 ;


		char *delim = " ";
		char *pstr = NULL;
		pstr = strtok(line, delim);
		arr[len] = strtol(line, NULL, 10);
		len++;
		while ((pstr = strtok(NULL, delim)) != NULL)
		{
			arr[len] = strtol(pstr, NULL, 10);
			len++;
		}

		// for(int i=0;i<len;i++)
		// 	printf("%d ", arr[i]);
		CocktailSort(arr, len);
		free(arr);
	}

	// char test[100];
	// strcpy(test, "");
	// strcat(test,"asdf");
	// printf("%s", test);
}
