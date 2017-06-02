/*Permet d'initialiser le tableau de pipe tel que
tous les pipes soient inutlisés */
void init_pipes() 
{
	int i = 0;
	for (int i;i<MAX_PIPES;i++)
		_pipe[i].pr_w=MAX_TACHE; //Tube inutilisé
}



/*Ouvre un nouveau pipe*/
unsigned p_open(unsigned redacteur, unsigned lecteur)
{
	if (/*Vérif si les tâches ne sont pas créées*/)
		return -1;

	//Vérifier qu’il n’existe pas de tube avec ces 2 taches
	int i = 0 ;
	for (int i ; i<MAX_PIPES ; i++)
	{
		if (_pipe[i].pr_w == redacteur && _pipe[i].pr_r == lecteur)
			//Il existe un tube avec ces 2 taches
			/* QUESTION : Dans l'autre sens possible ? Avec une autre tache possible ? */
			return -1;
	}

	//Trouver un tube non utilisé
	i=0;
	while ( (_pipe[i].pr_w != MAX_TACHE) && (i < MAX_PIPES) )
		i++;
	if (i == MAX_PIPES) //Aucun tube n'est libre
		return -2;

	//Initialisation du tube
	_pipe[i].pr_w = redacteur;
	_pipe[i].pr_r = lecteur;
	_pipe[i].is = _pipe[i].ie = 0;
	_pipe[i].occup = 0; //Données restantes (0 au départ)


	//Retourner le numéro du tube créé
	return i;
}


/*Ferme un pipe*/
void p_close (unsigned conduit)
{
	_pipe[i].pr_w = MAX_TACHE;
	/* FAUT-IL SUPPRIMER LES VALEURS DU TABLEAU tube ?*/
}

/*Lit un certain nombre de données sur un pipe*/
void p_read  (tube, donnees, quantité)
{
	//Vérifier que le tube existe et que la tâche en est propriétaire
	if ( (_pipe[tube].pr_r != numero_de_la_tache_courante) )
	{
		printf("Tache non autorisee a lire dans le pipe");
		return;
	}

	//Vérifier que le tampon n’est pas vide, sinon endormir la tache
	if (_pipe[tube].occup == 0)
	{
		printf("Tampon vide ==> endormissement de la tache %d", _pipe[tube].pr_r);
		//ENDORMISSEMENT
	}

	/*Si  le  tube  est  plein  et  si  
	la  tâche  écrivain  est  suspendue 
	sur  une  écriture  dans  ce  tube alors la réveiller */
	if ( (_pipe[tube].occup == SIZE_PIPE) && (_pipe[tube].pr_w est suspendue une écriture dans ce tube) )
		reveiller _pipe[tube].pr_w;

	//Lire les données à partir du tampon

	if (quantite>occup) //Si la quantite demandee est plus grande que ce qu'il y a dans le pipe
	{
		printf("Quantite demandee plus grande que quantite dans le pipe");
		return;		
	}

	int i = 0;
	is = _pipe[tube].is;
	occup = _pipe[tube].occup;
	for (int i ; i < quantite ; i++)
	{
		donnees[i] = _pipe[tube].tube[is];
		is++;
		occup--;
	}
	_pipe[tube].is = is;
	_pipe[tube].occup = occup;
}


/*Ecrit un certain nombre de données sur un pipe*/
void p_write(tube, donnees, quantité)
{
	//Vérifier que le tube existe et que la tâche en est propriétaire
	if ( (_pipe[tube].pr_w != numero_de_la_tache_courante) )
	{
		printf("Tache non autorisee a ecrire dans le pipe");
		return;
	}

	//Vérifier qu’il y a de la place dans le tampon, sinon endormir la tache
	if (_pipe[tube].occup == SIZE_PIPE)
	{
		printf("Plus de place dans le tampon ==> endormissement de la tache %d", _pipe[tube].pr_w);
		//ENDORMISSEMENT
	}

	/*Si le tube est vide et si 
	la tache lectrice est suspendue sur 
	une lecture de ce tube alors la réveiller*/
	if ( (_pipe[tube].occup == 0) && (_pipe[tube].pr_r est suspendue sur une lecture de ce tube) )
		reveiller _pipe[tube].pr_r;

	unsigned int occup = _pipe[tube].occup;

	//Copier les données dans le tampon
	if (quantite>SIZE_PIPE-occup) //Si le message est plus grand que la taille restante dans le pipe
	{
		printf("Message trop grand par rapport a place restante dans pipe");
		return;		
	}

	int i = 0;
	ie = _pipe[tube].ie;
	occup = _pipe[tube].occup;
	for (int i ; i < quantite ; i++)
	{
		_pipe[tube].tube[ie] = donnees[i];
		ie++;
		occup++;
	}
	_pipe[tube].ie = ie;
	_pipe[tube].occup = occup;
}