#include <Arduino.h>

// Definição dos pinos de conexão
#define TXD_PIN 17 // Pino TX2 do ESP32 conectado ao RX do módulo LoRa
#define RXD_PIN 16 // Pino RX2 do ESP32 conectado ao TX do módulo LoRa
#define M0_PIN 21  // Pino M0 do módulo LoRa
#define M1_PIN 19  // Pino M1 do módulo LoRa
#define AUX_PIN 15 // Pino AUX do módulo LoRa

void setup() {
  Serial.begin(9600);  // Comunicação com o Monitor Serial
  Serial2.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN); // Configura a Serial2 para comunicação com o módulo LoRa

  // Configuração dos pinos M0, M1 e AUX
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(AUX_PIN, OUTPUT);
  digitalWrite(AUX_PIN, LOW);

  // Configura o módulo para o Sleep Mode (M0=1, M1=1)
  digitalWrite(M0_PIN, HIGH);
  digitalWrite(M1_PIN, HIGH);
  
  Serial.println("Iniciando...");
  delay(1000);  // Aguarda inicialização
}

void loop() {
  // Envia o comando em formato hexadecimal C3 C3 C3
  byte command[] = {0xC3, 0xC3, 0xC3};  // Comando em formato HEX

  Serial.println("Enviando comando: C3 C3 C3");

  // Envia o comando HEX para o módulo LoRa
  Serial2.write(command, sizeof(command));
  delay(2000); // Aguarda a resposta do módulo

  // Verifica se há resposta do módulo
  if (Serial2.available() > 0) {
    Serial.println("Resposta recebida do módulo:");
    
    // Lê e exibe a resposta completa
    while (Serial2.available() > 0) {
      byte received = Serial2.read();
      Serial.print(received, HEX); // Exibe a resposta em formato hexadecimal
      Serial.print(" ");
    }
    Serial.println(); // Quebra de linha para separar respostas
  } else {
    Serial.println("Nenhuma resposta recebida.");
  }

  delay(5000); // Aguarda antes de repetir o ciclo
}
