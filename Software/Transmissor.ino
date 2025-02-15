#include <EBYTE.h>
#include <DHT22.h> // Alterado para a biblioteca DHT22

// Definição dos pinos do LoRa
#define TXD_PIN 17 // Pino TX2 do ESP32 conectado ao RX do módulo LoRa
#define RXD_PIN 16 // Pino RX2 do ESP32 conectado ao TX do módulo LoRa
#define M0_PIN 21  // Pino M0 do módulo LoRa
#define M1_PIN 19  // Pino M1 do módulo LoRa
#define AUX_PIN 15 // Pino AUX do módulo LoRa

// Definição do pino do sensor DHT22
#define DHT_PIN 4  // Pino do ESP32 conectado ao DHT22

// Objetos para o LoRa e o sensor DHT22
EBYTE LoRa(&Serial2, M0_PIN, M1_PIN, AUX_PIN);
DHT22 dht(DHT_PIN); // Alterado para o construtor da biblioteca DHT22

void setup() {
  Serial.begin(9600);                      // Comunicação com o monitor serial
  Serial2.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN); // Comunicação com o módulo LoRa

  Serial.println();
  Serial.println(LoRa.init()); 
  LoRa.SetAirDataRate(ADR_1K);  // Taxa de dados
  LoRa.SetAddress(1);           // Endereço do transmissor
  LoRa.SetChannel(23);          // Canal 23
  LoRa.SaveParameters(TEMPORARY);
  LoRa.SetMode(EBYTE_MODE_NORMAL);

  Serial.println("Transmissor iniciado!");
}

void loop() {
  // Leitura da temperatura e umidade
  float temperatura = dht.getTemperature(); // Alterado para o método da biblioteca DHT22
  float umidade = dht.getHumidity();        // Alterado para o método da biblioteca DHT22

  // Verificação de falha na leitura
  if (isnan(temperatura) || isnan(umidade)) {
    Serial.println("Falha na leitura do sensor DHT22!");
    delay(2000); // Aguarda antes de tentar novamente
    return;
  }

  // Criação da mensagem
  String mensagem = "Temp: " + String(temperatura, 1) + "C, Umid: " + String(umidade, 1) + "%";

  // Envio da mensagem via LoRa
  Serial2.println(mensagem);

  // Exibe a mensagem no monitor serial
  Serial.print("Mensagem enviada: ");
  Serial.println(mensagem);

  delay(5000); // Intervalo de 5 segundos entre as leituras
}
