#include <HTTPClient.h>
#include <ArduinoWebsockets.h>
#include <esp_camera.h>
#include "camera_config.h"

#define AUTH_URI    "http://192.168.1.239:8080/auth?entity=plant"
#define WS_URI_BASE "ws://192.168.1.239:8080/?plant_id="
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
        String getAuthToken();

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

        void initCamera();
        bool captureFrame(void (*f)(camera_fb_t *));
        void WsSendBinary(const char * data, size_t size);

        bool logData(const float *data);


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
        String auth_token;
        camera_config_t camera_config;
        camera_fb_t *fb;
        const char *ntp_server = "pool.ntp.org";
        const long gmt_offset_sec = 14400;
        const int daylight_offset_sec = 3600;
};