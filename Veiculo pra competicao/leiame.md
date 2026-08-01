# Sistema de Telemetria e Aquisição de Dados - Minerva BAJA SAE 🏁

Este repositório contém o código-fonte do sistema eletrônico embarcado do nosso veículo BAJA SAE. O projeto utiliza o microcontrolador **ESP32** devido ao seu poder de processamento dual-core e capacidade de comunicação sem fio nativa (ESP-NOW).

## 📌 Visão Geral do Projeto

Para garantir a confiabilidade dos dados e a segurança elétrica do sistema, dividimos a arquitetura em duas unidades de processamento distintas: a **Central de Aquisição de Dados (DAQ)** e o **Painel do Piloto (Dashboard)**.

Elas se comunicam **sem fio** através do protocolo **ESP-NOW**, que funciona de forma direta (ponto a ponto), sem necessidade de roteador Wi-Fi, garantindo baixíssima latência e imunidade a ruídos elétricos do motor.

---

## 🏗️ A Arquitetura (DAQ + Dashboard)

### 1. ESP 1: Central DAQ (A "Caixa Preta")
Fica localizada na parte traseira/protegida do carro. É responsável pelo trabalho pesado.
* **Função:** Ler todos os sensores físicos do carro.
* **Datalogger (Cartão SD):** Funciona como uma caixa preta. Salva absolutamente todos os dados lidos (em alta frequência) em um arquivo `.csv` no cartão MicroSD. Esses dados serão usados pela equipe de engenharia nos boxes para análise de desempenho (dinâmica, CVT, freios).
* **Transmissão:** Filtra os dados críticos e monta um pacote leve ("mastigado") contendo apenas o que o piloto precisa saber, enviando-o via rádio para o painel.

### 2. ESP 2: Painel do Piloto (Dashboard)
Fica no volante do veículo. Completamente isolado dos ruídos de 12V e da fiação pesada do motor.
* **Função:** Receber o pacote de dados filtrado da Central via ESP-NOW.
* **Exibição:** Atualizar a tela (Display OLED/TFT) em tempo real, informando ao piloto apenas o essencial, além de emitir alertas visuais (ex: Temperatura Alta).

---

## 🔌 Sensores e Variáveis Monitoradas

O sistema foi desenhado para integrar os seguintes sensores:

| Grandeza | Sensor Utilizado | Protocolo / Pino |
| :--- | :--- | :--- |
| **Velocidade & RPM da Roda** | Sensor Magnético / Indutivo | Pulso Digital (Interrupção) |
| **RPM do Motor** | Sensor Magnético / Indutivo | Pulso Digital (Interrupção) |
| **Nível de Combustível** | Sensor Capacitivo | Sinal Analógico (ADC) |
| **Tensão da Bateria** | Divisor de Tensão (Resistores) | Sinal Analógico (ADC) |
| **Temperatura do Motor** | Termopar (Módulo SPI) | SPI |
| **Temperatura da CVT** | Infravermelho (A Implementar) | I2C |
| **Dinâmica do Chassi** | Acelerômetro | I2C |
| **Posicionamento** | Módulo GPS | Serial (UART2) |

---

## 🛠️ Como o Código Está Estruturado (Modularidade)

Como ainda estamos aguardando a definição final dos modelos de alguns sensores, o código da **Central (ESP 1)** foi escrito de forma **modular**. 

No arquivo principal, você encontrará funções separadas para cada grupo de leitura, como:
* `lerRPMeVelocidade()`
* `lerBateriaCombustivel()`
* `lerTemperaturas()`
* `lerGPSeAcelerometro()`

**Regra para os Desenvolvedores da Equipe:**
Atualmente, essas funções possuem "valores falsos" (dummy data) para fins de teste da comunicação de rádio e Datalogger. Assim que um sensor real for definido:
1. Adicione a biblioteca correspondente no topo do arquivo.
2. Configure os pinos no `setup()`.
3. Substitua o valor falso dentro da função específica pela leitura real do sensor.
4. **Não altere** a lógica de envio (ESP-NOW) ou a estrutura de dados sem avisar o restante da equipe, pois isso quebrará a compatibilidade com o ESP 2 (Painel).

---

## 📍 Pinagem Oficial (ESP 1 - Central)

Para evitar queima de portas ou conflitos nos barramentos de comunicação, **siga estritamente** este mapa de pinos ao conectar os sensores na placa:

* **Sinais Analógicos (Seguros, apenas leitura):**
  * `34`: Tensão da Bateria
  * `35`: Nível de Combustível
* **Interrupções (Pulsos de RPM):**
  * `4`: RPM da Roda (Requer Optoacoplador para 12V)
  * `25`: RPM do Motor (Requer Optoacoplador para 12V)
* **Barramento I2C (Acelerômetro e Temp. IR):**
  * `21`: SDA (Dados)
  * `22`: SCL (Clock)
* **Barramento Serial/UART2 (GPS):**
  * `16`: RX2 (Conectar ao TX do módulo GPS)
  * `17`: TX2 (Conectar ao RX do módulo GPS)
* **Barramento SPI (Cartão SD e Termopar):**
  * `18`: SCK (Clock compartilhado)
  * `19`: MISO (Dados In compartilhado)
  * `23`: MOSI (Dados Out compartilhado)
  * `5`: CS (Chip Select do Cartão SD)
  * `13`: CS (Chip Select do Termopar)

> **Atenção Hardware:** O ESP32 opera em **3.3V**. NUNCA conecte sinais de 5V ou 12V (direto do chicote do Baja) nos pinos digitais ou analógicos sem antes passar por um divisor de tensão ou optoacoplador.