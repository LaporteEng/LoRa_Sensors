# Conexão entre os Módulos
O projeto visa implementar a conexão de dois módulos LoRa, um atuando como transmissor e outro como receptor, ambos conectados a microcontroladores ESP32. A mensagem é enviada pelo módulo transmissor e recebida pelo módulo receptor, que está conectado à internet. Utiliza-se um servidor HTTP para visualizar a mensagem recebida na web.

## Componentes Utilizados
* ESP32: Microcontrolador com capacidades de WiFi e Bluetooth.
* Rede WiFi: Rede sem fio à qual o ESP32 se conectará.
* Computador: Programar o ESP32 e acessar o servidor HTTP.
* Módulo LoRa Transmissor: Módulo responsável por enviar dados via comunicação LoRa.
* Módulo LoRa Receptor: Módulo responsável por receber dados via comunicação LoRa.

## Passos para Implementação
1 - Configuração do Ambiente de Desenvolvimento: Utilização da Arduino IDE para programar o ESP32.

2 - Conexão à Rede WiFi: Configuração do ESP32 para conectar-se a uma rede WiFi específica.

3 - Servidor HTTP: Implementação de um servidor HTTP no ESP32 que serve uma página HTML e uma rota para obter a mensagem recebida via LoRa.

# Módulo Receptor

Código principal da implementação:

```cpp
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
const char* ssid = "SENHA";                    // Nome da rede WiFi (SSID)
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


```
Para fornecer um feedback visual simples sobre o status da conexão do dispositivo, o sistema foi configurado para acender um LED no pino 2 caso o dispositivo esteja conectado. Se a conexão não for estabelecida, o LED é apagado.
<p align="center">
  <img src="https://github.com/user-attachments/assets/016124d6-8570-42e8-bba4-a61b911204e3" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>

Quando o ESP32 se conecta à rede, ele imprime uma mensagem de sucesso junto com o endereço IP atribuído. Caso a conexão falhe, uma mensagem informando a falha na conexão é exibida. Para que o ESP32 pudesse atualizar a mensagem e exibi-la em uma página web, foi implementado um servidor HTTP no ESP32 que servisse uma página HTML e uma rota para obter o valor atual da mensagem. O servidor HTTP serve para permitir que o microcontrolador se comunique com outros dispositivos na rede, como computadores, smartphones ou outros sistemas conectados. Ele atua como uma interface entre o ESP32 e os dispositivos que fazem requisições, permitindo que o ESP32 envie informações, responda a comandos e até mesmo controle hardware conectado, como LEDs ou sensores. Para possibilitar a comunicação sem fio entre os módulos LoRa, foram implementadas as bibliotecas LoRa no código, permitindo que o ESP32 envie e receba dados via LoRa de forma eficiente.
<p align="center">
  <img src="https://github.com/user-attachments/assets/e0c72889-0d22-43ac-be24-733d3ff92f0f" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>



# Módulo Transmissor



Código principal da implementação:

```cpp
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

```
Após integrar o código de comunicação HTTP com o código de conexão Wi-Fi, podemos observar no terminal serial o processo de criação do servidor web.

<p align="center">
  <img src="https://github.com/user-attachments/assets/e0c72889-0d22-43ac-be24-733d3ff92f0f" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>

Para acessar o servidor HTTP do ESP32, basta obter o endereço IP exibido no terminal serial após a conexão com o Wi-Fi e inseri-lo na barra de endereços de um navegador (http://<IP_do_ESP32>/). Isso permitirá visualizar a página gerada pelo servidor, como o contador sendo atualizado em tempo real. 
<p align="center">
  <img src="https://github.com/user-attachments/assets/a0a7c92c-feb1-4a61-b8e4-96d12b4e9d2d" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>

# Referências
* USINA INFO. ESP32 e Wi-Fi: Como Funciona a Comunicação com a Internet. 2024. Disponível em: https://www.usinainfo.com.br/blog/esp32-wifi-comunicacao-com-a-internet/. Acesso em: 13 dez. 2024.

* LABORATÓRIO DO ESP32. ESP32: Conectando-se à Internet via Wi-Fi. 2024. Disponível em: https://www.youtube.com/watch?v=FFPocTxOgmQ. Acesso em: 13 dez. 2024.

* ESP32IO.COM. ESP32 Web Server Tutorial. Disponível em: https://esp32io.com/tutorials/esp32-web-server. Acesso em: 14 dez. 2024.
