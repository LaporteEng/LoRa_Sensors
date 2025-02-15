#include <WiFi.h>
#include <WebServer.h>
#include <EBYTE.h>

// Definição dos pinos do LoRa
#define TXD_PIN 17
#define RXD_PIN 16
#define M0_PIN 21
#define M1_PIN 19
#define AUX_PIN 15

// Objeto para comunicação LoRa
EBYTE LoRa(&Serial2, M0_PIN, M1_PIN, AUX_PIN);

// Dados de Wi-Fi
const char* ssid = "SSID";
const char* senha = "Senha";

WebServer server(80);

String ultimaMensagem = "Aguardando dados...";

void handleRoot() {
  String page = "<html><body><h1>Dados do Sensor:</h1>";
  page += "<p>" + ultimaMensagem + "</p>";
  page += "<script>setInterval(function(){ fetch('/getMessage').then(response => response.text()).then(data => { document.body.innerHTML = '<h1>Dados do Sensor:</h1><p>' + data + '</p>'; }); }, 2000);</script>";
  page += "</body></html>";
  server.send(200, "text/html", page);
}

void handleGetMessage() {
  server.send(200, "text/plain", ultimaMensagem);
}

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD_PIN, TXD_PIN);

  LoRa.init(); 
  LoRa.SetAirDataRate(ADR_1K);
  LoRa.SetAddress(1);
  LoRa.SetChannel(23);
  LoRa.SaveParameters(TEMPORARY);
  LoRa.SetMode(EBYTE_MODE_NORMAL);

  Serial.println("Receptor iniciado!");

  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado ao Wi-Fi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/getMessage", handleGetMessage);
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  if (Serial2.available() > 0) {
    String mensagemRecebida = Serial2.readStringUntil('\n');
    mensagemRecebida.trim();

    if (mensagemRecebida.length() > 0) {
      ultimaMensagem = mensagemRecebida;
      Serial.println("Mensagem recebida: " + ultimaMensagem);
    }
  }

  server.handleClient();
}
