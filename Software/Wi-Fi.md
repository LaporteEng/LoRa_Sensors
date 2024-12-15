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

## Código

Para que o ESP32 pudesse atualizar o contador e exibi-lo em uma página web, foi necessário implementar um servidor HTTP no ESP32 que servisse uma página HTML e uma rota para obter o valor atual do contador.




