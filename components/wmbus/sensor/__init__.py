import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import (
    CONF_ID,
    CONF_TYPE,
    CONF_KEY,
    CONF_NAME,
    CONF_UNIT_OF_MEASUREMENT,
)

AUTO_LOAD = ["wmbus"]

CONF_METER_ID = "meter_id"
CONF_LISTENER_ID = "listener_id"
CONF_WMBUS_ID = "wmbus_id"
CONF_FIELD = "field"
CONF_SENSORS = 'sensors'

from .. import (
    WMBusComponent,
    wmbus_ns,
    register_driver,
)
from ..common import my_key

CODEOWNERS = ["@SzczepanLeon"]

WMBusListener = wmbus_ns.class_('WMBusListener')


def validate_sensor(config):
    if CONF_UNIT_OF_MEASUREMENT not in config:
        raise cv.Invalid(
            f"unit_of_measurement not defined for sensor '{config[CONF_NAME]}'"
        )
    return config


SENSOR_SCHEMA = cv.All(
    sensor.sensor_schema(
        #
    ).extend(
        {
            cv.Optional(CONF_FIELD, default=""): cv.string_strict,
        }
    ),
    validate_sensor,
)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_LISTENER_ID): cv.declare_id(WMBusListener),
        cv.GenerateID(CONF_WMBUS_ID): cv.use_id(WMBusComponent),
        cv.Optional(CONF_METER_ID, default=0): cv.hex_int,
        cv.Optional(CONF_TYPE, default=""): cv.string_strict,
        cv.Optional(CONF_KEY, default=""): my_key,
        cv.Optional(CONF_SENSORS): cv.ensure_list(SENSOR_SCHEMA),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    if config[CONF_TYPE]:
        register_driver(config[CONF_TYPE])
    if config[CONF_METER_ID]:
        wmbus = await cg.get_variable(config[CONF_WMBUS_ID])
        cg.add(wmbus.register_wmbus_listener(config[CONF_METER_ID], config[CONF_TYPE].lower(), config[CONF_KEY]))
        for s in config.get(CONF_SENSORS, []):
            if (s[CONF_FIELD]):
                field = s[CONF_FIELD].lower()
            else:
                field = s[CONF_NAME].lower()
            unit = s[CONF_UNIT_OF_MEASUREMENT]
            sens = await sensor.new_sensor(s)
            cg.add(wmbus.add_sensor(config[CONF_METER_ID], field, unit, sens))
