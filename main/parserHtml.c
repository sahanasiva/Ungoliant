#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/HTMLparser.h>

#include "parserHtml.h"
//#include "BDStruct.h"


void split(char *str){
  	char * caract;
    caract = strtok (str," ,.-");
  	while (caract != NULL){
		if(strlen(caract)>0){
    		printf ("mot: %s\n",caract);
            //BDStruct.CelluleMot.add(caract);
		}
		//appeler ici la fonction pour inserer les mots ainsi que leurs occurences
    	caract = strtok (NULL, " ,.-");
  	}
}

htmlDocPtr gethtml(char *doclocation,char *encoding) {
    htmlDocPtr doc;
    doc = htmlReadFile(doclocation, encoding, HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING | HTML_PARSE_NONET);

    if (doc == NULL) {
        fprintf(stderr, "\nDocument non parse avec succes.\n");
    }
    return doc;
}

static void get_element_names(xmlNode * a_node){
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            //printf("Contenu: %s\n",xmlNodeGetContent(cur_node));
			split((char *)xmlNodeGetContent(cur_node));
            //hyperliens
            if (strcmp((char *)cur_node->name,"a")==0){
                for(xmlAttrPtr attr = cur_node->properties; NULL != attr; attr = attr->next){
                    if (strcmp((char *)attr->name,"href")==0){
                        printf("hyperlien : %s\n",xmlNodeGetContent(attr->children));
                        //sscanf pour verifier si http
                        // puis ajouter a la liste de siteAParcourir dans crawler.c
                    }
                }
            }
        }
        get_element_names(cur_node->children);
    }
}

void getroot(htmlDocPtr doc) {
    xmlNode *cur = NULL;
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr, "Document vide\n");
        xmlFreeDoc(doc);
    }else
      fprintf(stderr, "Document parse avec succes\n");

    //printf("Root:  %s\n", cur->name);
    get_element_names(cur);

}

//main
void parser(char*url){
    char *documentLocation = url;
    char *encoding = "UTF-8";
    htmlDocPtr doc;
    doc = gethtml(documentLocation, encoding);
    getroot(doc);
}

/*
void ajoutMot(CelluleMot *bdd){

  ListSite *url=malloc(sizeof(ListSite));
  url->url="http://www.google.com";
  url->savedPageName="google.com";
  url->occurences=1;
  char *mot="google";
  addMot(bdd,mot,mot,url);

}
*/

// int main(int argc, char *argv[]){
//     char* URL = argv[1];
//     //char *website = "http://www.google.com/index.html"; "./pagetest.html"
//     char *documentLocation = URL;
//     char *encoding = "UTF-8";
//     htmlDocPtr doc;
//     doc = gethtml(documentLocation, encoding);
//     getroot(doc);
//     return 0;
// }
