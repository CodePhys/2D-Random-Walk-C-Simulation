#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EXP 10
#define ERR "errore nell'apertura di un file\n"

struct vet{
  int x;
  int y;
};

int main(int argc, char **argv){
  
  /* pf*: puntatore a file (* = a, c, d)
     paa: puntatore ad array
     seed: seed
     ntm: numero taiettorie massimo
     tms: tempo massimo
     ndt: numero di traiettorie

     tmp: tempo
     ndi: numero di istogrammi
     sdt: somma delle traiettorie
     sdq: somma dei quadrati delle traiettorie
     squ: somma delle potenze quarte
     
     pro: probabilità
     dis: distanza
     med: media
     dsm: deviazione standard della media
     mdq: media dei quadrati
     dmq: deviazione standard della media dei quadrati */

  FILE *pfa, **pfc, *pfd;
  struct vet *pos;
  char str[40];
  unsigned int seed, ntm, tms, ndt, tmp = 1, ndi = 0, idx, nxt;
  long long int sdt = 0;
  unsigned long long int sdq = 0, squ = 0;
  
  double pro, dis;
  long double med, dsm, mdq, dmq;
  
   if(argc != 3){
    fprintf(stderr,"sintassi: ./<nome_programma> <tempo_max> <numero_traiettorie>\n");
    exit(EXIT_FAILURE);
  }
   
   printf("il programma scrive un file chiamato momenti_per_tempo.dat in cui sono salvati:\nil tempo, la media delle posizioni, la dev std delle posizioni, la media delle pos quadre, la dev std delle pos quadre\ninoltre, produce i dati di un iostogramma primitivo in ist.dat, e dei file dentro la cartella pos_al_tempo che verranno poi letti dal programma che produce gli istogrammi\n");
  
  tms = atoi(argv[1]);
  ntm = atoi(argv[2]);
  
  printf("tempo massimo: %d \t numero di traiettorie: %d\n", tms, ntm);
  pos = (struct vet *)calloc(ntm,sizeof(struct vet));
  
  // calcolo del numero di istogrammi (pos_al_tempo_x.dat da aprire e riempire)
  // il programma attualmente ne fa uno ogni potenza di 10 (vedi define EXP)
  while(tmp <= tms){
    ndi++;
    tmp *= EXP;
  }
  // apertura dei file
  pfc = (FILE**)calloc(ndi,sizeof(FILE*));
  for(idx = 0; idx < ndi; idx++){
    if(!idx){tmp = 1;}
    else{tmp *= EXP;}
    sprintf(str, "pos_al_tempo/pos_al_tempo_%u.dat", tmp);
    if( (pfc[idx] = fopen(str,"w")) == NULL){
      printf(ERR);
      exit(EXIT_FAILURE);
    }
  }

  /* impostazione generatore di numeri casuali */
  pfa = fopen("/dev/random","r");
  fread(&seed, sizeof(unsigned int), 1, pfa);
  printf("seed: %u\n", seed);
  srand(seed);
  fclose(pfa);
  
  /* apertura file */
  if( (pfa = fopen("traiettorie.dat","w")) == NULL ){
    fprintf(stderr, ERR);
    exit(EXIT_FAILURE);
  }
  if( (pfd = fopen("momenti_per_tempo.dat","w")) == NULL ){
    fprintf(stderr,ERR);
    exit(EXIT_FAILURE);
  }
  
  // inizio ciclo principale
  nxt = 1;
  idx = 0;
  for(tmp = 1; tmp <= tms; tmp++){
    sdt = sdq = squ = 0;
    for(ndt = 0; ndt < ntm; ndt++){
      pro = (double)rand()/RAND_MAX;
      if(pro < 0.25){pos[ndt].x++;}
      else if(pro < 0.5){pos[ndt].x--;}
      else if(pro < 0.75){pos[ndt].y++;}
      else {pos[ndt].y--;}
      dis = sqrt(pos[ndt].x*pos[ndt].x + pos[ndt].y*pos[ndt].y);
      sdt += dis;
      sdq += dis*dis;
      squ += dis*dis*dis*dis;
      fprintf(pfa,"%u %d %d\n", tmp, pos[ndt].x, pos[ndt].y);
      if(tmp == nxt){
	fprintf(pfc[idx],"%d %d\n",pos[ndt].x, pos[ndt].y);
      }
    }
    if(tmp == nxt){
      nxt *= EXP;
      idx++;
    }
    med = (double)sdt/ntm;
    dsm = sqrt(((double)sdq/(ntm - 1) - med*med)/ntm);
    mdq = (double)sdq/ntm;
    dmq = sqrt(((double)squ/(ntm - 1) - mdq*mdq)/ntm);
    fprintf(pfd, "%u %Lf %Lf %Lf %Lf\n", tmp, med, dsm, mdq, dmq);
  }
  fclose(pfa);
  for(idx = 0; idx < ndi; idx++){
    fclose(pfc[idx]);
  }
  fclose(pfd);
  return 0;
}
