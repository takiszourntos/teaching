/*
 ============================================================================
 Name        : test_service.c
 Author      : Takis Zourntos
 Version     :
 Copyright   : Copyright (C) 2020 emad studio, inc.
 Description : a systemd service of my very own!
 ============================================================================
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(void)
{
	FILE *fp;
	size_t Nmax = 10, ctr = 0;
	bool working = true;

	fp = fopen("/var/log/test.log", "w+");

	printf("test service on line!\n");
	char cmdstr[80];
	while (working)
	{
		printf("%zu ... ", ++ctr);
		fflush(stdout);
		strcpy(cmdstr, "whoami >> /var/log/test.log");
		system(cmdstr);
		strcpy(cmdstr, "date >> /var/log/test.log");
		system(cmdstr);
		if (--Nmax == 0)
			working = false;
		usleep(1000000);
		printf("\r");
	}

	printf("test service shutting down! \n");
	fclose(fp);
	return EXIT_SUCCESS;
}
