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
- `/Arquivos antigos`: Nesta pasta contem todos os documentos antigos de membros antigos da equipe, informando sobre a maior parte (ou tudo) do nosso veiculo H2.
- `/Veiculo pra competicao`: Aqui estarao os codigos do nosso ESP32 para o veiculo de competicao de 2026.

## 🛠️ Tecnologias e Ferramentas Utilizadas
* **Hardware base:** ESP32 DEV KIT
* **Software:** VSCode com PlatformIO, EasyEDA (Projeto de PCB), SolidWorks e EnderIO
* **Protocolos:** I2C, SPI, UART, Sinais Analógicos e PWM

## 🚀 Como Contribuir (Para Membros e Trainees)
1. Faça o clone do repositório:
   ```bash
   git clone https://github.com/NatalNoUnturned/Minerva-Baja-Eletronica.git

2. Para abrir a pasta pelo VScode mesmo use no terminal:
   ```bash
   cd Minerva-Baja-Eletronica
   ```
   Em seguida use:
   ```bash
   code .