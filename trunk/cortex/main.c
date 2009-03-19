#include "elf_loader.h"
#include "device/device_motor.h"
#include "device/device_INTcontrol.h"
#include "device/device_leds.h"
#include "vbus-dev/vbus_interface.h"
#include "processor.h"

int main(){
	int i = 0,pcc;
	unsigned int instruction;

	motorDes motor;
	INTctrlDes ictrl;
	ledsDes leds;

	file = fopen("system_n.log", "w");
	load_elf("testelfled.elf");

	vb_load("vbus");
	motorInital(&motor);
	INTctrlInital(&ictrl);
	ledsInital(&leds);

	printf("Press Enter to start");
	getchar();
	printf("Running...");
	
	while(1){
		if( i != -1)
			i++;
		instruction = processorDo();
		motorDo(&motor);
		INTctrlDo(&ictrl);
		ledsDo(&leds);

		//For debug
		if(i == 1000000){
			i = -1;
			fclose(file);
			//return 0;
		}
		if(!(i % 100))
			fprintf(file,"%d\t%d\n",i,instruction);
	}
}