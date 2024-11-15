/*
	Nome: Cauan Gabriel de Souza
	RA: 231153163
	Programa: Numeros primos com funcoes iterativa e recursiva
*/

#include <stdio.h>
#include <math.h>

// Funcao que testa o valor num de entrada de forma iterativa
int primo_iter(int num)
{
	// Caso 'num' seja 2, o programa encerra os testes retornando positivo, caso ele seja menor que dois, o programa encerra os testes retornando falso
	if (num <= 2)
	{
		return (num == 2) ? 1 : 0;
	}
	// Caso 'num' seja par, o programa retorna falso
	if (num % 2 == 0)
	{
		return 0;
	}
	// Para 'num' maior que dois o programa prossegue com os testes
	if (num > 2)
	{
		// 'i' recebe o valor de um para iniciar no laco de repeticao para evitar erros caso o valor maximo seja raiz de 3 (1,7)
		int i = 1;
		// O programa ira testar apenas ate que 'i' alcance o valor da raiz
		while (i <= sqrt(num))
		{
			// 'i' eh incrementado antes do teste condicional para nao ser testado com o valor '1'
			i++;
			// Caso 'num' seja divisivel por qualquer numero maior que dois, o programa retorna falso
			if (num % i == 0)
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

// Funcao que testa o valor de entrada de forma recursiva
int primo_re(int num, int i)
{
	// Caso 'num' seja igual a dois o programa retorna '1' (verdadeiro), caso seja outro numero (1, 0, ou negativos), retorna '0' (falso)
	if (num <= 2)
	{
		if (num == 2)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	// Caso seja divisivel por dois, retorna '0'
	if (num % 2 == 0)
	{
		return 0;
	}
	// Caso seja divisivel por um numero igual ou maior que 'i' ('i' recebe inicialmente o valor '2'), retorna '0'
	if (num % i == 0)
	{
		return 0;
	}
	// Caso a variavel de incrimento 'i' ultrapasse o valor da raiz de 'num' sem entrar nos outros lacos, retorna '1'
	if (i > sqrt(num))
	{
		return 1;
	}

	return primo_re(num, i + 1);
}

int main()
{
	int num = 0;
	int i = 2;

	printf("Digite um numero inteiro:\n");
	scanf("%i", &num);

	// 'primo' = 0 --> falso
	// 'primo' = 1 --> verdadeiro

	// Printa o resultado dos testes da funcao iterativa
	printf("Resultado iterativo:\n");
	if (primo_iter(num) == 0)
	{
		printf("O numero nao eh primo\n");
	}
	else
	{
		printf("O numero eh primo\n");
	}

	// Printa o resultado dos testes da funcao recursiva
	printf("Resultado recursivo:\n");
	if (primo_re(num, i) == 0)
	{
		printf("O numero nao eh primo\n");
	}
	else
	{
		printf("O numero eh primo\n");
	}
	return 0;
}