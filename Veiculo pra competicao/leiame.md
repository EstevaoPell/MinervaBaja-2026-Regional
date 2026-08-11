# Sistema de Telemetria e Aquisição de Dados - Minerva BAJA SAE 🏁

Este repositório contém o código-fonte do sistema eletrônico embarcado do veículo BAJA SAE da Minerva. O projeto utiliza microcontroladores **ESP32** devido ao seu alto poder de processamento e capacidades de comunicação sem fio (ESP-NOW e LoRa).

---

## 📂 Estrutura de Pastas e Organização do Projeto:

Este repositório foi desenvolvido utilizando o **PlatformIO** no VS Code. O sistema está dividido em três projetos independentes, cada um correspondente a um microcontrolador da arquitetura:

1. **Caixa Preta (ESP 3):**
   * Caminho: `Caixa_Preta_ESP3/src/main.cpp`
   * Função: Módulo dinâmico independente.
2. **Central DAQ (ESP 1):**
   * Caminho: `ESP1 projeto/src/main.cpp`
   * Função: Cérebro integrador e central de processamento do chassi.
3. **Painel do Piloto (ESP 2):**
   * Caminho: `ESP2 projeto/src/main.cpp`
   * Função: Dashboard no volante com display OLED.

---

## 🏗️ A Nova Arquitetura de 3 ESPs (Fluxo de Dados)

Para garantir máxima eficiência, modularidade e confiabilidade, o sistema opera em cascata:

### 1. ESP 3: A Caixa Preta (Módulo Dinâmico)
Fica encarregada de medir a dinâmica do veículo de forma autônoma.
* **Sensores:** Módulo GPS (posicionamento e velocidade via satélite) e MPU6050 (Acelerômetro e Giroscópio).
* **Comunicação:** Possui um rádio **LoRa** para transmitir os dados de dinâmica em longo alcance diretamente para os boxes (engenharia), além de repassar os dados de velocidade para o ESP 1.

### 2. ESP 1: A Central DAQ (O Cérebro do Chassi)
Fica localizada na parte traseira/protegida do carro e centraliza todas as informações do veículo.
* **Entradas Locais (Sensores Físicos):**
  * Tensão da Bateria do carro (via circuito divisor de tensão).
  * Nível de Combustível (Sensor Capacitivo).
  * Rotação do Motor (Sensor Indutivo/Magnético com interrupção).
  * Rotação da Roda / Freio (Sensor Indutivo/Magnético com interrupção).
  * Temperatura da CVT.
* **Integração:** Recebe os dados dinâmicos da Caixa Preta (ESP 3), junta com as leituras locais, empacota tudo e transmite o pacote filtrado para o volante via **ESP-NOW**.

### 3. ESP 2: O Painel do Piloto (Dashboard)
Fica fixado no volante, isolado dos ruídos elétricos do motor.
* **Função:** Recebe o pacote de dados processado da Central (ESP 1) via ESP-NOW.
* **Exibição:** Atualiza dinamicamente o display OLED em tempo real com as informações vitais para o piloto (velocidade, bateria, combustível, temperatura).

---

## 📍 Pinagem Oficial (ESP 1 - Central DAQ)

Para evitar danos por sobretensão e conflitos de barramento, siga estritamente este mapa de pinos na Central:

* **Sinais Analógicos (Entradas Seguras / ADC):**
  * `PIN_BAT_ADC (34)`: Tensão da Bateria (Sinal do divisor de tensão)
  * `PIN_COMB_ADC (35)`: Nível de Combustível (Sensor Capacitivo)
* **Interrupções Digitais (Pulsos de Giro):**
  * `PIN_RPM_RODA (4)`: Sensor Indutivo da Roda (Requer Optoacoplador)
  * `PIN_RPM_MOTOR (25)`: Sensor Indutivo do Motor (Requer Optoacoplador)

> **⚠️ Alerta de Hardware:** O ESP32 opera estritamente em **3.3V**. Jamais conecte sinais de 12V diretamente aos pinos digitais ou analógicos sem utilizar divisores de tensão ou optoacopladores adequados.