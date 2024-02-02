//#include <string.h>

//Safely allocate the given size. The program exits on failure.
void* safeMalloc(size_t size) {
  void* pointer = malloc(size);
  if(pointer == NULL) {
    printf("Memory allocation error.\n");
    exit(-1);
  }
  return pointer;
}

//Safely free the given pointer. The program exists on failure.
void safeFree(void* ptr) {
  if(ptr == NULL) {
    error("Tried to free NULL");
  }
  free(ptr);
}

void error(char* message) {
  printf("\e[0;31mError: %s\e[0;0m\n", message);
  exit(1);
}

//Return the textual length of the given integer.
int lengthOfInt(int n) {
  int i = 0;
  if(n < 0) i++;
  while(n != 0) {
    i++;
    n /= 10;
  }
  return i;
}

//Clear/Flush the given stream.
void clear(FILE* stream){
  int nh;
  do{
    nh=fgetc(stream);
  }while(nh != EOF && nh != '\n');
}

//Renvoie true si la chaine de caractère `str` contient la chaine `part`
bool strcontains(char* str, char* part) {
  int strLength = strlen(str);
  int partLength = strlen(part);
  int matching = 0;

  for(int i = 0; i < strLength - partLength || matching == partLength; i++) {
    if(str[i] == part[matching]) matching++;
    else matching = 0;
  }

  return matching == partLength;
}

//Renvoie true si la chaine de caractère `str` contient au moins un élément de la chaine `chars`
bool strContainsAtLeast(char* str, char* chars) {
  int strLength = strlen(str);
  int charCount = strlen(chars);

  for(int i = 0; i < strLength; i++) {
    for(int j = 0; j < charCount; j++) {
      if(str[i] == chars[j]) return true;
    }
  }

  return false;
}


FILE* ouvrirFichier(char* nomFichier, char* mode){
  FILE* fichier = NULL;
  fichier = fopen(nomFichier, mode); 
	if(fichier == NULL){
		printf("\nerreur %d, %s : %s \n\n", errno, nomFichier, strerror(errno));
		exit(1);
	}
  return fichier;
}