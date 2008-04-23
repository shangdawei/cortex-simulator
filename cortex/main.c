#include "fetch.h"
#include "decode.h"

int main(){
     int i=0;
	while(1){
         unsigned int instruction = fetch(i++);
           if(instruction!=0){
               decode(instruction);
               printf("------------------------------------------------------------- \n");
          }else{
              break;
          }
      }
  }

