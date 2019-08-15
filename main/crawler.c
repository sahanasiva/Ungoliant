#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include <curl/curl.h>

#include "parserHtml.h"
#include "crawler.h"


// creer une liste (taille fixe : 10000) ou stocker les sites visités pour ensuite verifier ke ce site ne va pas etre revister !!!
//compare index
// les hyperliens ajouter en fin de liste pour pouvoir les visites par la suite

char *getFileName(){
   /* lire l'heure courante */
   time_t now = time (NULL);
   /* la convertir en heure locale */
   struct tm tm_now = *localtime (&now);
   /* Creer une chaine AAAAMMJJHHMMSS */
   char s_now[sizeof "AAAAMMJJHHMMSS"];
   strftime (s_now, sizeof s_now, "%Y%m%d%H%M%S", &tm_now);

  char *fileNameToSave=calloc(sizeof(char),100);
  strcat(fileNameToSave,"Sites/CprojYS_");
  strcat(fileNameToSave,s_now);
  strcat(fileNameToSave,".html");
  printf("%s\n",fileNameToSave);
   return fileNameToSave;
}

char *parseURL(char *adress){
  int length=strlen(adress)-1;
  char *str=calloc(sizeof(char),100);
  while(length>1){
    if(adress[length]=='/'){
      int i=0;
      for(i=0;i<length;i++){
        str[i]=adress[i];
      }
      return str;
    }
    length--;
  }
  return "";
}

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}

int crawler(char* URL){

  CURL *curl_handle;


  char *pagefilename = getFileName();
  FILE *pagefile;

  curl_global_init(CURL_GLOBAL_ALL);

  /* init the curl session */
  curl_handle = curl_easy_init();

  /* set URL to get here */
  curl_easy_setopt(curl_handle, CURLOPT_URL, URL);

  /* Switch on full protocol/debug output while bdding */
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

  /* disable progress meter, set to 0L to enable and disable debug output */
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

  /* open the file */
  pagefile = fopen(pagefilename, "wb");
  if(pagefile) {

    /* write the page body to this file handle */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

    /* get it! */
    curl_easy_perform(curl_handle);

    /* close the header file */
    fclose(pagefile);
  }

  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);

  return 0;

}

/*
void lancerCrawler(CelluleMot *bdd,char *tab[]){
  int i=0;
  for(i=0;i<3;i++){
    char* URL = tab[i];
    do{
        printf("\"%s\"\n",URL); //url actuel
        crawler(URL); //verifier si connection possible
        //parser(URL,bdd); // parser (methode de parserHtml)
        URL = parseURL(URL);
    } while (strcmp(URL,"")==0 || strlen(URL)>10);
  }
    //parser test
    ajoutMot(bdd);
}
*/



int main(int argc, char *argv[])
{

	char *tab[3]; //tab de sites
	tab[0]="http://www.google.fr";
	tab[1]="http://www.univ-paris-diderot.fr/";
	tab[2]="http://outlook.live.com";

	int i=0;
	for(i=0;i<3;i++){
    	char* URL = tab[i]; 
		do{
        	printf("\"%s\"\n",URL); //url actuel
        	crawler(URL); //verifier si connection possible
			parser(URL); // parser (methode de parserHtml)
            URL = parseURL(URL);
    	} while (strcmp(URL,"")==0 || strlen(URL)>10);
  	}
	return 0;
}
