#include <stdio.h>
/**************
M Ravi Kumar 
CS18MTEC
****************/
int main(void) {
  int miles;
  int stops;
  int min_stops=0;
  printf("Enter No of Miles He can surive\n");
  scanf("%d",&miles);
  printf("Enter No of stops\n");
  scanf("%d",&stops);
  int arr[stops];
  int i;
  printf("Enter stops  Distances \n");
  for(i=0;i<stops;i++){
    scanf("%d",&arr[i]);
  }
  int cur = miles;
  for(i=0;i<stops-1;i++){
    cur = cur-arr[i];
    if(arr[i+1] <= cur)
      continue;
    else{
      printf("Stop%d\n",i);
      min_stops++;
      cur = miles;
    }

  }
  printf("No of min stops %d\n",min_stops);


  return 0;
}