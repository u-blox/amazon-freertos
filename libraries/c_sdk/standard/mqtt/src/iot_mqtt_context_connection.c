/*
 * FreeRTOS MQTT V2.1.1
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */

/**
 * @file iot_mqtt_context_connection.c
 * @brief Implements data structure for storing the mapping of the MQTT Context and
 * MQTT Connection.
 */

/* The config header is always included first. */
#include "iot_config.h"

/* Standard includes. */
#include <string.h>

/* Error handling include. */
#include "private/iot_error.h"

/* MQTT internal includes. */
#include "private/iot_mqtt_internal.h"

/* Platform layer includes. */
#include "platform/iot_threads.h"
/*-----------------------------------------------------------*/

extern _connContext_t connToContext[ MAX_NO_OF_MQTT_CONNECTIONS ];

/*-----------------------------------------------------------*/


IotMqttError_t _IotMqtt_setContext( IotMqttConnection_t pNewMqttConnection,
                                    MQTTContext_t context )
{
    IotMqttError_t status = IOT_MQTT_NO_MEMORY;

    /* Assigning the newly created MQTT Connection to a MQTT Context. */
    for( size_t i = 0; i < MAX_NO_OF_MQTT_CONNECTIONS; i++ )
    {
        if( connToContext[ i ].mqttConnection != NULL )
        {
            continue;
        }
        else
        {
            connToContext[ i ].mqttConnection = pNewMqttConnection;
            connToContext[ i ].context = context;
            status = IOT_MQTT_SUCCESS;

            break;
        }
    }

    return status;
}

/*-----------------------------------------------------------*/

int8_t _IotMqtt_getContextFromConnection( IotMqttConnection_t mqttConnection )
{
    int8_t contextIndex = -1;

    /* Getting the index of context from the mapping Data Structure for the given MQTT Connection. */
    for( int8_t i = 0; i < MAX_NO_OF_MQTT_CONNECTIONS; i++ )
    {
        if( connToContext[ i ].mqttConnection == mqttConnection )
        {
            contextIndex = i;
            break;
        }
    }

    return contextIndex;
}

/*-----------------------------------------------------------*/

void _IotMqtt_removeContext( IotMqttConnection_t mqttConnection )
{
    /* Finding the index corresponding to given the MQTT Connection. */
    for( size_t i = 0; i < MAX_NO_OF_MQTT_CONNECTIONS; i++ )
    {
        if( connToContext[ i ].mqttConnection == mqttConnection )
        {
            connToContext[ i ].mqttConnection = NULL;
            break;
        }
    }
}

/*-----------------------------------------------------------*/
