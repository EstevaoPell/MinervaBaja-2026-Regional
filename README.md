# ⚡ Eletrônica e Telemetria - Minerva Baja

Bem-vindo ao repositório oficial do subsistema de **Eletrônica** da equipe **Minerva Baja - UFRJ**.

Este repositório concentra todo o código-fonte (firmware), projetos de hardware (PCBs) e documentação técnica do nosso sistema embarcado.

## 📌 Escopo do Projeto
O sistema eletrônico é responsável por garantir a segurança, aquisição de dados e controle térmico do veículo. Os principais módulos incluem:
- **Telemetria via rádio:** Monitoramento em tempo real do veículo utilizando microcontroladores ESP32 e comunicação LoRa.
- **Sensoriamento:** - Temperatura (Infravermelho MLX90614, Termistores)
  - Dinâmica (Acelerômetro MMA8452, GPS NEO 6M)
  - Powertrain (Pressão 4-20mA, TPS, Tensão e Corrente)
- **Controle Térmico:** Gerenciamento das ventoinhas de resfriamento com sinais PWM integrados a sistemas 48V e 12V.
- **Segurança:** Sistema de Kill Switch e luz de freio em conformidade com o Regulamento BAJA SAE 2025.

## 📂 Estrutura do Repositório
- `/docs`: Regulamentos da SAE, manuais de telemetria, pinouts e relatórios técnicos.
- `/firmware`: Códigos desenvolvidos (C/C++) para ESP32 DevKit V1, WROOM e LoRa V2.
- `/hardware`: Esquemáticos elétricos e projetos de placas de circuito impresso (PCB) no EasyEDA.
- `/mecanica_eletronica`: Modelagem 3D das cases de proteção para as PCBs e suporte para baterias 18650.

## 🛠️ Tecnologias e Ferramentas Utilizadas
* **Hardware base:** ESP32, Arduino Nano, Arduino Pro Mini
* **Software:** Arduino IDE, EasyEDA (Projeto de PCB), Software CAD 3D
* **Protocolos:** I2C, SPI, UART, Sinais Analógicos e PWM

## 🚀 Como Contribuir (Para Membros e Trainees)
1. Faça o clone do repositório:
   ```bash
   git clone https://github.com/NatalNoUnturned/Minerva-Baja-Eletronica.git

2. Para abrir a pasta pelo VScode mesmo use no terminal:
   ```bash
   cd Minerva-Baja-Eletronica
   
   ```bash
   code .