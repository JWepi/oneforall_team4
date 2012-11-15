# include <stdio.h>
# include <string.h>
# include <stdlib.h>

# include <time.h>
# include <ctype.h>
# include <fcntl.h>

# define DEBUG 0

void loadplaylists();
int readall(int all, char * name, int init);
void mywr(char * str);
void setaction(char * str);

void selectpl(char * pl);
void newpl(char * pl);
void delpl(char * pl);

void setactionselect(char * buffer, char * pl);
void newsong(char * pl, char * song);
void delsong(char * pl, char * song);

void showhelp(int nb);
void addpl(char * name, int init);
void addsong(char * pl, char * name);
void rempl(char * name);
void remsong(char * pl, char * name);
void savepls();

typedef struct playlist
{
	char * name;
	char * songs[1000];
	int songsnbr;
} playlist;

playlist playlists[1000];
int plnbr = 0;

int main(int ac, char ** av)
{
	char buffer[1024];
	char c;

	memset(buffer, 0, 1024);
	loadplaylists();

	mywr("--- Welcome to your playlist manager ---\n\n");
	
	while (strcmp(buffer, "quit") != 0)
	{
		memset(buffer, 0, 1024);
		mywr("You are at the main menu, what do you want to do ? (type 'help' for help) :> ");
		while ((c = getchar()) != '\n')
			if (c != '\n')
				buffer[strlen(buffer)] = c;
		mywr("\n");
		mywr("You said : ");
		mywr(buffer);
		mywr("\n\n");
		setaction(buffer);
	}
	return(0);
}

void loadplaylists()
{
	char buffer[1024];
	char songname[1024];
	char c = 'c';
	FILE * xmlpl;
	int i = -1;
	
	memset(playlists, 0, sizeof(playlists));
	while (++i < 1000)
	{
		playlists[i].songsnbr = 0;
	}

	xmlpl = fopen("playlists.xml","r");
	
	while(fscanf(xmlpl, "%s", buffer) != EOF)
	{
		if (strcmp(buffer, "<playlist>") == 0)
			while(fscanf(xmlpl, "%s", buffer) != EOF)
			{
				if (strcmp(buffer, "<song>") == 0)
				{
					memset(songname, 0, sizeof(songname));
					while(fscanf(xmlpl, "%s", buffer) != EOF)
					{
						if (strcmp(buffer, "</song>") == 0)
							break;
						strcat(songname, buffer);
						strcat(songname, " ");
					}
				}
				if (strcmp(buffer, "<name>") == 0)
				{
					fscanf(xmlpl, "%s", buffer);
					addpl(buffer, 1);
				}
				if (strcmp(buffer, "</song>") == 0)
					addsong(playlists[plnbr].name, songname);
				if (strcmp(buffer, "</playlist>") == 0)
				{
					mywr("\n");
					plnbr++;
					break;
				}
			}
		else if (DEBUG)
		{
			mywr("I read ");
			mywr(buffer);
			mywr("\n");
		}
	}
	printf("\n", buffer);
	fclose(xmlpl);
}

int readall(int all, char * name, int init)
{
	int i = -1;
	int found = 0;
	int minus = 0;

	while (++i < plnbr)
	{
		if (strlen(playlists[i].name) > 0 && (strlen(name) == 0 || strcmp(playlists[i].name, name) == 0))
		{
			mywr("I found the playlist '");
			mywr(playlists[i].name);
			mywr("'");
			if (all)
			{
				mywr(" with the following songs :\n");
				int j = -1;
				while (++j < playlists[i].songsnbr)
				{
					if (strlen(playlists[i].songs[j]) > 0)
					{
						char * num;
						num = malloc(100);
						sprintf(num, "%d", j - minus);
						mywr("Song n.");
						mywr(num);
						mywr(" : ");
						mywr(playlists[i].songs[j]);
						mywr("\n");
					}
					else
						minus++;
				}
				if (j == 0)
					mywr("This playlist has no songs\n");
			}
			mywr("\n");
			found++;
		}
	}
	
	if (found == 0 && init != 1)
		mywr("No playlist found !\n");
	mywr("\n");
	return(found);
}

void mywr(char * str)
{
	write(1, str, strlen(str));
}

void setaction(char * buffer)
{
	if (strcmp(buffer, "save") == 0)
		savepls();
	if (strcmp(buffer, "help") == 0)
		showhelp(0);
	if (strcmp(buffer, "showall") == 0)
		readall(1, "", 0);
	else if (strcmp(buffer, "show") == 0)
		readall(0, "", 0);
	else 
	{
		char * tmp = buffer;
		tmp += 3;
		if (strncmp(buffer, "sh ", 3) == 0)
			readall(1, tmp, 0);
		if (strncmp(buffer, "go ", 3) == 0)
			selectpl(tmp);
		if (strncmp(buffer, "nw ", 3) == 0)
			newpl(tmp);
		if (strncmp(buffer, "dl ", 3) == 0)
			delpl(tmp);
	}
}

void selectpl(char * pl)
{
	char buffer[1024];
	char c;

	memset(buffer, 0, 1024);
	
	if (readall(0, pl, 0))
	{
		while (strcmp(buffer, "exit") != 0)
		{
			memset(buffer, 0, 1024);
			mywr("You are focusing on the playlist '");
			mywr(pl);
			mywr("', what do you want to do ? (type 'help' for help) :> ");
			while ((c = getchar()) != '\n')
				if (c != '\n')
					buffer[strlen(buffer)] = c;
			mywr("\n");
			mywr("You said : ");
			mywr(buffer);
			mywr("\n\n");
			setactionselect(buffer, pl);
		}
	}
}

void newpl(char * pl)
{
	mywr("Adding a new playlist\n");
	addpl(pl, 0);
	plnbr++;
}

void delpl(char * pl)
{
	mywr("Removing a playlist\n");
	rempl(pl);
}

void setactionselect(char * buffer, char * pl)
{
	if (strcmp(buffer, "quit") == 0)
	{
		mywr("Exiting program");
		exit(0);
	}
	else if (strcmp(buffer, "show") == 0)
		readall(1, pl, 0);
	else if (strcmp(buffer, "help") == 0)
		showhelp(1);
	else 
	{
		char * tmp = buffer;
		tmp += 3;
		if (strncmp(buffer, "nw ", 3) == 0)
			newsong(pl, tmp);
		if (strncmp(buffer, "dl ", 3) == 0)
			delsong(pl, tmp);
	}
}

void newsong(char * pl, char * song)
{
	mywr("Adding a new song\n");
	addsong(pl, song);
}

void delsong(char * pl, char * song)
{
	mywr("Removing a song\n");
	remsong(pl, song);
}

void showhelp(int nb)
{
	if (nb == 0)
		mywr("You can display, select, create, delete playlists or exit the program : 'show', 'sh [name]', 'go [name]', 'nw [name]', 'dl [name]' or 'quit'\n\n");
	if (nb == 1)
		mywr("You can show, add, remove songs, go back to the main menu or exit the program : 'show', 'nw [name]', 'dl [name]', 'exit' or 'quit'\n\n");
}

void addpl(char * name, int init)
{
	if (readall(0, name, init) == 0)
	{
		playlists[plnbr].name = malloc(strlen(name) + 1);
		memcpy(playlists[plnbr].name, name, strlen(name) + 1);
		if (DEBUG)
		{
			mywr("Adding playlist '");
			mywr(playlists[plnbr].name);
			mywr("'\n");
		}
	}
}

void addsong(char * pl, char * name)
{
	int i = -1;
	
	while (++i < plnbr)
		if (strcmp(playlists[i].name, pl) == 0)
			break;
	
	playlists[i].songs[playlists[i].songsnbr] = malloc(strlen(name) + 1);
	memcpy(playlists[i].songs[playlists[i].songsnbr], name, strlen(name) + 0);
	playlists[i].songs[playlists[i].songsnbr][strlen(name) - 1] = '\0';
	
	if (DEBUG)
	{
		mywr("Adding song '");
		mywr(playlists[i].songs[playlists[i].songsnbr]);
		mywr("' to playlist '");
		mywr(playlists[i].name);
		mywr("'\n");
	}

	playlists[i].songsnbr++;
}

void rempl(char * name)
{
	int i = -1;
	if (readall(0, name, 0))
	{
		if (DEBUG)
		{
			mywr("Removing playlist '");
			mywr(playlists[i].name);
			mywr("'\n");
		}
		
		while (++i < plnbr)
			if (strcmp(playlists[i].name, name) == 0)
				break;
		
		memset(playlists[i].name, 0, sizeof(playlists[i].name));	
	}
}

void remsong(char * pl, char * name)
{
	int i = -1;
	
	while (++i < plnbr)
		if (strcmp(playlists[i].name, pl) == 0)
			break;
	
	int j = -1;
	
	while (++j < playlists[i].songsnbr)
		if (strcmp(playlists[i].songs[j], name) == 0)
			break;

	if (j < playlists[i].songsnbr)
	{
		memset(playlists[i].songs[j], 0, strlen(playlists[i].songs[j]));
		if (DEBUG)
		{
			mywr("Removing song '");
			mywr(playlists[i].songs[j]);
			mywr("' from playlist '");
			mywr(playlists[i].name);
			mywr("'\n");
		}
	}
	else
	{
		mywr("The playlist '");
		mywr(playlists[i].name);
		mywr("' has no song named '");
		mywr(name);
		mywr("'\n");
	}
}

void savepls()
{
	int i = -1;
	int j;
	FILE * xmlpl;

	xmlpl = fopen("playlists.xml","w");
	
	//fprintf(fp,”%s%d%f%d”,itemnumber,price,quality);
	while (++i < plnbr)
		if (strlen(playlists[i].name) > 0)
		{
			fprintf(xmlpl, "<playlist>\n");
			fprintf(xmlpl, "<name> %s </name>\n", playlists[i].name);
			j = -1;
			//if (playlists[i].songs[j][strlen(playlists[i].songs[j])] == ' ')
				//playlists[i].songs[j][strlen(playlists[i].songs[j])] = '\0';
			while (++j < playlists[i].songsnbr)
				if (strlen(playlists[i].songs[j]) > 0)
					fprintf(xmlpl, "<song> %s </song>\n", playlists[i].songs[j]);
			fprintf(xmlpl, "</playlist>\n\n"); 
		}
	
	fclose(xmlpl); 
}