
typedef struct
{ 
	ushort pr_w , pr_r ; /* redacteur & lecteur du tube */ 
	ushort ocupp ;  /* donnees restantes */ 
	uchar is, ie ;    /* pointeurs d’entree / sortie */
	uchar tube[SIZE_PIPE] ; /* Tampon */ 
} PIPE; 

PIPE  _pipe[MAX_PIPES] ;   /* Variables tubes */


unsigned p_open(unsigned redacteur, unsigned lecteur); //Allocation du conduit
void p_close ( unsigned conduit); //Libération du tube
void p_read  (tube, donnees, quantité); //Lecture dans un tube
void p_write(tube, donnees, quantité); //Ecriture dans un tube

//Ajouts

void init_pipes(PIPE _pipe);