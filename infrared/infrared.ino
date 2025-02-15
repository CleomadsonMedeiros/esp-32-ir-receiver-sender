#include <WiFi.h>
#include <HTTPClient.h>
#include <IRremote.hpp>

const char* ssid = "ssid"; // Coloque o nome da sua rede WiFi
const char* senha = "senha"; // Coloque a senha da sua rede WiFi

const char* rota = "coloque_aqui_a_url_do_seu_servidor";

const int IR_RECEIVE_PIN = 15; // GPIO15
const int IR_SENDER_PIN = 16; // GPIO16
uint32_t irCode = 0;

void setup() {
    Serial.begin(115200);
    
    WiFi.begin(ssid, senha);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }
    Serial.println("Conectado ao WiFi");
    
    IrReceiver.begin(IR_RECEIVE_PIN);
    Serial.println("Receptor IR iniciado");
    IrSender.begin(IR_SENDER_PIN);
    Serial.println("Transmissor IR iniciado");
}

void loop() {

    // Recebe o código IR
    if (IrReceiver.decode()) 
    {
        irCode = IrReceiver.decodedIRData.decodedRawData;
        if (irCode != 0) 
        {
            String jsonData = "{\"code\":\"" + String(irCode, HEX) + "\"}";

            HTTPClient http;
            http.begin(rota);
            http.addHeader("Content-Type", "application/json");
            
            int httpResponseCode = http.POST(jsonData);

            if (httpResponseCode > 0) 
            {
                String response = http.getString();
                Serial.println("Código IR enviado: 0x" + String(irCode, HEX));
                Serial.println("Resposta do servidor: " + response);
            } 
            else 
            {
                Serial.println("Erro no envio do código IR");
            }           
            
            http.end();
        }      
        IrReceiver.resume();
    }

    // Transmite o código IR em loop o último código recebido
    if (irCode != 0) {
        Serial.println("Transmitindo código IR...");
        IrSender.sendNECRaw(irCode, 32); // Adapte o número de bits conforme o protocolo do seu controle remoto
        delay(500);
        Serial.println("Código IR transmitido");
    }
    delay(100);
}