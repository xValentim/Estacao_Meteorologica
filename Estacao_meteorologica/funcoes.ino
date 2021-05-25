#include <math.h><br>
float media(float* amostras, float numero_de_amostras) {
  float soma = 0;
  for (int i = 0; i < numero_de_amostras; i++) {
    soma += amostras[i];
  }
  float media = soma / numero_de_amostras;
  return media;
}

float desvio_padrao_amostra(float* amostras, float numero_de_amostras) {
  float mi = media(amostras, numero_de_amostras);
  float somatorio_sigma = 0;
  for (int i = 0; i < numero_de_amostras; i++) {
    somatorio_sigma += (amostras[i] - mi) * (amostras[i] - mi);
  }
  float sigma = sqrt((1 / numero_de_amostras) * somatorio_sigma);
  return sigma;
}

float incerteza_A(float* amostras, float numero_de_amostras) {
  float sigma = desvio_padrao_amostra(amostras, numero_de_amostras);
  float sigma_A = sigma / sqrt(numero_de_amostras);
  return sigma_A;
}

float incerteza_padrao(float sigma_A, float sigma_B) {
  float sigma_P = sqrt(sigma_A * sigma_A + sigma_B * sigma_B);
  return sigma_P;
}

double get_temperatura_ntc(int valor_do_sensor) {
  double Temp;
  // Transforma valor do sensor em tensão e depois em resistência.
  Temp = log(((10240000 / valor_do_sensor) - 10000));

  // Eq de Steinhart-Hart
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;// Converierte de Kelvin a Celsius
  return Temp;
}

double get_temperatura_lm35(int valor_do_sensor) {
  double Temp;

  // Transforma valor do sensor em tensão
  double tensao = valor_do_sensor * (5 / 1023);

  // Transforma tensão em Temperatura (LM35: 1°C / 0.01 V)
  Temp = valor_do_sensor / 0.01;
  return Temp;
}
