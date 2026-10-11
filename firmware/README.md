### The Firmware section of the Power Profiling Repo.
Here lives all the data logger code of my antics. (Or at least there's supposed to be... Nothing for now.)

### TODO:
- [x] add basic serial data logging. Anything in any format for now.
- [ ] add WIFI connection
- [ ] add onboard LED blink code for error state
- [ ] add ring buffer for network dropout resilience (calculate size based on available memory)
- [ ] add compile time configured metadata to the data packets (sensor type, sensor settings, firmware hash, etc.)
- [ ] add Prometheus compatible scraping endpoint (OpenTelemetry format, json or protobuf)
- [ ] add manual triggered datapoint burst to send to Prometheus
- [ ] add automatic triggered datapoint burst to send to Prometheus
