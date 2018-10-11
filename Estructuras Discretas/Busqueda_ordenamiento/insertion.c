    /* Insertion sort ascending order */
     
    #include <stdio.h>
    #include<stdlib.h>
     
    void main()
    {
      int *array,n, i, j, temp;
     
      printf("Ingrese numero de elementos:\n");
      scanf("%d", &n);
      printf("Ingresa elementos:\n");
      array=(int*)malloc(n*sizeof(int));
      for (i=0;i<n;i++) scanf("%d", &array[i]);

      for (i=0;i<n;i++){
        j = i;
        while ( j > 0 && array[j-1] > array[j]) {
          temp       = array[j];
          array[j]   = array[j-1];
          array[j-1] = temp;
          j--;
        }
      }
     
      printf("lista ordenada:\n");
     
      for (i=0;i<n;i++){
        printf("%d ", array[i]);
      }
       printf("\n");
      }
