#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>

/*static struct gpio_keys_button gpio_key_buttons[] = {
 {
 .code = KEY_F1,
 .gpio = GPIO_TO_PIN(1, 30),
 .active_low = true,
 .desc = "menu",
 .type = EV_KEY,
// .wakeup = 1,
 },
 {
 .code = KEY_ESC,
 .gpio = GPIO_TO_PIN(1, 31),
 .active_low = true,
 .desc = "back",
 .type = EV_KEY,
// .wakeup = 1,
 },
 {
 .code = KEY_HOME,
 .gpio = GPIO_TO_PIN(0, 22),
 .active_low = true,
 .desc = "home",
 .type = EV_KEY,
// .wakeup = 1,
 }*/

/*
struct input_event {
	struct timeval time;
	__u16 type;
	__u16 code;
	__s32 value;
};*/

int main()
{

	struct input_event event_buttons;
	int sys_led, user_led, buttons;

	buttons = open("/dev/input/event1", O_RDONLY); 

	if(buttons == -1)
	{
		perror("Erreur d'ouverture de l'un des fichiers");
		return 0;
	}

	sys_led = open("/sys/class/leds/sys_led/brightness", O_RDWR);
	user_led = open("/sys/class/leds/user_led/brightness", O_RDWR);

	if(sys_led == -1 || user_led == -1)
	{
		perror("Erreur d'ouverture de l'un des fichiers");
		return 0;
	}


	while(1)
	{
		
		read(buttons, &event_buttons, sizeof(event_buttons));

		int code = (int)event_buttons.code;
		int value = (int)event_buttons.value;

		switch(code)
		{
			case KEY_F1: // MENU
				if(value == 1)
				{
					printf("MENU PUSH\n");
					if(write(sys_led, "1", 1) == -1)
						perror("Erreur d'ecriture");
				}
				else
				{
					printf("MENU RELEASE\n");
					if(write(sys_led, "0", 1) == -1)
						perror("Erreur d'ecriture");
				}
			break;

			case KEY_ESC: // BACK
				if(value == 1)
				{
					printf("BACK PUSH\n");
					if(write(user_led, "1", 1) == -1)
						perror("Erreur d'ecriture");
				}
				else
				{
					printf("BACK RELEASE\n");
					if(write(user_led, "0", 1) == -1)
						perror("Erreur d'ecriture");
				}
			break;

			case KEY_HOME: // HOME
				if(value == 1)
				{
					printf("HOME PUSH\n");
					if(write(user_led, "1", 1) == -1)
						perror("Erreur d'ecriture");
					if(write(sys_led, "1", 1) == -1)
						perror("Erreur d'ecriture");
				}
				else
				{
					printf("HOME RELEASE\n");
					if(write(user_led, "0", 1) == -1)
						perror("Erreur d'ecriture");
					if(write(sys_led, "0", 1) == -1)
						perror("Erreur d'ecriture");
				}
			break;

		}


	}

	if(close(sys_led) == -1)
		perror("Erreur de fermeture de l'un des fichiers");
	if(close(user_led) == -1)
		perror("Erreur de fermeture de l'un des fichiers");
	if(close(buttons) == -1)
		perror("Erreur de fermeture de l'un des fichiers");

	return 0;
}


