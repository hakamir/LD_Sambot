//
//  test_port_serie.c
//  - envoi de caracteres sur le port serie du PC et attente d'un caractere en reception
//  - teste avec Code::Blocks (projet de type "Console"
//
#include <windows.h>            //utilisation de l'API32 (Application Program Interface) de Windows
#include <stdio.h>
#include <stdlib.h>


    char    c;                  //Entrée clavier
    char    chaine[10];
	int     retour;
    char    NomPort[50];        //nom du port
	int     NumPort;            //numero du port
	HANDLE  hCom;               //gestionnaire du port serie7
	COMSTAT EtatCom;
	DWORD   NbOctetsEcrits;
	DWORD   NbOctetsLus;
	int     NbOctetsALire;
	DCB     dcb;	            //structure "Device-Control Block" definissant les parametres de la communication
	char    distance;

int main(void)
{



    NumPort=27;                     //a adapter
	//-----------ouverture------------------
	sprintf(NomPort, "\\\\.\\COM%d", NumPort);
	hCom=CreateFile(NomPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if(hCom==INVALID_HANDLE_VALUE)
	{
        printf("erreur CreateFile\n");
        return -1;
	}
    printf("CreateFile OK\n");
	//------------configuration-------------
	retour=GetCommState(hCom, &dcb);    //lecture des parametres actuels du port
	if(retour==0)
	{
	    printf("erreur GetCommState\n");
        exit(1);
	}
    printf("GetCommState OK\n");
	dcb.ByteSize=8;			            //nombre de bits de donnee
	dcb.StopBits=1;			            //nombre de bit(s) de stop
	dcb.Parity=NOPARITY;				//type de parite
	dcb.BaudRate=9600;				    //vitesse de transfert des donnees
                                        //ou 110, 150, 300, 600, 1200, 1800, 2400, 2800, 7200, 9600, 14400, 19200,
                                        // 38400, 57600, 115200, 128000, 256000
	retour=SetCommState(hCom, &dcb);    //ecriture de ces parametres
	if(retour==0)
	{
	    printf("erreur SetCommState\n");
        exit(1);
	}
    printf("SetCommState OK\n");

    while(1)
    {
        distance = Read();
        printf("%d\n",distance);
        printf("----------\n");
        Sleep(1000);

        /*do{

            printf("-------------------------------------------------------------------------------------\n\n\n");
            printf("Appuyer sur h pour obtenir de l'aide. \n");
            c = getchar();
            system("cls");
            switch(c)
            {
                case 'h':
                    system("cls");
                    printf("Voici la liste des commandes disponibles :\n");
                    printf("    h. Obtenir de l'aide.\n");
                    printf("    e. Fermer la console.\n");
                    printf("    1. Frequence de clignotement de la LED a 2 Hz.\n");
                    printf("    2. Frequence de clignotement de la LED a 5 Hz.\n");
                    printf("    3. Frequence de clignotement de la LED a 10 Hz.\n\n");
                    printf("Appuyez sur une touche pour continuer...\n");
                    if (read()!=NULL)
                    {
                        printf("Un caractere a ete recu : %d",read());
                    }
                    getch();
                    system("cls");
                    break;

                case 'e':
                    system("cls");
                    printf("Au revoir...");
                    getch();
                    CloseHandle(hCom);
                    return 0;
                    break;

                case '1':
                    printf("1. Clignotement de la LED a 2 Hz.\n");
                    Write(c);
                    printf("Appuyez sur une touche pour continuer...\n");
                    getch();
                    system("cls");
                    break;

                case '2':
                    printf("2. Clignotement de la LED a 5 Hz.\n");
                    Write(c);
                    printf("Appuyez sur une touche pour continuer...\n");
                    getch();
                    system("cls");
                    break;

                case '3':
                    printf("3. Clignotement de la LED a 10 Hz.\n");
                    Write(c);
                    printf("Appuyez sur une touche pour continuer...\n");
                    getch();
                    system("cls");
                    break;

            }
        }while(1);*/

    }
	CloseHandle(hCom);					//fermeture du gestionnaire de port (jamais atteint !)

    return 0;
}

void Write(char c)
{
    sprintf(chaine, "%c", c);
    retour=WriteFile(hCom, chaine, 1, &NbOctetsEcrits, NULL);   //ecriture dans port serie
    if(!retour)
    {
        printf("erreur WriteFile\n");
    }
    NbOctetsALire=1;
    Sleep(10);
    return;
}
int Read(void)
{
    retour=ReadFile(hCom, &c, 1, &NbOctetsLus , NULL);   //lecture port serie
    if(!retour)
    {
        printf("erreur ReadFile\n");
    }
    return c;
}
