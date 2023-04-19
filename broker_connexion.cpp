#include <iostream>
#include <mqtt/async_client.h>

using namespace std;


// Définition des constantes: adresse serveur, ID client et topic.
const string BROKER_ADDRESS = "mqtt://broker.emqx.io:1883";
const string CLIENT_ID = "mqtt_marion";
const string TOPIC = "/ynov/bordeaux/";

int main() 
{
    // Création d'un objet client asynchrone et configuration des options de connexion
    mqtt::async_client client(BROKER_ADDRESS, CLIENT_ID);
    mqtt::connect_options options;
    options.set_keep_alive_interval(20);
    options.set_clean_session(true);

    // Test de connexion
    cout << "Connexion en cours..." << flush; // Tentative de connexion
    try {
        mqtt::token_ptr connection_token = client.connect(options);
        connection_token->wait();
        cout << "OK" << endl;
    }
    catch (const mqtt::exception& e) {
        cerr << "Erreur de connexion : " << e.what() << endl; // Tentative échouée
        return 1;
    }

    // Boucle while permettant à l'utilisateur d'écrire son message
    while (true) {
        try {
            string payload;
            cout << "Entrez le message : "; // Propose à l'utilisateur d'écrire
            getline(cin, payload);

            mqtt::message_ptr message = mqtt::make_message(TOPIC, payload);
            client.publish(message)->wait();
        }
        catch (const mqtt::exception& e) {
            cerr << "Erreur de publication : " << e.what() << endl; // La publication n'a pas fonctionné
            break;
        }
    }

    // Déconnexion propre de l'utilisateur
    try {
        mqtt::token_ptr disconnection_token = client.disconnect();
        disconnection_token->wait();
        cout << "Déconnexion réussie" << endl; // La déconnexion à réussi
    }
    catch (const mqtt::exception& e) {
        cerr << "Erreur de déconnexion : " << e.what() << endl; // La déconnexion a échouée
        return 1;
    }

    return 0;
}
   	// Validation publication
    cout << "Message publié" << endl;
