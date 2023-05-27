typedef struct racional
{
	int num;
	int den;
} racional;

racional ler_racional();

void escreve_racional(racional r);

racional simplifica(racional r);

racional soma(racional a, racional b);

racional subt(racional a, racional b);

racional mult(racional a, racional b);

racional divi(racional a, racional b);
