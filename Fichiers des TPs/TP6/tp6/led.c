#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


int main()
{
	int sys_led, user_led;

	sys_led = open("/sys/class/leds/sys_led/brightness", O_RDWR);
	user_led = open("/sys/class/leds/user_led/brightness", O_RDWR);

	if(sys_led == -1 || user_led == -1)
	{
		perror("Erreur d'ouverture de l'un des fichiers");
		return 0;
	}

	while(1)
	{
		if(write(user_led, "0", 1) == -1)
			perror("Erreur d'ecriture");

		if(write(sys_led, "1", 1) == -1)
			perror("Erreur d'ecriture");

		sleep(1);

		if(write(sys_led, "0", 1) == -1)
			perror("Erreur d'ecriture");

		if(write(user_led, "1", 1) == -1)
			perror("Erreur d'ecriture");

		sleep(1);
	}

	close(sys_led);
	close(user_led);

	return 0;
}
