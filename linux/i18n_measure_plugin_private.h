#include <flutter_linux/flutter_linux.h>

#include "include/i18n_measure/i18n_measure_plugin.h"

// This file exposes some plugin internals for unit testing. See
// https://github.com/flutter/flutter/issues/88724 for current limitations
// in the unit-testable API.

// Handles the getMeasurementSystem method call.
FlMethodResponse *get_measurement_system();
