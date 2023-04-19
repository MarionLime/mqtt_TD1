#include <iostream>
#include <mqtt/client.h>

using namespace std;

// Définition des constantes: adresse serveur, ID client et topic.
const string SERVER_ADDRESS = "broker.emqx.io:1883";
const string CLIENT_ID = "mqtt_marion";
const string TOPIC = "/ynov/bordeaux/";

// Classe de rappel pour gérer les événements client
class MqttCallback : public virtual mqtt::callback {
public:
    // La méthode message_arrived affiche les messages reçu sur le topic
    void message_arrived(mqtt::const_message_ptr msg) override {
        cout << "Message reçu: " << msg->to_string() << endl;
    }
};

int main() {
    try {
        // Création du client MQTT et configuration des options de connexion
        mqtt::client client(SERVER_ADDRESS, CLIENT_ID);
        mqtt::connect_options options;
        options.set_keep_alive_interval(20);
        options.set_clean_session(true);

        // Création de l'objet Callback pour gérer les événements client
        MqttCallback callback;

        // Configuration du callback client
        client.set_callback(callback);

        // Connexion au broker
        cout << "Connexion en cours..." << flush;
        client.connect(options);
        cout << "OK" << endl;

        // Abonnement au topic
        cout << "Souscription au topic '" << TOPIC << "'..." << flush;
        client.subscribe(TOPIC, 0);
        cout << "OK" << endl;

        // Boucle infinie pour maintenir le client connecté et traiter les événements
        while (true) {
            // Ajouter du code ici pour publier des messages sur le topic spécifié
        }

        // Déconnexion du broker MQTT
        client.disconnect();
    }
    catch (const mqtt::exception& exc) {
        cerr << "Erreur: " << exc.what() << endl;
        return 1;
    }

    return 0;
}