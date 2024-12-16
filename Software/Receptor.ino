#include <WiFi.h>                                      // Biblioteca para conectar o ESP32 à rede WiFi
#include <WebServer.h>                                 // Biblioteca para criar um servidor HTTP no ESP32
#include <EBYTE.h>                                      

// Definição dos pinos
#define TXD_PIN 17 // Pino TX2 do ESP32 conectado ao RX do módulo LoRa
#define RXD_PIN 16 // Pino RX2 do ESP32 conectado ao TX do módulo LoRa
#define M0_PIN 21  // Pino M0 do módulo LoRa
#define M1_PIN 19  // Pino M1 do módulo LoRa
#define AUX_PIN 15 // Pino AUX do módulo LoRa

// Objeto para comunicação LoRa
EBYTE LoRa(&Serial2, M0_PIN, M1_PIN, AUX_PIN);

// Dados de Wi-Fi
const char* ssid = "VIVOFIBRA-3BD1";                    // Nome da rede WiFi (SSID)
const char* senha = "Buganvilha*";                      // Senha da rede WiFi

WebServer server(80);                                   // Cria um servidor HTTP na porta 80 (padrão)

String mensagem = "Ola, sou o ESP32 Receptor!";         // Mensagem inicial a ser enviada
unsigned long ultima_atualizacao = 0;                   // Variável para armazenar o tempo da última atualização
char buffer[64];                                        // Variável para armazenar a mensagem inserida pelo usuário

void handleRoot() {
  String page = "<html><body><h1>Mensagem Recebida: <span id='mensagem'>" + String(buffer) + "</span></h1>";
  page += "<p>" + mensagem + "</p>"; // Exibe a mensagem fixa
  page += "<script>";
  page += "setInterval(function(){";
  page += "  fetch('/getMessage').then(response => response.text()).then(data => {";
  page += "    document.getElementById('mensagem').innerHTML = data;";
  page += "  });";
  page += "}, 2000);"; // Atualiza a mensagem recebida a cada 2 segundos
  page += "</script>";
  page += "</body></html>";
  server.send(200, "text/html", page); // Envia a página com a mensagem
}

// Função que retorna a mensagem recebida
void handleGetMessage() {
  server.send(200, "text/plain", String(buffer)); // Retorna a mensagem armazenada no buffer
}

void setup() {
  Serial.begin(9600);    // Comunicação com o monitor serial
  Serial2.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN);   // Comunicação com o módulo LoRa
  
  LoRa.init(); 
  LoRa.SetAirDataRate(ADR_1K);  // Taxa de dados
  LoRa.SetAddress(1);           // Endereço do receptor
  LoRa.SetChannel(23);          // Canal 23
  LoRa.SaveParameters(TEMPORARY);
  LoRa.SetMode(EBYTE_MODE_NORMAL);
  
  Serial.println("Receptor iniciado!");
  
  WiFi.begin(ssid, senha);                             // Inicia a conexão com a rede WiFi utilizando SSID e senha

  pinMode(2, OUTPUT);                                  // Configura o pino 2 como saída (para controle de LED)
  delay(10);                                           // Pequeno atraso para garantir que o código seja executado corretamente

  // Aguarda até que o ESP32 esteja conectado ao WiFi
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);                                      // Espera meio segundo entre tentativas
      Serial.print(".");                               // Exibe pontos no monitor serial enquanto tenta conectar
  }
  // Quando a conexão é estabelecida, imprime uma linha de asteriscos e o status
  Serial.print("\n\t");
  if (WiFi.status() == WL_CONNECTED) {
    for (int i = 0; i < 32; i++) {                     // Imprime uma linha de asteriscos
      Serial.print("*");
    }
    Serial.println("\n\tESP32 está conectado à internet.");
    Serial.print("\tEndereço IP: ");
    Serial.println(WiFi.localIP());                    // Exibe o endereço IP do ESP32 na rede
    Serial.print("\t");

    server.on("/", handleRoot); // Define a rota principal
    server.on("/getMessage", handleGetMessage); // Define a rota para obter a mensagem
    
    server.begin();                                    // Inicia o servidor HTTP
    Serial.println("Servidor HTTP iniciado");
    Serial.print("\t");
    for (int i = 0; i < 32; i++) {                     
      Serial.print("*");
    }
  } else {
    // Caso a conexão falhe, imprime uma mensagem de erro
    Serial.println("ESP32 não está conectado à internet.");
  }
    Serial.print("\n");
  delay(2000);                                         // Atraso de 5 segundos antes de continuar
}

// Função que controla o estado do LED conectado ao pino 2
void ST_conexao() {
  if (WiFi.status() == WL_CONNECTED)                   // Se estiver conectado à internet
    digitalWrite(2, HIGH);                             // Acende o LED (pino 2)
  else
    digitalWrite(2, LOW);                              // Apaga o LED se não estiver conectado
}

void loop() {
  ST_conexao(); // Chama a função para controlar o LED de status

  // Verifica se há dados disponíveis para leitura na Serial2
  if (Serial2.available() > 0) {
    // Garante que o buffer esteja vazio antes de usá-lo
    memset(buffer, 0, sizeof(buffer));

    // Lê até encontrar '\n' ou preencher o buffer
    int tamanho = Serial2.readBytesUntil('\n', buffer, sizeof(buffer) - 1);

    if (tamanho > 0) {
      buffer[tamanho] = '\0'; // Finaliza a string recebida

      // Exibe a mensagem recebida
      Serial.print("Mensagem recebida: ");
      Serial.println(buffer);

    } else {
      Serial.println("Erro ao receber mensagem!");
    }
  } else {
    Serial.println("Aguardando mensagem...");
  }

  delay(1000); // Intervalo de 2 segundos para verificação

  server.handleClient(); // Mantém o servidor rodando e aguardando requisições
}

