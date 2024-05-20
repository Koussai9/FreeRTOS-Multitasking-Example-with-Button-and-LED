#include <Arduino_FreeRTOS.h>

const int boutonPin = 2;

// Broche des LED
const int ledPin13 = 13;
const int ledPin12 = 12;

// État de la LED 12
bool etatLed12 = false;

void tacheClignotement(void *pvParameters) {
  while(1) {
    digitalWrite(ledPin13, HIGH);
    vTaskDelay(pdMS_TO_TICKS(2000)); // Attendre
    digitalWrite(ledPin13, LOW);
    vTaskDelay(pdMS_TO_TICKS(1000)); // Attendre
  }
}
void tacheAnalog(void *pvParameters) {
  while(1) {
    analogRead(A0);
    vTaskDelay(pdMS_TO_TICKS(1000)); // Attendre

  }
}

// Tâche pour la détection du bouton-poussoir
void tacheBouton(void *pvParameters) {
  pinMode(boutonPin, INPUT_PULLUP);
  while(1) {
    if(digitalRead(boutonPin) == LOW) {
      etatLed12 = !etatLed12;
      digitalWrite(ledPin12, etatLed12 ? HIGH : LOW);
      vTaskDelay(pdMS_TO_TICKS(200)); // Attendre pour éviter les rebonds
    }
    vTaskDelay(pdMS_TO_TICKS(20)); // Attendre pour éviter les rebonds
  }
}

void setup() {
  // Initialisation des broches
  pinMode(ledPin13, OUTPUT);
  pinMode(ledPin12, OUTPUT);
  // Création des tâches FreeRTOS
  
  xTaskCreate(tacheAnalog, "Analog", 128, NULL, 3, NULL);
  xTaskCreate(tacheClignotement, "Clignotement", 128, NULL, 2, NULL);
  xTaskCreate(tacheBouton, "Bouton", 128, NULL, 1, NULL);

  // Démarrage du planificateur FreeRTOS
  vTaskStartScheduler();
}

void loop() {
  // Cette fonction ne sera jamais atteinte car FreeRTOS gère la boucle principale
}
