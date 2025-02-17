# 📂 Software

O projeto visa implementar a conexão de **dois módulos LoRa**, um atuando como **transmissor** e outro como **receptor**, ambos conectados a **microcontroladores ESP32**. A mensagem é enviada pelo módulo transmissor e recebida pelo módulo receptor, que está conectado à internet. Utiliza-se um **servidor HTTP** para visualizar a mensagem recebida na web. 💻

## 🔧 Componentes Utilizados

Os principais componentes utilizados neste projeto são:

- **ESP32**: Microcontrolador com capacidades de WiFi e Bluetooth. 🌐
- **Rede WiFi**: Rede sem fio à qual o ESP32 se conectará. 📶
- **Computador**: Para programar o ESP32 e acessar o servidor HTTP. 🖥️
- **Módulo LoRa Transmissor**: Envia dados via comunicação LoRa. 📡
- **Módulo LoRa Receptor**: Recebe dados via comunicação LoRa. 📡

## 📝 Passos para Implementação

1. **Configuração do Ambiente de Desenvolvimento**: Utilização da **Arduino IDE** para programar o ESP32.
2. **Conexão à Rede WiFi**: Configuração do ESP32 para conectar-se a uma rede WiFi específica.
3. **Servidor HTTP**: Implementação de um servidor HTTP no ESP32 para servir uma página HTML e uma rota para obter a mensagem recebida via LoRa.

---

# 💡 Módulo Receptor

Para fornecer um feedback visual simples sobre o status da conexão do dispositivo, o sistema foi configurado para acender um **LED no pino 2** caso o dispositivo esteja conectado. Se a conexão não for estabelecida, o LED é apagado. 🌟

<p align="center">
  <img src="https://github.com/user-attachments/assets/016124d6-8570-42e8-bba4-a61b911204e3" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>

Quando o ESP32 se conecta à rede, ele imprime uma mensagem de sucesso junto com o **endereço IP** atribuído. Caso a conexão falhe, uma mensagem informando a falha na conexão é exibida. Para atualizar a mensagem e exibi-la em uma página web, foi implementado um servidor HTTP no ESP32 que serve uma página HTML e uma rota para obter o valor atual da mensagem. O servidor HTTP permite que o microcontrolador se comunique com outros dispositivos na rede, como computadores, smartphones ou outros sistemas conectados. 📱💻

Para possibilitar a comunicação sem fio entre os módulos LoRa, foram implementadas as bibliotecas **LoRa** no código, permitindo que o ESP32 envie e receba dados via LoRa de forma eficiente. 🔄

<p align="center">
  <img src="https://github.com/user-attachments/assets/e0c72889-0d22-43ac-be24-733d3ff92f0f" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>

Para acessar o servidor HTTP do ESP32, basta obter o **endereço IP** exibido no terminal serial após a conexão com o Wi-Fi e inseri-lo na barra de endereços de um navegador (**http://<IP_do_ESP32>/**). Isso permitirá visualizar a página gerada pelo servidor, como a mensagem sendo atualizada em tempo real. 🌍

<p align="center">
  <img src="https://github.com/user-attachments/assets/ae5fcb1c-3d9f-41fa-af3f-fb4745dfb950" alt="Fonte: Xprojetos, 2019." width="400"/>
</p>

---

# 🛠️ Módulo Transmissor

O código configura o **ESP32** e o **módulo LoRa** para comunicação sem fio. Ele permite que o usuário envie **mensagens** através do **monitor serial**, que são então transmitidas via LoRa. O módulo LoRa é configurado com uma taxa de dados, endereço e canal específicos, e o **status da transmissão** é exibido no monitor serial.

---

# 📚 Referências

- **USINA INFO**. ESP32 e Wi-Fi: Como Funciona a Comunicação com a Internet. 2024. Disponível em: [Usina Info](https://www.usinainfo.com.br/blog/esp32-wifi-comunicacao-com-a-internet/). Acesso em: 13 dez. 2024.
- **LABORATÓRIO DO ESP32**. ESP32: Conectando-se à Internet via Wi-Fi. 2024. Disponível em: [YouTube - Laboratório do ESP32](https://www.youtube.com/watch?v=FFPocTxOgmQ). Acesso em: 13 dez. 2024.
- **ESP32IO.COM**. ESP32 Web Server Tutorial. Disponível em: [ESP32 IO](https://esp32io.com/tutorials/esp32-web-server). Acesso em: 14 dez. 2024.
- **YOUTUBE**. LoRa EBYTE trocando mensagens - EBYTE E32. YouTube, 2023. Disponível em: [YouTube - LoRa EBYTE](https://www.youtube.com/watch?v=Obb9QtNuG1M). Acesso em: 15 dez. 2024.
- **KASPRZAK, Kris**. EBYTE. 2024. Disponível em: [GitHub - Kris Kasprzak](https://github.com/KrisKasprzak/EBYTE). Acesso em: 15 dez. 2024.
