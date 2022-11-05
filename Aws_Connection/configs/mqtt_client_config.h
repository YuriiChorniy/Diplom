/******************************************************************************
* File Name:   mqtt_client_config.h
*
* Description: This file contains all the configuration macros used by the
*              MQTT client in this example.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2020-2022, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

#ifndef MQTT_CLIENT_CONFIG_H_
#define MQTT_CLIENT_CONFIG_H_

#include "cy_mqtt_api.h"

/*******************************************************************************
* Macros
********************************************************************************/

/***************** MQTT CLIENT CONNECTION CONFIGURATION MACROS *****************/
/* MQTT Broker/Server address and port used for the MQTT connection. */
#define MQTT_BROKER_ADDRESS               "a2orq4j7y3m75h-ats.iot.eu-central-1.amazonaws.com"
#define MQTT_PORT                         8883

/* Set this macro to 1 if a secure (TLS) connection to the MQTT Broker is  
 * required to be established, else 0.
 */
#define MQTT_SECURE_CONNECTION            ( 1 )

/* Configure the user credentials to be sent as part of MQTT CONNECT packet */
#define MQTT_USERNAME                     "User"
#define MQTT_PASSWORD                     ""


/********************* MQTT MESSAGE CONFIGURATION MACROS **********************/
/* The MQTT topics to be used by the publisher and subscriber. */
#define MQTT_PUB_TOPIC                    "ledstatus"
#define MQTT_SUB_TOPIC                    "ledstatus"

/* Set the QoS that is associated with the MQTT publish, and subscribe messages.
 * Valid choices are 0, 1, and 2. Other values should not be used in this macro.
 */
#define MQTT_MESSAGES_QOS                 ( 1 )

/* Configuration for the 'Last Will and Testament (LWT)'. It is an MQTT message 
 * that will be published by the MQTT broker if the MQTT connection is 
 * unexpectedly closed. This configuration is sent to the MQTT broker during 
 * MQTT connect operation and the MQTT broker will publish the Will message on 
 * the Will topic when it recognizes an unexpected disconnection from the client.
 * 
 * If you want to use the last will message, set this macro to 1 and configure
 * the topic and will message, else 0.
 */
#define ENABLE_LWT_MESSAGE                ( 0 )
#if ENABLE_LWT_MESSAGE
    #define MQTT_WILL_TOPIC_NAME          MQTT_PUB_TOPIC "/will"
    #define MQTT_WILL_MESSAGE             ("MQTT client unexpectedly disconnected!")
#endif

/* MQTT messages which are published on the MQTT_PUB_TOPIC that controls the
 * device (user LED in this example) state in this code example.
 */
#define MQTT_DEVICE_ON_MESSAGE            "TURN ON"
#define MQTT_DEVICE_OFF_MESSAGE           "TURN OFF"


/******************* OTHER MQTT CLIENT CONFIGURATION MACROS *******************/
/* A unique client identifier to be used for every MQTT connection. */
#define MQTT_CLIENT_IDENTIFIER            "psoc6-mqtt-client"

/* The timeout in milliseconds for MQTT operations in this example. */
#define MQTT_TIMEOUT_MS                   ( 5000 )

/* The keep-alive interval in seconds used for MQTT ping request. */
#define MQTT_KEEP_ALIVE_SECONDS           ( 60 )

/* Every active MQTT connection must have a unique client identifier. If you 
 * are using the above 'MQTT_CLIENT_IDENTIFIER' as client ID for multiple MQTT 
 * connections simultaneously, set this macro to 1. The device will then
 * generate a unique client identifier by appending a timestamp to the 
 * 'MQTT_CLIENT_IDENTIFIER' string. Example: 'psoc6-mqtt-client5927'
 */
#define GENERATE_UNIQUE_CLIENT_ID         ( 1 )

/* The longest client identifier that an MQTT server must accept (as defined
 * by the MQTT 3.1.1 spec) is 23 characters. However some MQTT brokers support 
 * longer client IDs. Configure this macro as per the MQTT broker specification. 
 */
#define MQTT_CLIENT_IDENTIFIER_MAX_LEN    ( 23 )

/* As per Internet Assigned Numbers Authority (IANA) the port numbers assigned 
 * for MQTT protocol are 1883 for non-secure connections and 8883 for secure
 * connections. In some cases there is a need to use other ports for MQTT like
 * port 443 (which is reserved for HTTPS). Application Layer Protocol 
 * Negotiation (ALPN) is an extension to TLS that allows many protocols to be 
 * used over a secure connection. The ALPN ProtocolNameList specifies the 
 * protocols that the client would like to use to communicate over TLS.
 * 
 * This macro specifies the ALPN Protocol Name to be used that is supported
 * by the MQTT broker in use.
 * Note: For AWS IoT, currently "x-amzn-mqtt-ca" is the only supported ALPN 
 *       ProtocolName and it is only supported on port 443.
 * 
 * Uncomment the below line and specify the ALPN Protocol Name to use this 
 * feature.
 */
#define MQTT_ALPN_PROTOCOL_NAME           "x-amzn-mqtt-ca"

/* Server Name Indication (SNI) is extension to the Transport Layer Security 
 * (TLS) protocol. As required by some MQTT Brokers, SNI typically includes the 
 * hostname in the Client Hello message sent during TLS handshake.
 * 
 * Uncomment the below line and specify the SNI Host Name to use this extension
 * as specified by the MQTT Broker.
 */
// #define MQTT_SNI_HOSTNAME                 "SNI_HOST_NAME"

/* A Network buffer is allocated for sending and receiving MQTT packets over 
 * the network. Specify the size of this buffer using this macro.
 * 
 * Note: The minimum buffer size is defined by 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE' 
 * macro in the MQTT library. Please ensure this macro value is larger than 
 * 'CY_MQTT_MIN_NETWORK_BUFFER_SIZE'.
 */
#define MQTT_NETWORK_BUFFER_SIZE          ( 2 * CY_MQTT_MIN_NETWORK_BUFFER_SIZE )

/* Maximum MQTT connection re-connection limit. */
#define MAX_MQTT_CONN_RETRIES            (150u)

/* MQTT re-connection time interval in milliseconds. */
#define MQTT_CONN_RETRY_INTERVAL_MS      (2000)


/**************** MQTT CLIENT CERTIFICATE CONFIGURATION MACROS ****************/

/* Configure the below credentials in case of a secure MQTT connection. */
/* PEM-encoded client certificate */
#define CLIENT_CERTIFICATE      \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDWjCCAkKgAwIBAgIVALwZV0Im4jdLWx0Oc/cvFc64L6edMA0GCSqGSIb3DQEBCwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29tIEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMjExMDUxMzA5MjdaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNhdGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC9nlYWfbuu7Z7TWXfX0UHQX7RorrlTXA7xpk5TIWt/aPQInrHixdIt6QrPDixf+cLePIbFaSolGR31c48toSFSYYVjp+tG9nbdibdYDXhmYhKb6AHQQiY6iWmF3FQEz314CTvqPAsiqQ552nbDlR3qNUt7X9NtFYWPELS0Pczw7BXu0eg93sebBtLIXLzzVEUCeDrUD8oVZNFhoGlJWGYVWuTi8TsLv4ub2YZThRclFOki4h5sUZ+dSubIywIHFypNgD0BSRo1ODT7NlJuuS38Q/9Oxr43zfTpBWsFKub9W8buL1KtmerF5bJKj4+ndo+/nPDF39PLYF3ByBQ5wi8VAgMBAAGjYDBeMB8GA1UdIwQYMBaAFOikkscPQcq/AFrmkJnlkPKesc4rMB0GA1UdDgQWBBQqeaiAXdtPNNtNb7o+wumC+B+S2TAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAheY+VC13nyBH74LeA7R3xqSOvoGBT/knBoTR+WYGVrreLoJnWdbPAMbrZlbga8z7Afzak+rr7YvZR6JfPxvPVQXb5r5iVWHJ/1PbpG0NPpcS6MMU6FEzg50sJ+A7wI+mYybBSAKzIr+gPMkLtgLx/LYNvf2fbZC9HK7n18kDGQ5f7tITQ0pXVk/JXAyItJg1vuYQ0NwAmMY/aF13UJObUUQ8WNJYUQlca/Kj73T4vDhkWBolCiTNR2tmmdO/aRic8AtnZ2FApG5Hvg6q0slJ4lSZHTR0TyK6h5wgc5eu/rGIgPRrW2ke+0J3xngoqWmRW5m9p4M3Q5O+Xb44X5rQGg==\n" \
"-----END CERTIFICATE-----"

/* PEM-encoded client private key */
#define CLIENT_PRIVATE_KEY          \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"MIIEogIBAAKCAQEAvZ5WFn27ru2e01l319FB0F+0aK65U1wO8aZOUyFrf2j0CJ6x4sXSLekKzw4sX/nC3jyGxWkqJRkd9XOPLaEhUmGFY6frRvZ23Ym3WA14ZmISm+gB0EImOolphdxUBM99eAk76jwLIqkOedp2w5Ud6jVLe1/TbRWFjxC0tD3M8OwV7tHoPd7HmwbSyFy881RFAng61A/KFWTRYaBpSVhmFVrk4vE7C7+Lm9mGU4UXJRTpIuIebFGfnUrmyMsCBxcqTYA9AUkaNTg0+zZSbrkt/EP/Tsa+N8306QVrBSrm/VvG7i9SrZnqxeWySo+Pp3aPv5zwxd/Ty2BdwcgUOcIvFQIDAQABAoIBAANZtt+y3QwcOsA1Rn7Tvbv21PM8kx279K+kZqHlZ0bbDeTRGQeOw0X4Zi5+a55OhXjzzNXUI+B/7x2VKyR9Ql94RakbIHcih7smYcz2f/gfJ4EFunJ5mL9UCj9JQ1rKZ8clMp/S68dzAUR57btK+TpYMrs9WDkHNlLu0qKUrPhcy7zJZ5TCc/WTEcLhzekiWDxEfZzG5wq4z+88jJjcewHuwyHf3x6M8X/7VyAhbAsJaYZtudTnvI/RopRrVyx+HY7IFQ664XlwnU9a8Lge27+yEhK5wQJscqGVcQaAEb59l52S/RaP22MKS5x/nB3GZ8fBLyrp0xKXAUd9er3oRUkCgYEA8X2Kdtzx1ahrN92qD4oK4gje+F2vrROmf9ZEd58RDc3PYKY6QlTtXD/SNdb5r4okHZcuC84ta/8ZGFZEgnBf8n9BwzovZo8iP7NdswapAE4ULo7iXKD6stmi1JeUajZ7gH88ahGsQYL9WTUjFjeCj39e6S4RzfZXAQq799tb3ScCgYEAyQLu7ukZABcUA7cQPHUrBKnaR+4U/UFxrtNSQPBXSntTkj60GVbcyQUu3MMqiYx4aIqK5WE4qHENdnL8MrFmvLEkbMasAWUSQVXwe1vGz9LsqTkTv7nf2NLLrsI8rbsVwDTlDkpdiMljj7vXVjO0339BXOec8rp9rKIZUuNCr2MCgYAUvtIsT+K+lg9P50z6tMMmk9iDwZib57o/9SpAlHukke+kv+L1W9JgQGNQmL0uZVGg8SHVhcrFIk8HljGgewLjFCeUG+WCi/1HN6NvA71090Aol8G+b13aC3Q/ix4G2dNWQJfyDL6diiE1jqkK+Y3PwgNnSLvi06y5vDBVpJSJtQKBgAz+2I2vmkMsOsoGstEFzjMt/AO8e7Tn3z6rQN0b7LjPAlcpIKGmwP1qDV6Oa5ia8Uno8xPjVjNlo7YttupcF8VJOo6hxYsNisGYmcSP6WmUPGKwYvt5O+SbtDlnK18cAkr74HctDaEDTCGFxmU3UJFGe+ZSvw3eSrO3gyWdtbj7AoGAJjpobqhgGCq+i2Q2Ke3Anwz2BktQkuE4o4wiwEsD1SoIZN65n9BEg+EhTq6/sRJHXsEa7//Cg5oZl9qBFac5TMsUyiJNe+rR8iUgW6eZylMQ+/GI2EaxJMr6WaxMxPGmUYF6kVnCPYXdBksULpqT6yvpQYXywTntcxo53DWs7RA=\n" \
"-----END RSA PRIVATE KEY-----"

/* PEM-encoded Root CA certificate */
#define ROOT_CA_CERTIFICATE     \
"-----BEGIN CERTIFICATE-----\n" \
"MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsFADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTELMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJvb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXjca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qwIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQmjgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMCAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUAA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDIU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUsN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vvo/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpyrqXRfboQnoZsG4q5WTP468SQvvG5\n" \
"-----END CERTIFICATE-----"


/******************************************************************************
* Global Variables
*******************************************************************************/
extern cy_mqtt_broker_info_t broker_info;
extern cy_awsport_ssl_credentials_t  *security_info;
extern cy_mqtt_connect_info_t connection_info;


#endif /* MQTT_CLIENT_CONFIG_H_ */
