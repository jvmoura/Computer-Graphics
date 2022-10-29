#include <iostream>
#include <SDL2/SDL.h>
#include "./funcoes/screen.h"
#include "./funcoes/calculos.h"

const double wJanela = 1200, hJanela = 1200;
const double n_linha = 1200, n_coluna = 1200;
const double dx = wJanela/n_coluna, dy = hJanela/n_linha;

const double dJanela = 100;

const double rEsfera = 300;
double centroEsfera[3] = {300, 300, -(dJanela + rEsfera)};

double I_L[3] = {0.7, 0.7, 0.7};
double P_F[3] = {0, 5, 0}; 

bool lookAndPaint(double dr[3], double p0[3]) {
  double co[3]; // CO: Distancia centro ao olho
  co[0] = p0[0] - centroEsfera[0];
  co[1] = p0[1] - centroEsfera[1];
  co[2] = p0[2] - centroEsfera[2];
  // Raio encontra esfera: at^2 + bt + c = 0
  double coefA = prodEscalar(dr, dr);                     //<D, D>
  double coefB = 2 * prodEscalar(co, dr);                 // 2<CO, D>
  double coefC = prodEscalar(co, co) - rEsfera * rEsfera; //<CO, CO> - r^2
  double delta = coefB * coefB - 4 * coefA * coefC;

  return delta >= 0;
}

int main( int argc, char *argv[] )
{
    double x, y;
    double olho[3] = {300, 300, 0};

    Screen tela;

    for (int linha = 0; linha < n_linha; linha++){
        y = hJanela / 2 - dy / 2 - dy * linha;
        for (int coluna = 0; coluna < n_coluna; coluna++){
            x = -wJanela/2 + dx/2 + dx * coluna;
            double visao[3] = {x, y, -dJanela};
            double vetorDirecao[3];
            vetorDirecao[0] = visao[0] - olho[0];
            vetorDirecao[1] = visao[1] - olho[1];
            vetorDirecao[2] = visao[2] - olho[2];

            if (lookAndPaint(vetorDirecao, olho)) {
                tela.pixel(x, y);
            }
        }
    }

    while(true){
        tela.show();
        tela.input();
    }
    return 0;
}