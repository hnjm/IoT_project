#include "./utils.h"

int
sensor_rand_int(int min, int max)
{
  return ((rand() %(max - min + 1)) + min);
}

void json_sample(char *message_buffer, size_t size, char* topic, int sample, int id)
{
  memset(message_buffer, 0, size);

  snprintf(message_buffer,
          size,
          "{\"n\":\"%s\",\"v\":\"%d\",\"u\":\"%s\",\"id\":\"%d\"}",
          topic,
          sample,
          TEMPERATURE_UNIT, 
          id);
}