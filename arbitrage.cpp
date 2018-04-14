#include <iostream>
#include <map>
using namespace std;

map< string, int> diccionario;
double dist[50][50] , costo;



int main()
{
    for(int test = 1; ; test++)
    {
        int numeroDeMonedas;
        cin >> numeroDeMonedas;
        // Condicion de fin del input
        if(numeroDeMonedas == 0)
            return 0;
        string nombreDeMoneda , inicio , destino;
        for(int i = 0 ; i < numeroDeMonedas ; i++)
        {
           // Monedas en un diccionario con numeros
            cin >> nombreDeMoneda;
            diccionario[nombreDeMoneda] = i;
        }
        // Numero de transacciones
        int tabla;
        cin >> tabla;
        // El costo inicial entre conexiones es 0
        for(int i = 0 ; i < numeroDeMonedas ; i++){
            for(int j = 0 ; j < numeroDeMonedas ; j++){
                dist[i][j] = 0.0;
            }
        }
        // Informacion de las transacciones al diccionario
        // + El costo de la conexion
        for(int i = 0 ; i < tabla ; i++){
            cin >> inicio >> costo >> destino;
            int x , y;
            x = diccionario[inicio];
            y = diccionario[destino];
            dist[x][y] = costo;
        }
        // Nuestro algoritmo Floyd-Warshall
        for(int k = 0 ; k < numeroDeMonedas ; k++)
            for(int i = 0 ; i < numeroDeMonedas ; i++)
                for(int j = 0 ; j < numeroDeMonedas ; j++)
                        dist[i][j] = max(dist[i][j] , dist[i][k] * dist[k][j]);
        // Si satisface la Condicion
        int caso = 0;
        for(int i = 0 ; i < numeroDeMonedas ; i++){
                if(dist[i][i] > 1.0 ){
                    caso = 1;
                    break;
                }
        }
        if (caso) cout<<"Case "<<test<<": Yes\n";
        else cout<<"Case "<<test<<": No\n";
    }
}
