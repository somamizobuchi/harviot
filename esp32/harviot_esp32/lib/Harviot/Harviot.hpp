#include <HTTPClient.h>
#include <ArduinoWebsockets.h>

#define AUTH_URI "http://api.harviot.com/auth?entity=plant"
#define WS_URI_BASE "ws://api.harviot.com/plant_id="
#define HTTP_HEADER_CONTENT_TYPE "Content-Type"

class Harviot {
    public:
        /**
         * @brief Construct a new Harviot object
         * 
         * @param plant_id The ID of the plant
         * @param password The password used to retrive the authorization token
         */
        Harviot(const char *plant_id, const char *password);

        void init();

        /**
         * @brief Request an authorization token (cookie) from the Harviot API
         * 
         */
        void requestAuthToken();

        /**
         * @brief Get the authorization token
         * 
         * @return const char* The token
         */
        const char * getAuthToken();

        /**
         * @brief Connect to the Harviot websocket
         * 
         */
        void wsConnect();

        void wsOnMessage(void (*f)(websockets::WebsocketsMessage));

        /**
         * @brief Poll the websocket connection
         * 
         */
        void poll();
    private:
        /**
         * @brief Http client instance
         */
        HTTPClient http_client;
        /**
         * @brief ArduinoWebsockets Client isntance
         */
        websockets::WebsocketsClient ws;
        const char *plant_id;
        const char *password;
        const char *auth_token;
};