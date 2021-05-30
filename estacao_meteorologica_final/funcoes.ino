float calibragem_dht22(float x, float a, float b)
{
  return a * x + b;
}

float calibragem_lm35(float x, float a, float b)
{
  return a * x + b;
}

float tensao_na_porta(int porta)
{
  float valor_do_sensor = analogRead(porta);
  float tensao = (valor_do_sensor * 1.1) / 1023;
  return tensao;
}

float get_temperatura_lm35(float tensao)
{
  return tensao * 100.0;
}

float converte_luminosidade(float R)
{
  return pow(10, 5.0 - log10(R));
}
