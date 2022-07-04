#ifndef ENERGY_GENERATED_H_
#define ENERGY_GENERATED_H_

#define SAMPLING_INTERVAL         5
#define SAMPLE_LOWER_BOUND        1500 //kw
#define SAMPLE_UPPER_BOUND        1500

PROCESS_NAME(energy_sensor_process);

extern process_event_t ENERGY_SAMPLE_EVENT;
extern process_event_t ENERGY_EVENT_SUB;

#endif 