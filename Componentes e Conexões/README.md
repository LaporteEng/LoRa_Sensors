# Componentes e Conexões

Neste diretório, serão apresentados os compenentes utilizados e suas conexões.

A seguir, é possível visualizar um diagrama de blocos que descreve o projeto.

![Diagrama de Blocos](DiagramaDeBlocos.png)

Conforme apresentado no diagrama, é composto por:
1. Hardware:
    - Sensores de temperatura.
    - Módulos de comunicação LoRa.
    - Microcontroladores ESP32.
    - Fontes de alimentação e baterias.
      
2. Software:
    - Firmware para ESP32 para ler dados dos sensores e transmitir via LoRa.
    - Microcontrolador receptor para receber dados via LoRa e exibi-los.
    - Interface web ou painel para exibir dados em tempo real.
