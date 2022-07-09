#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "coap-engine.h"
#include "./res-battery-voltage.h"
#include "../../sensors/utils.h"

static void res_get_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset);
static void res_event_handler(void);

/*
 * A handler function named [resource name]_handler must be implemented for each RESOURCE.
 * A buffer for the response payload is provided through the buffer pointer. Simple resources can ignore
 * preferred_size and offset, but must respect the REST_MAX_CHUNK_SIZE limit for the buffer.
 * If a smaller block size is requested for CoAP, the REST framework automatically splits the data.
 */
static int battery_voltage_sample;
static int node_id;

EVENT_RESOURCE(res_battery_voltage,
        "title =\"Battery voltage\";obs",
        res_get_handler,
        NULL,
        NULL,
        NULL,
		res_event_handler);

static void
res_get_handler(coap_message_t *request, coap_message_t *response, uint8_t *buffer, uint16_t preferred_size, int32_t *offset)
{
  char json_response[512];
  int length;

  json_sample(json_response, 512, "battery_voltage", battery_voltage_sample, "L", node_id);
  length = strlen(json_response);
  memcpy(buffer, json_response, length);

  coap_set_header_content_format(response, APPLICATION_JSON);
  coap_set_payload(response, buffer, length);
}

static void
res_event_handler(void)
{
    // Notify all the observers
    coap_notify_observers(&res_battery_voltage);
}

void
res_battery_voltage_activate(void)
{
  battery_voltage_sample = -1;
  coap_activate_resource(&res_battery_voltage, "battery_voltage");
}

void
res_battery_voltage_update
(int sample, int id)
{
  node_id = id;
  battery_voltage_sample = sample;
  res_battery_voltage.trigger();
}