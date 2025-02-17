
# Receptor e Transmissor IR para ESP-32

## Funcionalidades:
- Decodificar sinal infravermelho
- Enviar sinal infravermelho
- Armazenar códigos emitidos pelo infravermelho por meio do método HTTP POST

---

<br>

## Instalação:

### Servidor Flask:
1. **Requisitos:**
   - Python
   - Flask
2. **Instalação do Flask (É recomendável instalar em um ambiente virtual):**
   ```bash
   pip install flask
   ```
3. **Configuração e Execução:**
   - Salve o arquivo `local_server.py` em um diretório.
   - Execute o servidor:
     ```bash
     python local_server.py
     ```
   - O servidor iniciará na porta 5000 e criará/atualizará o arquivo `ir_codigos.txt` com os códigos IR recebidos.

### ESP-32:
1. **Requisitos:**
   - Placa ESP-32
   - Arduino IDE ou outra ferramenta compatível com ESP-32
   - Bibliotecas necessárias:
     - `WiFi.h`
     - `HTTPClient.h`
     - `IRremote` (certifique-se de utilizar a versão compatível com ESP-32)
2. **Configuração:**
   - Abra o arquivo `infrared.ino` no Arduino IDE.
   - Atualize as variáveis:
     - `ssid` e `senha` com as credenciais da sua rede WiFi.
     - `rota` com o endereço do seu servidor Flask, por exemplo:
       ```
       const char* rota = "http://<endereco_ip>:5000/guardar-codigo";
       ```
3. **Upload:**
   - Compile e faça o upload do código para a placa ESP-32.

<br>

## Uso:
1. Inicie o servidor Flask executando:
   ```bash
   python local_server.py
   ```
2. Conecte a placa ESP-32 à sua rede WiFi e faça o upload do código.
3. Aponte um controle remoto IR ou outro emissor de sinal IR para o receptor conectado à ESP-32.
4. A placa capturará o sinal IR, enviará os dados para o servidor via HTTP POST e também retransmitirá o sinal IR.
5. Confira:
   - O **Serial Monitor** da ESP-32 para acompanhar as mensagens de status.
   - O arquivo `ir_codigos.txt` para verificar os códigos IR armazenados.