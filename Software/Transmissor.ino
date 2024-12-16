#include <EBYTE.h>

// Definição dos pinos
#define TXD_PIN 17 // Pino TX2 do ESP32 conectado ao RX do módulo LoRa
#define RXD_PIN 16 // Pino RX2 do ESP32 conectado ao TX do módulo LoRa
#define M0_PIN 21  // Pino M0 do módulo LoRa
#define M1_PIN 19  // Pino M1 do módulo LoRa
#define AUX_PIN 15 // Pino AUX do módulo LoRa

// Objeto para comunicação LoRa
EBYTE LoRa(&Serial2, M0_PIN, M1_PIN, AUX_PIN);

void setup() {
  Serial.begin(9600);    // Comunicação com o monitor serial
  Serial2.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN);   // Comunicação com o módulo LoRa
  
  Serial.println();
  Serial.println(LoRa.init()); 
  LoRa.SetAirDataRate(ADR_1K);  // Taxa de dados
  LoRa.SetAddress(1);           // Endereço do transmissor
  LoRa.SetChannel(23);          // Canal 23
  LoRa.SaveParameters(TEMPORARY);
  LoRa.SetMode(EBYTE_MODE_NORMAL);
  
  Serial.println("Transmissor iniciado!");
}

String mensagem = ""; // Variável para armazenar a mensagem inserida pelo usuário

void loop() {
  // Verifica se há entrada do usuário via Serial
  if (Serial.available() > 0) {
    // Lê a mensagem digitada pelo usuário
    mensagem = Serial.readStringUntil('\n'); // Lê até encontrar uma nova linha

    // Remove espaços extras ou quebras de linha indesejadas
    mensagem.trim();

    // Envia a mensagem usando Serial2
    Serial2.println(mensagem);

    // Exibe a mensagem enviada no monitor serial
    Serial.print("Mensagem enviada: ");
    Serial.println(mensagem);

    // Exibe status no monitor serial
    if (Serial2) {
      Serial.println("Mensagem enviada com sucesso!");
    } else {
      Serial.println("Falha ao enviar mensagem!");
    }
  }

  delay(200); // Intervalo para evitar leituras excessivas
}


