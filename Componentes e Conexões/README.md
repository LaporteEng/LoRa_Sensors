# Componentes e Conexões

Neste diretório, serão apresentados os compenentes utilizados e suas conexões.

A seguir, é possível visualizar um diagrama de blocos que descreve o projeto.

![Diagrama de Blocos](DiagramaDeBlocos.png)

Conforme apresentado no diagrama, é composto por:
1. Hardware:
    - Sensores de temperatura.
    - Módulos de comunicação LoRa.
    - Microcontroladores ESP32.
    - Fontes de alimentação.
      
2. Software:
    - Firmware para ESP32 para ler dados dos sensores e transmitir via LoRa.
    - Microcontrolador receptor para receber dados via LoRa e exibi-los.
    - Interface para exibição de dados via serial em tempo real.
# Descrição dos Componentes do Projeto

Este projeto utiliza os seguintes componentes:

1. **ESP32**
2. **Módulo EBYTE LoRa E32900T20D**
3. **Sensor de Temperatura e Umidade DHT22**

## 1. ESP32
<p align="center">
  <img src="https://github.com/user-attachments/assets/f673b9d5-a285-49c0-a299-b4abc0e7da35" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>
<p align="center">
  Fonte: <a href="https://xprojetos.net/esp32-e-suas-versoes/">xProjetos, 2019 
</p>
      
### Descrição:
O ESP32 é um microcontrolador desenvolvido pela Espressif Systems, com capacidades de Wi-Fi e Bluetooth integradas. Ele possui uma arquitetura de 32 bits, com alto desempenho, baixo consumo de energia e uma grande variedade de interfaces de comunicação, como SPI, I2C, UART, ADC, DAC e PWM.

### Razão para Utilização:
O ESP32 é amplamente utilizado devido à sua versatilidade e custo-benefício. Neste projeto, ele é responsável por controlar o sistema e gerenciar a comunicação com os outros componentes. Sua conectividade Wi-Fi ou Bluetooth permite que ele se conecte à Internet ou a outros dispositivos, além de ser capaz de processar dados de sensores de forma eficiente. O baixo consumo de energia também torna o ESP32 ideal para sistemas embarcados que requerem operação por longos períodos sem necessidade de recarga frequente.

## 2. Módulo EBYTE LoRa E32900T20D

<p align="center">
  <img src="https://github.com/user-attachments/assets/8e00d34d-15f9-4cfd-8294-75cbdf1d9b20" alt="Fonte:cdebyte" width="400"/>
</p>
<p align="center">
  Fonte: <a href="https://www.cdebyte.com/products/E32-900T20D">cdebyte
</p>
      
### Descrição:
O módulo LoRa E32900T20D é um transceptor sem fio que utiliza a tecnologia LoRa (Long Range) para transmissão de dados a longas distâncias, utilizando baixo consumo de energia. Ele opera em frequências sub-giga hertz (como 433 MHz ou 915 MHz), o que permite que os sinais sejam transmitidos por longas distâncias (geralmente até 10-15 km em áreas abertas) com baixo consumo de energia e boa resistência a interferências.

### Razão para Utilização:
Este módulo é ideal para sistemas que precisam enviar dados a longas distâncias, especialmente em ambientes onde as redes de comunicação tradicionais, como Wi-Fi ou GSM, não são viáveis ou não têm cobertura adequada. A utilização do LoRa permite a comunicação em áreas remotas ou em locais de difícil acesso, com baixo consumo de energia e alta confiabilidade. No contexto do projeto, o módulo LoRa pode ser usado para enviar dados do sensor de temperatura e umidade para uma estação base ou servidor, utilizando pouca energia e cobrindo grandes distâncias.

## 3. Sensor de Temperatura e Umidade DHT22

<p align="center">
  <img src="https://github.com/user-attachments/assets/37cc7d90-2eab-460a-ada4-1ed84da9e27d" alt="Fonte:arduinoecia, 2015" width="400"/>
</p>
<p align="center">
  Fonte: <a href="https://www.arduinoecia.com.br/sensor-de-temperatura-e-umidade-dht22/">arduinoecia, 2015
</p>
      
### Descrição:
O DHT22 é um sensor digital de temperatura e umidade, capaz de medir a temperatura no intervalo de -40°C a 80°C e a umidade relativa de 0 a 100%, com uma boa precisão para a maioria das aplicações. Ele possui um sensor resistivo de umidade e um termistor para medir a temperatura, e a comunicação com o microcontrolador é feita através de um único pino digital, simplificando a integração.

### Razão para Utilização:
O DHT22 é utilizado devido à sua precisão e custo acessível. Ele oferece uma boa precisão para medições de temperatura e umidade em ambientes internos, tornando-o adequado para monitoramento ambiental. A comunicação digital do DHT22 também facilita a interface com o ESP32, o que simplifica o desenvolvimento do sistema. O sensor é ideal para o projeto de monitoramento remoto, onde o objetivo é coletar dados ambientais (temperatura e umidade) e transmiti-los a longas distâncias via LoRa.

## Resumo da Utilização dos Componentes no Projeto

- **ESP32**: Controla o sistema, processa os dados dos sensores e gerencia a comunicação com outros dispositivos via LoRa.
- **Módulo LoRa E32900T20D**: Permite a transmissão de dados a longas distâncias, utilizando a tecnologia LoRa, para enviar as leituras do sensor de temperatura e umidade.
- **Sensor DHT22**: Mede a temperatura e a umidade do ambiente, fornecendo dados que são coletados pelo ESP32 e enviados ao longo da rede LoRa para monitoramento remoto.

Esses componentes são escolhidos devido à sua combinação de baixo custo, baixa potência, facilidade de uso e capacidade de operação em ambientes com limitações de conectividade, oferecendo uma solução eficiente para o projeto.

## Referências

- Espressif Systems. ESP32 Wi-Fi & Bluetooth SoC. Disponível em: https://www.espressif.com/en/products/socs/esp32. Acesso em: 18 nov. 2024.
- EBYTE. LoRa/WiFi/BLE/ZigBee wireless modules Manufacturers, industrial IoT terminals suppliers. Disponível em: https://www.cdebyte.com. Acesso em: 17 nov. 2024.
- Aosong Electronics Co., Ltd. ASAIR Sensor. Disponível em: http://www.aosong.com/en/. Acesso em: 18 nov. 2024.
