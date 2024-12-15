# Conexão Wi-Fi do ESP32

O objetivo deste teste é configurar o ESP32 para se conectar a uma rede WiFi e hospedar um servidor HTTP básico. Este servidor enviará uma mensagem simples e um contador que é incrementado a cada 10 segundos, permitindo a verificação da conectividade e funcionalidade em tempo real.

## Componentes Utilizados
* ESP32: Microcontrolador com capacidades de WiFi e Bluetooth.
* Rede WiFi: Rede sem fio à qual o ESP32 se conectará.
* Computador: Programar o ESP32 e acessar o servidor HTTP.

## Passos para Implementação
1 - Configuração do Ambiente de Desenvolvimento: Utilização da Arduino IDE para programar o ESP32.

2 - Conexão à Rede WiFi: Configuração do ESP32 para conectar-se a uma rede WiFi específica.

3 - Servidor HTTP: Implementação de um servidor HTTP simples que responderá com uma mensagem e um contador incrementado.

# Código

Para que o ESP32 pudesse atualizar o contador e exibi-lo em uma página web, foi implementado um servidor HTTP no ESP32 que servisse uma página HTML e uma rota para obter o valor atual do contador.

```cpp
#include <WiFi.h>                                      // Biblioteca para conectar o ESP32 à rede WiFi
#include <WebServer.h>                                 // Biblioteca para criar um servidor HTTP no ESP32

// Substitua pelos seus dados de Wi-Fi
const char* ssid = "REDE";                      // Nome da rede WiFi (SSID)
const char* senha = "SENHA";                      // Senha da rede WiFi

WebServer server(80);                                  // Cria um servidor HTTP na porta 80 (padrão)

String mensagem = "Ola, sou o ESP32!";                 // Mensagem inicial a ser enviada
unsigned long ultima_atualizacao = 0;                  // Variável para armazenar o tempo da última atualização
int contador = 0;                                      // Contador que será incrementado a cada 10 segundos

// Função que será chamada quando o servidor receber uma requisição na rota "/"
void handleRoot() {
  String page = "<html><body><h1>Contador: <span id='contador'>" + String(contador) + "</span></h1>";
  page += "<p>" + mensagem + "</p>";                   // Exibe a mensagem
  page += "<script>";
  page += "setInterval(function(){";
  page += "  fetch('/getCounter').then(response => response.text()).then(data => {";
  page += "    document.getElementById('contador').innerHTML = data;";
  page += "  });";
  page += "}, 10000);";                                // Atualiza o contador a cada 10 segundos
  page += "</script>";
  page += "</body></html>";
  server.send(200, "text/html", page);                 // Envia a página com o contador
}

// Função que retorna o contador atual
void handleGetCounter() {
  server.send(200, "text/plain", String(contador));    // Retorna o valor atual do contador
}

void setup() {
  Serial.begin(115200);                                // Inicializa a comunicação serial para monitoramento
  WiFi.begin(ssid, senha);                             // Inicia a conexão com a rede WiFi utilizando SSID e senha

  pinMode(2, OUTPUT);                                  // Configura o pino 2 como saída (para controle de LED)
  delay(10);                                           // Pequeno atraso para garantir que o código seja executado corretamente

  // Aguarda até que o ESP32 esteja conectado ao WiFi
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);                                      // Espera meio segundo entre tentativas
      Serial.print(".");                               // Exibe pontos no monitor serial enquanto tenta conectar
  }
  // Quando a conexão é estabelecida
  Serial.print("\n\t");
  if (WiFi.status() == WL_CONNECTED) {
    for (int i = 0; i < 32; i++) {                     // Imprime uma linha de asteriscos
      Serial.print("*");
    }
    Serial.println("\n\tESP32 está conectado à internet.");
    Serial.print("\tEndereço IP: ");
    Serial.println(WiFi.localIP());                    // Exibe o endereço IP do ESP32 na rede
    Serial.print("\t");

    // Configura o servidor para responder com a função handleRoot quando acessar "/"
    server.on("/", handleRoot);
    
    // Rota para retornar o contador atual
    server.on("/getCounter", handleGetCounter);
    
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
  delay(5000);                                         // Atraso de 5 segundos antes de continuar
}

// Função que controla o estado do LED conectado ao pino 2
void ST_conexao() {
  if (WiFi.status() == WL_CONNECTED)                   // Se estiver conectado à internet
    digitalWrite(2, HIGH);                             // Acende o LED (pino 2)
  else
    digitalWrite(2, LOW);                              // Apaga o LED se não estiver conectado
}

void loop() {
  ST_conexao();                                        // Chama a função para controlar o LED de status
  
  // Verifica se 10 segundos se passaram desde a última atualização
  if (millis() - ultima_atualizacao >= 10000) {
    contador++;                                        // Incrementa o contador
    ultima_atualizacao = millis();                     // Atualiza o tempo da última execução
  }

  server.handleClient();                               // Mantém o servidor rodando e aguardando requisições
}
```
A seguir, será apresentada uma explicação detalhada sobre os principais componentes do código, como a conexão WiFi, a criação do servidor HTTP, a atualização do contador e a interação com o usoário através da página web.

# Conexão Wi-Fi
Para realizar a conexão do ESP32 com o Wi-Fi, utilizamos do seguinte código:
```cpp
#include <WiFi.h>

const char* ssid = "REDE";                      // Nome da rede WiFi (SSID)
const char* senha = "SENHA";                      // Senha da rede WiFi

void setup() {
  Serial.begin(115200);                                // Inicializa a comunicação serial para monitoramento
  WiFi.begin(ssid, senha);                             // Inicia a conexão com a rede WiFi utilizando SSID e senha

  pinMode(2, OUTPUT);                                  // Configura o pino 2 como saída (para controle de LED)
  delay(10);                                           // Pequeno atraso para garantir que o código seja executado corretamente

  // Aguarda até que o ESP32 esteja conectado ao WiFi
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);                                      // Espera meio segundo entre tentativas
      Serial.print(".");                               // Exibe pontos no monitor serial enquanto tenta conectar
  }
  // Quando a conexão é estabelecida
  Serial.print("\n\t");
  if (WiFi.status() == WL_CONNECTED) {
    for (int i = 0; i < 32; i++) {                     // Imprime uma linha de asteriscos
      Serial.print("*");
    }
    Serial.println("\n\tESP32 está conectado à internet.");
    Serial.print("\tEndereço IP: ");
    Serial.println(WiFi.localIP());                    // Exibe o endereço IP do ESP32 na rede
    Serial.print("\t");
    for (int i = 0; i < 32; i++) {                     
      Serial.print("*");
    }
  } else {
    // Caso a conexão falhe, imprime uma mensagem de erro
    Serial.println("ESP32 não está conectado à internet.");
  }
  delay(5000);                                         // Atraso de 5 segundos antes de continuar
}
void ST_conexao() {
  if (WiFi.status() == WL_CONNECTED)                   // Se estiver conectado à internet
    digitalWrite(2, HIGH);                             // Acende o LED (pino 2)
  else
    digitalWrite(2, LOW);                              // Apaga o LED se não estiver conectado
}
void loop() {
  ST_conexao();                                        // Chama a função para controlar o LED de status
}
```
Se o dispositivo estiver conectado, ela acende um LED no pino 2 (em azul). Caso contrário, apaga o LED, indicando que a conexão não foi estabelecida. Isso fornece um feedback visual simples sobre o status da conexão.
<p align="center">
  <img src="https://github.com/user-attachments/assets/016124d6-8570-42e8-bba4-a61b911204e3" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>

Quando o ESP32 finalmente se conecta à rede, ele imprime uma mensagem de sucesso junto com o endereço IP atribuído. Caso a conexão falhe, uma mensagem informando a falha na conexão é exibida.
<p align="center">
  <img src="https://github.com/user-attachments/assets/016124d6-8570-42e8-bba4-a61b911204e3" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>







