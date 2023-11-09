/* programma che calcola gli istogrammi a partire da file */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct vet {
  int x;
  int y;
};

#define ERR "errore nell'apertura di un file\n"

int main(int argc, char **argv){
  struct vet pos, max, min, jmax, jmin, nbin, cnt, loc, jpos;
  char sta[40], stb[60];
  FILE *pfa, *pfb;
  double lar;
  unsigned int num = 1;
  int **bin;
  double var;
  
  if(argc != 3){
    fprintf(stderr,"<intassi: ./nome_programma> <nome_file_da_istogrammare> <larghezza_bin>\n");
    exit(EXIT_FAILURE);
  }
  
  printf("il programma produce un file per creare un istogramma a partire dai dati forniti dal file dato, che si deve trovare nella cartella pos_al_tempo (il file viene creato nella cartella file_per_istogrammi)\n");
  
  // apertura file e inizializzazione di massimo e minimo
  printf("file letto: %s\n", argv[1]);
  sprintf(sta, "pos_al_tempo/%s", argv[1]);
  if( (pfa = fopen(sta,"r")) == NULL ){
    printf(ERR);
    exit(EXIT_FAILURE);
  }
  lar = atof(argv[2]);
  fscanf(pfa, "%d %d", &max.x, &max.y);
  min.x = max.x;
  min.y = max.y;
  
  // ricerca di massimo e minimo
  while(fscanf(pfa,"%d %d", &pos.x, &pos.y) != EOF){
    num++;
    if(pos.x > max.x){max.x = pos.x;}
    if(pos.x < min.x){min.x = pos.x;}
    if(pos.y > max.y){max.y = pos.y;}
    if(pos.y < min.y){min.y = pos.y;}
  }
  rewind(pfa);
  
  // calcolo delle posizioni dei bin nell'array
  jmax.x = lround(max.x/lar);
  jmax.y = lround(max.y/lar);
  jmin.x = lround(min.x/lar);
  jmin.y = lround(min.y/lar);
  nbin.x = abs(jmax.x) + abs(jmin.x) + 1;
  nbin.y = abs(jmax.y) + abs(jmin.y) + 1;
  bin = (int**)calloc(nbin.x,sizeof(int*));
  for(cnt.x = 0; cnt.x < nbin.x; cnt.x++){
    bin[cnt.x] = (int*)calloc(nbin.y,sizeof(int));
  }
  printf("max.x: %d, max.y: %d, min.x: %d, min.y: %d\nnbin.x: %d, nbin.y: %d\n", max.x, max.y, min.x, min.y, nbin.x, nbin.y);
  
  // assegnazione dei valori nei bin
  while(fscanf(pfa,"%d %d", &pos.x, &pos.y) != EOF){
    jpos.x = lround(pos.x/lar);
    jpos.y = lround(pos.y/lar);
    loc.x = abs(jpos.x - jmin.x);
    loc.y = abs(jpos.y - jmin.y);
    bin[loc.x][loc.y]++;
  }
  fclose(pfa);
  
  // apertura del file
  sprintf(stb, "file_per_istogrammi/istogramma_%s", sta+13);
  if( (pfb = fopen(stb,"w")) == NULL ){
    printf(ERR);
    exit(EXIT_FAILURE);
  }
  
  // stampa dei valori
  for(cnt.x = 0; cnt.x < nbin.x; cnt.x++){
    for(cnt.y = 0; cnt.y < nbin.y; cnt.y++){
      fprintf(pfb,"%lf %lf %lf\n", min.x + (double)cnt.x*lar, min.y + (double)cnt.y*lar, (double)bin[cnt.x][cnt.y]/(num*lar*lar));
      var += (double)bin[cnt.x][cnt.y]/(num*lar);
    }
    //printf("area totale: %f\n",var);
  }
  return 0;
}
