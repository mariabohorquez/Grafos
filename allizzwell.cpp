// Este programa puese ser usado para buscar otros strings que no sean
// ALLIZZWELL. Cambias valores de myString y el chequeo de count y
// funciona con otros test cases


// Escrito con C para que no se pase de tiempo
#include <cstdio>

// Inicializamos nuestro string, el mapa (matriz) y visitados
char myString[11] = "ALLIZZWELL";
char map[101][101];
int visited[102][102];
// Fila, columna, dx y dy (adyacentes en la matriz en todas las direcciones posibles)
// Para entender las adyacentes: revisa esquina inferior derecha (1,1), esq sup der (1, -1),
// derecha (1, 0), abajo (0, 1), arriba (0, -1), esq inf izq (-1, 1),
// esq super izq (-1, -1), izquierda (-1, 0)
int dx[8] = {1, 1, 1, 0, 0,-1, -1,-1};
int dy[8] = {1,-1, 0, 1,-1, 1, -1, 0};
int row, col, check;

// Subprograma para encontrar el string en la matriz con Recursion
// Como parametros entra la posicion 'x', 'y' y el numero del caracter de myString
// que buscamos

void find_str(int x, int y, int count) {
   // Verifica si ya encontramos a myString. Si es cierto sale del subprograma
	if (count == 10){
		check = 1;
		return;
	}
   // Marca posicion actual como visitado
	visited[x][y] = 1;
   // Loop para pasear por toda la matriz
	for(int i=0; i<8; i++) {
      // Revisamos todos los adyacentes para verificar si se encuentra el myString
		int tempx = x + dx[i];
		int tempy = y + dy[i];
      // Verifica que nos encontremos dentro de la matriz
		if(tempx >=0 && tempx < row && tempy >= 0 && tempy < col \
         // Y que la posicion actual tenga el caracter que buscamos!!!
			&& map[tempx][tempy] == myString[count] \
         // Y que no hayamos visitado este lugar en especifico anteriormente
			&& visited[tempx][tempy] == 0) {
            // Por recursion seguimos llamando al Subprograma
            // Con el siguiente caracter de myString
            // Hasta que encontremos myString Completo o se acabe la matriz
				find_str(tempx, tempy, count + 1);
				if(check == 1)
					break;
				}
	}
   // Volvemos a reiniciar el visitado global para la siguiente matriz
	visited[x][y] = 0;
}

int main() {
   // Leemos el numero de matrices que tenemos que explorar
	int numberOfTests;
	scanf("%d", &numberOfTests);
   // Hacemos un loop para leer todas las matrices
	for(int test = 0; test < numberOfTests; test++) {
      //  Numero de filas y columnas
		scanf("%d %d", &row, &col);
      //  Iteramos por las filas para leerlas y agregar valores al mapa
		for(int i = 0; i < row; i++)
			scanf("%s", map[i]);
         // Inicializamos a Check (si el string es encontrado) como falso
			check = 0;
      // Iteramos por filas y columnas para chequear que encontremos 'A'
      // El primer caracter de nuestro string.
      // Si no se encuentra no tiene sentido buscar el string en la matriz
		for(int i = 0; i < row; i++)
			for(int j = 0; j < col; j++)
			{
				if(map[i][j] == 'A')find_str(i, j, 1);
			}
      // Imprimimos nuestra respuesta
		if(check == 0)
			printf("NO\n");
		else
			printf("YES\n");
	}
	return 0;
}
