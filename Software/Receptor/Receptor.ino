#include <WiFi.h>
#include <WebServer.h>
#include <EBYTE.h>

// Definição dos pinos do LoRa
#define TXD_PIN 17
#define RXD_PIN 16
#define M0_PIN 21
#define M1_PIN 19
#define AUX_PIN 15

// Definição do pino do LED azul (LED embutido do ESP32)
#define LED_WIFI 2

// Objeto para comunicação LoRa
EBYTE LoRa(&Serial2, M0_PIN, M1_PIN, AUX_PIN);

// Dados de Wi-Fi
const char* ssid = "SSID";
const char* senha = "Senha";

WebServer server(80);

// Variável para armazenar a última mensagem recebida
String ultimaMensagem = "Aguardando dados...";

// Função para lidar com a requisição da página principal
void handleRoot() {
  String page = "<html><head>";
  page += "<style>";
  page += "body { background: linear-gradient(to right, #4A90E2, #FFFFFF); font-family: Arial, sans-serif; text-align: center; padding: 50px; }";
  page += "h1 { color: #333; }";
  page += "#container { background: white; padding: 20px; border-radius: 10px; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2); display: inline-block; }";
  page += "</style></head><body>";
  page += "<div id='container'><h1>Dados do Sensor</h1>";
  page += "<p id='mensagem'>" + ultimaMensagem + "</p></div>";
  page += "<script>setInterval(function(){ fetch('/getMessage').then(response => response.text()).then(data => { document.getElementById('mensagem').innerText = data; }); }, 2000);</script>";
  page += "</body></html>";
  server.send(200, "text/html", page);
}

// Função para lidar com requisições de atualização de dados
void handleGetMessage() {
  server.send(200, "text/plain", ultimaMensagem);
}

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
  Serial2.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN); // Inicia a comunicação com o módulo LoRa

  // Inicializa o módulo LoRa
  LoRa.init(); 
  LoRa.SetAirDataRate(ADR_1K);
  LoRa.SetAddress(1);
  LoRa.SetChannel(23);
  LoRa.SaveParameters(TEMPORARY);
  LoRa.SetMode(EBYTE_MODE_NORMAL);

  Serial.println("Receptor iniciado!");

  // Configuração do LED de status do Wi-Fi
  pinMode(LED_WIFI, OUTPUT);
  digitalWrite(LED_WIFI, LOW); // LED apagado inicialmente

  // Conexão com a rede Wi-Fi
  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado ao Wi-Fi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  digitalWrite(LED_WIFI, HIGH); // Acende o LED azul indicando conexão Wi-Fi

  // Configuração do servidor HTTP
  server.on("/", handleRoot);
  server.on("/getMessage", handleGetMessage);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  // Verifica se há dados recebidos via LoRa
  if (Serial2.available() > 0) {
    String mensagemRecebida = Serial2.readStringUntil('\n');
    mensagemRecebida.trim();

    if (mensagemRecebida.length() > 0) {
      ultimaMensagem = mensagemRecebida; // Atualiza a última mensagem recebida
      Serial.println("Mensagem recebida: " + ultimaMensagem);
    }
  }

  // Mantém o servidor HTTP ativo
  server.handleClient();
}
