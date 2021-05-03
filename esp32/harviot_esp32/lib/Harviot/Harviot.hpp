#include <HTTPClient.h>
#include <ArduinoWebsockets.h>
#include <esp_camera.h>
#include "camera_config.h"

#define AUTH_URI    "https://api.harviot.com/auth?entity=plant"
#define WS_URI_BASE "wss://api.harviot.com/?plant_id="
#define HTTP_HEADER_CONTENT_TYPE "Content-Type"

#define SHA_1 "48 50 4E 97 4C 0D AC 5B 5C D4 76 C8 20 22 74 B2 4C 8C 71 72"

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

        /**
         * @brief sets the onMessage callback
         * 
         * @param f the callback function 
         */
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
        char * ws_uri;
    const char *ssl_ca_cert = "-----BEGIN CERTIFICATE-----\n"\
    "MIIEZTCCA02gAwIBAgIQQAF1BIMUpMghjISpDBbN3zANBgkqhkiG9w0BAQsFADA/\n"\
    "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"\
    "DkRTVCBSb290IENBIFgzMB4XDTIwMTAwNzE5MjE0MFoXDTIxMDkyOTE5MjE0MFow\n"\
    "MjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxCzAJBgNVBAMT\n"\
    "AlIzMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuwIVKMz2oJTTDxLs\n"\
    "jVWSw/iC8ZmmekKIp10mqrUrucVMsa+Oa/l1yKPXD0eUFFU1V4yeqKI5GfWCPEKp\n"\
    "Tm71O8Mu243AsFzzWTjn7c9p8FoLG77AlCQlh/o3cbMT5xys4Zvv2+Q7RVJFlqnB\n"\
    "U840yFLuta7tj95gcOKlVKu2bQ6XpUA0ayvTvGbrZjR8+muLj1cpmfgwF126cm/7\n"\
    "gcWt0oZYPRfH5wm78Sv3htzB2nFd1EbjzK0lwYi8YGd1ZrPxGPeiXOZT/zqItkel\n"\
    "/xMY6pgJdz+dU/nPAeX1pnAXFK9jpP+Zs5Od3FOnBv5IhR2haa4ldbsTzFID9e1R\n"\
    "oYvbFQIDAQABo4IBaDCCAWQwEgYDVR0TAQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8E\n"\
    "BAMCAYYwSwYIKwYBBQUHAQEEPzA9MDsGCCsGAQUFBzAChi9odHRwOi8vYXBwcy5p\n"\
    "ZGVudHJ1c3QuY29tL3Jvb3RzL2RzdHJvb3RjYXgzLnA3YzAfBgNVHSMEGDAWgBTE\n"\
    "p7Gkeyxx+tvhS5B1/8QVYIWJEDBUBgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEE\n"\
    "AYLfEwEBATAwMC4GCCsGAQUFBwIBFiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2Vu\n"\
    "Y3J5cHQub3JnMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9jcmwuaWRlbnRydXN0\n"\
    "LmNvbS9EU1RST09UQ0FYM0NSTC5jcmwwHQYDVR0OBBYEFBQusxe3WFbLrlAJQOYf\n"\
    "r52LFMLGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjANBgkqhkiG9w0B\n"\
    "AQsFAAOCAQEA2UzgyfWEiDcx27sT4rP8i2tiEmxYt0l+PAK3qB8oYevO4C5z70kH\n"\
    "ejWEHx2taPDY/laBL21/WKZuNTYQHHPD5b1tXgHXbnL7KqC401dk5VvCadTQsvd8\n"\
    "S8MXjohyc9z9/G2948kLjmE6Flh9dDYrVYA9x2O+hEPGOaEOa1eePynBgPayvUfL\n"\
    "qjBstzLhWVQLGAkXXmNs+5ZnPBxzDJOLxhF2JIbeQAcH5H0tZrUlo5ZYyOqA7s9p\n"\
    "O5b85o3AM/OJ+CktFBQtfvBhcJVd9wvlwPsk+uyOy2HI7mNxKKgsBTt375teA2Tw\n"\
    "UdHkhVNcsAKX1H7GNNLOEADksd86wuoXvg==\n"\
    "-----END CERTIFICATE-----";

    // const char * ssl_ca_cert_2 = \
    //     "-----BEGIN CERTIFICATE-----\n"\
    //     "MIIFJjCCBA6gAwIBAgISA0GEvNd/wrd+sRLMl/crbS+pMA0GCSqGSIb3DQEBCwUA\n"\
    //     "MDIxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBFbmNyeXB0MQswCQYDVQQD\n"\
    //     "EwJSMzAeFw0yMTA1MDMwOTE4MjdaFw0yMTA4MDEwOTE4MjdaMBoxGDAWBgNVBAMT\n"\
    //     "D2FwaS5oYXJ2aW90LmNvbTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEB\n"\
    //     "AM0xcE9VOOSTSiWZEu7TyozneGGMDB5czxq0pJozC4vEPP7xZeFX3L48Df4WAbh9\n"\
    //     "tyXZ++xXGL9Gzm5w3+9HEd3Wgp4yXlH/QvpMtzm6w+ZuNmgy9IAsVsYYdceN/q+B\n"\
    //     "jgEg+SexnW5JKndeWKl8T0r3r78zqmDFE92IV5SUEn7RyJKi63vGAiyxoE5av5Rl\n"\
    //     "eRBDOJgdnYb2/Ow5IMQ4J4PuDJWXjWibSs15jkCmvY5IAQpl1rWLusAgHnzjinoF\n"\
    //     "R97WdqGhMC0xFkFGPyZdu3+D+MCRMo6tyKZMkQld0B3k7hQ1XOUK/U3l+LDV7YhG\n"\
    //     "IkiRu23tgvhYManLNWsJ6wECAwEAAaOCAkwwggJIMA4GA1UdDwEB/wQEAwIFoDAd\n"\
    //     "BgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwDAYDVR0TAQH/BAIwADAdBgNV\n"\
    //     "HQ4EFgQUr5Xwq6FB6CMXuqv83JBo+CGQWmUwHwYDVR0jBBgwFoAUFC6zF7dYVsuu\n"\
    //     "UAlA5h+vnYsUwsYwVQYIKwYBBQUHAQEESTBHMCEGCCsGAQUFBzABhhVodHRwOi8v\n"\
    //     "cjMuby5sZW5jci5vcmcwIgYIKwYBBQUHMAKGFmh0dHA6Ly9yMy5pLmxlbmNyLm9y\n"\
    //     "Zy8wGgYDVR0RBBMwEYIPYXBpLmhhcnZpb3QuY29tMEwGA1UdIARFMEMwCAYGZ4EM\n"\
    //     "AQIBMDcGCysGAQQBgt8TAQEBMCgwJgYIKwYBBQUHAgEWGmh0dHA6Ly9jcHMubGV0\n"\
    //     "c2VuY3J5cHQub3JnMIIBBgYKKwYBBAHWeQIEAgSB9wSB9ADyAHcARJRlLrDuzq/E\n"\
    //     "QAfYqP4owNrmgr7YyzG1P9MzlrW2gagAAAF5MbyA9gAABAMASDBGAiEAhMzx2+ul\n"\
    //     "Fv5ITFUpAEjGAY0b03M4XwTgZO0dj1TXz3QCIQD7KbYM3A0wHzvYXCU8eks3kkxO\n"\
    //     "abf2naTPikf2iaOT+AB3APZclC/RdzAiFFQYCDCUVo7jTRMZM7/fDC8gC8xO8WTj\n"\
    //     "AAABeTG8gO0AAAQDAEgwRgIhAJ+UOd6ebojjZvz1+vOysB5keQ019Rbbqjp3icLB\n"\
    //     "bBRkAiEAlvQi3/wZkT6HFTJPvcReV7F1NhITmWk9wCzrpG1YiQ0wDQYJKoZIhvcN\n"\
    //     "AQELBQADggEBADfxlsNHu4Aqlu7CrEgRpXb18EeojeTsa1KIyuHe7+4H2qd+HR4k\n"\
    //     "ud2e/OQ5cVdENi0TC+jiO7p1rsQ2WGl/jlLmH5eXG/Jf7UB/l9hN7WGqlwPXUtDz\n"\
    //     "XBOy1erc8zu1VQqCDoFwk05kaKUmcak59hs4XflDlcVY8Aokzo1IWjULXnebXGyV\n"\
    //     "cE5AQhgffesHWTmBnRt66oFaw5DOwwF46UerdhQu+wvlbpJJN/YDWQ4K3jydKmY/\n"\
    //     "zBv9ENdsqeSuRilMVyB7w8BUw2QRQY0W9SIepurqPL+orYbl8zKwpEOsgF84BhNQ\n"\
    //     "G5QgJ3T+xlHjAtuLtiy6oukbTQN7hYhBB2M=\n"\
    //     "-----END CERTIFICATE-----";
};