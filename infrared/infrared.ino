#include <WiFi.h>
#include <HTTPClient.h>
#include <IRremote.hpp>

const char* ssid = "ssid"; // Coloque o nome da sua rede WiFi
const char* senha = "senha"; // Coloque a senha da sua rede WiFi

const char* rota = "endereco/rota"; 

const int IR_RECEIVE_PIN = 15; // GPIO15
const int IR_SENDER_PIN = 16; // GPIO16
uint32_t codigoIR = 0;

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

    if (IrReceiver.decode()) {
        codigoIR = IrReceiver.decodedIRData.decodedRawData;    

        if (codigoIR != 0) {
            String jsonData = "{\"codigo\":\"" + String(codigoIR, HEX) + "\"}";
            
            Serial.println("Transmitindo código IR...");
            IrSender.sendNEC(codigoIR, 32);
            delay(500);
            Serial.println("Código IR transmitido");

            HTTPClient http;
            
            http.begin(rota);
            http.addHeader("Content-Type", "application/json");
            
            int httpResponse = http.POST(jsonData);
            
            if (httpResponse > 0) {
                String response = http.getString();
                Serial.println("Código IR enviado: 0x" + String(codigoIR, HEX));
                Serial.println("Resposta do servidor: " + response);
            } else {
                Serial.println("Erro no envio do código IR");
            }           
            http.end();
        }      
        IrReceiver.resume();
    }
    delay(100);
}